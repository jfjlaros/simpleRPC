#include <WiFi101.h>
#include <simpleRPC.h>

#include "arduino_secrets.h"

IPAddress ip(192, 168, 1, 50);
WiFiServer server(10000);


void connectWifi(char const* ssid, char const* password, const IPAddress& ip) {
  while (WiFi.status() == WL_NO_SHIELD) {
    // Do nothing without WiFi hardware.
    delay(1);
  }
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    // Wait for WiFi connection.
    delay(1);
  }
  WiFi.config(ip);
}


byte ping(byte data) {
  return data;
}


void setup(void) {
  WiFi.setPins(8, 7, 4, 2);
  connectWifi(SECRET_SSID, SECRET_PASS, ip);
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
    // Wait for data transmission to complete.
    client.flush();
    // Give the client time to receive data.
    delay(1);
    client.stop();
  }
}
