#ifndef SIMPLE_RPC_WIFI_IO_H_
#define SIMPLE_RPC_WIFI_IO_H_

#include <Arduino.h>
#include <WiFi.h>

class WiFiIO {
  public:
    WiFiIO(void) {}
    void begin(WiFiServer&);
    size_t available(void),
           read(byte*, size_t),
           write(byte*, size_t);
  private:
    WiFiServer *_ws;
    WiFiClient *_wc;
};

#endif
