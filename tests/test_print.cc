#include <catch.hpp>

#include "../src/print.tcc"

extern Stream Serial;


TEST_CASE("Print", "[print]") {
  // Print single string.
  Serial.reset();
  rpcPrint(Serial, "abc");
  REQUIRE(Serial.inspect<string>() == "abc");

  // Print multiple strings.
  Serial.reset();
  rpcPrint(Serial, "abc", "12345");
  REQUIRE(Serial.inspect<string>() == "abc12345");
}
