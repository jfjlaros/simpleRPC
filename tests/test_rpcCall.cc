#include <catch.hpp>

#include "../src/rpcCall.tcc"


TEST_CASE("RPC call function", "[call]") {
  struct S {
    static void v_0(void) {}
    static void v_1(int) {}
    static void v_2(int, char) {}
    static void v_3(int, char, float) {}
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
}

TEST_CASE("RPC call function with String types", "[call]") {
  struct S {
    static void p_str_1(String, int) {}
    static void p_str_2(int, String) {}
    static String r_str(void) {
      return "xyz";
    }
  };

  // Void function, first parameter is of type String.
  Serial.reset();
  Serial.prepare("xyz", 1234);
  rpcCall(S::p_str_1);
  REQUIRE(Serial.rx == 4 + sizeof(int));
  REQUIRE(Serial.tx == 0);

  // Void function, second parameter is of type String.
  Serial.reset();
  Serial.prepare(1234, "xxx");
  rpcCall(S::p_str_2);
  REQUIRE(Serial.rx == sizeof(int) + 4);
  REQUIRE(Serial.tx == 0);

  // Function with return type String. 
  Serial.reset();
  rpcCall(S::r_str);
  REQUIRE(Serial.inspect<String>() == "xyz");
  REQUIRE(Serial.rx == 0);
  REQUIRE(Serial.tx == 4);
}

TEST_CASE("RPC call function with Tuple types", "[call]") {
  struct S {
    static void p_tuple_1(Tuple <int, char>) {}
    static Tuple <int, char>r_tuple_2(void) {
      Tuple <int, char>t = {1234, 'x'};

      return t;
    }
  };

  // Void function, parameter is of type Tuple.
  Serial.reset();
  Serial.prepare(1234, 'x');
  rpcCall(S::p_tuple_1);
  REQUIRE(Serial.rx == sizeof(int) + sizeof(char));
  REQUIRE(Serial.tx == 0);

  // Function with return type Tuple.
  Serial.reset();
  rpcCall(S::r_tuple_2);
  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<char>() == 'x');
  REQUIRE(Serial.rx == 0);
  REQUIRE(Serial.tx == sizeof(int) + sizeof(char));
}

TEST_CASE("RPC call function with Object types", "[call]") {
  struct S {
    static void p_obj_1(Object <int, char>) {}
    static Object <int, char>r_obj_2(void) {
      Object <int, char>o = {1234, 'x'};

      return o;
    }
  };

  // Void function, parameter is of type Object.
  Serial.reset();
  Serial.prepare(1234, 'x');
  rpcCall(S::p_obj_1);
  REQUIRE(Serial.rx == sizeof(int) + sizeof(char));
  REQUIRE(Serial.tx == 0);

  // Function with return type Object.
  Serial.reset();
  rpcCall(S::r_obj_2);
  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<char>() == 'x');
  REQUIRE(Serial.rx == 0);
  REQUIRE(Serial.tx == sizeof(int) + sizeof(char));
}

TEST_CASE("RPC call function with Vector types", "[call]") {
  struct S {
    static bool p_vect_1(Vector <int> *v) {
      if ((*v).length != 2 || (*v)[0] != 1234 || (*v)[1] != 2345) {
        return false;
      }
      return true;
    }
    static Vector <int>r_vect_2(void) {
      Vector <int>v;

      v.setLength(2);
      v[0] = 1234;
      v[1] = 2345;

      return v;
    }
  };

  // Void function, parameter is of type Vector.
  Serial.reset();
  Serial.prepare((size_t)2, 1234, 2345);
  rpcCall(S::p_vect_1);
  REQUIRE(Serial.inspect<bool>());
  REQUIRE(Serial.rx == sizeof(size_t) + 2 * sizeof(int));
  REQUIRE(Serial.tx == 1);

  // Function with return type Vector.
  Serial.reset();
  rpcCall(S::r_vect_2);
  REQUIRE(Serial.inspect<size_t>() == 2);
  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<int>() == 2345);
  REQUIRE(Serial.rx == 0);
  REQUIRE(Serial.tx == sizeof(size_t) + 2 * sizeof(int));
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
