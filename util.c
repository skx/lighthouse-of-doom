/*
 * util.c - Utility functions
 */

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

// Get the name of the object from input such as:
//
//   USE TORCH
//   CALL RYDER
//   DROP CAKE
//
char *object_from_input(char *input)
{

    char seps[]   = " \t";
    char *token;
    char *obj = NULL;

    /* Establish string and get the first token: */
    token = strtok(input, seps);

    while (token != NULL)
    {
        if (obj)
            free(obj);

        obj = strdup(token);

        /* Get next token: */
        token = strtok(NULL, seps);
    }

    if (obj != NULL)
    {
        for (int i = 0; i < strlen(obj); i++)
        {
            obj[i] = tolower(obj[i]);
        }
    }

    return obj;
}
