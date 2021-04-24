/*
 * Items.c - List of global objects
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "globals.h"

object_t items[] =
{
    {name: "generator", desc: "A small generator.", use: use_generator, use_carried: use_generator_carried, get_fn: get_generator, drop_fn: drop_generator},
    {name: "mirror", desc: "A small mirror.", use: use_mirror, get_fn: get_mirror, drop_fn: drop_mirror},
    {name: "mirror-broken", desc: "A small mirror, which is cracked and broken.", use: use_mirror, get_fn: get_mirror_broken, drop_fn: drop_mirror_broken},
    {name: "rug", desc: "A small rug."},
    {name: "book", desc: "A small black book.", get_fn: get_book, drop_fn: drop_book},
    {name: "telephone", desc: "A telephone, wired to the wall.", use: use_telephone },
    {name: "torch", desc: "A small torch.", use: use_torch, use_carried: use_torch_carried,     get_fn: get_torch, drop_fn: drop_torch },

    {name: "torch-lit", desc: "A small torch, which is lit.", get_fn: get_torch_lit, drop_fn: drop_torch_lit  },
    {name: "trapdoor-closed", desc: "A closed trapdoor."},
    {name: "trapdoor-open", desc: "An open trapdoor."},
    {name: "", desc: ""},
};



//******************************
//
// Add/Remove/Test for items in a location
//

// is the named object present?
int is_object_present(char *name)
{

    for (int i = 0; i < MAX_ITEMS_PER_ROOM; i++)
    {

        int item = world[location].items[i];

        if ((item != -1) &&
                (strcmp(items[item].name, name) == 0))
        {
            return 1;
        }
    }

    return 0;
}

// add a named item to the given location
void location_add_item(char *name, int location)
{
    int id = 0;

    while (strlen(items[id].name) > 0)
    {

        if (strcmp(items[id].name, name) == 0)
        {

            // found the item
            for (int i = 0; i < MAX_ITEMS_PER_ROOM; i++)
            {
                if (world[location].items[i] == -1)
                {
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
void location_remove_item(char *name, int location)
{

    // find the item-id
    int id = 0;

    while (strlen(items[id].name) > 0)
    {

        if (strcmp(items[id].name, name) == 0)
        {

            // found the item - with ID: "id"
            // remove it
            for (int i = 0; i < MAX_ITEMS_PER_ROOM; i++)
            {
                if (world[location].items[i] == id)
                {
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


void drop_book(int id)
{
    printf("You drop the small black book.\n");
    inventory_drop_item(items[id].name);
    location_add_item("mirror-broken", location);
}

void drop_mirror(int id)
{
    printf("You drop the mirror, which cracks and breaks.\n");
    inventory_drop_item(items[id].name);
    location_add_item("mirror-broken", location);
}
void drop_mirror_broken(int id)
{
    printf("You drop the broken mirror, more carefully this time.\n");
    inventory_drop_item(items[id].name);
    location_add_item(items[id].name, location);
}
void drop_torch(int id)
{
    printf("You drop the torch.\n");
    inventory_drop_item(items[id].name);
    location_add_item(items[id].name, location);
}
void drop_torch_lit(int id)
{
    printf("You drop the torch.\n");
    inventory_drop_item(items[id].name);
    location_add_item(items[id].name, location);
}
void drop_generator(int id)
{
    printf("You place the generator down on the ground.\n");
    inventory_drop_item(items[id].name);
    location_add_item(items[id].name, location);
}


void get_book(int id)
{
    printf("You pickup the book\n");
}
void get_torch(int id)
{
    printf("You pickup the torch.\n");
}
void get_torch_lit(int id)
{
    printf("You pickup the lit torch.\n");
}

// When the user "USES TORCH" it becomes lit
void use_torch(char *txt)
{
    location_remove_item("torch", location);
    location_add_item("torch-lit", location);

    printf("The torch turns on.\n");
}

// This is invoked when the user "USE TORCH", when carrying the torch.
void use_torch_carried(char *txt)
{
    inventory_drop_item("torch");
    inventory_take_item("torch-lit");

    printf("The torch turns on.\n");

    // If we're in the dark room move to the lit basement
    if (location == 4)
    {
        location = 3;
        look_fn(txt);
    }
}

void get_generator(int id)
{
    printf("You take the generator, struggling under the weight.\n");
}
void use_generator(char *txt)
{
    printf("You study the diagram drawn on the side of the generator,\n"
           "and connect it to the side of the lighting console.\n");
    printf("With a mighty pull of the starting mechanism the machine\n"
           "comes to life, and power returns to the console\n\n");
    printf("The lighthouse beam of light starts to rotate, and in the\n"
           "distance you hear a horn from the approaching boat.\n");
    printf("It obviously sees you, and starts to turn.  It looks like\n"
           "everything is going to be OK!\n");
    won = 1;
}

void use_generator_carried(char *txt)
{
    printf("You try to use the generator, but that seems impossible while\n"
           "you're still carrying it.");
}

void get_mirror(int id)
{
    printf("You pickup the mirror.\n");
}
void get_mirror_broken(int id)
{
    printf("You pickup the broken mirror.\n");
}
void use_mirror(char *txt)
{
    printf("USE_MIRROR");
}

void use_telephone(char *txt)
{
    printf("To use the telephone you must CALL somebody!\n");
}
