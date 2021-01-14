
#include <Curve25519.h>

#define NODE_ID     22
#define NODE_GROUP  0
#define NODE_NAME  "Test Sensor"

void setup() {
  Serial.begin(9600);

  delay(4000);
  Serial.println("First, we need to create some entropy.");
  Serial.println("Enter some text then press ENTER:");

  long seed = 0;
  char c = 0;
  while (c != '\n') {
    if (Serial.available()) {
      c = Serial.read();
      seed <<= 3;
      seed += c;
    }
  }

  seed ^= micros();

  Serial.print("Random seed = ");
  Serial.println(seed);

  randomSeed(seed);

  uint8_t prv_key[32];
  uint8_t pub_key[32];
  
  // generate random private key 
  for (int i = 0; i < 32; i++) {
    prv_key[i] = (uint8_t) random(0, 0xFF);
  }
  
  // Fix up the private key by applying the standard masks
  prv_key[0] &= 0xF8;
  prv_key[31] = (prv_key[31] & 0x7F) | 0x40;

  // compute public key
  Curve25519::eval(pub_key, prv_key, 0);

  int i;

  Serial.println("C code: -----------");

  Serial.print("#define NODE_ID     "); Serial.println(NODE_ID);
  Serial.print("#define NODE_GROUP  "); Serial.println(NODE_GROUP);
  Serial.print("#define NODE_NAME \""); Serial.print(NODE_NAME); Serial.println('"');

  Serial.print("uint8_t prv_key[] = {");
  for (i = 0; i < 32; i++) {
    if (i > 0) {
      Serial.print(',');
    }
    Serial.print("0x");
    Serial.print(hexChar(prv_key[i] >> 4));
    Serial.print(hexChar(prv_key[i] & 0x0F));
  }
  Serial.println("};");

  Serial.print("uint8_t pub_key[] = {");
  for (i = 0; i < 32; i++) {
    if (i > 0) {
      Serial.print(',');
    }
    Serial.print("0x");
    Serial.print(hexChar(pub_key[i] >> 4));
    Serial.print(hexChar(pub_key[i] & 0x0F));
  }
  Serial.println("};");

  Serial.println("QR code for others to import: -------------");
  Serial.print("https://chart.googleapis.com/chart?chs=250x250&cht=qr&chl=");
  Serial.print((int) (int8_t) NODE_ID);
  Serial.print(',');
  const char *sp = NODE_NAME;
  while (*sp) {
    if (*sp == ' ' || *sp == ',' || *sp == '&' || *sp == '=') {  // vorboten chars
      Serial.print('+');
    } else {
      Serial.print(*sp);
    }
    sp++;
  }
  Serial.print(',');
  for (i = 0; i < 32; i++) {
    Serial.print(hexChar(pub_key[i] >> 4));
    Serial.print(hexChar(pub_key[i] & 0x0F));
  }
  Serial.println();

}

char hexChar(uint8_t v) {
  if (v >= 10) return 'A' + (v - 10);
  return '0' + v;
}

void loop() {
  delay(1000);
}
