#pragma once

#include <Arduino.h>

struct MeshMessage {
  long timestampOrCrc;
  uint8_t from;
  char text[127];
};

#define FROM_ACK   0xFF

#define MAX_RETRIES  3

struct MeshRetrySender {
  uint8_t to;
  char _m[127];
  long _t;
  int _s;
  long _p[MAX_RETRIES];
};

class RippleMesh {
  public:
    RippleMesh();
    bool begin(Stream* serial, uint8_t id, uint8_t grp, const char* name, const uint8_t prv_key[], const uint8_t pub_key[], int freq, int sf);
    bool addContact(uint8_t id, const char* name, const char *pub_key_hex);
    MeshRetrySender createSender(uint8_t to, long timestamp, const char* text);
    bool trySend(MeshRetrySender& sender);
    int calcExpoBackoffDelay(const MeshRetrySender& sender);
    bool receive(MeshMessage& msg);
    bool isPendingAck(long crc, const MeshRetrySender& sender);

  private:
    Stream* _serial;
    char buf[256];
    int buf_len;
    const uint8_t* _prv;
    const uint8_t* _pub;

    void readLine(char *dest, int maxlen);
};
