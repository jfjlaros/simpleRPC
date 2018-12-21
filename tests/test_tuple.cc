#include <catch.hpp>

#include "../simpleRPC/tuple.tcc"


TEST_CASE("Direct initialisation", "[tuple]") {
  Tuple <char, int>t = {'x', 1};

  // Using an initialisation list.
  REQUIRE(t.head == 'x');
  REQUIRE(t.tail.head == 1);
}

TEST_CASE("Pack values", "[tuple]") {
  Tuple <char, int>t = pack('x', 1);

  // Using the pack() function.
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

  // Using the castStruct() function.
  REQUIRE(t.head == 'x');
  REQUIRE(t.tail.head == 1);
}
