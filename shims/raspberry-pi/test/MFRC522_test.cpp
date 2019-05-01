#include "constants.h"
#include <iostream>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define SDA_PIN 8 // SDA
#define RST_PIN 25
typedef uint8_t byte;

void init() {
  if (wiringPiSPISetup(0, 1000000) < 0)
    throw "Couldn't initialize SPI";

  wiringPiSetupGpio();

  pinMode(RST_PIN, OUTPUT);
  digitalWrite(RST_PIN, HIGH);

#ifdef SELECT
  pinMode(SDA_PIN, OUTPUT);
  digitalWrite(SDA_PIN, HIGH);
#endif
}

void writeToRegister(byte addr, byte val) {
#ifdef SELECT
  digitalWrite(SDA_PIN, LOW);
#endif
  std::cout << "---\n";
  byte data[2]{(addr << 1) & 0x7E, val};
  std::cout << std::hex << static_cast<int>(data[0]) << "," << static_cast<int>(data[1]) << "\n";
  wiringPiSPIDataRW(0, &data[0], 2);
  std::cout << std::hex << static_cast<int>(data[0]) << "," << static_cast<int>(data[1]) << "\n";
  
  std::cout << std::hex << "Write, " << static_cast<int>(addr) << ","
            << static_cast<int>(val) << "\n";


#ifdef SELECT
  digitalWrite(SDA_PIN, HIGH);
#endif
}

byte readFromRegister(byte addr) {

#ifdef SELECT
  digitalWrite(SDA_PIN, LOW);
#endif
  byte data[2]{((addr << 1) & 0x7E) | 0x80, 0};
  std::cout << std::hex << static_cast<int>(data[0]) << "," << static_cast<int>(data[1]) << "\n";
  wiringPiSPIDataRW(0, &data[0], 2);
  std::cout << std::hex << static_cast<int>(data[0]) << "," << static_cast<int>(data[1]) << "\n";
  std::cout << std::hex << "Read," << static_cast<int>(addr) << ","
            << static_cast<int>(data[1]) << "\n";
#ifdef SELECT
  digitalWrite(SDA_PIN, HIGH);
#endif
  return data[1];
}

int main() {
#ifdef SELECT
  std::cout << "Running with SELECT on\n";
#endif
  std::cout << "SDA=" << SDA_PIN << "  RST=" << RST_PIN << "\n";	
  init();

  std::cout << "Reset\n";
  writeToRegister(CommandReg, MFRC522_SOFTRESET);
  writeToRegister(TModeReg, 0x8D); // Tauto=1; f(Timer) = 6.78MHz/TPreScaler
  writeToRegister(TPrescalerReg, 0x3E); // TModeReg[3..0] + TPrescalerReg
  writeToRegister(TReloadRegL, 30);
  writeToRegister(TReloadRegH, 0);
  writeToRegister(TxAutoReg, 0x40); // 100%ASK
  writeToRegister(ModeReg, 0x3D);   // CRC initial value 0x6363
  writeToRegister(TxControlReg, 0x03);   // Turn antenna on.

  std::cout << "Version: " << std::hex
            << static_cast<int>(readFromRegister(VersionReg));
}
