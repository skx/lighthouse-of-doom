//
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "globals.h"


// The player's location
int location = 0;

// Count of elapsed turns
int turn = 0;

// Did you win?
int won = 0;

// Did you die?
int dead = 0;

// The player's inventory
int inv[MAX_INV] = {0};



int main(int argc, char *argv[])
{
    srand(time(NULL));
    char line[1024];

    // all rooms are empty
    for (int r = 0 ; r <= MAX_ROOMS; r++)
    {
        for (int i = 0; i < MAX_ITEMS_PER_ROOM; i++)
        {
            world[r].items[i] = -1;
        }
    }

    // The play is carrying nothing
    for (int i = 0; i < MAX_INV; i++)
    {
        inv[i] = -1;
    }

    // add the rug to the ground-floor,
    // and the torch to the top-floor.
    location_add_item("torch", 0);
    location_add_item("mirror", 1);
    location_add_item("telephone", 1);
    location_add_item("rug", 2);
    location_add_item("generator", 3);

    look_fn("LOOK");

    while ((won == 0) && (dead == 0))
    {

        // show prompt
        printf(">");
        fflush(stdout);

        // read line
        if (fgets(line, sizeof(line) - 1, stdin) == NULL)
        {
            printf("Ctrl-D pressed; aborting\n");
            return 0;
        }

        // strip newlines
        for (int i = 0; i < sizeof(line) - 1; i++)
        {
            if (line[i] == '\n' ||
                    line[i] == '\r')
            {
                line[i] = '\0';
            }
        }

        if (strlen(line) < 1)
        {
            goto ok;
        }

        // upper-case for consistency
        size_t len = strlen(line);

        for (size_t i = 0; i < len; i++)
        {
            line[i] = toupper(line[i]);
        }

        // Can we split this into a word?
        int dict = 0;

        while (strlen(dictionary[dict].name) > 0)
        {

            // If we got a match on this word
            if (strncmp(dictionary[dict].name, line, strlen(dictionary[dict].name)) == 0)
            {
                // Call the handler
                (*dictionary[dict].ptr)(line);

                // And prepare for more input
                goto end;
            }

            dict++;
        }

        // handlers now ..
        printf("I'm sorry, I did not understand: %s\n", line);
end:

        turn ++;

        if (turn % 10 == 0)
        {
            printf("\nThe ship is coming closer, you had best hurry up!\n\n");
        }

        printf("\n");
ok:
        memset(line, '\0', sizeof(line));
    }

    printf("Game over in %d turns\n", turn);
}
