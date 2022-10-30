#include <simpleRPC.h>

uint8_t const txPin {9};
unsigned long const txDelay {1000}; // Increase for slow connections.

HalfDuplexStream RS485Serial(Serial, txPin, txDelay);


byte ping(byte data) {
  return data;
}


void setup() {
  Serial.begin(9600);
  RS485Serial.begin();
}

void loop() {
  interface(
    RS485Serial,
    ping, F("ping: Echo a value. @data: Value. @return: Value of data."));
}
