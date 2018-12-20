#include <catch.hpp>

#include "../simpleRPC/rpcCall.tcc"


TEST_CASE("RPC call function", "[call]") {
  struct S {
    static void f(int, char) {}
    static short int g(int, char) {
      return 0;
    }
    static void h(int, char *) {}
    static void i(int, const char *) {}
    static void j(char *, int) {}
    static void k(const char *, int) {}
  };

  Serial.reset();
  rpcCall(S::f);

  REQUIRE(Serial.rx == sizeof(int) + sizeof(char));
  REQUIRE(Serial.tx == 0);

  Serial.reset();
  rpcCall(S::g);

  REQUIRE(Serial.rx == sizeof(int) + sizeof(char));
  REQUIRE(Serial.tx == sizeof(short int));

  Serial.reset();
  rpcCall(S::h);

  REQUIRE(Serial.rx == sizeof(int) + 3);
  REQUIRE(Serial.tx == 0);

  Serial.reset();
  rpcCall(S::i);

  REQUIRE(Serial.rx == sizeof(int) + 3);
  REQUIRE(Serial.tx == 0);

  Serial.reset();
  rpcCall(S::j);

  REQUIRE(Serial.rx == sizeof(int) + 3);
  REQUIRE(Serial.tx == 0);

  Serial.reset();
  rpcCall(S::k);

  REQUIRE(Serial.rx == sizeof(int) + 3);
  REQUIRE(Serial.tx == 0);
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

  Serial.reset();
  rpcCall(pack(&c, &C::f));

  REQUIRE(Serial.rx == sizeof(int) + sizeof(char));
  REQUIRE(Serial.tx == 0);

  Serial.reset();
  rpcCall(pack(&c, &C::g));

  REQUIRE(Serial.rx == sizeof(int) + sizeof(char));
  REQUIRE(Serial.tx == sizeof(short int));
}
