#include <simpleRPC.h>

#define TRANSMIT_PIN 9
#define TRANSMIT_DELAY_MICROSECONDS 1000  // Increase for slow connections.

HalfDuplexStream RS485Serial(
  Serial, TRANSMIT_PIN, TRANSMIT_DELAY_MICROSECONDS);


byte ping(byte data) {
  return data;
}


void setup(void) {
  Serial.begin(9600);
  RS485Serial.begin();
}

void loop(void) {
  interface(
    RS485Serial,
    ping, F("ping: Echo a value. @data: Value. @return: Value of data."));
}
