#include <Ethernet.h>

#include <simpleRPC.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 50);
EthernetServer server(10000);


void connectEthernet(byte* mac, const IPAddress& ip) {
  Ethernet.begin(mac, ip);
  while (Ethernet.hardwareStatus() == EthernetNoHardware) {
    // Do nothing without Ethernet hardware.
    delay(1);
  }
  while (Ethernet.linkStatus() == LinkOFF) {
    // Wait for ethernet connection.
    delay(1);
  }
}


byte ping(byte data) {
  return data;
}


void setup(void) {
  connectEthernet(mac, ip);
  server.begin();
}

void loop(void) {
  EthernetClient client = server.available();
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
