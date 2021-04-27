# The Lighthouse of Doom

This repository contain a simple text-based adventure game, implemented
twice:

* [C Implementation](#c-implementation)
* [Z80 Implementation](#z80-implementation)

My intention was to write a simple text-based adventure game to run under
CP/M.  Starting large projects in Z80 assembly language from scratch
is a bit of a daunting prospect, so I decided to code a simple game in C
to get the design right and to avoid getting stuck in too many low-level
details.


## Plot

* You're inside a lighthouse (trapped? doesn't really matter I guess).
* You see a boat on the horizon, heading your way.
* But "oh no!", the lighthouse is dark.
  * The boat will surely crash if you don't turn on the main light.

The game is over, when you either fix the light, or find another solution.
If you do not achieve victory within a turn-limit the boat runs aground, and
death will consume you all.  (It is a _very_ big boat!)



## C Implementation

The implementation is mostly concerned with creating the correct series of
data-structures, which are essentially arrays of objects.  Because if we
can make the game table-based we simplify the coding that needs to be
done - we don't need to write per-object handlers anywhere, we can just
add pointers to tables/structures.

The C implementation defines most of the important things in the file [globals.h](globals.h) such as:

* The structure to define a location.
* The structure to define an object.

The game-state itself is stored in a couple of global variables, there isn't
too much state to care about:

* The current location (i.e. index into location-table).
* A list of any items you're carrying.
* The number of turns you've taken.
  * Incremented by one each time you enter a command, be it recognized or not.
* Whether you won/lost.


### Building & Running It

Build the game by running `make`, and then run `./lighthouse`

If you get stuck you can see command by entering `help`.



## Z80 Implementation

The Z80 implementation is based upon the C-implementation, with a few
small changes.

The implementation uses a simple set of structures:

* A command-table to map input-commands to handlers.
* An item-table to store details about each object in the game.
* A person table to store telephone messages.

The whole implementation is defined in the file [game.z80](game.z80).

Along the way I did realize that having fixed inventory slots made the
coding more of a challenge, so I made the location of each object a
property of the object itself.


### Changes

* The Z80 version has more easter-eggs (Try typing "`xyzzy`" a few times).
* There is no grue in this version.
  * It will come.
* The Z80 version can be built with the text-strings, and game code, protected by simple XOR encryption
  * Stops you looking through the binary for hints.
  * Run `make release` to build the _protected_ version, and `make game` to build a rare version.


### Building & Running It

Ensure you have the `pasmo` assembler installed, then build the code
by running `make game`, or `make release`.

In either case the output will be a binary named `lihouse.com` which you
should be able to run upon your system - or under a CP/M emulator.


### Downloading It

If you look on our [release page](https://github.com/skx/lighthouse-of-doom/releases/) you can find the latest stable build.

Transfer `lihouse.com` to your system, and run `LIHOUSE` to launch it.


## Bugs

Report them as you see them :)


Steve
