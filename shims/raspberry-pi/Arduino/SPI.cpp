#include "SPI.h"

SPIObject SPI;

void SPIObject::beginTransaction(const SPISettings &s) { _address = 0; }

byte SPIObject::transfer(byte val) {

  if (_address == 0) {
    _address = val;
    return 0;
  }
//  std::cout << "---\n";
  byte data[2]{_address, val};

  //std::cout << std::hex << static_cast<int>(data[0]) << "," << static_cast<int>(data[1]) << "\n";
  wiringPiSPIDataRW(0, &data[0], 2);
  //std::cout << std::hex << static_cast<int>(data[0]) << "," << static_cast<int>(data[1]) << "\n";
  
  byte realAddress = (_address & 0x7E ) >> 1;
//  if (_address & 0x80) {
//    std::cout << std::hex
//	      << "Read," << static_cast<int>(realAddress) << "," << static_cast<int>(data[1]) << "\n";
//  } else {
//    std::cout << std::hex
//	      << "Wrote," << static_cast<int>(realAddress) << "," << static_cast<int>(val) << "\n";
//  }
  //std::cout << std::hex
  //	    << "Address = " << static_cast<int>(_address)
  //          << " Data[0] = " << static_cast<int>(data[0])
  //          << " Data[1] = " << static_cast<int>(data[1])
  //          << " Wrote = " << static_cast<int>(val)
  //          << " Read = " << static_cast<int>(data[1]) << "\n";

  return data[1];
}

void SPIObject::endTransaction() { _address = 0; }
