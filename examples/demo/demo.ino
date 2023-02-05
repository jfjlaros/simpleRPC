#include <simpleRPC.h>


byte ping(byte data) {
  return data;
}

void setLed(byte brightness) {
  analogWrite(LED_BUILTIN, brightness);
}

unsigned long milliTime() {
  return millis();
}

int inc(int a) {
  return a + 1;
}

Tuple<char, Tuple<int, char> > tuple(Tuple<char, Tuple<int, char> >& t) {
  Tuple<char, Tuple<int, char> > r;

  get<0>(r) = get<0>(t) + 1;
  get<0>(get<1>(r)) = get<0>(get<1>(t)) + 1;
  get<1>(get<1>(r)) = get<1>(get<1>(t)) + 1;

  return r;
}

Vector<float> vector(Vector<int>& v) {
  Vector<float> r(v.size());

  for (size_t i {0}; i < v.size(); ++i) {
    r[i] = float(v[i]) + 0.4;
  }

  return r;
}

Vector<float> cVector(int* v) {
  Vector<float> r(4);

  for (size_t i {0}; i < 4; i++) {
    r[i] = float(v[i]) + 0.4;
  }

  return r;
}


void setup() {
  Serial.begin(9600);
}

void loop() {
  interface(
    Serial,
    ping, F("ping: Echo a value. @data: Value. @return: Value of data."),
    inc, F("inc: Increment a value. @a: Value. @return: a + 1."),
    setLed, F("set_led: Set LED brightness. @brightness: Brightness."),
    milliTime, F("milli_time: Report the system time. @return: System time."),
    tuple, F("tuple: Example with tuples. @o: Tuple. @return: Tuple."),
    vector, F("cpp_vector: Example with vectors. @v: Vector. @return: Vector."),
    cVector, F("c_vector: Example with C vectors. @v: C vector. @return: Vector."));
}
