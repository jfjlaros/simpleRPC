#include <catch.hpp>

#include "../src/simpleRPC.h"
#include "../src/plugins/hardwareserial/io.h"

extern HardwareSerialIO io;


TEST_CASE("RPC call function x", "[call][basic]") {
  struct S {
    static short int f(int) {
      return 2;
    }
  };

  // One interface.
  Serial.reset();
  Serial.prepare('\0');
  interface(io, S::f, "");
  REQUIRE(Serial.inspect<short int>() == 2);
  REQUIRE(Serial.rx == sizeof(byte) + sizeof(int));
  REQUIRE(Serial.tx == sizeof(short int));

  // Two interfaces.
  Serial.reset();
  Serial.prepare('\0');
  Serial.prepare('\0');
  interface(pack(&io, &io), S::f, "");
  REQUIRE(Serial.inspect<short int>() == 2);
  REQUIRE(Serial.inspect<short int>() == 2);
  REQUIRE(Serial.rx == 2 * (sizeof(byte) + sizeof(int)));
  REQUIRE(Serial.tx == 2 * (sizeof(short int)));
}
