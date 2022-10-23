#include <catch.hpp>

#include "../src/interface.tcc"

extern Stream Serial;


TEST_CASE("Describe function", "[describe][basic]") {
  void (*f)(){};

  // Empty description.
  Serial.reset();
  describe_(Serial, f, "");
  REQUIRE(Serial.inspect<String>() == ":;");

  // Non-empty description.
  Serial.reset();
  describe_(Serial, f, "Function description.");
  REQUIRE(Serial.inspect<String>() == ":;Function description.");
}

TEST_CASE("Describe class member function", "[describe][class]") {
  class C {
    public:
      void f() {}
  };

  C c;

  // Empty description.
  Serial.reset();
  describe_(Serial, pack(&c, &C::f), "");
  REQUIRE(Serial.inspect<String>() == ":;");

  // Non-empty description.
  Serial.reset();
  describe_(Serial, pack(&c, &C::f), "Function description.");
  REQUIRE(Serial.inspect<String>() == ":;Function description.");
}

TEST_CASE("Multiple functions", "[describe][class]") {
  class C {
    public:
      void f() {}
  };

  void (*f)(){};
  C c;

  // Normal function first.
  Serial.reset();
  describe_(Serial, f, "f", pack(&c, &C::f), "C::f");
  REQUIRE(Serial.inspect<String>() == ":;f");
  REQUIRE(Serial.inspect<String>() == ":;C::f");

  // Class member function first.
  Serial.reset();
  describe_(Serial, pack(&c, &C::f), "C::f", f, "f");
  REQUIRE(Serial.inspect<String>() == ":;C::f");
  REQUIRE(Serial.inspect<String>() == ":;f");
}

TEST_CASE("Select by number", "[describe][select]") {
  struct S {
    static short int f0() {
      return 1;
    }
    static short int f1() {
      return 2;
    }
  };

  // Select first function.
  Serial.reset();
  select_(Serial, 0, 0, S::f0, "", S::f1, "");
  REQUIRE(Serial.inspect<short int>() == 1);

  // Select second function.
  Serial.reset();
  select_(Serial, 1, 0, S::f0, "", S::f1, "");
  REQUIRE(Serial.inspect<short int>() == 2);
}

TEST_CASE("RPC interface", "[describe][interface]") {
  struct S {
    static short int f0() {
      return 1;
    }
    static short int f1() {
      return 2;
    }
  };

  // Describe interface.
  Serial.reset();
  Serial.prepare(LIST_REQ_);
  interface(Serial, S::f0, "f", S::f1, "g");
  REQUIRE(Serial.inspect<String>() == PROTOCOL_);
  REQUIRE(Serial.inspect<byte>() == VERSION_[0]);
  REQUIRE(Serial.inspect<byte>() == VERSION_[1]);
  REQUIRE(Serial.inspect<byte>() == VERSION_[2]);
  REQUIRE(Serial.inspect<String>().size() == 2);
  REQUIRE(Serial.inspect<String>() == "h:;f");
  REQUIRE(Serial.inspect<String>() == "h:;g");

  // Select first function.
  Serial.reset();
  Serial.prepare('\x00');
  interface(Serial, S::f0, "f0", S::f1, "f1");
  REQUIRE(Serial.inspect<short int>() == 1);

  // Select second function.
  Serial.reset();
  Serial.prepare('\x01');
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
