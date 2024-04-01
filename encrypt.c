/*
 * Generate an encrypted version of the specified input file.
 *
 * Optionally update the CRC check of the file - this is necessary
 * for the .TAP version we generate for the ZX Spectrum.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef unsigned char byte;


// calculate the checksum for the given region
byte crc(byte *start, int length)
{
    byte tcrc = 0;

    for (int i = 0; i < length; i++)
        tcrc = tcrc ^ start[i];

    return tcrc;
}

int main(int argc, char *argv[])
{
    // check argument count
    if (argc != 3 && argc != 4)
    {
        printf("Usage: encrypt [-crc] input output\n");
        return 1;
    }

    // flags / arguments
    int do_crc = 0;
    char *input = NULL;
    char *output = NULL;

    // look for flags
    if (argc == 4)
    {
        // Should we run a CRC update?
        for (int i = 1; i < argc ; i++)
        {
            if (strcmp(argv[i], "-crc") == 0)
            {
                do_crc = 1;
            }
        }
    }

    // look for input/output names.
    for (int i = 1; i < argc ; i++)
    {
        // Ignore flags
        if (strcmp(argv[i], "-crc") == 0)
        {
            continue;
        }

        // input file goes first
        if (input == NULL)
        {
            input = argv[i];
            continue;
        }

        // output file goes second.
        if (output == NULL)
        {
            output = argv[i];
            continue;
        }
    }

    printf("Input file: %s\n", input);
    printf("Output file: %s\n", output);

    if (do_crc)
    {
        printf("CRC will be updated\n");
    }
    else
    {
        printf("No CRC update\n");
    }

    // Open the file for reading
    FILE *f = fopen(input, "r");

    if (f == NULL)
    {
        printf("Failed to open input file: %s\n", input);
        return 1;
    }

    // get file size
    fseek(f, 0L, SEEK_END);
    size_t sz = ftell(f);

    printf("File size is %ld bytes\n", sz);

    // get back to start
    fseek(f, 0L, SEEK_SET);

    // allocate memory
    unsigned char *buf = malloc(sz);

    if (buf == NULL)
    {
        printf("failed to allocate memory\n");
        return 1;
    }

    // read the file
    int n = fread(buf, sizeof(unsigned char), sz, f);

    if (ferror(f) != 0)
    {
        printf("error reading\n");
        return 1;
    }

    if (n != sz)
    {
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

            if (do_crc)
            {
                // Now we have to fixup the CRC
                unsigned char *pos = buf;

                for (int i = 1; i < sz; i++)
                {
                    size_t blocksize = pos[0] | (pos[1] << 8);

                    if ((pos + blocksize + 1) < (buf + sz))
                    {
                        if (blocksize > 1)
                        {
                            char ccrc = crc(&pos[2], blocksize - 1);

                            if (pos[blocksize + 1] != ccrc)
                            {
                                printf("Updated CRC\n");
                                pos[blocksize + 1] = ccrc;
                            }
                        }
                    }


                    pos += blocksize + 2;
                }
            }

            // Write
            FILE *nw = fopen(output, "w");

            if (nw == NULL)
            {
                printf("Failed to open file for writing: %s\n", output);
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
