#include <catch.hpp>

#include "../src/interface.tcc"

extern Stream Serial;


TEST_CASE("Describe function", "[describe][basic]") {
  void (*f)(void);

  // Empty description.
  Serial.reset();
  _describe(Serial, f, "");
  REQUIRE(Serial.inspect<String>() == ":;");

  // Non-empty description.
  Serial.reset();
  _describe(Serial, f, "Function description.");
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
  _describe(Serial, pack(&c, &C::f), "");
  REQUIRE(Serial.inspect<String>() == ":;");

  // Non-empty description.
  Serial.reset();
  _describe(Serial, pack(&c, &C::f), "Function description.");
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
  _describe(Serial, f, "f", pack(&c, &C::f), "C::f");
  REQUIRE(Serial.inspect<String>() == ":;f");
  REQUIRE(Serial.inspect<String>() == ":;C::f");

  // Class member function first.
  Serial.reset();
  _describe(Serial, pack(&c, &C::f), "C::f", f, "f");
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
  _select(Serial, 0, 0, S::f0, "", S::f1, "");
  REQUIRE(Serial.inspect<short int>() == 1);

  // Select second function.
  Serial.reset();
  _select(Serial, 1, 0, S::f0, "", S::f1, "");
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
  interface(Serial, S::f0, "f", S::f1, "g");
  REQUIRE(Serial.inspect<String>() == (String)_PROTOCOL);
  REQUIRE(Serial.inspect<byte>() == _VERSION[0]);
  REQUIRE(Serial.inspect<byte>() == _VERSION[1]);
  REQUIRE(Serial.inspect<byte>() == _VERSION[2]);
  REQUIRE(Serial.inspect<String>().size() == 2);
  REQUIRE(Serial.inspect<String>() == "h:;f");
  REQUIRE(Serial.inspect<String>() == "h:;g");

  // Select first function.
  Serial.reset();
  Serial.prepare((byte)0x00);
  interface(Serial, S::f0, "f0", S::f1, "f1");
  REQUIRE(Serial.inspect<short int>() == 1);

  // Select second function.
  Serial.reset();
  Serial.prepare((byte)0x01);
  interface(Serial, S::f0, "f0", S::f1, "f1");
  REQUIRE(Serial.inspect<short int>() == 2);
}

TEST_CASE("RPC call function x", "[call][basic]") {
  struct S {
    static short int f(int) {
      return 2;
    }
  };

  // One interface.
  Serial.reset();
  Serial.prepare('\0');
  interface(Serial, S::f, "");
  REQUIRE(Serial.inspect<short int>() == 2);
  REQUIRE(Serial.rx == sizeof(byte) + sizeof(int));
  REQUIRE(Serial.tx == sizeof(short int));

  // Two interfaces.
  Serial.reset();
  Serial.prepare('\0');
  Serial.prepare('\0');
  interface(pack(&Serial, &Serial), S::f, "");
  REQUIRE(Serial.inspect<short int>() == 2);
  REQUIRE(Serial.inspect<short int>() == 2);
  REQUIRE(Serial.rx == 2 * (sizeof(byte) + sizeof(int)));
  REQUIRE(Serial.tx == 2 * (sizeof(short int)));
}
