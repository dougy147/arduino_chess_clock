# Arduino Chess Clock ♟️ ⏰ [unmaintened repo]

I needed a chess clock, so I made one (_an ugly but functional one_).

Arduino is an easy way to familiarize with both electronics and coding.
Moreover they are cheap (especially _non official_ ones), and they can do a lot.

To replicate this clock, feed your Arduino with `code.ino`, and wire it has described on the schema below ⬇️.

The clock functionalities are simple :

* set time (in minutes) for player 1 (P1) and player 2 (P2) [allocated times can differ]
* allocate the increment (in seconds) for P1 and P2 [increments can differ too]
* start the game by pressing the middle/start button
* pause the clock by pressing both P1 and P2 buttons
* start a new game by pressing P1 and P2 buttons and then pressing start

## What you need

* Arduino (tested on Arduino UNO)
* 3 push buttons
* 7digits LED display
* A bunch of wires
* 3 resistors 10kΩ
* Facultative : a battery holder
* Facultative : a buzzer to be warned when a player time's runs out

## Schema

<p align="center">
<img src="https://raw.githubusercontent.com/dougy147/arduino_chess_clock/master/schema/schema.jpg" width="44%" />
</p>

## Limitations ⚠️

The only limitation here is the hardware memory capacity (pretty low on Arduino UNO). The clock can stop from working when playing long or rich games (~70 moves by player).

One solution is to use a RTC (real time clock) module, but it's not implemented in this code (should be a minor workaround tho).
