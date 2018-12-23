#include <catch.hpp>

#include "Arduino.h"


TEST_CASE("Read one byte", "[arduino]") {
  Serial.reset();

  Serial.rxBuffer[0] = 'x';
  Serial.rxBuffer[1] = 'y';

  // Test the read() function.
  REQUIRE(Serial.read() == 'x');
  REQUIRE(Serial.read() == 'y');
}

TEST_CASE("Read different types", "[arduino]") {
  int offset = 0;

  Serial.reset();

  Serial.rxBuffer[offset] = 'x';
  offset += sizeof(char);
  ((int *)&Serial.rxBuffer[offset])[0] = (int)1234;
  offset += sizeof(int);
  ((float *)&Serial.rxBuffer[offset])[0] = (float)3.14;

  // Test the readBytes() funcion.
  REQUIRE(_read<char>() == 'x');
  REQUIRE(_read<int>() == (int)1234);
  REQUIRE(_read<float>() == (float)3.14);
}

TEST_CASE("Read string", "[arduino]") {
  Serial.reset();

  strcpy(Serial.rxBuffer, "A string.");

  // Test the readStringUntil() function.
  REQUIRE(Serial.readStringUntil('\0') == "A string.");
}

TEST_CASE("Write one byte", "[arduino]") {
  Serial.reset();

  Serial.write('x');
  Serial.write('y');

  // Test the write(char) function.
  REQUIRE(Serial.txBuffer[0] == 'x');
  REQUIRE(Serial.txBuffer[1] == 'y');
}

TEST_CASE("Write different types", "[arduino]") {
  int offset = 0;

  Serial.reset();

  _write('x');
  _write((int)1234);
  _write((float)3.14);

  // Test the write(byte *, size_t) function.
  REQUIRE(Serial.txBuffer[offset] == 'x');
  offset += sizeof(char);
  REQUIRE(((int *)&Serial.txBuffer[offset])[0] == (int)1234);
  offset += sizeof(int);
  REQUIRE(((float *)&Serial.txBuffer[offset])[0] == (float)3.14);
}

TEST_CASE("Write string", "[arduino]") {
  Serial.reset();

  Serial.write("A string.");

  // Test the write(String) function.
  REQUIRE(((String)Serial.txBuffer).substr(0, 9) == "A string.");
}
