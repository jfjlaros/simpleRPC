#include <catch.hpp>

#include "../src/tuple.tcc"


TEST_CASE("Direct initialisation", "[tuple]") {
  Tuple <char, int>t = {'x', 1};

  REQUIRE(t.head == 'x');
  REQUIRE(t.tail.head == 1);
}

TEST_CASE("Indexing 1", "[tuple]") {
  Tuple <char, int>t;

  t.head = 'x';
  t.tail.head = 1;

  REQUIRE(t.get<char>(0) == 'x');
  REQUIRE(t.get<int>(1) == 1);
}

TEST_CASE("Indexing 2", "[tuple]") {
  Tuple <char, int>t;

  t.get<char>(0) = 'x';
  t.get<int>(1) = 1;

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
