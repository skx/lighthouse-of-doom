#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "globals.h"



// Word will have a term the user can enter, and a function-pointer
// of code to invoke.
//
// If a word is "hidden:1" it is not shown in the output of help.
word_t dictionary[] =
{
    { name: "DOWN", txt: "Descend the stairs", ptr: down_fn },
    { name: "DROP", txt: "Drop an item", ptr: drop_fn },
    { name: "EXAMINE", txt: "Examine an object or item", ptr: examine_fn },
    { name: "GET", txt: "Take an item", ptr: get_fn },
    { name: "HELP", txt: "Show some help", ptr: help_fn },
    { name: "INVENTORY", txt: "See what you're carrying", ptr: inventory_fn },
    { name: "LOOK", txt: "Look at your surroundings", ptr: look_fn },
    { name: "OPEN", txt: "Open an item", ptr: open_fn },
    { name: "QUIT", txt: "Quit the game", ptr: quit_fn },
    { name: "UP",   txt: "Climb the stairs", ptr: up_fn },
    { name: "USE", txt: "Use an item", ptr: use_fn },

    // Synonyms
    { name: "TAKE", hidden: 1, ptr: get_fn },
    { name: "PICKUP", hidden: 1, ptr: get_fn },

    // Easter-Eggs
    { name: "CALL", hidden: 1, ptr: call_fn},
    { name: "DIAL", hidden: 1, ptr: call_fn},
    { name: "PHONE", hidden: 1, ptr: call_fn},
    { name: "FUCK", hidden: 1, ptr: language_fn},
    { name: "SHIT", hidden: 1, ptr: language_fn},

    // Abbreviations
    { name: "L", hidden: 1, ptr: look_fn },
    { name: "INV", hidden: 1, ptr: inventory_fn },
    { name: "I", hidden: 1, ptr: inventory_fn },
    { name: "U",  hidden: 1, ptr: up_fn },
    { name: "D",  hidden: 1, ptr: down_fn },
    { name: "", ptr: NULL },
};


void call_fn(char *input)
{
    if (!is_object_present("telephone"))
    {
        printf("There is no telephone here!\n");
        return;
    }

    if ((strstr(input, "999") != NULL) ||
            (strstr(input, "911") != NULL) ||
            (strstr(input, "POLICE") != NULL))
    {
        printf("Trying to call the police was a smart move, but Adventure Bay\n"
               "does not have a well-funded police-service.\n");
        return;
    }

    if ((strstr(input, "PAW") != NULL) &&
            (strstr(input, "PATROL") != NULL))
    {
        printf("The Paw Patrol are already on a roll, and cannot be disturbed.\n");
        return;
    }

}

void inventory_fn(char *input)
{
    int found = 0;

    for (int i = 0; i < MAX_INV; i++)
    {

        // this slot is not empty?
        if (inv[i] != -1)
        {
            found = 1;
        }
    }

    if (found)
    {
        printf("You are carrying:\n");

        for (int i = 0; i < MAX_INV; i++)
        {

            // this slot is not empty?
            int item = inv[i];

            if (item != -1)
            {
                printf("\t%s\n", items[item].desc);
            }
        }
    }
    else
    {
        printf("You are not carrying anything.\n");
    }
}

void language_fn(char *input)
{
    printf("Such bad language!\n");
}

void look_fn(char *input)
{
    printf("You are in %s\n\n", world[location].desc);

    // First time we enter a room we show the full
    // description.
    //
    // Or if the user types "LOOK"
    int full = 0;

    if (world[location].seen == 0 ||
            strcmp(input, "LOOK") == 0)
    {
        full = 1;
    }

    // We've shown the short description, return unless
    // we're showing everything
    if (!full)
        return;

    printf("%s\n", world[location].edesc);

    int found  = 0;

    for (int i = 0; i < MAX_ITEMS_PER_ROOM; i++)
    {
        if (world[location].items[i] != -1)
        {
            found = 1;
        }
    }

    if (found)
    {
        printf("You see:\n");

        for (int i = 0; i < MAX_ITEMS_PER_ROOM; i++)
        {
            int id = world[location].items[i];

            if (id != -1)
            {
                printf("\t%s\n", items[id].desc);
            }
        }
    }

    world[location].seen = 1;
}

void quit_fn(char *input)
{
    printf("Game over man, game over!\n");
    exit(0);
}

void help_fn(char *input)
{
    int dict = 0;
    printf("The following commands are available:\n");

    while (strlen(dictionary[dict].name) > 0)
    {
        if (dictionary[dict].hidden != 1)
        {
            printf("\t%s\n\t  %s\n", dictionary[dict].name, dictionary[dict].txt);
        }

        dict++;
    }
}

void up_fn(char *input)
{

    // basement - no torch
    if (location == 4)
    {

        if ((rand() % 10) >= 6)
        {
            printf("You cannot see where you're going, but it seems like the\n"
                   "smell is getting stronger\n");
            return;
        }
        else
        {
            printf("The smell is definitely closer now.\n");
            printf("You panic, and fall to the ground.\n");
            printf("The darkness is a mercy, as the grue attacks..\n");
            printf("Too bad the ship will crash; more food for the grue though.\n");
            dead = 1;
        }
    }

    // basement - with torch
    if (location == 3)
    {
        location = 2;
        look_fn(input);
        return;
    }

    // ground
    if (location == 2)
    {
        location = 1;
        look_fn(input);
        return;
    }

    // middle
    if (location == 1)
    {
        location = 0;
        look_fn(input);
        return;
    }

    // top
    printf("You cannot go up from here!\n");
}

void down_fn(char *input)
{
    if (location == 0)
    {
        location = 1;
        look_fn(input);
        return;
    }

    if (location == 1)
    {
        location = 2;
        look_fn(input);
        return;
    }

    if (location == 2)
    {

        // we're on the ground floor
        // if the trapdoor is open you can go down
        if (is_object_present("trapdoor-open"))
        {

            if (inventory_has_item("torch-lit"))
            {
                location = 3;
                look_fn(input);
            }
            else
            {
                location = 4;
                look_fn(input);
            }

            return;

        }
    }

    if (location == 4)
    {
        if ((rand() % 10) >= 6)
        {
            printf("You cannot see where you're going, but it seems like the\n"
                   "smell is getting stronger\n");
            return;
        }
        else
        {
            printf("The smell is definitely closer now.\n");
            printf("You panic, and fall to the ground.\n");
            printf("The darkness is a mercy, as the grue attacks..\n");
            printf("Too bad the ship will crash; more food for the grue though.\n");
            dead = 1;
        }
    }

    printf("You cannot go down from here!\n");
}

// examine floor|rug
void examine_fn(char *input)
{

    if (strstr(input, "MIRROR") != NULL)
    {
        if (is_object_present("mirror") || inventory_has_item("mirror"))
        {
            printf("The mirror doesn't seem to be anything special.\n");
            printf("But your reflection?  It looks fabulous.\n");
            return;
        }

        if (is_object_present("mirror-broken") || inventory_has_item("mirror-broken"))
        {
            printf("The mirror looks like it was once small and delicate.\n");
            printf("But now it shows a distorted reflection of yourself,\n");
            printf("which is oddly unsettling.\n");
            return;
        }

        printf("I see no mirror here!\n");
        return;
    }

    // ground-floor
    if ((strstr(input, "RUG") != NULL)  ||
            (strstr(input, "FLOOR") != NULL))
    {
        if (is_object_present("rug"))
        {
            printf("The rug on the floor seems to be covering a trapdoor\n");
            printf("You move it out of the way..\n");

            location_add_item("trapdoor-closed", location);
            location_remove_item("rug", location);

            return ;
        }
        else
        {
            printf("I see no rug here.\n");
            return;
        }
    }

    if (strstr(input, "TRAPDOOR") != NULL)
    {
        if (is_object_present("trapdoor-open"))
        {
            printf("The trapdoor is an average trapdoor.\n");
            return;
        }

        if (is_object_present("trapdoor-closed"))
        {
            printf("The trapdoor is an average trapdoor.\n"
                   "Perhaps you should open it to learn more?\n");
            return;
        }
    }

    printf("You notice nothing special.\n");
}

// get <torch>
void get_fn(char *input)
{

    if (strstr(input, "TORCH") != NULL)
    {
        if (is_object_present("torch"))
        {
            printf("You take the torch.\n");
            location_remove_item("torch", location);
            inventory_take_item("torch");
            return ;
        }

        if (is_object_present("torch-lit"))
        {
            printf("You take the torch.\n");
            location_remove_item("torch-lit", location);
            inventory_take_item("torch-lit");
            return ;
        }

        printf("The torch is not here, and cannot be taken!");
        return;
    }

    if (strstr(input, "MIRROR") != NULL)
    {
        if (is_object_present("mirror"))
        {
            printf("You take the mirror.\n");
            location_remove_item("mirror", location);
            inventory_take_item("mirror");
            return ;
        }

        if (is_object_present("mirror-broken"))
        {
            printf("You take the broken mirror.\n");
            location_remove_item("mirror-broken", location);
            inventory_take_item("mirror-broken");
            return ;
        }

        printf("The mirror is not here, and cannot be taken!");
        return;
    }

    if (strstr(input, "RUG") != NULL)
    {
        if (is_object_present("rug"))
        {
            printf("The rug is too heavy to carry, but you can push it aside.\n");
            location_add_item("trapdoor-closed", location);
            location_remove_item("rug", location);
            return;
        }
        else
        {
            printf("I see no rug here.\n");
            return;
        }
    }

    if (strstr(input, "GENERATOR") != NULL)
    {
        if (is_object_present("generator"))
        {
            printf("You take the generator, struggling under the weight.\n");
            location_remove_item("generator", location);
            inventory_take_item("generator");
            return ;
        }
        else
        {
            printf("The generator is not here, and cannot be taken!");
            return;
        }
    }

    printf("You cannot %s\n", input);
}

// drop <torch>
void drop_fn(char *input)
{

    if (strstr(input, "TORCH") != NULL)
    {
        if (inventory_has_item("torch"))
        {
            inventory_drop_item("torch");
            location_add_item("torch", location);
            printf("You drop the torch.\n");
            return;
        }

        if (inventory_has_item("torch-lit"))
        {
            inventory_drop_item("torch-lit");
            location_add_item("torch-lit", location);
            printf("You drop the torch.\n");
            return;
        }

        printf("You're not carrying a torch!");
        return ;
    }

    if (strstr(input, "MIRROR") != NULL)
    {
        if (inventory_has_item("mirror"))
        {
            inventory_drop_item("mirror");
            location_add_item("mirror-broken", location);
            printf("You drop the mirror, which cracks and breaks.\n");
            return;
        }

        if (inventory_has_item("mirror-broken"))
        {
            inventory_drop_item("mirror-broken");
            location_add_item("mirror-broken", location);
            printf("You drop the broken mirror, but luckily it doesn't break any more.\n");
            return;
        }

        printf("You're not carrying a mirror!");
        return ;
    }

    if (strstr(input, "GENERATOR") != NULL)
    {
        if (inventory_has_item("generator"))
        {
            inventory_drop_item("generator");
            location_add_item("generator", location);
            printf("You place the generator down on the ground.\n");
            return;
        }

        printf("You're not carrying the generator!");
        return ;
    }

    printf("You can't %s\n", input);
}

void open_fn(char *input)
{

    if (strstr(input, "TRAPDOOR") != NULL)
    {

        if (is_object_present("trapdoor-closed"))
        {

            printf("The trapdoor opens, and you see a shadowy set of stairs\n"
                   "leading downward into what is obviously a basement.\n");

            location_add_item("trapdoor-open", location);
            location_remove_item("trapdoor-closed", location);
        }
        else
        {
            printf("I see no trapdoor here.\n");
        }

        return;
    }

    printf("Opening that doesn't make sense!\n");
}

void use_fn(char *input)
{
    //
    // OK when this is called we'll be "USE XXXX"
    //
    // We want to find the item, if it exists.
    //
    // If the item is not found we say "We can't use XXXX"
    //
    // If the item is found it either needs to be:
    //
    //   A.  IN the location
    //
    //   B.  In the inventory
    //
    // We'll be called with "USE XXXX" - so we need to find
    // the item.
    char *itm = object_from_input(input);

    if (itm == NULL)
    {
        printf("You need to tell me what to use!\n");
        return;
    }

    //
    // Right see if this item is in the user's possession
    //
    for (int i = 0; i < MAX_INV; i++)
    {

        // The item
        int carried  = inv[i];

        // Is the item present?  With the same name?
        //
        // Here we cap the comparison length to allow "mirror" to
        // match both "mirror" and "mirror-broken".
        //
        if (carried != -1 && strncmp(itm, items[carried].name, strlen(items[carried].name)) == 0)
        {
            if (items[carried].use_carried != NULL)
            {
                (*items[carried].use_carried)(itm);
            }
            else
            {
                printf("Nothing happens\n");
            }

            free(itm);
            return;
        }
    }

    //
    // Look for the item in the environment
    //
    for (int i = 0; i < MAX_ITEMS_PER_ROOM; i++)
    {

        // The item
        int present = world[location].items[i];

        // Is this slot full of something?
        if (present != -1)
        {
            // Here we cap the comparison length to allow "mirror" to
            // match both "mirror" and "mirror-broken".
            if (strncmp(itm, items[present].name, strlen(items[present].name)) == 0)
            {
                if (items[present].use != NULL)
                {
                    (*items[present].use)(itm);
                }
                else
                {
                    printf("Nothing happens\n");
                }

                free(itm);
                return;
            }
        }
    }

    printf("It doesn't look like that item is present, or in your inventory!\n");
    free(itm);
    return;
}
