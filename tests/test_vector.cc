#include <catch.hpp>

#include "../src/vector.tcc"


TEST_CASE("Initialisation.", "[vector]") {
  Vector <int>v;

  REQUIRE(v.size == 0);
}

TEST_CASE("Set size.", "[vector]") {
  Vector <int>v;

  v.resize(2);

  REQUIRE(v.size == 2);
}

TEST_CASE("Set and get elements.", "[vector]") {
  Vector <int>v;

  v.resize(2);
  v[0] = 1234;
  v[1] = 2345;

  REQUIRE(v.size == 2);
  REQUIRE(v[0] == 1234);
  REQUIRE(v[1] == 2345);
}
