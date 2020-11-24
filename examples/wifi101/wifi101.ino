#include <simpleRPC.h>
#include <SPI.h>
#include <WiFi101.h>
#include "arduino_secrets.h"

char ssid[] = SECRET_SSID;    // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
WiFiClient wc;
WiFi101IO io;

byte ping(byte data) {
  return data;
}

void setup(void) {
  Serial.begin(9600);
  WiFi.setPins(8, 7, 4, 2);
  while (!connectWiFi()) {
    delay(10);
  }
  printWiFiStatus();
  wc.connect(IPAddress("192.168.1.218"), 11511);
  io.begin(wc);
}

void connectWiFi() {
  static int status = WL_IDLE_STATUS;
  if (WiFi.status() == WL_NO_SHIELD) {
    return false;
  }
  if (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, password);
  }
  return status == WL_CONNECTED;
}

void printWiFiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void loop(void) {
  interface(
    io,
    ping, F("ping: Echo a value. @data: Value. @return: Value of data."));
}
