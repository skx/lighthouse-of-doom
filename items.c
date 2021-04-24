/*
 * Items.c - List of global objects
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "globals.h"

object_t items[] = {
    {name: "generator", desc: "A small generator."},
    {name: "mirror", desc: "A small mirror."},
    {name: "mirror-broken", desc: "A small mirror, which is cracked and broken."},
    {name: "rug", desc: "A small rug."},
    {name: "telephone", desc: "A telephone, wired to the wall."},
    {name: "torch", desc: "A small torch."},
    {name: "trapdoor-closed", desc: "A closed trapdoor."},
    {name: "trapdoor-open", desc: "An open trapdoor."},
    {name: "", desc: ""},
};



//******************************
//
// Add/Remove/Test for items in a location
//

// is the named object present?
int is_object_present( char *name ) {

    for( int i = 0; i < MAX_ITEMS_PER_ROOM; i++ ) {

        int item = world[location].items[i];
        if ( ( item != -1 ) &&
             ( strcmp( items[item].name, name ) == 0 ) ) {
            return 1;
        }
    }
    return 0;
}
// add a named item to the given location
void add_item( char *name, int location ) {
    int id = 0;

    while( strlen(items[id].name) > 0 ) {

        if ( strcmp(items[id].name, name ) == 0 ) {

            // found the item
            for ( int i = 0; i < MAX_ITEMS_PER_ROOM; i++ ) {
                if ( world[location].items[i] == -1 ) {
                    world[location].items[i] = id;
                    return;
                }
            }
            printf("FAILED TO ADD %s to location - it is full\n", name);
        }
        id++;
    }

    printf("Failed to find item %s\n", name);
}

// remove the named item to the given location
void remove_item( char *name, int location ) {

    // find the item-id
    int id = 0;
    while( strlen(items[id].name) > 0 ) {

        if ( strcmp(items[id].name, name ) == 0 ) {

            // found the item - with ID: "id"
            // remove it
            for ( int i = 0; i < MAX_ITEMS_PER_ROOM; i++ ) {
                if ( world[location].items[i] == id ) {
                    world[location].items[i] = -1;
                    return;
                }
            }
            printf("FAILED TO ADD %s to location - it is full\n", name);
        }
        id++;
    }

    printf("Failed to find item to remove %s\n", name);
}
