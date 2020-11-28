#include <simpleRPC.h>
#include <WiFi101.h>
#include "arduino_secrets.h"

char ssid[] = SECRET_SSID;    // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
WiFiServer server(10000);

byte ping(byte data) {
  return data;
}

void connectWifi(const char* ssid, const char* password) {
  static int status = WL_IDLE_STATUS;
  if (WiFi.status() == WL_NO_SHIELD) {
    while(true);
  }
  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, password);
  }
}

void printWifiStatus(Print& print) {
  print.print("SSID: ");
  print.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  print.print("IP Address: ");
  print.println(ip);
  long rssi = WiFi.RSSI();
  print.print("signal strength (RSSI):");
  print.print(rssi);
  print.println(" dBm");
}

void setup(void) {
  Serial.begin(9600);
  WiFi.setPins(8,7,4,2);
  connectWifi(ssid, pass);
  server.begin();
  printWifiStatus(Serial);
}

void loop(void) {
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        interface(
          client,
          ping, F("ping: Echo a value. @data: Value. @return: Value of data."));
      }
    }
    delay(1);       // give the client time to receive data
    client.stop();  // close the connection
  }
}
