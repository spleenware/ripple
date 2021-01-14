#pragma once

#include <Arduino.h>

struct MeshMessage {
  uint8_t from;
  long timestampOrCrc;
  char text[126];
};

#define FROM_ACK   0xFF

class RippleMesh {
  public:
    RippleMesh();
    bool begin(Stream* serial, uint8_t id, uint8_t grp, const char* name, const uint8_t prv_key[], const uint8_t pub_key[], int freq, int sf);
    bool addContact(uint8_t id, const char* name, const char *pub_key_hex);
    long sendMessage(uint8_t to, long timestamp, const char* text);
    bool receive(MeshMessage& msg);

  private:
    Stream* _serial;
    char buf[256];
    int buf_len;
    const uint8_t* _prv;
    const uint8_t* _pub;

    void readLine(char *dest, int maxlen);
};
