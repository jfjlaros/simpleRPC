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

  // Basic types.
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

  // String types.
  REQUIRE(_typeof(cP) == "s");
  REQUIRE(_typeof(ccP) == "s");
}

TEST_CASE("Compound types", "[types][tuple]") {
  Tuple <int, char>ic;
  Tuple <int, signed char, unsigned long>iscul;
  Tuple <int, int *>iiP;
  Tuple <Vector <int>, char>v;
  //Tuple <Tuple<int, char>, Tuple<unsigned char, float>>t;
  //Object <Vector <Object <Object <int, char>, Object<float>>>, char, char, char>t;
  Object <
    Object <
      Object <char, char, char>,
      char
    >,
    char,
    Object <
      Object <char, char>,
      Object <char>
    >
  >t;

  // Tuples.
  //REQUIRE(_typeof(ic) == "<ic");
  //REQUIRE(_typeof(iscul) == "<ib<L");
  //REQUIRE(_typeof(iiP) == "<i<i*");
  //REQUIRE(_typeof(v) == "(<i)c");
  //REQUIRE(_typeof(t) == "?");
}

TEST_CASE("Vector", "[types][vector]") {
  Vector <int>vi;
  Vector <float>vf;
  Vector <signed char>vsc;
  Vector <Tuple <int, char>>vt;

  //REQUIRE(_typeof(vi) == "(<i)");
  //REQUIRE(_typeof(vf) == "(<f)");
  //REQUIRE(_typeof(vsc) == "(b)");
  //REQUIRE(_typeof(vt) == "(<ic)");
}
