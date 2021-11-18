#include <simpleRPC_STL.h>


std::string greet(std::string person) {
  return "Hello, " + person + "\n";
}


void setup() {
  Serial.begin(9600);
}

void loop() {
  interface(Serial, greet, "");
}
