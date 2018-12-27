#include <catch.hpp>

#include "../simpleRPC/interface.tcc"


TEST_CASE("Describe function", "[describe]") {
  void (*f)(void);

  // Empty description.
  Serial.reset();
  _describe(f, "");
  REQUIRE(Serial.inspect<String>() == ":;");

  // Non-empty description.
  Serial.reset();
  _describe(f, "Function description.");
  REQUIRE(Serial.inspect<String>() == ":;Function description.");
}

TEST_CASE("Describe class member function", "[describe]") {
  class C {
    public:
      void f(void) {}
  };

  C c;

  // Empty description.
  Serial.reset();
  _describe(pack(&c, &C::f), "");
  REQUIRE(Serial.inspect<String>() == ":;");

  // Non-empty description.
  Serial.reset();
  _describe(pack(&c, &C::f), "Function description.");
  REQUIRE(Serial.inspect<String>() == ":;Function description.");
}

TEST_CASE("Multiple functions", "[describe]") {
  class C {
    public:
      void f(void) {}
  };

  void (*f)(void);
  C c;

  // Normal function first.
  Serial.reset();
  _describe(f, "f", pack(&c, &C::f), "C::f");
  REQUIRE(Serial.inspect<String>() == ":;f");
  REQUIRE(Serial.inspect<String>() == ":;C::f");

  // Class member function first.
  Serial.reset();
  _describe(pack(&c, &C::f), "C::f", f, "f");
  REQUIRE(Serial.inspect<String>() == ":;C::f");
  REQUIRE(Serial.inspect<String>() == ":;f");
}

// TODO: select and interface.
