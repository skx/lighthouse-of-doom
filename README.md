# The Lighthouse of Doom

This repository contain a simple text-based adventure game.

Currently this is implemented in portable C, however the intention is
to re-implement the game to run on a CP/M system.



## Plot

* You're inside a lighthouse (trapped? doesn't really matter I guess).
* You see a boat on the horizon, heading your way.
* But "oh no!", the lighthouse is dark.
  * The boat will surely crash if you don't turn on the main light.

The game is over, when you either fix the light, or find another solution.
If you do not achieve victory in 100 turns the boat runs aground, and
death will consume you all.  (It is a _very_ big boat!)



## C Implementation

My goal behind this game is to write something simple, which can then be ported
to run upon a CP/M system.  That mostly means that we should store as much
logic as possible in a series of lookup-tables, or array of items - rather
than writing complex logic within our handlers.

The implementation will mostly be concerned with a series of data-structures,
which are essentially arrays of objects.

The obvious structures we're going to need are:

* A location.
  * This has a short description and a long one.
    * The long one will be displayed the first time you enter the location.
    * The short one otherwise.
      * Though "LOOK" will display the long one.
  * Since we're a vertical game we're not going to focus upon entrances/exits.
  * A location can contain objects, some of which can be taken and dropped.
* An object
  * An object has a name and a description.
  * Objects need to have a "collectible" property, if this is not set they are immobile.
  * Objects have no state, so we fake actions via "duplicate" objects.

The game-state will contain:

* Your current location (i.e. index into location-table).
* A list of any items you're carrying.
* The number of turns you've taken.
  * Incremented by one each time you enter a command, be it recognized or not.
* Whether you won/lost.


### Running The Game

Build the game by running `make`, and then launch it.

If you get stuck you can see command by entering `help`.



## Z80 Implementation

There is not yet a complete implementation of the game written in z80
assembly language, however there is a basic stub.

The C-code will not be literally ported over, however the same text will
be used and the idea of using tables and structures will be maintained.



## Bugs

Report them as you see them :)


Steve
