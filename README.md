# Arduino Chess Clock ♟️ ⏰ [unmaintened repo]

I needed a chess clock, so I made one (_an ugly but functional one_).

So, feed your Arduino with this code (`code.ino`) and wire it has described on the schema (see below ⬇️).

When flashing `code.ino` to a correctly wired Arduino, your can :

* set same/different time (in minutes) for player 1 (P1) and player 2 (P2)
* set same/different increment (in seconds) for P1 and P2
* start the game by pressing the start button
* pause the clock by pressing both P1 and P2 buttons
* start over by pressing P1 and P2 buttons and then the start button

Arduino is an easy way to familiarize with both electronics and coding.
Moreover they are cheap (especially _non official_ ones), and they can do a lot.

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


## Limitations

The only limitation is hardware memory capacity (pretty low on Arduino UNO). Indeed, storing elapsed time since the beginning of the game can stop the clock from working when playing long or rich games (~70 moves by player).
One solution is to use a RTC (real time clock), but it's not implemented in this code, tho it's a minor workaround.
