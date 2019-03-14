#include <catch.hpp>

#include "../src/write.tcc"


TEST_CASE("Write basic types", "[write]") {
  int i = 1234;
  char c = 'x';

  Serial.reset();

  _write(i);
  _write(c);

  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<char>() == 'x');
}

TEST_CASE("Write tuple", "[write]") {
  Tuple <int, char>t = {1234, 'x'};

  Serial.reset();

  _write(t);

  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<char>() == 'x');
}

TEST_CASE("Write vector", "[write]") {
  Vector <int>v;

  v.length = 2;
  v.data = (int *)malloc(2 * sizeof(int));
  v.data[0] = 1234;
  v.data[1] = 2345;

  Serial.reset();

  _write(v);

  REQUIRE(Serial.inspect<size_t>() == 2);
  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<int>() == 2345);

  free(v.data);
}

TEST_CASE("Write object", "[write]") {
  Object <int, char>o;

  o.members.head = 1234;
  o.members.tail.head = 'x';

  Serial.reset();

  _write(o);

  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<char>() == 'x');
}

TEST_CASE("Write nested vector", "[write]") {
  Vector <Vector <int>>v;

  v.length = 2;
  v.data = (Vector <int> *)malloc(2 * sizeof(Vector <int>));
  v.data[0].length = 2;
  v.data[0].data = (int *)malloc(2 * sizeof(int));
  v.data[0].data[0] = 1234;
  v.data[0].data[1] = 2345;
  v.data[1].length = 2;
  v.data[1].data = (int *)malloc(2 * sizeof(int));
  v.data[1].data[0] = 3456;
  v.data[1].data[1] = 4567;

  Serial.reset();

  _write(v);

  REQUIRE(Serial.inspect<size_t>() == 2);
  REQUIRE(Serial.inspect<size_t>() == 2);
  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<int>() == 2345);
  REQUIRE(Serial.inspect<size_t>() == 2);
  REQUIRE(Serial.inspect<int>() == 3456);
  REQUIRE(Serial.inspect<int>() == 4567);

  free(v.data[0].data);
  free(v.data[1].data);
  free(v.data);
}

TEST_CASE("Write complex vector", "[write]") {
  Vector <Object <int, Object<char>>>v;

  v.length = 2;
  v.data = (Object <int, Object<char>> *)malloc(
    2 * sizeof(Object <int, Object<char>>));
  v.data[0].members.head = 1234;
  v.data[0].members.tail.head.members.head = 'x';
  v.data[1].members.head = 2345;
  v.data[1].members.tail.head.members.head = 'y';

  Serial.reset();

  _write(v);

  REQUIRE(Serial.inspect<size_t>() == 2);
  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<char>() == 'x');
  REQUIRE(Serial.inspect<int>() == 2345);
  REQUIRE(Serial.inspect<char>() == 'y');

  free(v.data);
}

TEST_CASE("Write complex object", "[write]") {
  Object <Vector <int>, char>o;

  o.members.head.length = 2;
  o.members.head.data = (int *)malloc(2 * sizeof(int));
  o.members.head.data[0] = 1234;
  o.members.head.data[1] = 2345;
  o.members.tail.head = 'x';

  Serial.reset();

  _write(o);

  REQUIRE(Serial.inspect<size_t>() == 2);
  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<int>() == 2345);
  REQUIRE(Serial.inspect<char>() == 'x');

  free(o.members.head.data);
}
