#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define F(X) X
#define DEC 1
#define HEX 2

typedef char unsigned byte;
typedef char __FlashStringHelper;

#define SPI_CLOCK_DIV4 1000000 // MFRC522 accept upto 10MHz

#define SS 8
#define PROGMEM
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))

#define MFRC522_SPICLOCK 0
#define MSBFIRST 0
#define SPI_MODE0 0

#endif
