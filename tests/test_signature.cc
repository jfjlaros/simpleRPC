#include <catch.hpp>

#include <Arduino.h>

#include "../src/signature.tcc"


TEST_CASE("Function pointer types", "[signature]") {
  short int (*f)(char, float);
  void (*g)(char, float);

  // Function pointers.
  REQUIRE(signature(f) == "<h: c <f");
  REQUIRE(signature(g) == ": c <f");
}

TEST_CASE("Class member function pointer types", "[signature]") {
  class C {
    public:
      short int f(char, float) {}
      void g(char, float) {}
  };

  // Function pointers.
  REQUIRE(signature(&C::f) == "<h: c <f");
  REQUIRE(signature(&C::g) == ": c <f");
}
