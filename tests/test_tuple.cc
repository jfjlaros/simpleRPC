#include <catch.hpp>

#include "../src/tuple.tcc"


TEST_CASE("Direct initialisation", "[tuple]") {
  Tuple <char, int>t = {'x', 1};

  REQUIRE(t.head == 'x');
  REQUIRE(t.tail.head == 1);
}

TEST_CASE("Pack values", "[tuple]") {
  Tuple <char, int>t = pack('x', 1);

  REQUIRE(t.head == 'x');
  REQUIRE(t.tail.head == 1);
}

TEST_CASE("Cast struct to tuple", "[tuple]") {
  struct S {
    char c;
    int i;
  };

  S s = {'x', 1};
  Tuple <char, int>t = castStruct<char, int>(s);

  REQUIRE(t.head == 'x');
  REQUIRE(t.tail.head == 1);
}
