#include <simpleRPC.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 151);
EthernetServer server(10000);

byte ping(byte data) {
  return data;
}

void connectEthernet() {
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
}

void printEthernetStatus(Print& print) {
  print.print("IP Address: ");
  print.println(ip);
  if (Ethernet.linkStatus() == LinkOFF) {
    print.println("Ethernet cable is not connected.");
  }
}

void setup(void) {
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  connectEthernet();
  server.begin();
  printEthernetStatus(Serial);
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
