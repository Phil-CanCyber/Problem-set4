#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// definitions
#define BUFBYTE 512
typedef uint8_t BYTE;

// Start bool
bool find_JPEG(BYTE[]);
FILE *newfile(FILE *, char[], int, BYTE[]);

// Starting point
int main(int argc, char *argv[])
{
    // Conditions and error message
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image \n");
        return 1;
    }

    // open the file body!
    char *input = argv[1];
    FILE *infile = fopen(input, "r");


    // check format, check carefully!
    if (infile == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", input);
        return 2;
    }

    /**
     * Let find those .jpg
     */

    // declare variables... blah blah
    BYTE buffer[BUFBYTE];
    int Locate_JPG = 0;
    char filename [8];
    FILE *img = NULL;
    img = newfile(img, filename, Locate_JPG, buffer);

    // While we loop...Weeee
    while (!feof(infile) && fread(&buffer, BUFBYTE, 1, infile) == true)
    {
        //  If we find a jpg, crack open a beer and celebrate!!! 
        if (find_JPEG(buffer) == true)
        {
            // Close that file but open that bag of doritos
            fclose(img);

            // start new file, buff it and rock & roll
            img = newfile(img, filename, Locate_JPG, buffer);
            Locate_JPG++;
        }

        // if not else ... what do you want from me?
        if (find_JPEG(buffer) == false)
        {
            //if no, life sucks.
            if (Locate_JPG == 0)
            {
                continue;
            }

            // Dump that.
            else
            {
                fwrite(buffer, 1, BUFBYTE, img);
            }
        }

    }
    // wrap it up!
    if (feof(infile))
    {
        fclose(img);
        fclose(infile);
    }

    return 0;
}

// coucou jpg
bool find_JPEG(BYTE buffer[])
{
    // determine if new JPEG present?
    if (buffer[0] == 0xff &&
        buffer[1] == 0xd8 &&
        buffer[2] == 0xff &&
        (buffer[3] & 0xf0) == 0xe0)
    {
        return true;
    }

    else
    {
        return false;
    }
}

// wrap up this shit into the file

FILE *newfile(FILE *img, char filename[], int Locate_JPG, BYTE buffer[])
{
    sprintf(filename, "%03i.jpg", Locate_JPG);
    img = fopen(filename, "w");
    fwrite(buffer, 1, BUFBYTE, img);
    return img;
}

// call it a day!
