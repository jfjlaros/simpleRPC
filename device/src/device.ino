#include "interface.h"
#include "led.h"

LED led(13);


int bla(void) {
  return 1;
}

int add(int a, int b) {
  return a + b;
}

void setLed(int brightness) {
  led.setBrightness((byte)brightness);
}

bool state = false;

void toggle(void) {
  if (state) {
    led.off();
    state = false;
  }
  else {
    led.on();
    state = true;
  }
}

void setup(void) {
  led.setBrightness(40);
  Serial.begin(9600);
}


void readValue(byte *data, int size) {
  int i;

  for (i = 0; i < size; i++) {
    Serial.readBytes((char *)&data[i], 1);
  }
}

void writeValue(byte *data, int size) {
  int i;

  for (i = 0; i < size; i++) {
    Serial.write(data[i]);
  }
}

int readInt(void) {
  int data;

  readValue((byte *)&data, sizeof(int));

  return data;
}

float readFloat(void) {
  float data;

  readValue((byte *)&data, sizeof(float));

  return data;
}

void writeInt(int data) {
  writeValue((byte *)&data, sizeof(int));
}

void writeFloat(float data) {
  writeValue((byte *)&data, sizeof(float));
}

void loop(void) {
  // caller();
  int i;

  if (Serial.available()) {
    switch (Serial.read()) {
      case 0: Serial.write(bla()); break;
      case 1: 
        writeVal(add(readVal<int>(), readVal<int>()));
        writeVal((float)3.1415);
        writeVal(sizeof(int));
      case 2: setLed(Serial.parseInt()); break;
      case 3: toggle(); break;
      default:
        Serial.write(numberOfMethods);
        for (i = 0; i < numberOfMethods; i++) {
          Serial.print(methods[i].type);
          Serial.print(" ");
          Serial.print(methods[i].name);
          Serial.print(" ");
          Serial.println(methods[i].args);
        }
        break;
    }
  }
}
