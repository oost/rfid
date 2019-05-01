#ifndef SPI_H
#define SPI_H

#include "Arduino.h"
#include <iostream>

#define MFRC522_SPICLOCK 0
#define MSBFIRST 0
#define SPI_MODE0 0

struct SPISettings {
  SPISettings(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}
  int a, b, c;
};

class SPIObject {
public:
  void beginTransaction(const SPISettings &s);
  byte transfer(byte val);
  void endTransaction();

  SPIObject() : _address{0} {

    if (wiringPiSPISetup(0, MFRC522_SPICLOCK) < 0)
      throw "Couldn't initialize SPI";

    wiringPiSetup();
  }

private:
  byte _address;
};

extern SPIObject SPI;

#endif