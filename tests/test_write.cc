#include <catch.hpp>

#include "../src/write.tcc"


TEST_CASE("Write basic types", "[write]") {
  int i = 1234;
  char c = 'x';

  Serial.reset();

  _write(&i);
  _write(&c);

  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<char>() == 'x');
}

TEST_CASE("Write string", "[write]") {
  String s = "xyz";

  Serial.reset();

  _write(&s);

  REQUIRE(Serial.inspect<String>() == "xyz");
}

TEST_CASE("Write tuple", "[write]") {
  Tuple <int, char>t = {1234, 'x'};

  Serial.reset();

  _write(&t);

  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<char>() == 'x');
}

TEST_CASE("Write vector", "[write]") {
  Vector <int>v;

  v.setLength(2);
  v[0] = 1234;
  v[1] = 2345;

  Serial.reset();

  _write(&v);

  REQUIRE(Serial.inspect<size_t>() == 2);
  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<int>() == 2345);
}

TEST_CASE("Write object", "[write]") {
  Object <int, char>o;

  o.members.head = 1234;
  o.members.tail.head = 'x';

  Serial.reset();

  _write(&o);

  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<char>() == 'x');
}

TEST_CASE("Write nested vector", "[write]") {
  Vector <Vector <int>>v;

  v.setLength(2);
  v[0].setLength(2);
  v[0][0] = 1234;
  v[0][1] = 2345;
  v[1].setLength(2);
  v[1][0] = 3456;
  v[1][1] = 4567;

  Serial.reset();

  _write(&v);

  REQUIRE(Serial.inspect<size_t>() == 2);
  REQUIRE(Serial.inspect<size_t>() == 2);
  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<int>() == 2345);
  REQUIRE(Serial.inspect<size_t>() == 2);
  REQUIRE(Serial.inspect<int>() == 3456);
  REQUIRE(Serial.inspect<int>() == 4567);
}

TEST_CASE("Write complex vector", "[write]") {
  Vector <Object <int, Object<char>>>v;

  v.setLength(2);
  v[0].members.head = 1234;
  v[0].members.tail.head.members.head = 'x';
  v[1].members.head = 2345;
  v[1].members.tail.head.members.head = 'y';

  Serial.reset();

  _write(&v);

  REQUIRE(Serial.inspect<size_t>() == 2);
  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<char>() == 'x');
  REQUIRE(Serial.inspect<int>() == 2345);
  REQUIRE(Serial.inspect<char>() == 'y');
}

TEST_CASE("Write complex object", "[write]") {
  Object <Vector <int>, char>o;

  o.members.head.setLength(2);
  o.members.head[0] = 1234;
  o.members.head[1] = 2345;
  o.members.tail.head = 'x';

  Serial.reset();

  _write(&o);

  REQUIRE(Serial.inspect<size_t>() == 2);
  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<int>() == 2345);
  REQUIRE(Serial.inspect<char>() == 'x');
}
