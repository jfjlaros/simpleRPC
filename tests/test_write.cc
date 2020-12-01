#include <catch.hpp>

#include "../src/write.tcc"

extern Stream Serial;


TEST_CASE("Write basic types", "[write][basic]") {
  int i = 1234;
  char c = 'x';

  Serial.reset();
  rpcWrite(Serial, &i);
  rpcWrite(Serial, &c);
  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<char>() == 'x');
}

TEST_CASE("Write String", "[write][string]") {
  String s = "xyz";

  Serial.reset();
  rpcWrite(Serial, &s);
  REQUIRE(Serial.inspect<String>() == "xyz");
}

TEST_CASE("Write C string of type char*", "[write][string]") {
  char* s = (char*)"xyz";

  Serial.reset();
  rpcWrite(Serial, &s);
  REQUIRE(Serial.inspect<String>() == "xyz");
}

TEST_CASE("Write C string of type char const*", "[write][string]") {
  char const* s = "xyz";

  Serial.reset();
  rpcWrite(Serial, &s);
  REQUIRE(Serial.inspect<String>() == "xyz");
}

TEST_CASE("Write tuple", "[write][tuple]") {
  Tuple<int, char> t = {1234, 'x'};

  Serial.reset();
  rpcWrite(Serial, &t);
  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<char>() == 'x');
}


TEST_CASE("Write object", "[write][object]") {
  Object<int, char> o;

  o.head = 1234;
  o.tail.head = 'x';

  Serial.reset();
  rpcWrite(Serial, &o);
  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<char>() == 'x');
}
TEST_CASE("Write vector", "[write][vector]") {
  Vector<int> v(2);

  v[0] = 1234;
  v[1] = 2345;

  Serial.reset();
  rpcWrite(Serial, &v);
  REQUIRE(Serial.inspect<size_t>() == 2);
  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<int>() == 2345);
}

TEST_CASE("Write complex tuple", "[write][tuple][complex]") {
  Tuple<Vector<int>, char> t;

  t.head.resize(2);
  t.head[0] = 1234;
  t.head[1] = 2345;
  t.tail.head = 'x';

  Serial.reset();
  rpcWrite(Serial, &t);
  REQUIRE(Serial.inspect<size_t>() == 2);
  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<int>() == 2345);
  REQUIRE(Serial.inspect<char>() == 'x');
}

TEST_CASE("Write complex object", "[write][object][complex]") {
  Object<Vector<int>, char> o;

  o.head.resize(2);
  o.head[0] = 1234;
  o.head[1] = 2345;
  o.tail.head = 'x';

  Serial.reset();
  rpcWrite(Serial, &o);
  REQUIRE(Serial.inspect<size_t>() == 2);
  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<int>() == 2345);
  REQUIRE(Serial.inspect<char>() == 'x');
}

TEST_CASE("Write nested vector", "[write][vector][complex]") {
  Vector<Vector<int>> v(2);

  v[0].resize(2);
  v[0][0] = 1234;
  v[0][1] = 2345;
  v[1].resize(2);
  v[1][0] = 3456;
  v[1][1] = 4567;

  Serial.reset();
  rpcWrite(Serial, &v);
  REQUIRE(Serial.inspect<size_t>() == 2);
  REQUIRE(Serial.inspect<size_t>() == 2);
  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<int>() == 2345);
  REQUIRE(Serial.inspect<size_t>() == 2);
  REQUIRE(Serial.inspect<int>() == 3456);
  REQUIRE(Serial.inspect<int>() == 4567);
}

TEST_CASE("Write complex vector", "[write][vector][complex]") {
  Vector<Object<int, Object<char>>> v(2);

  v[0].head = 1234;
  v[0].tail.head.head = 'x';
  v[1].head = 2345;
  v[1].tail.head.head = 'y';

  Serial.reset();
  rpcWrite(Serial, &v);
  REQUIRE(Serial.inspect<size_t>() == 2);
  REQUIRE(Serial.inspect<int>() == 1234);
  REQUIRE(Serial.inspect<char>() == 'x');
  REQUIRE(Serial.inspect<int>() == 2345);
  REQUIRE(Serial.inspect<char>() == 'y');
}
