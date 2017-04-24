#include "NECremote.h"

NECremote remote(4);

void setup() {
  Serial.begin(57600);
}

void loop() {
  int32_t data = remote.listen();

  if (data == -3) {
    Serial.println("Repeat code...");
  } else if (data > 0) {
    Serial.print(data >> 8, HEX);
    Serial.print(" -> ");
    Serial.println(data & 0xFF, HEX);
  } else {
    Serial.println("Invalid packet!");
  }
}
