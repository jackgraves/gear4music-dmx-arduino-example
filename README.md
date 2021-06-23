## Gear4Music Galaxy-72 Arduino DMX Example

This repository contains an example of how you can control the 'Galaxy-72' LED Strip that Gear4Music offer.

I bought mine ([here](https://www.gear4music.com/PA-DJ-and-Lighting/Galaxy-72W-LED-Wall-Wash-by-Gear4music/2IFB)).

The Galaxy-72 LED Strip contains 24 RGB LEDs, which can be addressed in sets of 3 ( 8 Addresses * 3 LEDs = 24 Total LEDs).

Using [DMX](https://en.wikipedia.org/wiki/DMX512), you can control these lights.

![image](https://user-images.githubusercontent.com/12021631/123093068-1a975000-d423-11eb-9afb-cea57e4e0a39.png)

### Requirements

* 1+ Galaxy-72 LED Strips (I'm using 2)
* 1+ DMX Cables (don't use standard XLR cables, as they [don't work](https://www.bax-shop.co.uk/blog/cables/whats-the-difference-between-dmx-and-xlr-cables/))
* Arduino (I'm using an Arduino Uno)
* DMX Shield

### Hardware Setup

Before we program the Arduino to control the lights, we first need to setup the equipment:

1. On each Galaxy-72 device, set the following settings:
    * Address (First Device: 1, Second: 51, Third: 101 etc.)
    * Channels: 50 Channels
    * Mode: Slave 1
2. If you have more than 1 Galaxy-72 device:
    * Daisy-chain the devices together (DMX OUT -> DMX IN)
3. Next, attach the DMX Shield to your Arduino
    * Set the following headers on the DMX Shield: NOT EN, DE, TX-uart, RX-uart (all on the right)
4. Plug a DMX Cable from the Arduino to the DMX IN on the first Galaxy-72

#### Note on the DMX Shield

The Arduino DMX Shield has a 'quirk' that caused me some confusion initially - most libraries are available to interface with the board use the UART or SERIAL port to communicate with the DMX Shield.

This means that you cannot upload code to the Arduino when the DMX Shield is listening to these ports and have to change the headers:
* When you are uploading code to the Arduino, you must set the boards 'NOT EN' header (not enabled)
* When you have uploaded the code and want to output DMX, set the 'EN' header (enabled)

### Software Setup

At this point, you should have your Arduino with DMX Shield plugged into your computer and be ready to develop:

1. Install the Arduino IDE if you haven't already
2. Clone this repository or copy the contents of the `project.ino` file into your Arduino IDE, add dependencies (ArduinoRS485 and ArduinoDMX)
3. Upload the project to your Arduino
4. Move the `NOT EN` header to the `EN` position
5. You should see the Galaxy-72 display flashing and the lights should operate
5. Whenever you need to re-upload the code, make sure you put the `EN` pin back into the right slot

### What does the example do?

The example script controls 2 devices and makes them perform a mirrored sequence.

e.g.

```
Time | Left Device | Right Device
1 [x][ ][ ][ ][ ][ ][ ][ ] | [ ][ ][ ][ ][ ][ ][ ][x]
2 [ ][x][ ][ ][ ][ ][ ][ ] | [ ][ ][ ][ ][ ][ ][x][ ]
3 [ ][ ][x][ ][ ][ ][ ][ ] | [ ][ ][ ][ ][ ][x][ ][ ]
4 [ ][ ][ ][x][ ][ ][ ][ ] | [ ][ ][ ][ ][x][ ][ ][ ]
5 [ ][ ][ ][ ][x][ ][ ][ ] | [ ][ ][ ][x][ ][ ][ ][ ]
6 [ ][ ][ ][ ][ ][x][ ][ ] | [ ][ ][x][ ][ ][ ][ ][ ]
7 [ ][ ][ ][ ][ ][ ][x][ ] | [ ][x][ ][ ][ ][ ][ ][ ]
8 [ ][ ][ ][ ][ ][ ][ ][x] | [x][ ][ ][ ][ ][ ][ ][ ]
```

It is contained in a loop that will also reverse the pattern so that it looks smoother on the devices.

### License

This repository is fully open-source, do what you want with it 😎!
