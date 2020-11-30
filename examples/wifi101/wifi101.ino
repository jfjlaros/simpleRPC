#include <simpleRPC.h>
#include <WiFi101.h>
#include "arduino_secrets.h"

char ssid[] = SECRET_SSID;      // your network SSID (name)
char pass[] = SECRET_PASS;      // your network password (use for WPA, or use as key for WEP)
IPAddress ip(192, 168, 1, 50);
WiFiServer server(10000);

byte ping(byte data) {
  return data;
}

void connectWifi(const char* ssid, const char* password, const IPAddress& ip) {
  while (WiFi.status() == WL_NO_SHIELD) {
    delay(1);  // do nothing, no point running without WiFi hardware
  }
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    delay(1);  // wait for wifi connection
  }
  WiFi.config(ip);
}

void setup(void) {
  WiFi.setPins(8,7,4,2);
  connectWifi(ssid, pass, ip);
  server.begin();
}

void loop(void) {
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      interface(
        client,
        ping, F("ping: Echo a value. @data: Value. @return: Value of data."));
    }
    client.flush(); // wait for data transmission to complete
    delay(1);       // give the client time to receive data
    client.stop();
  }
}
