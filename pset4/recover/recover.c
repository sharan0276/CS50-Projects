#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef uint8_t BYTE;


int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage : ./recover <filename>");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    char *filename = malloc(sizeof(char) * 8);


    if (file == NULL)
    {
        printf("File is not present in the directory....\n");
        return 2;
    }

    BYTE buffer[512];

    bool jpeg_form;

    int count = 0;

    FILE *img;

    bool first_file = false;

    while (fread(buffer, 512, 1, file) > 0)
    {
        jpeg_form = false;

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //JPEG format
            jpeg_form = true;
        }



        if (jpeg_form)
        {
            if (!first_file)
            {
                // If the first file wasnt found
                first_file = true;
            }

            else
            {
                //if it exists close the prev file
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", count);
            count++;
            img = fopen(filename, "w");

            fwrite(buffer, 512, 1, img);
        }

        else if (first_file)
        {
            //if the first jpeg if found append it to prev file
            fwrite(buffer, 512, 1, img);
        }
    }

    fclose(img);
    fclose(file);

    return 0;
}


