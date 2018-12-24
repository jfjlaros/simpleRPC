#include <valarray>

#include "Arduino.h"


/**
 * Constructor.
 */
HardwareSerial::HardwareSerial(void) {
  rxBuffer[_BUFFER_SIZE - 1] = '\0';
  txBuffer[_BUFFER_SIZE - 1] = '\0';

  reset();
}

/**
 * Reset the internal counters.
 */
void HardwareSerial::reset(void) {
  rx = 0;
  tx = 0;
}

/**
 * Test for serial availability.
 *
 * @return {bool} - True;
 */
bool HardwareSerial::available(void) {
  return true;
}

/**
 * Read one byte from serial.
 *
 * @return {byte} - One byte;
 */
byte HardwareSerial::read(void) {
  rx++;

  return rxBuffer[rx - 1];
}

/**
 * Read a number of bytes from serial.
 *
 * @arg {char *} buffer - Buffer.
 * @arg {size_t} size - Number of bytes to read.
 */
void HardwareSerial::readBytes(char *buffer, size_t size) {
  strncpy(buffer, &rxBuffer[rx], size);
  rx += size;
}

/**
 * Read a string from serial.
 *
 * @arg {char} delimiter - String delimiter.
 *
 * @return {String} - A string.
 */
String HardwareSerial::readStringUntil(char delimiter) {
  size_t size = strchr(&rxBuffer[rx], delimiter) - &rxBuffer[rx] + 1;

  rx += size;

  return ((String)&rxBuffer[rx - size]).substr(0, size - 1);
}

/**
 * Write one byte to serial.
 *
 * @return {size_t} - Number of bytes written.
 */
size_t HardwareSerial::write(char c) {
  txBuffer[tx] = c;
  tx++;

  return 1;
}

/**
 * Write a number of bytes to serial.
 *
 * @arg {char *} buffer - Buffer.
 * @arg {size_t} size - Number of bytes to read.
 *
 * @return {size_t} - Number of bytes written.
 */
size_t HardwareSerial::write(byte *buffer, size_t size) {
  strncpy(&txBuffer[tx], (char *)buffer, size);
  tx += size;

  return size;
}

/**
 * Write a string to serial.
 *
 * @arg {String} s - A string.
 *
 * @return {size_t} - Number of bytes written.
 */
size_t HardwareSerial::write(String s) {
  size_t size = s.length();

  strncpy(&txBuffer[tx], s.c_str(), size);
  tx += size;

  return size;
}


HardwareSerial Serial;
