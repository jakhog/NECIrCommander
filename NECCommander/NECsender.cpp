#include "NECsender.h"

NECsender::NECsender(uint8_t pin, uint16_t address) {
  _irpin = pin;
  _addr1 = (address >> 8) & 0xFF;
  _addr2 = address & 0xFF;  
}

void NECsender::begin() {
  pinMode(_irpin, OUTPUT);
  digitalWrite(_irpin, LOW);
}

void NECsender::write(uint8_t code, uint8_t repeat) {
  unsigned long start = millis();
  unsigned long finish, wait;

  // Send the code
  transmitCommand(code);

  // Repeat spefified amount of times
  while (repeat > 0) {
    // Calculate delay for 110ms time between transmitted pulses
    finish = millis();
    if (finish >= start) wait = 110 - finish + start;
    else wait = 110 - 0xFFFFFF + start - finish;

    delay(wait);

    start = millis();
    transmitRepeat();
    repeat--;
  }
}

/* --- Private methods --- */
void NECsender::transmitStart() {
  digitalWrite(_irpin, HIGH);
  delayMicroseconds(9000);
  digitalWrite(_irpin, LOW);
  delayMicroseconds(4500);
}

void NECsender::transmitZero() {
  digitalWrite(_irpin, HIGH);
  delayMicroseconds(562);
  digitalWrite(_irpin, LOW);
  delayMicroseconds(562);
}

void NECsender::transmitOne() {
  digitalWrite(_irpin, HIGH);
  delayMicroseconds(562);
  digitalWrite(_irpin, LOW);
  delayMicroseconds(1687);
}

void NECsender::transmitByte(uint8_t data) {
  for (uint8_t i = 0; i < 8; ++i) {
    if (data & 0x01) transmitOne();
    else transmitZero();
    data >>= 1;
  }
}

void NECsender::transmitAddress() {
  transmitByte(_addr1);
  transmitByte(_addr2);
}

void NECsender::transmitCommand(uint8_t cmd) {
  transmitStart();
  transmitAddress();

  transmitByte(cmd);
  transmitByte(~cmd);

  transmitZero();
}

void NECsender::transmitRepeat() {
  digitalWrite(_irpin, HIGH);
  delayMicroseconds(9000);
  digitalWrite(_irpin, LOW);
  delayMicroseconds(2250);

  transmitZero();
}

