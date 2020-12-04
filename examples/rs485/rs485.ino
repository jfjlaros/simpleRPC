#include <simpleRPC.h>


const int TRANSMIT_PIN = 9;
const unsigned TRANSMIT_DELAY_MICROSECONDS = 1000;  // try increasing this if RS485 is not working
HalfDuplexStream RS485Serial(Serial, TRANSMIT_PIN, TRANSMIT_DELAY_MICROSECONDS);

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
