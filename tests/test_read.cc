#include <catch.hpp>

#include "../src/del.tcc"
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
  String s;

  Serial.reset();
  Serial.prepare("xyz");
  rpcRead(Serial, &s);
  REQUIRE(s == "xyz");
}

TEST_CASE("Read string of type char*", "[read][string]") {
  char* s;

  Serial.reset();
  Serial.prepare("xyz");
  rpcRead(Serial, &s);
  REQUIRE((String)s == "xyz");
  rpcDel(&s);
}

TEST_CASE("Read string of type char const*", "[read][string]") {
  char const* s;

  Serial.reset();
  Serial.prepare("xyz");
  rpcRead(Serial, &s);
  REQUIRE((String)s == "xyz");
  rpcDel(&s);
}

TEST_CASE("Read tuple", "[read][tuple]") {
  Tuple<int, char> t;

  Serial.reset();
  Serial.prepare(1234, 'x');
  rpcRead(Serial, &t);
  REQUIRE(t.head == 1234);
  REQUIRE(t.tail.head == 'x');
}

TEST_CASE("Read object", "[read][object]") {
  Object<int, char> o;

  Serial.reset();
  Serial.prepare(1234, 'x');
  rpcRead(Serial, &o);
  REQUIRE(o.head == 1234);
  REQUIRE(o.tail.head == 'x');
}

TEST_CASE("Read vector", "[read][vector]") {
  Vector<int> v;

  Serial.reset();
  Serial.prepare((size_t)3, 1234, 2345, 3456);
  rpcRead(Serial, &v);
  REQUIRE(v.size == 3);
  REQUIRE(v[0] == 1234);
  REQUIRE(v[1] == 2345);
  REQUIRE(v[2] == 3456);
}

TEST_CASE("Read complex tuple", "[read][tuple][complex]") {
  Tuple<Vector<int>, char> t;

  Serial.reset();
  Serial.prepare((size_t)2, 1234, 2345, 'x');
  rpcRead(Serial, &t);
  REQUIRE(t.head[0] == 1234);
  REQUIRE(t.head[1] == 2345);
  REQUIRE(t.tail.head == 'x');
}

TEST_CASE("Read complex object", "[read][object][complex]") {
  Object<Vector<int>, char> o;

  Serial.reset();
  Serial.prepare((size_t)2, 1234, 2345, 'x');
  rpcRead(Serial, &o);
  REQUIRE(o.head[0] == 1234);
  REQUIRE(o.head[1] == 2345);
  REQUIRE(o.tail.head == 'x');
}

TEST_CASE("Read nested vector", "[read][vector][complex]") {
  Vector<Vector<int>> v;

  Serial.reset();
  Serial.prepare((size_t)2, (size_t)2, 1234, 2345, (size_t)2, 3456, 4567);
  rpcRead(Serial, &v);
  REQUIRE(v[0][0] == 1234);
  REQUIRE(v[0][1] == 2345);
  REQUIRE(v[1][0] == 3456);
  REQUIRE(v[1][1] == 4567);
}

TEST_CASE("Read complex vector", "[read][vector][complex]") {
  Vector<Object<int, Object<char>>> v;

  Serial.reset();
  Serial.prepare((size_t)2, 1234, 'x', 2345, 'y');
  rpcRead(Serial, &v);
  REQUIRE(v[0].head == 1234);
  REQUIRE(v[0].tail.head.head == 'x');
  REQUIRE(v[1].head == 2345);
  REQUIRE(v[1].tail.head.head == 'y');
}
