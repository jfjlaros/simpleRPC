#include <catch.hpp>

#include "Arduino.h"

#include "../simpleRPC/signature.tcc"


TEST_CASE("Basic types 1", "[types]") {
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

TEST_CASE("Basic types 2", "[types]") {
  int i;
  unsigned int ui;
  double d;

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

TEST_CASE("String types", "[types]") {
  char *cP;
  const char *ccP;

  REQUIRE(_typeof(cP) == "s");
  REQUIRE(_typeof(ccP) == "s");
}

TEST_CASE("List types", "[types]") {
  unsigned char *ucP;
  const signed char *cscP;
  int *iP;

  REQUIRE(_typeof(ucP) == "B*");
  REQUIRE(_typeof(cscP) == "b*");
  REQUIRE(_typeof(iP) == "<i*");
}

TEST_CASE("Compound types", "[types]") {
  Tuple <int, char>ic;
  Tuple <int, signed char, unsigned long>iscul;
  Tuple <int, int *>iiP;

  REQUIRE(_typeof(ic) == "<ic");
  REQUIRE(_typeof(iscul) == "<ib<L");
  REQUIRE(_typeof(iiP) == "<i<i*");
}
