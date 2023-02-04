#include <catch.hpp>

#include "../src/array.tcc"


TEST_CASE("Array initialisation, default.", "[array]") {
  Array<int, 3> a {};

  REQUIRE(a.size() == 3);
  REQUIRE(a[1] == 0);
}

TEST_CASE("Array initialisation, C array.", "[array]") {
  int data[] {1, 2, 3};
  Array<int, 3> a {data};

  REQUIRE(a.size() == 3);
  REQUIRE(a[1] == 2);
}

TEST_CASE("Array initialisation, temporary array.", "[array]") {
  Array<int, 3> a {{1, 2, 3}};

  REQUIRE(a.size() == 3);
  REQUIRE(a[1] == 2);
}

TEST_CASE("Array initialisation, initialiser list.", "[array]") {
  Array<int, 3> a {1, 2, 3};

  REQUIRE(a.size() == 3);
  REQUIRE(a[1] == 2);
}

TEST_CASE("Array set and get elements.", "[array]") {
  Array<int, 2> a {};

  a[0] = 1234;
  a[1] = 2345;

  REQUIRE(a.size() == 2);
  REQUIRE(a[0] == 1234);
  REQUIRE(a[1] == 2345);
}

TEST_CASE("Array get constant elements.", "[array]") {
  Array<int, 2> const a {{1234, 2345}};

  REQUIRE(a.size() == 2);
  REQUIRE(a[0] == 1234);
  REQUIRE(a[1] == 2345);
}


TEST_CASE("Array range loop.", "[array]") {
  Array<int, 2> a {{1234, 2345}};

  for (int& el: a) {
    el = 1234;
  }
  for (int const& el: a) {
    REQUIRE(el == 1234);
  }
}


TEST_CASE("Array size.", "[array]") {
  Array<int, 2> a {{1234, 2345}};

  REQUIRE(a.size() == 2);
}


TEST_CASE("Array return.", "[array]") {
  struct S {
    static Array<int, 2> f() {
      Array<int, 2> a {{1234, 2345}};
      return a;
    }
  };

  Array<int, 2> a {};
  a = S::f();

  REQUIRE(a[0] == 1234);
}

TEST_CASE("Array pass by value.", "[array]") {
  struct S {
    static void f(Array<int, 2> a) {
      REQUIRE(a.size() == 2);
      REQUIRE(a[0] == 1234);
    }
  };

  Array<int, 2> a {{1234, 2345}};
  S::f(a);
}
