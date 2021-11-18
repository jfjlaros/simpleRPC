#include <simpleRPC_STL.h>


String hi(String person) {
  return "Hello, " + person;
}

std::string stdHi(std::string person) {
  return "Hello, " + person;
}

Vector<float> vector(Vector<int>& v) {
  Vector<float> r(v.size);

  for (size_t i = 0; i < v.size; i++) {
    r[i] = float(v[i]) + 0.4;
  }

  return r;
}

std::vector<float> stdVector(std::vector<int>& v) {
  std::vector<float> r(v.size());

  for (size_t i = 0; i < v.size(); i++) {
    r[i] = float(v[i]) + 0.4;
  }

  return r;
}


void setup() {
  Serial.begin(9600);
}

void loop() {
  interface(Serial,
    hi, "",
    stdHi, "",
    vector, "",
    stdVector, ""
  );
}
