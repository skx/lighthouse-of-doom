#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"

//******************************
//
// Inventory Management
//

// does the user have this item in their inventory?
int inventory_has_item(char *name)
{
    for (int i = 0; i < MAX_INV ; i++)
    {
        int id  = inv[i];

        if (id != -1)
        {
            if (strcmp(items[id].name, name) == 0)
            {
                return 1;
            }
        }
    }

    return 0;
}

// add the item to the inventory
// return 0 if we can take it
void inventory_take_item(char *name)
{

    for (int slot = 0 ; slot < MAX_INV; slot ++)
    {

        // found an empty slot?
        if (inv[slot] == -1)
        {

            // find the item by name
            int id = 0;

            while (strlen(items[id].name) > 0)
            {
                if (strcmp(items[id].name, name) == 0)
                {

                    // take it
                    inv[slot] = id;
                    return;
                }

                id++;
            }

            printf("Failed to find item to take:%s\n", name);
        }
    }

    printf("You're carrying too much.\n");
}

// remove item from the inventory
void inventory_drop_item(char *name)
{

    // for each item we could carry
    for (int i = 0; i < MAX_INV ; i++)
    {

        // get the item
        int id  = inv[i];

        if (id != -1)
        {

            // if it matches - drop it
            if (strcmp(items[id].name, name) == 0)
            {
                inv[i] = -1;
                return ;
            }
        }
    }
}
