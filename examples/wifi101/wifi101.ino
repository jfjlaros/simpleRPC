#include <simpleRPC.h>
#include <WiFi101.h>
#include "arduino_secrets.h"

char ssid[] = SECRET_SSID;    // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
WiFi101IO io;

byte ping(byte data) {
  return data;
}

void setup(void) {
  Serial.begin(9600);
  WiFi.setPins(8,7,4,2);
  io.begin(ssid, pass);
  io.printStatus(Serial);
}

void loop(void) {
  interface(
    io,
    ping, F("ping: Echo a value. @data: Value. @return: Value of data."));
}
