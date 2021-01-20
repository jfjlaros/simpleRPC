#include <BluetoothSerial.h>

#include <simpleRPC.h>

BluetoothSerial serial;


byte ping(byte data) {
  return data;
}


void setup() {
  serial.begin("ESP32");
}

void loop() {
  interface(
    serial,
    ping, F("ping: Echo a value. @data: Value. @return: Value of data."));
}
