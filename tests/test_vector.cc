#include <catch.hpp>

#include "../src/vector.tcc"


TEST_CASE("Initialisation.", "[vector]") {
  Vector <int>v;

  REQUIRE(v.length == 0);
}

TEST_CASE("Set length.", "[vector]") {
  Vector <int>v;

  v.setLength(2);

  REQUIRE(v.length == 2);
}

TEST_CASE("Set and get elements.", "[vector]") {
  Vector <int>v;

  v.setLength(2);
  v[0] = 1234;
  v[1] = 2345;

  REQUIRE(v.length == 2);
  REQUIRE(v[0] == 1234);
  REQUIRE(v[1] == 2345);
}
