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

std::vector<Tuple<int, char>> tupleVector(std::vector<Tuple<int, char>>& t) {
  std::vector<Tuple<int, char>> v(2);
  v[0] = {get<0>(t[0]) + 1, 'a'};
  v[1] = {get<0>(t[1]) + 1, 'b'};

  return v;
}

std::vector<std::tuple<int, char>>
    stdTupleVector(std::vector<std::tuple<int, char>>& t) {
  std::vector<std::tuple<int, char>> v(2);
  v[0] = std::make_tuple<int, char>(std::get<0>(t[0]) + 1, 'a');
  v[1] = std::make_tuple<int, char>(std::get<0>(t[1]) + 1, 'b');

  return v;
}

std::array<float, 4> stdArray(std::array<int, 4>& v) {
  std::array<float, 4> r;

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
    stdVector, "",
    tupleVector, "",
    stdTupleVector, "",
    stdArray, ""
  );
}
