#include <catch.hpp>

#include "../src/vector.tcc"


TEST_CASE("Initialisation, no parameters.", "[vector]") {
  Vector<int> v;

  REQUIRE(v.size == 0);
}

TEST_CASE("Initialisation, size parameter.", "[vector]") {
  Vector<int> v(1);

  REQUIRE(v.size == 1);
}

TEST_CASE("Initialisation, pointer parameter.", "[vector]") {
  int* data = (int*)malloc(sizeof(int) * 10);
  Vector<int> v(10, data);

  REQUIRE(v.size == 10);
}

TEST_CASE("Initialisation, pointer parameter, no free.", "[vector]") {
  int* data = (int*)malloc(sizeof(int) * 10);
  Vector<int> v(10, data, false);

  REQUIRE(v.size == 10);
  free(data);
}

TEST_CASE("Resize.", "[vector]") {
  Vector<int> v(5);
  int i;

  for (i = 0; i < 5; i++) {
    v[i] = i;
  }

  v.resize(10);
  REQUIRE(v.size == 10);
  REQUIRE(v[4] == 4);

  v.resize(2);
  REQUIRE(v.size == 2);
  REQUIRE(v[1] == 1);
}

TEST_CASE("Set and get elements.", "[vector]") {
  Vector<int> v(2);

  v[0] = 1234;
  v[1] = 2345;

  REQUIRE(v.size == 2);
  REQUIRE(v[0] == 1234);
  REQUIRE(v[1] == 2345);
}
