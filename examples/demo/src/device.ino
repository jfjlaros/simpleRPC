#include <simpleRPC.h>


void setLed(byte brightness) {
  analogWrite(13, brightness);
}

unsigned long time(void) {
  return millis();
}

int inc(int a) {
  return a + 1;
}


void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  interface(
    inc, F("inc: Increment a value. @a: Value. @return: a + 1."),
    setLed, F("set_led: Set LED brightness. @brightness: Brightness."),
    time, F("time: Report the system time. @return: System time."));
}
