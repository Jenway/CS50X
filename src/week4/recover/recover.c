#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
#define BLOCK_SIZE 512
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    };
    BYTE buffer[BLOCK_SIZE];
    int jpg_count = 0;
    char out_put_name[8];
    FILE *img = NULL;
    // Open memory card
    // repeat until end of card
    // read 512 bytes into a buffer
    while (fread(&buffer, BLOCK_SIZE, 1, file))
    {
        // If it starts a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if it's not the first jpeg no need to closeit
            if (jpg_count != 0)
            {
                fclose(img);
            }
            // find it so open it
            sprintf(out_put_name, "%03i.jpg", jpg_count);
            jpg_count++;
            img = fopen(out_put_name, "w");
        }
        if (jpg_count != 0)
        {
            // write it as wh have found
            fwrite(&buffer, BLOCK_SIZE, 1, img);
        }
    }
    fclose(file);
    fclose(img);
    return 0;
}