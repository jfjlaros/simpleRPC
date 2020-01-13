#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include "../src/plugins/hardwareserial/io.h"

HardwareSerialIO io;


int main(int argc, char** argv) {
  io.begin(Serial);

  return Catch::Session().run(argc, argv);
}
