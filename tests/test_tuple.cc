#include <catch.hpp>

#include "../src/tuple.tcc"


TEST_CASE("Tuple initialisation.", "[tuple]") {
  Tuple<char, int> t {'x', 1};

  REQUIRE(t.head == 'x');
  REQUIRE(t.tail.head == 1);
}

TEST_CASE("Tuple read by index.", "[tuple]") {
  Tuple<char, int> t {};

  t.head = 'x';
  t.tail.head = 1;

  REQUIRE(get<0>(t) == 'x');
  REQUIRE(get<1>(t) == 1);
}

TEST_CASE("Tuple write by index.", "[tuple]") {
  Tuple<char, int> t {};

  get<0>(t) = 'x';
  get<1>(t) = 1;

  REQUIRE(t.head == 'x');
  REQUIRE(t.tail.head == 1);
}

TEST_CASE("Make a temporary Tuple.", "[tuple]") {
  Tuple<char, int> t {makeTuple('x', 1)};

  REQUIRE(t.head == 'x');
  REQUIRE(t.tail.head == 1);
}
