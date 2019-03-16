#include <catch.hpp>

#include "../src/read.tcc"


TEST_CASE("Read basic types", "[read]") {
  int i;
  char c;

  Serial.reset();
  Serial.prepare((int)1234);
  Serial.prepare((char)'x');

  _read(&i);
  _read(&c);

  REQUIRE(i == 1234);
  REQUIRE(c == 'x');
}

TEST_CASE("Read string", "[read]") {
  String s;

  Serial.reset();
  Serial.prepare("xyz");

  _read(&s);

  REQUIRE(s == "xyz");
}

TEST_CASE("Read tuple", "[read]") {
  Tuple <int, char>t;

  Serial.reset();
  Serial.prepare((int)1234);
  Serial.prepare((char)'x');

  _read(&t);

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

  _read(&v);

  REQUIRE(v.length == 3);
  REQUIRE(v[0] == 1234);
  REQUIRE(v[1] == 2345);
  REQUIRE(v[2] == 3456);
}

TEST_CASE("Read object", "[read]") {
  Object <int, char>o;

  Serial.reset();
  Serial.prepare((int)1234);
  Serial.prepare((char)'x');

  _read(&o);

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

  _read(&v);

  REQUIRE(v[0][0] == 1234);
  REQUIRE(v[0][1] == 2345);
  REQUIRE(v[1][0] == 3456);
  REQUIRE(v[1][1] == 4567);
}

TEST_CASE("Read complex vector", "[read]") {
  Vector <Object <int, Object<char>>>v;

  Serial.reset();
  Serial.prepare((size_t)2);
  Serial.prepare((int)1234);
  Serial.prepare((char)'x');
  Serial.prepare((int)2345);
  Serial.prepare((char)'y');

  _read(&v);

  REQUIRE(v[0].members.head == 1234);
  REQUIRE(v[0].members.tail.head.members.head == 'x');
  REQUIRE(v[1].members.head == 2345);
  REQUIRE(v[1].members.tail.head.members.head == 'y');
}

TEST_CASE("Read complex object", "[read]") {
  Object <Vector <int>, char>o;

  Serial.reset();
  Serial.prepare((size_t)2);
  Serial.prepare((int)1234);
  Serial.prepare((int)2345);
  Serial.prepare((char)'x');

  _read(&o);

  REQUIRE(o.members.head[0] == 1234);
  REQUIRE(o.members.head[1] == 2345);
  REQUIRE(o.members.tail.head == 'x');
}
