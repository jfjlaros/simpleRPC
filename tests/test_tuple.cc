#include <catch.hpp>

#include "../src/tuple.tcc"


TEST_CASE("Tuple initialiser list", "[tuple]") {
  Tuple<char, int> t = {'x', 1};

  REQUIRE(t.head == 'x');
  REQUIRE(t.tail.head == 1);
}

TEST_CASE("Tuple read by index", "[tuple]") {
  Tuple<char, int> t;

  t.head = 'x';
  t.tail.head = 1;

  REQUIRE(get<0>(t) == 'x');
  REQUIRE(get<1>(t) == 1);
}

TEST_CASE("Tuple write by index", "[tuple]") {
  Tuple<char, int> t;

  get<0>(t) = 'x';
  get<1>(t) = 1;

  REQUIRE(t.head == 'x');
  REQUIRE(t.tail.head == 1);
}

TEST_CASE("Object initialiser list", "[object]") {
  Object<char, int> o = {'x', 1};

  REQUIRE(o.head == 'x');
  REQUIRE(o.tail.head == 1);
}

TEST_CASE("Object constructor", "[object]") {
  Object<char, int> o('x', 1);

  REQUIRE(o.head == 'x');
  REQUIRE(o.tail.head == 1);
}

TEST_CASE("Object read by index", "[object]") {
  Object<char, int> o;

  o.head = 'x';
  o.tail.head = 1;

  REQUIRE(get<0>(o) == 'x');
  REQUIRE(get<1>(o) == 1);
}

TEST_CASE("Object write by index", "[object]") {
  Object<char, int> o;

  get<0>(o) = 'x';
  get<1>(o) = 1;

  REQUIRE(o.head == 'x');
  REQUIRE(o.tail.head == 1);
}

TEST_CASE("Pack values", "[tuple]") {
  Tuple<char, int> t = pack('x', 1);

  REQUIRE(t.head == 'x');
  REQUIRE(t.tail.head == 1);
}

TEST_CASE("Cast struct to tuple", "[tuple]") {
  struct S {
    char c;
    int i;
  };

  S s = {'x', 1};
  Tuple<char, int> t = castStruct<char, int>(s);

  REQUIRE(t.head == 'x');
  REQUIRE(t.tail.head == 1);
}
