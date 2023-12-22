#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;
    FILE *file, *img;
    int count = 0, BLOCK_SIZE = 512;
    BYTE *buffer;
    char *filename;

    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    //Open memory card
    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("file can't be opened \n");
        return 2;
    }

    buffer = (BYTE *)malloc(BLOCK_SIZE * sizeof(BYTE));
    if (buffer == NULL)
    {
        printf("failed to alocat memory\n");
        fclose(file);
        return 3;
    }

    filename = (char *)malloc(8 * sizeof(char));
    if (filename == NULL)
    {
        printf("failed to allocate memory\n");
        free(buffer);
        fclose(file);
        return 3;
    }

    img = NULL;
    //Repeat until end of the caed
    //Read 512 bytes into a buffer
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        for (int i = 0; i < BLOCK_SIZE; i++)
        {
            //Look for beginning of a JPEG
            //If start of new JPEG
            if ((buffer[i] == 0xff) && (buffer[i + 1] == 0xd8) && (buffer[i + 2] == 0xff) && ((buffer[i + 3] & 0xf0) == 0xe0))
            {
                // Close the previous JPEG file (if it's open).
                if (img != NULL)
                {
                    fclose(img);
                }

                // Open a new JPEG file.
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                if (img == NULL)
                {
                    printf("Failed to create a new JPEG file\n");
                    free(filename);
                    free(buffer);
                    fclose(file);
                    return 4;
                }

                // Write the current block data to the new JPEG file.
                fwrite(&buffer[i], 1, BLOCK_SIZE - i, img);
                count += 1;
                // Break out of the inner loop to read the next block.
                break;
            }

            else if (count != 0 && img != NULL)
            {
                fwrite(&buffer[i], 1, sizeof(BYTE), img);
            }
        }
    }

    if (img != NULL)
    {
        fclose(img);
    }
    free(filename);
    free(buffer);
    fclose(file);
    return 0;
}
