#include <catch.hpp>

#include "../src/read.tcc"


TEST_CASE("Read basic types", "[read]") {
  int i;
  char c;

  Serial.reset();
  Serial.prepare((int)1234);
  Serial.prepare((char)'x');

  REQUIRE(_read(i) == 1234);
  REQUIRE(_read(c) == 'x');
}

TEST_CASE("Read tuple", "[read]") {
  Tuple <int, char>t;

  Serial.reset();
  Serial.prepare((int)1234);
  Serial.prepare((char)'x');

  t = _read(t);

  REQUIRE(t.head == 1234);
  REQUIRE(t.tail.head == 'x');
}

TEST_CASE("Read vector", "[read]") {
  Vector <int>v;

  Serial.reset();
  Serial.prepare((size_t)3);
  Serial.prepare((int)1234);
  Serial.prepare((int)2345);
  Serial.prepare((int)3456);

  v = _read(v);

  REQUIRE(v.length == 3);
  REQUIRE(v.data[0] == 1234);
  REQUIRE(v.data[1] == 2345);
  REQUIRE(v.data[2] == 3456);

  free(v.data);
}

TEST_CASE("Read object", "[read]") {
  Object <int, char>o;

  Serial.reset();
  Serial.prepare((int)1234);
  Serial.prepare((char)'x');

  o = _read(o);

  REQUIRE(o.members.head == 1234);
  REQUIRE(o.members.tail.head == 'x');
}

TEST_CASE("Read nested vector", "[read]") {
  Vector <Vector <int>>v;

  Serial.reset();
  Serial.prepare((size_t)2);
  Serial.prepare((size_t)2);
  Serial.prepare((int)1234);
  Serial.prepare((int)2345);
  Serial.prepare((size_t)2);
  Serial.prepare((int)3456);
  Serial.prepare((int)4567);

  v = _read(v);

  REQUIRE(v.data[0].data[0] == 1234);
  REQUIRE(v.data[0].data[1] == 2345);
  REQUIRE(v.data[1].data[0] == 3456);
  REQUIRE(v.data[1].data[1] == 4567);

  free(v.data[0].data);
  free(v.data[1].data);
  free(v.data);
}

TEST_CASE("Read complex vector", "[read]") {
  Vector <Object <int, Object<char>>>v;

  Serial.reset();
  Serial.prepare((size_t)2);
  Serial.prepare((int)1234);
  Serial.prepare((char)'x');
  Serial.prepare((int)2345);
  Serial.prepare((char)'y');

  v = _read(v);

  REQUIRE(v.data[0].members.head == 1234);
  REQUIRE(v.data[0].members.tail.head.members.head == 'x');
  REQUIRE(v.data[1].members.head == 2345);
  REQUIRE(v.data[1].members.tail.head.members.head == 'y');

  free(v.data);
}

TEST_CASE("Read complex object", "[read]") {
  Object <Vector <int>, char>o;

  Serial.reset();
  Serial.prepare((size_t)2);
  Serial.prepare((int)1234);
  Serial.prepare((int)2345);
  Serial.prepare((char)'x');

  o = _read(o);

  REQUIRE(o.members.head.data[0] == 1234);
  REQUIRE(o.members.head.data[1] == 2345);
  REQUIRE(o.members.tail.head == 'x');

  free(o.members.head.data);
}
