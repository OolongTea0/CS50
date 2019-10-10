#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        fprintf(stderr, "Not enough inputs\n");
        return 1;
    }

    if (argc > 2)
    {
        fprintf(stderr, "Too much inputs\n");
        return 2;
    }

    FILE *output, *input = fopen(argv[1], "r");

    int n = 0; //File counter
    char *filename = malloc(10);

    // Used to hold blocks of data
    BYTE *buffer = malloc(512);

    // Reads 512 Bytes (1 block) of information at once
    while (fread(buffer, sizeof(buffer), 1, input) == 1)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] % 0xf0) == 0xe0)
        {
            if (n > 0)
            {
                fclose(output);
            }

            //Creates and opens file, increases counter
            sprintf(filename, "%03i.jpg", n);
            output = fopen(filename, "w");
            n++;
       }

        if (n >= 1)
        {
            fwrite(buffer, sizeof(buffer), 1, output);
        }

    }


    fclose(output);

    fclose(input);

    return 0; //mission successful
}