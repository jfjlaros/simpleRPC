#include <catch.hpp>

#include "../src/interface.tcc"
#include "../src/serial/io.h"

extern HardwareSerialIO io;


TEST_CASE("Describe function", "[describe][basic]") {
  void (*f)(void);

  // Empty description.
  Serial.reset();
  _describe(io, f, "");
  REQUIRE(Serial.inspect<String>() == ":;");

  // Non-empty description.
  Serial.reset();
  _describe(io, f, "Function description.");
  REQUIRE(Serial.inspect<String>() == ":;Function description.");
}

TEST_CASE("Describe class member function", "[describe][class]") {
  class C {
    public:
      void f(void) {}
  };

  C c;

  // Empty description.
  Serial.reset();
  _describe(io, pack(&c, &C::f), "");
  REQUIRE(Serial.inspect<String>() == ":;");

  // Non-empty description.
  Serial.reset();
  _describe(io, pack(&c, &C::f), "Function description.");
  REQUIRE(Serial.inspect<String>() == ":;Function description.");
}

TEST_CASE("Multiple functions", "[describe][class]") {
  class C {
    public:
      void f(void) {}
  };

  void (*f)(void);
  C c;

  // Normal function first.
  Serial.reset();
  _describe(io, f, "f", pack(&c, &C::f), "C::f");
  REQUIRE(Serial.inspect<String>() == ":;f");
  REQUIRE(Serial.inspect<String>() == ":;C::f");

  // Class member function first.
  Serial.reset();
  _describe(io, pack(&c, &C::f), "C::f", f, "f");
  REQUIRE(Serial.inspect<String>() == ":;C::f");
  REQUIRE(Serial.inspect<String>() == ":;f");
}

TEST_CASE("Select by number", "[describe][select]") {
  struct S {
    static short int f0(void) {
      return 1;
    }
    static short int f1(void) {
      return 2;
    }
  };

  // Select first function.
  Serial.reset();
  _select(io, 0, 0, S::f0, "", S::f1, "");
  REQUIRE(Serial.inspect<short int>() == 1);

  // Select second function.
  Serial.reset();
  _select(io, 1, 0, S::f0, "", S::f1, "");
  REQUIRE(Serial.inspect<short int>() == 2);
}

TEST_CASE("RPC interface", "[describe][interface]") {
  struct S {
    static short int f0(void) {
      return 1;
    }
    static short int f1(void) {
      return 2;
    }
  };

  // Describe interface.
  Serial.reset();
  Serial.prepare(_LIST_REQ);
  rpcInterface(io, S::f0, "f", S::f1, "g");
  REQUIRE(Serial.inspect<String>() == (String)_PROTOCOL);
  REQUIRE(Serial.inspect<byte>() == _VERSION[0]);
  REQUIRE(Serial.inspect<byte>() == _VERSION[1]);
  REQUIRE(Serial.inspect<byte>() == _VERSION[2]);
  REQUIRE(Serial.inspect<String>() == _hardwareDefs());
  REQUIRE(Serial.inspect<String>() == "h:;f");
  REQUIRE(Serial.inspect<String>() == "h:;g");

  // Select first function.
  Serial.reset();
  Serial.prepare((byte)0x00);
  rpcInterface(io, S::f0, "f0", S::f1, "f1");
  REQUIRE(Serial.inspect<short int>() == 1);

  // Select second function.
  Serial.reset();
  Serial.prepare((byte)0x01);
  rpcInterface(io, S::f0, "f0", S::f1, "f1");
  REQUIRE(Serial.inspect<short int>() == 2);
}
