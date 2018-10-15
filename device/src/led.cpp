#include "led.h"

// LED blink durations.
#define LED_SHORT 100
#define LED_LONG 500


/**
 * Constructor.
 *
 * @arg {int} pin - Output pin.
 */
LED::LED(int pin) {
  _pin = pin;

  pinMode(_pin, OUTPUT);
  off();
}

/**
 * Turn the LED on.
 */
void LED::on(void) {
  digitalWrite(_pin, HIGH);
}

/**
 * Turn the LED off.
 */
void LED::off(void) {
  digitalWrite(_pin, LOW);
}

/**
 * Set the brightness.
 *
 * Note that this only works for analogue output pins.
 *
 * @arg {int} brightness - Brightness.
 */
void LED::setBrightness(byte brightness) {
  analogWrite(_pin, brightness);
}

/**
 * Pulse.
 *
 * @arg {int} durationOn - LED on duration.
 * @arg {int} durationOff - LED off duration.
 */
void LED::pulse(int durationOn, int durationOff) {
  on();
  delayMicroseconds(durationOn);
  off();
  delayMicroseconds(durationOff);
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
      pulse(LED_LONG, LED_SHORT);
    }
    else {
      pulse(LED_SHORT, LED_SHORT);
    }
  }
}
