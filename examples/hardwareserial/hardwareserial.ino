#include <simpleRPC.h>


byte ping(byte data) {
  return data;
}


void setup() {
  Serial.begin(9600);
}

void loop() {
  interface(
    Serial,
    ping, F("ping: Echo a value. @data: Value. @return: Value of data."));
}
