#include <catch.hpp>

#include <Arduino.h>

#include "../src/signature.tcc"


TEST_CASE("Function pointer types", "[signature][basic]") {
  short int (*f0)(char, float);
  void (*f1)(char, float);

  REQUIRE(signature(f0) == "h: c f");
  REQUIRE(signature(f1) == ": c f");
}

TEST_CASE("Class member function pointer types", "[signature][class]") {
  class C {
    public:
      short int f0(char, float) {
        return 0;
      }
      void f1(char, float) {}
  };

  REQUIRE(signature(&C::f0) == "h: c f");
  REQUIRE(signature(&C::f1) == ": c f");
}

TEST_CASE("Tuples", "[signature][tuple]") {
  void (*f0)(Tuple<int, char>, float);
  Tuple<int, char> (*f1)(float);

  REQUIRE(signature(f0) == ": ic f");
  REQUIRE(signature(f1) == "ic: f");
}

TEST_CASE("Objects", "[signature][object]") {
  void (*f0)(Object<int, char>, float);
  Object<int, char> (*f1)(float);

  REQUIRE(signature(f0) == ": (ic) f");
  REQUIRE(signature(f1) == "(ic): f");
}

TEST_CASE("Vectors", "[signature][vector]") {
  void (*f0)(Vector<int>, float);
  Vector<int> (*f1)(float);
  int (*f2)(Vector<signed char>&, int);

  REQUIRE(signature(f0) == ": [i] f");
  REQUIRE(signature(f1) == "[i]: f");
  REQUIRE(signature(f2) == "i: [b] i");
}
