#include <simpleRPC.h>


byte ping(byte data) {
  return data;
}


void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  interface(
    Serial,
    ping, F("ping: Echo a value. @data: Value. @return: Value of data."));
}
