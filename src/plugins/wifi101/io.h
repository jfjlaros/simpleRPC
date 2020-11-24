#ifndef SIMPLE_RPC_WIFI101_IO_H_
#define SIMPLE_RPC_WIFI101_IO_H_

#include <WiFi101.h>

// Connect using WiFi101
class WiFi101IO {
  public:
    WiFi101IO(void) {}
    void begin(WiFiClient& wc);
    size_t available(void);
    size_t read(uint8_t*, size_t);
    size_t write(uint8_t*, size_t);
  private:
    WiFiClient* _wc;
};

bool begin(const char* ssid, const char* password);

#endif
