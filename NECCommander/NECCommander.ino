#include "NECsender.h"

NECsender sender(12, 0x877C);

void setup() {
  // Enable LED to flash when commands are sent
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  // Init sender pin
  sender.begin();
  
  // Init Serial port so that we receive commands
  Serial.begin(57600);
}

#define Ncmd 10
#define Nrep 10

void loop() {
  char command[Ncmd] = {0};
  char repeat[Nrep] = {0};
  byte i = 0;

  // Read command from serial port
  bool finished = false, rep = false;
  while (!finished) {
    int c = Serial.read();
    switch (c) {
      case -1:
        // Ignore errors
        break;
      case '\r':
        // Ignore CR
        break;
      case '\n':
        // Finish on LF
        finished = true;
        break;
      case ',':
        // Comma is COMMAND-REPEAT separator
        rep = true;
        i = 0;
        break;
      default:
        if (rep) repeat[i] = c;
        else command[i] = toupper(c);
        i++;
    }
    if ((!rep && i == Ncmd) || (rep && i == Nrep)) {
      // Overflowed, flush to LF
      while (Serial.read() != '\n') {};
      break;
    }
  }

  // Parse the command
  int repeats = atoi(repeat);

  if (strcmp("ON", command) == 0) {
    sender.write(0x25, repeats);
  } else if (strcmp("OFF", command) == 0) {
    sender.write(0xC8, repeats);
  } else if (strcmp("CD", command) == 0) {
    sender.write(0x85, repeats);
  } else if (strcmp("TUNER", command) == 0) {
    sender.write(0xDD, repeats);
  } else if (strcmp("AUX", command) == 0) {
    sender.write(0x9B, repeats);
  } else if (strcmp("DISC", command) == 0) {
    sender.write(0x89, repeats);
  } else if (strcmp("TAPEMON", command) == 0) {
    sender.write(0x8D, repeats);
  } else if (strcmp("TAPE2", command) == 0) {
    sender.write(0x91, repeats);
  } else if (strcmp("VIDEO1", command) == 0) {
    sender.write(0xC2, repeats);
  } else if (strcmp("VIDEO2", command) == 0) {
    sender.write(0xC0, repeats);
  } else if (strcmp("VIDEO3", command) == 0) {
    sender.write(0xC1, repeats);
  } else if (strcmp("VOLUP", command) == 0) {
    sender.write(0x88, repeats);
  } else if (strcmp("VOLDOWN", command) == 0) {
    sender.write(0x8C, repeats);
  } else if (strcmp("MUTE", command) == 0) {
    sender.write(0x94, repeats);
  }
}
