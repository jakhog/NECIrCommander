# NECIrCommander
Simple Arduino-code for controlling the NAD325BEE amplifier by using the IR-IN port - as a replacement for the SR 5 remote control. This project consists of two pieces of code, the `NECReceiver` directory contains code to decode the commands sent by the remote control, and the `NECCommander` emulates these commands to control the amplifier.

### NECReceiver
This code is a slightly modified version of [this Adafruit project](https://github.com/adafruit/Adafruit-NEC-remote-control-library). By hooking up an IR receiver like [this](https://www.adafruit.com/product/157) to pin `4` of an Arduino, it will output lines of the following format:
- `ADDRESS -> CODE` when a valid packet is decoded. E.g.: `877C -> 85` (the address should be `877C` for the SR 5 remote).
- `Repeat code...` if the NEC repeat code is sent, i.e. when a button on the remote is held down.
- `Invalid packet!` if something whent wrong while decoding.

### NECCommander
This code waits for commands on the format `COMMAND[,REPEAT]` on the serial port, and sends the corresponding code using the NEC encoding through pin 12 (repeated the specified amount of times). Simply connect ground to the sleeve and pin 12 to the tip of a mini-jack plug, insert it into the IR-IN port of the NAD325BEE and greatness is ensured :smile:.

Currently, the following commands are implemented: `ON`, `OFF`, `CD`, `TUNER`, `AUX`, `DISC`, `TAPEMON`, `TAPE2`, `VIDEO1`, `VIDEO2`, `VIDEO3`, `VOLUP`, `VOLDOWN` and `MUTE`.
