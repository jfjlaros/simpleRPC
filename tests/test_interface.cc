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

TEST_CASE("Select by number", "[select]") {
  struct S {
    static short int f(void) {
      return 1;
    }
    static short int g(void) {
      return 2;
    }
  };

  // Select first function.
  Serial.reset();
  _select(0, 0, S::f, "", S::g, "");
  REQUIRE(Serial.inspect<short int>() == 1);

  // Select second function.
  Serial.reset();
  _select(1, 0, S::f, "", S::g, "");
  REQUIRE(Serial.inspect<short int>() == 2);
}

TEST_CASE("RPC interface", "[interface]") {
  struct S {
    static short int f(void) {
      return 1;
    }
    static short int g(void) {
      return 2;
    }
  };

  // Describe interface.
  Serial.reset();
  Serial.prepare(_LIST_REQ);
  rpcInterface(S::f, "f", S::g, "g");
  REQUIRE(Serial.inspect<String>() == "<h:;f");
  REQUIRE(Serial.inspect<String>() == "<h:;g");

  // Select first function.
  Serial.reset();
  Serial.prepare((byte)0x00);
  rpcInterface(S::f, "f", S::g, "g");
  REQUIRE(Serial.inspect<short int>() == 1);

  // Select second function.
  Serial.reset();
  Serial.prepare((byte)0x01);
  rpcInterface(S::f, "f", S::g, "g");
  REQUIRE(Serial.inspect<short int>() == 2);
}
