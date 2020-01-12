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

  REQUIRE(typeof(b) == "?");
  REQUIRE(typeof(c) == "c");
  REQUIRE(typeof(sc) == "b");
  REQUIRE(typeof(uc) == "B");
  REQUIRE(typeof(si) == "h");
  REQUIRE(typeof(usi) == "H");
  REQUIRE(typeof(li) == "l");
  REQUIRE(typeof(uli) == "L");
  REQUIRE(typeof(lli) == "q");
  REQUIRE(typeof(ulli) == "Q");
  REQUIRE(typeof(f) == "f");
}

TEST_CASE("Basic types 2", "[types][basic]") {
  int i;
  unsigned int ui;
  double d;

  // Basic types of which the size may differ between platforms.
  if (sizeof(int) == 2) {
    REQUIRE(typeof(i) == "h");
    REQUIRE(typeof(ui) == "H");
  }
  else {
    REQUIRE(typeof(i) == "i");
    REQUIRE(typeof(ui) == "I");
  }
  if (sizeof(double) == 4) {
    REQUIRE(typeof(d) == "f");
  }
  else {
    REQUIRE(typeof(d) == "d");
  }
}

TEST_CASE("String type", "[types][string]") {
  String s;

  REQUIRE(typeof(s) == "s");
}

TEST_CASE("Tuple types", "[types][tuple]") {
  Tuple<int, char> ic;
  Tuple<int, signed char, unsigned long> iscul;

  REQUIRE(typeof(ic) == "ic");
  REQUIRE(typeof(iscul) == "ibL");
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

  REQUIRE(typeof(o0) == "((ci)L)");
  REQUIRE(typeof(o1) == "(((ccc)c)c((cc)(c)))");
}

TEST_CASE("Vector", "[types][vector]") {
  Vector<int> v0;
  Vector<float> v1;
  Vector<signed char> v2;
  Vector<Vector<int>> v3;

  REQUIRE(typeof(v0) == "[i]");
  REQUIRE(typeof(v1) == "[f]");
  REQUIRE(typeof(v2) == "[b]");
  REQUIRE(typeof(v3) == "[[i]]");
}

TEST_CASE("Complex tuple types", "[types][tuple][complex]") {
  Tuple<Vector<int>, char> t0;
  Tuple<Tuple<int, char>, Tuple<unsigned char, float>> t1;
  Tuple<Object<int, char>, Vector<int>> t2;

  REQUIRE(typeof(t0) == "[i]c");
  REQUIRE(typeof(t1) == "icBf");
  REQUIRE(typeof(t2) == "(ic)[i]");
}

TEST_CASE("Complex object types", "[types][object][complex]") {
  Object<Vector<Object<int, char>>, Object<float>> o0;
  Object<Tuple<int, char>, Object<char>> o1;

  REQUIRE(typeof(o0) == "([(ic)](f))");
  REQUIRE(typeof(o1) == "(ic(c))");
}

TEST_CASE("Complex vector types", "[types][vector][complex]") {
  Vector<Tuple<int, char>> v0;
  Vector<Object<int, Vector<char>>> v1;
  Vector<Tuple<char, Object<int, char>>> v2;

  REQUIRE(typeof(v0) == "[ic]");
  REQUIRE(typeof(v1) == "[(i[c])]");
  REQUIRE(typeof(v2) == "[c(ic)]");
}
