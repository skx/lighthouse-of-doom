/*
 * Load `game.com` and scramble the strings.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

int main(int argc, char *argv[])
{
    FILE *f = fopen("lihouse.com", "r");

    if (f == NULL)
    {
        printf("Failed to open file\n");
        return 0;
    }

    // get file size
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);

    // get back to start
    fseek(f, 0L, SEEK_SET);

    // allocate memory
    char *buf = malloc(sz);

    if (buf == NULL)
    {
        printf("failed to allocate memory\n");
        return 0;
    }

    // read the file
    int n = fread(buf, sizeof(char), sz, f);

    if (ferror(f) != 0)
    {
        printf("error reading\n");
        return 1;
    }
    if ( n != sz ) {
        printf("short read\n");
        return 1;
    }

    fclose(f);

    // Look for our flag
    for (int i = 0; i < sz; i++)
    {
        if ((buf[i] == 'S') &&
                (buf[i + 1] == 'K') &&
                (buf[i + 2] == 'X'))
        {

            printf("Found start of section to encrypt.\n");

            // starting key
            char k = '%';

            // XOR with our key, and increase that key
            for (int pos = i ; pos < sz; pos++)
            {
                buf[pos] ^= k;
                k++;
            }

            // Write
            FILE *nw = fopen("lihouse2.com", "w");

            if (nw == NULL)
            {
                printf("Failed to open file for writing\n");
            }

            fwrite(buf, sz, 1, nw);
            fclose(nw);

            printf("All done\n");
            return 0;

        }
    }

    printf("Failed to find encryption start position\n");
    return 1;
}
