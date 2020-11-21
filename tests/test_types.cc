#include <catch.hpp>

#include <Arduino.h>

#include "../src/types.tcc"
#include "../src/plugins/stream/io.h"

extern HardwareSerialIO io;


TEST_CASE("Basic types 1", "[types][basic]") {
  bool b;
  char c;
  signed char sc;
  unsigned char uc;
  short int si;
  unsigned short int usi;
  long int li;
  unsigned long int uli;
  long long int lli;
  unsigned long long int ulli;
  float f;

  Serial.reset();
  rpcTypeOf(io, b);
  rpcTypeOf(io, c);
  rpcTypeOf(io, sc);
  rpcTypeOf(io, uc);
  rpcTypeOf(io, si);
  rpcTypeOf(io, usi);
  rpcTypeOf(io, li);
  rpcTypeOf(io, uli);
  rpcTypeOf(io, lli);
  rpcTypeOf(io, ulli);
  rpcTypeOf(io, f);
  REQUIRE(Serial.inspect<String>() == "?cbBhHlLqQf");
}

TEST_CASE("Basic types 2", "[types][basic]") {
  int i;
  unsigned int ui;
  double d;

  // Basic types of which the size may differ between platforms.
  Serial.reset();
  rpcTypeOf(io, i);
  rpcTypeOf(io, ui);
  if (sizeof(int) == 2) {
    REQUIRE(Serial.inspect<String>() == "hH");
  }
  else {
    REQUIRE(Serial.inspect<String>() == "iI");
  }

  Serial.reset();
  rpcTypeOf(io, d);
  if (sizeof(double) == 4) {
    REQUIRE(Serial.inspect<String>() == "f");
  }
  else {
    REQUIRE(Serial.inspect<String>() == "d");
  }
}

TEST_CASE("String type", "[types][string]") {
  String s0;
  char* s1;
  char const* s2;

  Serial.reset();
  rpcTypeOf(io, s0);
  rpcTypeOf(io, s1);
  rpcTypeOf(io, s2);
  REQUIRE(Serial.inspect<String>() == "sss");
}

TEST_CASE("Tuple types", "[types][tuple]") {
  Tuple<int, char> ic;
  Tuple<int, signed char, unsigned long> iscul;

  Serial.reset();
  rpcTypeOf(io, ic);
  rpcTypeOf(io, iscul);
  REQUIRE(Serial.inspect<String>() == "icibL");
}

TEST_CASE("Object types", "[types][object]") {
  Object<Object<char, int>, unsigned long> o0;
  Object<
    Object<
      Object<char, char, char>,
      char>,
    char,
    Object<
      Object<char, char>,
      Object<char>>> o1;

  Serial.reset();
  rpcTypeOf(io, o0);
  rpcTypeOf(io, o1);
  REQUIRE(Serial.inspect<String>() == "((ci)L)(((ccc)c)c((cc)(c)))");
}

TEST_CASE("Vector", "[types][vector]") {
  Vector<int> v0;
  Vector<float> v1;
  Vector<signed char> v2;
  Vector<Vector<int>> v3;

  Serial.reset();
  rpcTypeOf(io, v0);
  rpcTypeOf(io, v1);
  rpcTypeOf(io, v2);
  rpcTypeOf(io, v3);
  REQUIRE(Serial.inspect<String>() == "[i][f][b][[i]]");
}

TEST_CASE("Complex tuple types", "[types][tuple][complex]") {
  Tuple<Vector<int>, char> t0;
  Tuple<Tuple<int, char>, Tuple<unsigned char, float>> t1;
  Tuple<Object<int, char>, Vector<int>> t2;

  Serial.reset();
  rpcTypeOf(io, t0);
  rpcTypeOf(io, t1);
  rpcTypeOf(io, t2);
  REQUIRE(Serial.inspect<String>() == "[i]cicBf(ic)[i]");
}

TEST_CASE("Complex object types", "[types][object][complex]") {
  Object<Vector<Object<int, char>>, Object<float>> o0;
  Object<Tuple<int, char>, Object<char>> o1;

  Serial.reset();
  rpcTypeOf(io, o0);
  rpcTypeOf(io, o1);
  REQUIRE(Serial.inspect<String>() == "([(ic)](f))(ic(c))");
}

TEST_CASE("Complex vector types", "[types][vector][complex]") {
  Vector<Tuple<int, char>> v0;
  Vector<Object<int, Vector<char>>> v1;
  Vector<Tuple<char, Object<int, char>>> v2;

  Serial.reset();
  rpcTypeOf(io, v0);
  rpcTypeOf(io, v1);
  rpcTypeOf(io, v2);
  REQUIRE(Serial.inspect<String>() == "[ic][(i[c])][c(ic)]");
}
