#include "RippleMesh.h"
#include <Curve25519.h>

static uint8_t hexVal(char c) {
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'A' && c <= 'F') return c - 'A' + 10;
  return 0;
}

static void hexToBytes(uint8_t* dest, const char* src, int charCount) {
  while (charCount >= 2) {
    *dest++ = (hexVal(*src++) << 4) | hexVal(*src++);
    charCount -= 2;
  }
}

static char hexChar(uint8_t v) {
  if (v >= 10) return 'A' + (v - 10);
  return '0' + v;
}

RippleMesh::RippleMesh() {
  _serial = NULL;
}

bool RippleMesh::begin(Stream* serial, uint8_t id, uint8_t grp, const char* name, const uint8_t prv_key[], const uint8_t pub_key[], int freq, int sf) {
  _serial = serial;
  _prv = prv_key;
  _pub = pub_key;

  _serial->print('i');
  _serial->print((int) (int8_t) id);
  _serial->print(',');
  _serial->print((int) (int8_t) grp);
  _serial->print(',');
  _serial->print(freq);
  _serial->print(',');
  _serial->print(sf);
  _serial->print('\n');

  buf_len = 0;

  char reply[32];
  readLine(reply, sizeof(reply));
  if (memcmp(reply, "I:", 2) == 0) {
    return true;  // expected reply prefix
  }

  return false;  // something wrong
}

bool RippleMesh::addContact(uint8_t id, const char* name, const char *pub_key_hex) {
  uint8_t result[32];
  uint8_t pub_key[32];

  if (strlen(pub_key_hex) != 64) return false;  // should be 32 bytes (64 hex chars)

  hexToBytes(pub_key, pub_key_hex, 64);
  Curve25519::eval(result, _prv, pub_key);

  _serial->print('f');
  _serial->print((int) (int8_t) id);
  _serial->print(',');
  for (int i = 0; i < 32; i++) {
    _serial->print(hexChar(result[i] >> 4));
    _serial->print(hexChar(result[i] & 0x0F));
  }
  _serial->print('\n');

  char reply[32];
  readLine(reply, sizeof(reply));
  if (memcmp(reply, "F:", 2) == 0 && atoi(&reply[2]) != 0) {
    return true;  // succes
  }

  return false;  // something went wrong
}

MeshRetrySender RippleMesh::createSender(uint8_t to, long timestamp, const char* text) {
  MeshRetrySender sender;

  sender.to = to;
  strncpy(sender._m, text, 126);
  sender._m[126] = 0;
  sender._t = timestamp;
  sender._s = 0;
  memset(sender._p, 0, sizeof(sender._p));

  return sender;
}

bool RippleMesh::trySend(MeshRetrySender& sender) {
  if (sender._s >= MAX_RETRIES) return false;  // max retries reached

  sender._s++;
  _serial->print('t');
  _serial->print((int) (int8_t) sender.to);
  _serial->print(',');
  _serial->print(sender._t);
  _serial->print(',');
  _serial->print((int)sender._s);
  _serial->print(',');
  _serial->print(sender._m);
  _serial->print('\n');

  char reply[32];
  readLine(reply, sizeof(reply));
  if (memcmp(reply, "O:", 2) == 0) {
    long crc = atol(&reply[2]);
    sender._p[sender._s - 1] = crc;
    return true;  // success
  }

  return false;  // something went wrong
}

int RippleMesh::calcExpoBackoffDelay(const MeshRetrySender& sender) {
  return 1000 * (sender._s * 3 / 2);
}

bool RippleMesh::isPendingAck(long crc, const MeshRetrySender& sender) {
  for (int i = 0; i < sender._s; i++) {
    if (sender._p[i] == crc) return true;
  }
  return false;
}

bool RippleMesh::receive(MeshMessage& msg) {
  bool complete = false;
  while (_serial->available()) {
    char c = _serial->read();
    if (c == '\n') {
      complete = true;
      break;
    }
    if (buf_len < sizeof(buf)-1) {
      buf[buf_len++] = c;
    }
  }

  bool incoming = false;

  if (complete) {
    buf[buf_len] = 0;  // set null terminator

    if (buf[0] == 'A' && buf[1] == ':') {
      // we got an ACK
      msg.from = FROM_ACK;
      msg.timestampOrCrc = atol(&buf[2]);
      incoming = true;

      _serial->print("d\n");    // send 'DELETE' command
    } else if (buf[0] == 'M' && buf[1] == ':') {
      // we got a message
      int i = 2;
      msg.from = (uint8_t) atoi(&buf[i]);

      while (i < buf_len && buf[i] != ',') i++;
      i++;  // skip comma

      msg.timestampOrCrc = atol(&buf[i]);

      while (i < buf_len && buf[i] != ',') i++;
      i++;  // skip comma

      if (i < buf_len) {
        strcpy(msg.text, &buf[i]);
        incoming = true;
      }

      _serial->print("d\n");    // send 'DELETE' command
    } else if (buf[0] == 'T' && buf[1] == ':') {
      // we got a 'tickle' 
      _serial->print("p\n"); // send 'poll' command
    }
    buf_len = 0;  // reset buf
  }
  return incoming;
}

void RippleMesh::readLine(char *dest, int maxlen) {
  char c = 0;
  int len = 0;
  while (c != '\n' && len < maxlen-1) {
    if (_serial->available()) {
      c = _serial->read();
      dest[len++] = c;
    } else {
      delay(20);
    }
  }
  dest[len] = 0;  // set null terminator
}
