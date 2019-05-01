#ifndef ARDUINO_H
#define ARDUINO_H

#include <stddef.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

typedef uint_8 byte;
typedef char __FlashStringHelper;

#define SPI_CLOCK_DIV4 1000000 // MFRC522 accept upto 10MHz

#define SS 8
#define PROGMEM
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))

#endif
