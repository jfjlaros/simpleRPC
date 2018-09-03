#include "led.h"

// LED blink durations.
#define LED_SHORT 100
#define LED_LONG 500


/**
 * Constructor.
 *
 * @arg {int} pin - Analog output pin.
 */
LED::LED(int pin) {
  _pin = pin;

  pinMode(_pin, OUTPUT);
  setBrightness(0);
}

/**
 * Set the brightness.
 *
 * @arg {int} brightness - Brightness.
 */
void LED::setBrightness(byte brightness) {
  analogWrite(_pin, brightness);
}

/**
 * Blink.
 *
 * @arg {int} duration - LED on duration.
 */
void LED::blink(int duration) {
  digitalWrite(_pin, HIGH);
  delay(duration);
  digitalWrite(_pin, LOW);
}


/**
 * Convert a byte of data to a series of LED pulses.
 *
 * @arg {byte} data - Data to be converted.
 */
void LED::signal(byte data) {
  int i;

  for (i = 7; i >= 0; i--) {
    if (data & (1 << i)) {
      blink(LED_LONG);
    }
    else {
      blink(LED_SHORT);
    }
    delay(LED_SHORT);
  }
}
