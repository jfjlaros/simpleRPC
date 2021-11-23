#include <catch.hpp>

#include "../src/tuple.tcc"


TEST_CASE("Internal tuple initialiser list", "[tuple]") {
  _Tuple<char, int> t = {'x', 1};

  REQUIRE(t.head == 'x');
  REQUIRE(t.tail.head == 1);
}

TEST_CASE("Internal tuple read by index", "[tuple]") {
  _Tuple<char, int> t;

  t.head = 'x';
  t.tail.head = 1;

  REQUIRE(get<0>(t) == 'x');
  REQUIRE(get<1>(t) == 1);
}

TEST_CASE("Internal tuple write by index", "[tuple]") {
  _Tuple<char, int> t;

  get<0>(t) = 'x';
  get<1>(t) = 1;

  REQUIRE(t.head == 'x');
  REQUIRE(t.tail.head == 1);
}

TEST_CASE("Tuple initialiser list", "[tuple]") {
  Tuple<char, int> o = {'x', 1};

  REQUIRE(o.head == 'x');
  REQUIRE(o.tail.head == 1);
}

TEST_CASE("Tuple constructor", "[tuple]") {
  Tuple<char, int> o('x', 1);

  REQUIRE(o.head == 'x');
  REQUIRE(o.tail.head == 1);
}

TEST_CASE("Tuple read by index", "[tuple]") {
  Tuple<char, int> o;

  o.head = 'x';
  o.tail.head = 1;

  REQUIRE(get<0>(o) == 'x');
  REQUIRE(get<1>(o) == 1);
}

TEST_CASE("Tuple write by index", "[tuple]") {
  Tuple<char, int> o;

  get<0>(o) = 'x';
  get<1>(o) = 1;

  REQUIRE(o.head == 'x');
  REQUIRE(o.tail.head == 1);
}

TEST_CASE("Pack values", "[tuple]") {
  _Tuple<char, int> t = pack('x', 1);

  REQUIRE(t.head == 'x');
  REQUIRE(t.tail.head == 1);
}

TEST_CASE("Cast struct to internal tuple", "[tuple]") {
  struct S {
    char c;
    int i;
  };

  S s = {'x', 1};
  _Tuple<char, int> t = castStruct<char, int>(s);

  REQUIRE(t.head == 'x');
  REQUIRE(t.tail.head == 1);
}
