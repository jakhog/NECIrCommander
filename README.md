# NECIrCommander
Simple Arduino-code for controlling the NAD325BEE amplifier by using the IR-IN port - as a replacement for the SR 5 remote control.
This project consists of two pieces of code, the `NECReceiver` directory contains code to decode the commands sent by the remote control, and the `NECCommander` emulates these commands to control the amplifier.

### NECReceiver
This code is a slightly modified version of [this Adafruit project](https://github.com/adafruit/Adafruit-NEC-remote-control-library). By hooking up an IR receiver like [this](https://www.adafruit.com/product/157) to pin `4` of an Arduino, it will output lines of the following format:
- `ADDRESS -> CODE` when a valid packet is decoded. E.g.: `877C -> 85` (the address should be `877C` for the SR 5 remote).
- `Repeat code...` if the NEC repeat code is sent, i.e. when a button on the remote is held down.
- `Invalid packet!` if something whent wrong while decoding.

### NECCommander
