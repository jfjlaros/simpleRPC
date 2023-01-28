#include <catch.hpp>

#include "../src/vector.tcc"


TEST_CASE("Initialisation, no parameters.", "[vector]") {
  Vector<int> v;

  REQUIRE(v.size() == 0);
}

TEST_CASE("Initialisation, size parameter.", "[vector]") {
  Vector<int> v(1);

  REQUIRE(v.size() == 1);
}

TEST_CASE("Resize.", "[vector]") {
  Vector<int> v(5);

  for (int i {0}; i < 5; i++) {
    v[i] = i;
  }

  v.resize(10);
  REQUIRE(v.size() == 10);
  REQUIRE(v[4] == 4);

  v.resize(2);
  REQUIRE(v.size() == 2);
  REQUIRE(v[1] == 1);
}

TEST_CASE("Set and get elements.", "[vector]") {
  Vector<int> v(2);

  v[0] = 1234;
  v[1] = 2345;

  REQUIRE(v.size() == 2);
  REQUIRE(v[0] == 1234);
  REQUIRE(v[1] == 2345);
}

TEST_CASE("Copy.", "[vector]") {
  Vector<int> v(2);

  v[0] = 1234;
  v[1] = 2345;

  Vector<int> w {v};

  REQUIRE(w.size() == 2);
  REQUIRE(w[0] == 1234);
  REQUIRE(w[1] == 2345);
}

TEST_CASE("Copy assign.", "[vector]") {
  Vector<int> v(2);
  v[0] = 1234;
  v[1] = 2345;
  Vector<int> w;
  w = v;

  REQUIRE(w.size() == 2);
  REQUIRE(w[0] == 1234);
  REQUIRE(w[1] == 2345);
}

TEST_CASE("Return.", "[vector]") {
  struct S {
    static Vector<int> f() {
      Vector<int> v(2);
      v[0] = 1234;
      return v;
    }
  };

  Vector<int> v {};
  v = S::f();

  REQUIRE(v[0] == 1234);
}

TEST_CASE("Pass by value.", "[vector]") {
  struct S {
    static void f(Vector<int> v) {
      REQUIRE(v.size() == 2);
      REQUIRE(v[0] == 1234);
    }
  };

  Vector<int> v(2);
  v[0] = 1234;
  S::f(v);
}
