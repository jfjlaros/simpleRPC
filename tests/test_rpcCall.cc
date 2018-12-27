#include <catch.hpp>

#include "../simpleRPC/rpcCall.tcc"


TEST_CASE("RPC call function", "[call]") {
  struct S {
    static void f(int, char) {}
    static short int g(int i, char c) {
      return i + c + 1;
    }
    static void h(int, char *) {}
    static void i(int, const char *) {}
    static void j(char *, int) {}
    static void k(const char *, int) {}
    static char *l(void) {
      return (char *)"xxx";
    }
    static const char *m(void) {
      return "xxx";
    }
  };

  // Void function.
  Serial.reset();
  rpcCall(S::f);
  REQUIRE(Serial.rx == sizeof(int) + sizeof(char));
  REQUIRE(Serial.tx == 0);

  // Non-void function.
  Serial.reset();
  Serial.prepare(12, '\3');
  rpcCall(S::g);
  REQUIRE(Serial.rx == sizeof(int) + sizeof(char));
  REQUIRE(Serial.tx == sizeof(short int));
  REQUIRE(Serial.inspect<short int>() == 16);

  // Second parameter is of type char *.
  Serial.reset();
  Serial.prepare(1234, "xxx");
  rpcCall(S::h);
  REQUIRE(Serial.rx == sizeof(int) + 4);
  REQUIRE(Serial.tx == 0);

  // Second parameter is of type const char *.
  Serial.reset();
  Serial.prepare(1234, "xxx");
  rpcCall(S::i);
  REQUIRE(Serial.rx == sizeof(int) + 4);
  REQUIRE(Serial.tx == 0);

  // First parameter is of type char *.
  Serial.reset();
  Serial.prepare("xxx", 1234);
  rpcCall(S::j);
  REQUIRE(Serial.rx == 4 + sizeof(int));
  REQUIRE(Serial.tx == 0);

  // First parameter is of type const char *.
  Serial.reset();
  Serial.prepare("xxx", 1234);
  rpcCall(S::k);
  REQUIRE(Serial.rx == 4 + sizeof(int));
  REQUIRE(Serial.tx == 0);

  // Return type char *.
  Serial.reset();
  rpcCall(S::l);

  REQUIRE(Serial.inspect<String>() == "xxx");
  REQUIRE(Serial.rx == 0);
  REQUIRE(Serial.tx == 4); // FIXME: off by one.

  // Return type const char *.
  Serial.reset();
  rpcCall(S::m);

  REQUIRE(Serial.inspect<String>() == "xxx");
  REQUIRE(Serial.rx == 0);
  REQUIRE(Serial.tx == 4);
}

TEST_CASE("RPC call class member functions", "[call]") {
  class C {
    public:
      void f(int, char) {}
      short int g(int, char) {
        return 0;
      }
  };

  C c;

  // Void function.
  Serial.reset();
  rpcCall(pack(&c, &C::f));

  REQUIRE(Serial.rx == sizeof(int) + sizeof(char));
  REQUIRE(Serial.tx == 0);

  // Non-void function.
  Serial.reset();
  rpcCall(pack(&c, &C::g));

  REQUIRE(Serial.rx == sizeof(int) + sizeof(char));
  REQUIRE(Serial.tx == sizeof(short int));
}

short int add(int i, char c) {
  return i + c + 1;
}

TEST_CASE("Input and output", "[call]") {
  Serial.reset();
  Serial.prepare(1234, '\3');
  rpcCall(add);

  REQUIRE(Serial.rx == sizeof(int) + sizeof(char));
  REQUIRE(Serial.tx == sizeof(short int));
  REQUIRE(Serial.inspect<short int>() == 1238);
}
