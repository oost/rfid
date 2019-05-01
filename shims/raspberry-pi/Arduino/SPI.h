#ifndef SPI_H
#define SPI_H

#include "definitions.h"
#include <iostream>
#include <wiringPi.h>
#include <wiringPiSPI.h>

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

  void begin() {}

private:
  byte _address;
};

extern SPIObject SPI;

#endif