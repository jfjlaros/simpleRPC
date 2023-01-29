#include <catch.hpp>

#include "../src/span.tcc"


TEST_CASE("Span initialisation.", "[span]") {
  int data[] {1, 2, 3};
  Span<int> s {data};

  REQUIRE(s.size() == 3);
  REQUIRE(s[1] == 2);
}

TEST_CASE("Span set and get elements.", "[span]") {
  int data[2] {};
  Span<int> s {data};

  data[0] = 1234;
  data[1] = 2345;

  REQUIRE(s.size() == 2);
  REQUIRE(s[0] == 1234);
  REQUIRE(s[1] == 2345);
}

TEST_CASE("Span get constant elements.", "[span]") {
  int const data[] {1234, 2345};
  Span<int const> const s {data};

  REQUIRE(s.size() == 2);
  REQUIRE(s[0] == 1234);
  REQUIRE(s[1] == 2345);
}


TEST_CASE("Span range loop.", "[span]") {
  int data[2] {};
  Span<int> s {data};

  for (int& el: s) {
    el = 1234;
  }
  for (int const& el: s) {
    REQUIRE(el == 1234);
  }
}


TEST_CASE("Span data.", "[span]") {
  int data[2] {};
  Span<int> s {data};

  REQUIRE(s.data() == data);
}

TEST_CASE("Span size.", "[span]") {
  int data[2] {};
  Span<int> s {data};

  REQUIRE(s.size() == 2);
}


TEST_CASE("Span return.", "[span]") {
  struct S {
    static Span<int> f() {
      static int data[] {1234, 2345};
      Span<int> s {data};
      return s;
    }
  };

  Span<int> s {};
  s = S::f();

  REQUIRE(s[0] == 1234);
}

TEST_CASE("Span pass by value.", "[span]") {
  struct S {
    static void f(Span<int> s) {
      REQUIRE(s.size() == 2);
      REQUIRE(s[0] == 1234);
    }
  };

  int data[] {1234, 2345};
  Span<int> s {data};
  S::f(s);
}
