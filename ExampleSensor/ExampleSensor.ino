#include "RippleMesh.h"

#define SENSOR_ANALOG_PIN  10

#define LORA_FREQUENCY     915
#define SPREADING_FACTOR    10

#define HOME_ID   1

// -------------------- run the GenerateKeypair.ino sketch to create code below -------------------
#define NODE_ID     22
#define NODE_GROUP  0
#define NODE_NAME "Test Sensor"

uint8_t prv_key[] = {0xD8,0x22,0xAB,0x09,0x20,0xF2,0x8F,0xF3,0xC9,0xAC,0x3B,0x62,0x1C,0x21,0x30,0x6B,0x56,0xB1,0xC7,0xBF,0xF0,0x02,0x6D,0x34,0x41,0xF3,0x10,0xE2,0x74,0xCB,0x76,0x5B};
uint8_t pub_key[] = {0xB5,0x0B,0xCE,0x03,0x7A,0x92,0xE5,0xB2,0x11,0x79,0xC4,0xFA,0xA3,0xCE,0x09,0xF1,0xAF,0x96,0x2B,0x87,0x60,0x9E,0x9F,0x97,0xFA,0xC6,0x6A,0xCF,0x81,0xC3,0x5B,0x05};

//QR code for others to import: -------------
//https://chart.googleapis.com/chart?chs=250x250&cht=qr&chl=22,Test+Sensor,B50BCE037A92E5B21179C4FAA3CE09F1AF962B87609E9F97FAC66ACF81C35B05

// -------------------- --------------------- -------------------

RippleMesh mesh;
bool flash = false;
unsigned long last_flash = 0;
MeshRetrySender sender;
unsigned long last_time = 0;
unsigned long next_attempt = 0;

#define TIMER_INTERVAL 60000  // 60 seconds

void setup() {
  Serial1.begin(9600);

  delay(2000);  // Give the Ripple device time to startup

 // waitForEnter();  // TEMP!!

  if (!mesh.begin(&Serial1, NODE_ID, NODE_GROUP, NODE_NAME, prv_key, pub_key, LORA_FREQUENCY, SPREADING_FACTOR)) {
    Serial.println("Mesh.begin() failed");
    haltFlash(2);
  }
    // TODO: send clock info
  if (!mesh.addContact(HOME_ID, "Home", "6156797E8D028622EF225C934BFA1033EF934E8EA6FBDE41C970FDC565D11327")) {  // enter the public key of the other node here
    Serial.println("Mesh.addContact() failed");
    haltFlash(3);
  }

  sender.to = 0;  // not active
}

void loop() {
  MeshMessage msg;
  if (mesh.receive(msg)) {
    if (msg.from == FROM_ACK) {
      // process incoming Ack
      if (sender.to != 0 && mesh.isPendingAck(msg.timestampOrCrc, sender)) {
        // Yay, we got an ack that our send was received
        sender.to = 0;  // stop retries
      }
    } else {
      if (strcmp(msg.text, "read") == 0) {  // an example 'command'
        // read the sensor value
        int sensor_value = analogRead(SENSOR_ANALOG_PIN);
        char text[64];
        sprintf(text, "Sensor: %d", sensor_value);

        MeshRetrySender send_once = mesh.createSender(msg.from, millis() / 1000, text);
        mesh.trySend(send_once);
      }
    }
  }

  if ((unsigned long) (millis() - last_time) > TIMER_INTERVAL) {
    last_time = millis();

    int sensor_value = analogRead(SENSOR_ANALOG_PIN);
    char text[64];
    sprintf(text, "Sensor reading now %d", sensor_value);

    sender = mesh.createSender(HOME_ID, millis() / 1000, text);
    next_attempt = 0;
  }

  if (sender.to != 0 && millis() > next_attempt) {
    if (mesh.trySend(sender)) {
      // success, we now wait for an Ack
      next_attempt = millis() + mesh.calcExpoBackoffDelay(sender);  // schedule our next send attempt
    } else {
      // max retries reached, send failed
      sender.to = 0;    // cancel send
    }
  }

  if ((unsigned long) (millis() - last_flash) > 500) {
    last_flash = millis();

    flash = !flash;   // flash the built LED to give us an idea if everything is still working
    digitalWrite(LED_BUILTIN, flash ? LOW : HIGH);
  }
}

void waitForEnter() {
  while (1) {
    if (Serial.available()) {
      char c = Serial.read();
      if (c == '\n') return;
    }
  }
}

void haltFlash(int count) {
  while (1) {
    for (int i = 0; i < count; i++) {
      digitalWrite(LED_BUILTIN, LOW);
      delay(300);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(300);
    }
    delay(1000);
  }
}
