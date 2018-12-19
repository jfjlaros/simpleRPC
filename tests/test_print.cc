#include <catch.hpp>

#include "../simpleRPC/print.tcc"


TEST_CASE("Print", "[print]") {
  REQUIRE(multiPrint((string)"abc") == 3);
  REQUIRE(multiPrint((string)"abc", (string)"12345") == 8);
}
