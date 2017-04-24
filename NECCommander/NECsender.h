#include "Arduino.h"

class NECsender {
 public:
  NECsender(uint8_t pin, uint16_t address);
  void begin();
  void write(uint8_t code, uint8_t repeat = 0);

 private:
  uint8_t _irpin, _addr1, _addr2;
  
  void transmitStart();
  void transmitZero();
  void transmitOne();
  void transmitByte(uint8_t data);
  void transmitAddress();
  void transmitCommand(uint8_t cmd);
  void transmitRepeat();
};
