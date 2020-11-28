#include <simpleRPC.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 50);
EthernetServer server(10000);

byte ping(byte data) {
  return data;
}

void connectEthernet(byte* mac, const IPAddress& ip) {
  Ethernet.begin(mac, ip);
  while (Ethernet.hardwareStatus() == EthernetNoHardware) {
    delay(1);  // do nothing, no point running without Ethernet hardware
  }
  while (Ethernet.linkStatus() == LinkOFF) {
    delay(1);  // wait for ethernet connection
  }
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
    client.flush(); // wait for data transmission to complete
    delay(1);       // give the client time to receive data
    client.stop();
  }
}
