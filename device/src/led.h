#ifndef LED_h
#define LED_h

#include <Arduino.h>


class LED {
  public:
    LED(void) {};
    LED(int);
    void on(void),
         off(void),
         setBrightness(byte),
         pulse(int, int),
         signal(byte);
  private:
    int _pin;
};

#endif
