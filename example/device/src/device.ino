#include <simpleRPC.h>


void setLed(byte brightness) {
  analogWrite(13, brightness);
}

int add(int a, int b) {
  return a + b;
}

char *str(void) {
  return "abc";
}

const char *eat(const char *s) {
  return s;
}


void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  void (*f)(int, int);

  interface(
    f, "f: @a: @b: @c: @return:",
    str, "",
    eat, "",
    add, "add: Add two numbers. @a: Value. @b: Value. @return: Sum of a and b.",
    setLed, "set_led: Set LED brightness. @brightness: Brightness."
  );
}
