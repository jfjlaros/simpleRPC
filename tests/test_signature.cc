#include <catch.hpp>

#include <Arduino.h>

#include "../src/signature.tcc"


TEST_CASE("Function pointer types", "[signature]") {
  short int (*f)(char, float);
  void (*g)(char, float);

  REQUIRE(signature(f) == "<h: c <f");
  REQUIRE(signature(g) == ": c <f");
}

TEST_CASE("Class member function pointer types", "[signature]") {
  class C {
    public:
      short int f(char, float) {}
      void g(char, float) {}
  };

  REQUIRE(signature(&C::f) == "<h: c <f");
  REQUIRE(signature(&C::g) == ": c <f");
}

TEST_CASE("Tuples", "[signature]") {
  void (*f)(Tuple <int, char>, float);
  Tuple <int, char> (*g)(float);

  REQUIRE(signature(f) == ": <ic <f");
  REQUIRE(signature(g) == "<ic: <f");
}

TEST_CASE("Objects", "[signature]") {
  void (*f)(Object <int, char>, float);
  Object <int, char> (*g)(float);

  REQUIRE(signature(f) == ": [<ic] <f");
  REQUIRE(signature(g) == "[<ic]: <f");
}

TEST_CASE("Vectors", "[signature]") {
  void (*f)(Vector <int>, float);
  Vector <int> (*g)(float);

  REQUIRE(signature(f) == ": (<i) <f");
  REQUIRE(signature(g) == "(<i): <f");
}
