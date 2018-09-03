#ifndef LED_h
#define LED_h

#include <Arduino.h>


class LED {
  public:
    LED(int);
    void setBrightness(byte),
         blink(int),
         signal(byte);
  private:
    int _pin;
};

#endif
