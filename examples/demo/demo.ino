#include <simpleRPC.h>

HardwareSerialIO io;


void setLed(byte brightness) {
  analogWrite(LED_BUILTIN, brightness);
}

unsigned long time(void) {
  return millis();
}

int inc(int a) {
  return a + 1;
}

Object<char, Object<int, char> > object(Object<char, Object<int, char> >& o) {
  Object<char, Object<int, char> > r;

  get<0>(r) = get<0>(o) + 1;
  get<0>(get<1>(r)) = get<0>(get<1>(o)) + 1;
  get<1>(get<1>(r)) = get<1>(get<1>(o)) + 1;

  return r;
}

Vector<float> vector(Vector<int>& v) {
  Vector<float> r(v.size);
  int i;

  for (i = 0; i < v.size; i++) {
    r[i] = float(v[i]) + 0.4;
  }

  return r;
}


void setup(void) {
  Serial.begin(9600);
  io.begin(Serial);
}

void loop(void) {
  interface(
    io,
    inc, F("inc: Increment a value. @a: Value. @return: a + 1."),
    setLed, F("set_led: Set LED brightness. @brightness: Brightness."),
    time, F("time: Report the system time. @return: System time."),
    object, F("object: Example with objects. @o: Object. @return: Object."),
    vector, F("vector: Example with vectors. @v: Vector. @return: Vector."));
}
