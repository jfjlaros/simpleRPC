#include <catch.hpp>

#include <Arduino.h>

#include "../src/types.tcc"


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

  REQUIRE(rpcTypeOf(b) == "?");
  REQUIRE(rpcTypeOf(c) == "c");
  REQUIRE(rpcTypeOf(sc) == "b");
  REQUIRE(rpcTypeOf(uc) == "B");
  REQUIRE(rpcTypeOf(si) == "h");
  REQUIRE(rpcTypeOf(usi) == "H");
  REQUIRE(rpcTypeOf(li) == "l");
  REQUIRE(rpcTypeOf(uli) == "L");
  REQUIRE(rpcTypeOf(lli) == "q");
  REQUIRE(rpcTypeOf(ulli) == "Q");
  REQUIRE(rpcTypeOf(f) == "f");
}

TEST_CASE("Basic types 2", "[types][basic]") {
  int i;
  unsigned int ui;
  double d;

  // Basic types of which the size may differ between platforms.
  if (sizeof(int) == 2) {
    REQUIRE(rpcTypeOf(i) == "h");
    REQUIRE(rpcTypeOf(ui) == "H");
  }
  else {
    REQUIRE(rpcTypeOf(i) == "i");
    REQUIRE(rpcTypeOf(ui) == "I");
  }
  if (sizeof(double) == 4) {
    REQUIRE(rpcTypeOf(d) == "f");
  }
  else {
    REQUIRE(rpcTypeOf(d) == "d");
  }
}

TEST_CASE("String type", "[types][string]") {
  String s0;
  char* s1;
  const char* s2;

  REQUIRE(rpcTypeOf(s0) == "s");
  REQUIRE(rpcTypeOf(s1) == "s");
  REQUIRE(rpcTypeOf(s2) == "s");
}

TEST_CASE("Tuple types", "[types][tuple]") {
  Tuple<int, char> ic;
  Tuple<int, signed char, unsigned long> iscul;

  REQUIRE(rpcTypeOf(ic) == "ic");
  REQUIRE(rpcTypeOf(iscul) == "ibL");
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

  REQUIRE(rpcTypeOf(o0) == "((ci)L)");
  REQUIRE(rpcTypeOf(o1) == "(((ccc)c)c((cc)(c)))");
}

TEST_CASE("Vector", "[types][vector]") {
  Vector<int> v0;
  Vector<float> v1;
  Vector<signed char> v2;
  Vector<Vector<int>> v3;

  REQUIRE(rpcTypeOf(v0) == "[i]");
  REQUIRE(rpcTypeOf(v1) == "[f]");
  REQUIRE(rpcTypeOf(v2) == "[b]");
  REQUIRE(rpcTypeOf(v3) == "[[i]]");
}

TEST_CASE("Complex tuple types", "[types][tuple][complex]") {
  Tuple<Vector<int>, char> t0;
  Tuple<Tuple<int, char>, Tuple<unsigned char, float>> t1;
  Tuple<Object<int, char>, Vector<int>> t2;

  REQUIRE(rpcTypeOf(t0) == "[i]c");
  REQUIRE(rpcTypeOf(t1) == "icBf");
  REQUIRE(rpcTypeOf(t2) == "(ic)[i]");
}

TEST_CASE("Complex object types", "[types][object][complex]") {
  Object<Vector<Object<int, char>>, Object<float>> o0;
  Object<Tuple<int, char>, Object<char>> o1;

  REQUIRE(rpcTypeOf(o0) == "([(ic)](f))");
  REQUIRE(rpcTypeOf(o1) == "(ic(c))");
}

TEST_CASE("Complex vector types", "[types][vector][complex]") {
  Vector<Tuple<int, char>> v0;
  Vector<Object<int, Vector<char>>> v1;
  Vector<Tuple<char, Object<int, char>>> v2;

  REQUIRE(rpcTypeOf(v0) == "[ic]");
  REQUIRE(rpcTypeOf(v1) == "[(i[c])]");
  REQUIRE(rpcTypeOf(v2) == "[c(ic)]");
}
