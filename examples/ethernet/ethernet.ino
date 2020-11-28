#include <simpleRPC.h>
#include <Ethernet.h>

EthernetServer server(10000);

byte ping(byte data) {
  return data;
}

void setup(void) {
  Serial.begin(9600);
  WiFi.setPins(8,7,4,2);
  connectWifi(ssid, pass);
  server.begin();
  printWifiStatus(Serial);
}

void loop(void) {
  EthernetClient client = server.available();
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
