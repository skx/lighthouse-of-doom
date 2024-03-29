/*
 * World.c - List of locations
 */

#include "globals.h"


/*
 * The world
 */
location_t world[] =
{
    // 0
    {
desc: "the top floor of the lighthouse."
        ,
edesc:
        "The lighthouse has a spiral staircase which runs from top to bottom.\n"
        "Through the window you can see the lights of an approach ship, and\n"
        "you know that it will crash upon the rocks if you can't signal it away.\n"
        "Too bad the lighthouse light doesn't seem to be working, it looks like\n"
        "there's a problem with the power.\n"
        ""
        ,
    },

    // 1
    {
desc: "the middle floor of the lighthouse."
        ,
edesc:
        "The middle floor of the lighthouse seems to be a relaxation-room,\n"
        "you see some comfy chairs, a work-desk, as well as various odds and\n"
        "ends.\n\n"
        "An impressive painting hangs over the desk.\n"
        ,
    },

    // 2
    {
desc: "the ground floor of the lighthouse."
        ,
edesc: "The ground floor seems very crowded, with most of the room\n"
        "taken up by a coat-rack, boots, and similar things\n"
        ,
    },

    // 3
    {
desc: "the lighthouse basement."
        ,
edesc: "This seems to be a graveyard for discarded machinery, and\n"
        "oddly enough old children's toys.\n"
        ,
    },

    // 4
    {
desc: "a dark place."
        ,
edesc: "You cannot see anything, but you can hear a snarling.\n"
        "There is also a strong smell, a feral smell, could it be that this\n"
        "is the haunt of a grue?"
        ,
    },
};
