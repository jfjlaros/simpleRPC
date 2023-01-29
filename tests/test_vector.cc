#include <catch.hpp>

#include "../src/vector.tcc"


TEST_CASE("Vector initialisation, no parameters.", "[vector]") {
  Vector<int> v {};

  REQUIRE(v.size() == 0);
  REQUIRE(not v.data());
}

TEST_CASE("Vector initialisation, copy.", "[vector]") {
  Vector<int> v {{1234, 2345}};
  Vector<int> w {v};

  REQUIRE(w.size() == 2);
  REQUIRE(w[0] == 1234);
  REQUIRE(w[1] == 2345);
}

TEST_CASE("Vector initialisation, size parameter.", "[vector]") {
  Vector<int> v(1);

  REQUIRE(v.size() == 1);
  REQUIRE(v.data());
}

TEST_CASE("Vector initialisation, array parameter.", "[vector]") {
  int a[] {1, 2, 3};
  Vector<int> v {a};

  REQUIRE(v.size() == 3);
  REQUIRE(v.data());
  REQUIRE(v[1] == 2);
}

TEST_CASE("Vector initialisation, initialiser list parameter.", "[vector]") {
  Vector<int> v {{1, 2, 3}};

  REQUIRE(v.size() == 3);
  REQUIRE(v.data());
  REQUIRE(v[1] == 2);
}

TEST_CASE("Vector initialisation, pointer parameter.", "[vector]") {
  int* data {new int[3]};
  data[0] = 1;
  data[1] = 2;
  data[2] = 3;
  Vector<int> v(data, 3);

  REQUIRE(v.size() == 3);
  REQUIRE(v.data());
  REQUIRE(v[1] == 2);
}


TEST_CASE("Vector copy assign.", "[vector]") {
  Vector<int> v {{1234, 2345}};
  Vector<int> w {};

  REQUIRE(w.size() == 0);
  REQUIRE(not w.data());

  w = v;
  REQUIRE(w.size() == 2);
  REQUIRE(w.data());
  REQUIRE(w[0] == 1234);
  REQUIRE(w[1] == 2345);
}

TEST_CASE("Vector set and get elements.", "[vector]") {
  Vector<int> v(2);

  v[0] = 1234;
  v[1] = 2345;

  REQUIRE(v.size() == 2);
  REQUIRE(v.data());
  REQUIRE(v[0] == 1234);
  REQUIRE(v[1] == 2345);
}

TEST_CASE("Vector get constant elements.", "[vector]") {
  Vector<int> const v {{1234, 2345}};

  REQUIRE(v.size() == 2);
  REQUIRE(v.data());
  REQUIRE(v[0] == 1234);
  REQUIRE(v[1] == 2345);
}


TEST_CASE("Vector range loop.", "[vector]") {
  Vector<int> v(2);

  for (int& el: v) {
    el = 1234;
  }
  for (int const& el: v) {
    REQUIRE(el == 1234);
  }
}


TEST_CASE("Vector data.", "[vector]") {
  int* data {new int[3]};
  Vector<int> v(data, 3);

  REQUIRE(v.data() == data);
}

TEST_CASE("Vector size.", "[vector]") {
  Vector<int> v(2);

  REQUIRE(v.size() == 2);
}

TEST_CASE("Vector resize.", "[vector]") {
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

TEST_CASE("Vector clear.", "[vector]") {
  Vector<int> v(2);

  REQUIRE(v.size() == 2);
  REQUIRE(v.data());

  v.clear();
  REQUIRE(v.size() == 0);
  REQUIRE(not v.data());
}

TEST_CASE("Vector push element.", "[vector]") {
  Vector<int> v {};

  REQUIRE(v.size() == 0);
  REQUIRE(not v.data());

  v.push_back(1);
  REQUIRE(v.size() == 1);
  REQUIRE(v.data());
  REQUIRE(v[0] == 1);
}

TEST_CASE("Vector pop element.", "[vector]") {
  Vector<int> v {{1, 2}};

  REQUIRE(v.size() == 2);

  int el {v.pop_back()};
  REQUIRE(v.size() == 1);
  REQUIRE(el == 2);
}


TEST_CASE("Vector return.", "[vector]") {
  struct S {
    static Vector<int> f() {
      Vector<int> v {{1234, 2345}};
      return v;
    }
  };

  Vector<int> v {};
  v = S::f();

  REQUIRE(v[0] == 1234);
}

TEST_CASE("Vector pass by value.", "[vector]") {
  struct S {
    static void f(Vector<int> v) {
      REQUIRE(v.size() == 2);
      REQUIRE(v[0] == 1234);
    }
  };

  Vector<int> v {{1234, 2345}};
  S::f(v);
}
