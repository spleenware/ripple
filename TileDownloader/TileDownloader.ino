
#include <Arduino.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>

//--------------- Enter your WiFi credentials ------------------------
#define WIFI_SSID      "ENTER YOUR SSSID"
#define WIFI_PASSWORD  "ENTER YOUR PASSWORD"
// ------------------------------------------------------------------------------

// -------------- uncomment one of these, depending on target board -------------
//#include "lilygo_t4.h"
#include "lilygo_tdeck.h"
// ------------------------------------------------------------------------------

// -------------- set the bounding box and zoom levels to download -------------
//   All 'world level' tiles are downloaded up to (but not including) START_ZOOM.
//   Tiles from START_ZOOM to END_ZOOM (inclusive) are filtered to only those
//    within the LAT/LON bounds specified below:
#define START_ZOOM  6

// #define MIN_LAT   -39.52 // Victoria
// #define MAX_LAT   -33.82
// #define MIN_LON   140.62
// #define MAX_LON   150.6
// #define END_ZOOM    8

#define MIN_LAT   35.88 // Europe
#define MAX_LAT   70.99
#define MIN_LON   -11.7
#define MAX_LON   43.91
#define END_ZOOM    7

// #define MIN_LAT    49.09 // UK
// #define MAX_LAT    61.13
// #define MIN_LON   -11.65
// #define MAX_LON     4.75
// #define END_ZOOM    8

// #define MIN_LAT   -38.62 // Melbourne
// #define MAX_LAT   -37.47
// #define MIN_LON   144.18
// #define MAX_LON   145.73
// #define END_ZOOM    14

// #define MIN_LAT   -46.13 // Australia
// #define MAX_LAT   -9.29
// #define MIN_LON   112.22
// #define MAX_LON   157.33
// #define END_ZOOM    7

// ------------------------------------------------------------------------------


#define FILESYSTEM SD
// You only need to format the filesystem once
#define FORMAT_FILESYSTEM false
#define DBG_OUTPUT_PORT Serial

#if FILESYSTEM == SD
#include <SD.h>
#endif
#if FILESYSTEM == SPIFFS
#include <SPIFFS.h>
#endif


uint32_t lon2tilex(double lon, uint8_t zoom) {
  int zs = 1 << zoom;
  double t = (lon + 180.0) / 360.0 * zs;
  return (uint32_t)floor(t);
}
uint32_t lat2tiley(double lat, uint8_t zoom) {
  int zs = 1 << zoom;
  double lr = lat * M_PI / 180.0;  // to radians
  double t = (1.0 - log(tan(lr) + 1.0 / cos(lr)) / M_PI) / 2.0 * zs;
  return (uint32_t)floor(t);
}

void get_tile(int zoom, int x, int y) {
  char filename[128];

  DBG_OUTPUT_PORT.print(zoom);
  DBG_OUTPUT_PORT.print("/");
  DBG_OUTPUT_PORT.print(x);
  DBG_OUTPUT_PORT.print("/");
  DBG_OUTPUT_PORT.print(y);
  DBG_OUTPUT_PORT.print(": ");

  sprintf(filename, "/tiles/%d/%d/%d.png", zoom, x, y);
  if (FILESYSTEM.exists(filename)) {
    DBG_OUTPUT_PORT.println("Skipping");
  } else {
    HTTPClient http;

    DBG_OUTPUT_PORT.print("downloading... ");

    sprintf(filename, "https://a.tile.openstreetmap.org/%d/%d/%d.png", zoom, x, y);
    http.begin(filename);
    int httpResponseCode = http.GET();
    if (httpResponseCode == 200) {
      sprintf(filename, "/tiles/%d/%d/%d.png", zoom, x, y);
      fs::File file = FILESYSTEM.open(filename, "w");
      if (file) {
        DBG_OUTPUT_PORT.print(http.getSize());

        http.writeToStream(&file);
        file.close();
      } else {
        DBG_OUTPUT_PORT.print("FileSystem error");
      }
    } else {
      DBG_OUTPUT_PORT.print("HTTP error: ");
      DBG_OUTPUT_PORT.print(httpResponseCode);
    }
    // Free resources
    http.end();

    DBG_OUTPUT_PORT.println();
  }
}

void setup(void) {
  DBG_OUTPUT_PORT.begin(115200);

  delay(5000);

  DBG_OUTPUT_PORT.print("\n");
  DBG_OUTPUT_PORT.setDebugOutput(true);
  //if (FORMAT_FILESYSTEM) FILESYSTEM.format();

#if LORA_CS >= 0
  pinMode(LORA_CS, OUTPUT);
  digitalWrite(LORA_CS, HIGH);   // LoRa module on same SPI bus as SD card, so de-select
#endif

  SPI.begin(SD_CLK, SD_MISO, SD_MOSI);
  bool success = FILESYSTEM.begin(SD_CS, SPI, 4000000U, "/fs");
  if (!success) {
    DBG_OUTPUT_PORT.println("ERROR: SD interface init fail");
    return;
  }

  sdcard_type_t cardtype = FILESYSTEM.cardType();
  if (cardtype == CARD_UNKNOWN || cardtype == CARD_NONE) {
    DBG_OUTPUT_PORT.println("ERROR: SD card not found");
    return;
  }

  // list top level files/dirs
  {
      File root = FILESYSTEM.open("/");
      File file = root.openNextFile();
      while(file){
          String fileName = file.name();
          size_t fileSize = file.size();
          DBG_OUTPUT_PORT.printf("FS File: %s, size: %d\n", fileName.c_str(), fileSize);
          file = root.openNextFile();
      }
      DBG_OUTPUT_PORT.printf("\n");
  }


  //WIFI INIT
  DBG_OUTPUT_PORT.printf("Connecting to %s\n", WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    DBG_OUTPUT_PORT.print(".");
  }
  DBG_OUTPUT_PORT.println("");
  DBG_OUTPUT_PORT.print("Connected! IP address: ");
  DBG_OUTPUT_PORT.println(WiFi.localIP());

  char filename[128];

  FILESYSTEM.mkdir("/tiles");

  // get all world-level tiles first
  for (int zoom = 1; zoom < START_ZOOM; zoom++) {
    int n = 1 << zoom;

    sprintf(filename, "/tiles/%d", zoom);
    FILESYSTEM.mkdir(filename);  // make sure zoom directory exists

    for (int x = 0; x < n; x++) {

      sprintf(filename, "/tiles/%d/%d", zoom, x);
      FILESYSTEM.mkdir(filename);   // make sure directory exists

      for (int y = 0; y < n; y++) {
        get_tile(zoom, x, y);
      }
    }
  }

  // get detail tiles within bounding box
  for (int zoom = START_ZOOM; zoom <= END_ZOOM; zoom++) {
    sprintf(filename, "/tiles/%d", zoom);
    FILESYSTEM.mkdir(filename);  // make sure zoom directory exists

    uint32_t start_x = lon2tilex(MIN_LON, zoom);
    uint32_t end_x = lon2tilex(MAX_LON, zoom);
    uint32_t start_y = lat2tiley(MAX_LAT, zoom);
    uint32_t end_y = lat2tiley(MIN_LAT, zoom);

    for (uint32_t x = start_x; x <= end_x; x++) {
      sprintf(filename, "/tiles/%d/%d", zoom, x);
      FILESYSTEM.mkdir(filename);   // make sure directory exists

      for (uint32_t y = start_y; y <= end_y; y++) {
        get_tile(zoom, x, y);
      }
    }
  }

  DBG_OUTPUT_PORT.println("---- DONE ----");
}

void loop(void) {
  delay(20);
}
