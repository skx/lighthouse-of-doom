# The Lighthouse of Doom

This repository contain a simple text-based adventure game, implemented
twice, once in portable C, and once in Z80 assembly language, available
for both the CP/M operating system and the humble 48k ZX Spectrum.

My intention was to write a simple text-based adventure game to run under
CP/M.  Starting large projects in Z80 assembly language from scratch
is a bit of a daunting prospect, so I decided to code the game in C first,
so that I could get the design right, and avoid getting stuck in too many
low-level details initially.  Later I ported to the Spectrum, because
it seemed like a fun challenge for myself!

Quick links within this README file:

* [Plot of the game](#game-plot)
* [C Implementation](#c-implementation)
* [Z80 Implementation](#z80-implementation)
  * [Z80 Changes](#z80-changes)
* [Compiling & running it](#compiling--running-it)
* [Downloading It](#downloading-it)
* [Bugs?](#bugs)


## Game Plot

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



## Z80 Implementation

The Z80 implementation is based upon the C-implementation, with a few
small changes.

The implementation uses a simple set of structures:

* A command-table to map input-commands to handlers.
* An item-table to store details about each object in the game.
* A person table to store telephone messages.

The main implementation can be found in the file [game.z80](game.z80),
but because we support two targets (CP/M 2.x and the ZX Spectrum) there
is a small amount of platform-specific code found in [bios.z80](bios.z80).

The `Makefile` should build everything appropriately for both systems,
defining `SPECTRUM`, and `ENTRYPOINT` as appropriate.


### Z80 Changes

* Along the way I realized that having fixed inventory slots made the coding more of a challenge, so I made the location of each object a property of the object itself.
* The Z80 version has more easter-eggs (Try typing "`xyzzy`" a few times).
* There are __two__ victory conditions.
* The CP/M version of the game can be built with the text-strings, and game code, protected by simple XOR encryption:
  * This stops users from looking through the binary for hints.
  * Run `make release` to build the _protected_ CP/M version.


## Compiling & Running It

Ensure you have the `pasmo` assembler installed, and then use the supplied Makefile to compile the game.

Running `make` will generate the default targets:

* `make lighthouse`  -> Build the game for linux.
* `make lihouse.com` -> Build the game for CP/M, without the XOR encryption.
* `make lihouse.tap` -> Build the game for the 48k ZX Spectrum.

If you wish to build only individual things then :

* `make game-cpm` to build a normal CP/M version.
* `make game-spectrum` to build the ZX Spectrum version.
* `make lighthouse` will build the C-game for Linux
* `make release` will build the _protected_ CP/M version.



## Downloading It

If you look on our [release page](https://github.com/skx/lighthouse-of-doom/releases/) you can find the latest stable build.

* For CP/M download `lihouse.com` to your system, and then run `LIHOUSE` to launch it.
* For the ZX Spectrum download `lihouse.tap` to your system, and then launch in your favourite emulator.


## Bugs?

Report any bugs as you see them:

* A crash of the game is a bug.
* Bad spelling, grammar, or broken punctuation are also bugs.
* Getting into a zombie-state where winning or losing are impossible is a bug.



Steve
