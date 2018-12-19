#include <catch.hpp>

#include "../simpleRPC/rpcCall.tcc"


TEST_CASE("RPC call function", "[call]") {
  struct S {
    static void f(int, char) {}
    static short int g(int, char) {
      return 0;
    }
  };

  Serial.reset();
  rpcCall(S::f);

  REQUIRE(Serial.rx == sizeof(int) + sizeof(char));
  REQUIRE(Serial.tx == 0);

  Serial.reset();
  rpcCall(S::g);

  REQUIRE(Serial.rx == sizeof(int) + sizeof(char));
  REQUIRE(Serial.tx == sizeof(short int));
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
