#include <catch.hpp>

#include "../simpleRPC/rpcCall.tcc"


TEST_CASE("RPC call function", "[call]") {
  struct S {
    static void v_0(void) {}
    static void v_1(int) {}
    static void v_2(int, char) {}
    static void v_3(int, char, float) {}
    static void v_c_1(char *, int) {}
    static void v_cc_1(const char *, int) {}
    static void v_c_2(int, char *) {}
    static void v_cc_2(int, const char *) {}
    static short int s_0(void) {
      return 1;
    }
    static short int s_1(int) {
      return 2;
    }
    static short int s_2(int, char) {
      return 3;
    }
    static float f_0(void) {
      return 1.0F;
    }
    static float f_1(int) {
      return 2.0F;
    }
    static float f_2(int, char) {
      return 3.0F;
    }
    static char *c_0(void) {
      return (char *)"xyz";
    }
    static const char *cc_0(void) {
      return "xyz";
    }
  };

  // Void function, no parameters.
  Serial.reset();
  rpcCall(S::v_0);
  REQUIRE(Serial.rx == 0);
  REQUIRE(Serial.tx == 0);

  // Void function, one parameter.
  Serial.reset();
  rpcCall(S::v_1);
  REQUIRE(Serial.rx == sizeof(int));
  REQUIRE(Serial.tx == 0);

  // Void function, two parameters.
  Serial.reset();
  rpcCall(S::v_2);
  REQUIRE(Serial.rx == sizeof(int) + sizeof(char));
  REQUIRE(Serial.tx == 0);

  // Void function, three parameters.
  Serial.reset();
  rpcCall(S::v_3);
  REQUIRE(Serial.rx == sizeof(int) + sizeof(char) + sizeof(float));
  REQUIRE(Serial.tx == 0);

  // Void function, first parameter is of type char *.
  Serial.reset();
  Serial.prepare("xyz", 1234);
  rpcCall(S::v_c_1);
  REQUIRE(Serial.rx == 4 + sizeof(int));
  REQUIRE(Serial.tx == 0);

  // Void function, first parameter is of type const char *.
  Serial.reset();
  Serial.prepare("xyz", 1234);
  rpcCall(S::v_cc_1);
  REQUIRE(Serial.rx == 4 + sizeof(int));
  REQUIRE(Serial.tx == 0);

  // Void function, second parameter is of type char *.
  Serial.reset();
  Serial.prepare(1234, "xxx");
  rpcCall(S::v_c_2);
  REQUIRE(Serial.rx == sizeof(int) + 4);
  REQUIRE(Serial.tx == 0);

  // Void function, second parameter is of type const char *.
  Serial.reset();
  Serial.prepare(1234, "xxx");
  rpcCall(S::v_cc_2);
  REQUIRE(Serial.rx == sizeof(int) + 4);
  REQUIRE(Serial.tx == 0);

  // Function of type short int, zero parameters.
  Serial.reset();
  rpcCall(S::s_0);
  REQUIRE(Serial.inspect<short int>() == 1);
  REQUIRE(Serial.rx == 0);
  REQUIRE(Serial.tx == sizeof(short int));

  // Function of type short int, one parameter.
  Serial.reset();
  rpcCall(S::s_1);
  REQUIRE(Serial.inspect<short int>() == 2);
  REQUIRE(Serial.rx == sizeof(int));
  REQUIRE(Serial.tx == sizeof(short int));

  // Function of type short int, two parameters.
  Serial.reset();
  rpcCall(S::s_2);
  REQUIRE(Serial.inspect<short int>() == 3);
  REQUIRE(Serial.rx == sizeof(int) + sizeof(char));
  REQUIRE(Serial.tx == sizeof(short int));

  // Function of type float, zero parameters.
  Serial.reset();
  rpcCall(S::f_0);
  REQUIRE(Serial.inspect<float>() == 1.0F);
  REQUIRE(Serial.rx == 0);
  REQUIRE(Serial.tx == sizeof(float));

  // Function of type float, one parameter.
  Serial.reset();
  rpcCall(S::f_1);
  REQUIRE(Serial.inspect<float>() == 2.0F);
  REQUIRE(Serial.rx == sizeof(int));
  REQUIRE(Serial.tx == sizeof(float));

  // Function of type float, two parameters.
  Serial.reset();
  rpcCall(S::f_2);
  REQUIRE(Serial.inspect<float>() == 3.0F);
  REQUIRE(Serial.rx == sizeof(int) + sizeof(char));
  REQUIRE(Serial.tx == sizeof(float));

  // Function of type char *.
  Serial.reset();
  rpcCall(S::c_0);
  REQUIRE(Serial.inspect<String>() == "xyz");
  REQUIRE(Serial.rx == 0);
  REQUIRE(Serial.tx == 4);

  // Function of type const char *.
  Serial.reset();
  rpcCall(S::cc_0);
  REQUIRE(Serial.inspect<String>() == "xyz");
  REQUIRE(Serial.rx == 0);
  REQUIRE(Serial.tx == 4);
}

TEST_CASE("RPC call class member functions", "[call]") {
  class C {
    public:
      void f(int, char) {}
      short int g(int, char) {
        return 1;
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
  REQUIRE(Serial.inspect<short int>() == 1);
  REQUIRE(Serial.rx == sizeof(int) + sizeof(char));
  REQUIRE(Serial.tx == sizeof(short int));
}

TEST_CASE("Executing a function", "[call]") {
  struct S {
    static short int f(int i, char c) {
      return i + c + 1;
    }
  };

  Serial.reset();
  Serial.prepare(1234, '\3');
  rpcCall(S::f);
  REQUIRE(Serial.rx == sizeof(int) + sizeof(char));
  REQUIRE(Serial.tx == sizeof(short int));
  REQUIRE(Serial.inspect<short int>() == 1238);
}
