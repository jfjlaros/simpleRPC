#include <catch.hpp>

#include "../src/print.tcc"
#include "../src/plugins/stream/io.h"

extern HardwareSerialIO io;


TEST_CASE("Print", "[print]") {
  // Print single string.
  Serial.reset();
  rpcPrint(io, "abc");
  REQUIRE(Serial.inspect<string>() == "abc");

  // Print multiple strings.
  Serial.reset();
  rpcPrint(io, "abc", "12345");
  REQUIRE(Serial.inspect<string>() == "abc12345");
}
