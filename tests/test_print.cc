#include <catch.hpp>

#include "../simpleRPC/print.tcc"


TEST_CASE("Print", "[print]") {
  // Print single string.
  REQUIRE(multiPrint((string)"abc") == 3);

  // Print multiple strings.
  REQUIRE(multiPrint((string)"abc", (string)"12345") == 8);
}
