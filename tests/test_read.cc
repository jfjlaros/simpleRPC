#include <catch.hpp>

#include "../src/read.tcc"

extern Stream Serial;


TEST_CASE("Read basic types", "[read][basic]") {
  int i;
  char c;

  Serial.reset();
  Serial.prepare(1234, 'x');
  rpcRead(Serial, &i);
  rpcRead(Serial, &c);
  REQUIRE(i == 1234);
  REQUIRE(c == 'x');
}

TEST_CASE("Read String", "[read][string]") {
  Serial.reset();
  Serial.prepare(4ul, "xyz");

  String s;
  rpcRead(Serial, &s);
  REQUIRE(not strcmp(s.c_str(), "xyz"));
}

TEST_CASE("Read tuple", "[read][tuple]") {
  Tuple<int, char> t;

  Serial.reset();
  Serial.prepare(1234, 'x');
  rpcRead(Serial, &t);
  REQUIRE(t.head == 1234);
  REQUIRE(t.tail.head == 'x');
}

TEST_CASE("Read vector", "[read][vector]") {
  Vector<int> v;

  Serial.reset();
  Serial.prepare(3ul, 1234, 2345, 3456);
  rpcRead(Serial, &v);
  REQUIRE(v.size() == 3);
  REQUIRE(v[0] == 1234);
  REQUIRE(v[1] == 2345);
  REQUIRE(v[2] == 3456);
}

TEST_CASE("Read array", "[read][array]") {
  Array<int, 3> a;

  Serial.reset();
  Serial.prepare(3ul, 1234, 2345, 3456);
  rpcRead(Serial, &a);
  REQUIRE(a.size() == 3);
  REQUIRE(a[0] == 1234);
  REQUIRE(a[1] == 2345);
  REQUIRE(a[2] == 3456);
}

TEST_CASE("Read complex tuple", "[read][tuple][complex]") {
  Tuple<Vector<int>, char> t;

  Serial.reset();
  Serial.prepare(2ul, 1234, 2345, 'x');
  rpcRead(Serial, &t);
  REQUIRE(t.head[0] == 1234);
  REQUIRE(t.head[1] == 2345);
  REQUIRE(t.tail.head == 'x');
}

TEST_CASE("Read nested vector", "[read][vector][complex]") {
  Vector<Vector<int>> v;

  Serial.reset();
  Serial.prepare(2ul, 2ul, 1234, 2345, 2ul, 3456, 4567);
  rpcRead(Serial, &v);
  REQUIRE(v[0][0] == 1234);
  REQUIRE(v[0][1] == 2345);
  REQUIRE(v[1][0] == 3456);
  REQUIRE(v[1][1] == 4567);
}

TEST_CASE("Read complex vector", "[read][vector][complex]") {
  Vector<Tuple<int, Tuple<char>>> v;

  Serial.reset();
  Serial.prepare(2ul, 1234, 'x', 2345, 'y');
  rpcRead(Serial, &v);
  REQUIRE(v[0].head == 1234);
  REQUIRE(v[0].tail.head.head == 'x');
  REQUIRE(v[1].head == 2345);
  REQUIRE(v[1].tail.head.head == 'y');
}
