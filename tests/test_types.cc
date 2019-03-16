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

  REQUIRE(_typeof(b) == "?");
  REQUIRE(_typeof(c) == "c");
  REQUIRE(_typeof(sc) == "b");
  REQUIRE(_typeof(uc) == "B");
  REQUIRE(_typeof(si) == "<h");
  REQUIRE(_typeof(usi) == "<H");
  REQUIRE(_typeof(li) == "<l");
  REQUIRE(_typeof(uli) == "<L");
  REQUIRE(_typeof(lli) == "<q");
  REQUIRE(_typeof(ulli) == "<Q");
  REQUIRE(_typeof(f) == "<f");
}

TEST_CASE("Basic types 2", "[types][basic]") {
  int i;
  unsigned int ui;
  double d;

  // Basic types of which the size may differ between platforms.
  if (sizeof(int) == 2) {
    REQUIRE(_typeof(i) == "<h");
    REQUIRE(_typeof(ui) == "<H");
  }
  else {
    REQUIRE(_typeof(i) == "<i");
    REQUIRE(_typeof(ui) == "<I");
  }
  if (sizeof(double) == 4) {
    REQUIRE(_typeof(d) == "<f");
  }
  else {
    REQUIRE(_typeof(d) == "<d");
  }
}

TEST_CASE("String types", "[types][string]") {
  char *cP;
  const char *ccP;

  REQUIRE(_typeof(cP) == "s");
  REQUIRE(_typeof(ccP) == "s");
}

TEST_CASE("Tuple types", "[types][tuple]") {
  Tuple <int, char>ic;
  Tuple <int, signed char, unsigned long>iscul;

  REQUIRE(_typeof(ic) == "<ic");
  REQUIRE(_typeof(iscul) == "<ib<L");
}

TEST_CASE("Object types", "[types][object]") {
  Object <Object<char, int>, unsigned long>o1;
  Object <
    Object <
      Object <char, char, char>,
      char>,
    char,
    Object <
      Object <char, char>,
      Object <char>>>o2;

  REQUIRE(_typeof(o1) == "[[c<i]<L]");
  REQUIRE(_typeof(o2) == "[[[ccc]c]c[[cc][c]]]");
}

TEST_CASE("Vector", "[types][vector]") {
  Vector <int>v1;
  Vector <float>v2;
  Vector <signed char>v3;
  Vector <Vector <int>>v4;

  REQUIRE(_typeof(v1) == "(<i)");
  REQUIRE(_typeof(v2) == "(<f)");
  REQUIRE(_typeof(v3) == "(b)");
  REQUIRE(_typeof(v4) == "((<i))");
}

TEST_CASE("Complex tuple types", "[types][tuple]") {
  Tuple <Vector <int>, char>t1;
  Tuple <Tuple<int, char>, Tuple<unsigned char, float>>t2;
  Tuple <Object<int, char>, Vector<int>>t3;

  REQUIRE(_typeof(t1) == "(<i)c");
  REQUIRE(_typeof(t2) == "<icB<f");
  REQUIRE(_typeof(t3) == "[<ic](<i)");
}

TEST_CASE("Complex object types", "[types][object]") {
  Object <Vector <Object <int, char>>, Object<float>>o1;
  Object <Tuple <int, char>, Object <char>>o2;

  REQUIRE(_typeof(o1) == "[([<ic])[<f]]");
  REQUIRE(_typeof(o2) == "[<ic[c]]");
}

TEST_CASE("Complex vector types", "[types][vector]") {
  Vector <Tuple <int, char>>v1;
  Vector <Object <int, Vector <char>>>v2;
  Vector <Tuple <char, Object <int, char>>>v3;

  REQUIRE(_typeof(v1) == "(<ic)");
  REQUIRE(_typeof(v2) == "([<i(c)])");
  REQUIRE(_typeof(v3) == "(c[<ic])");
}
