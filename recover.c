#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


/*PSUEDOCODE
repeat until end of card
    if start of new JPEG (detect by looking at first 4 bytes of the JPEG and determining if they match the JPEG format)
        if First JPEG, write to 000.JPEG and start writing to it
        Else, if new JPEG is found, based on the header, then you need to open up this new file you're going to start writing to
    Else if you already found a JPEG, you need to keep writing to it
  at end of Memory, CLOSE any remaining files
*/


typedef uint8_t BYTE;


int main(int argc, char *argv[])
{

    //checks if you didn't enter an additional argument
    if (argc != 2)
    {
        printf("You didn't enter enough arguments \n");
        return 1;
    }

    //Open memory Card
    FILE *raw = fopen(argv[1], "r");
    //initialize an image file for writing to, but set it to NULL because you don't know its size.
    FILE *jay_peg = NULL;

    //0xff 0xd8 0xff && 0xe0...f are the Headers of a start of a new JPEG file

    //initialize a buffer[] to read 512 bytes into
    unsigned char data_buff[512];

    //Loop through chunks of 512 byte data in Raw, then write them to the buffer data_buff
    int jpeg_count = 0;
    while (fread(data_buff, 512, 1, raw) == 1) //use instead of for loop here as it's simpler
    {
        //check first 4 elements within the current 512 byte chunk of memory from the Raw file
        //See if the byte matches 0xff, then if 0xd8, then if 0xff, AND finally see if it matches 0xe0...f and BITWISE map those to 0xe0 because all are fine and typing out all 16 0ex's would be cumbersome
        if ((data_buff[0] == 0xff) && (data_buff[1] == 0xd8) && (data_buff[2] == 0xff) && ((data_buff[3] & 0xf0) == 0xe0))
        {
            //check to see if you previously had a file Open for writing, and then terminate it becuase you don't want to keep writing to it.
            if (jay_peg != NULL)
            {
                //printf("Am I closing Files? YES!!!\n");
                fclose(jay_peg);
            }

            //name your new file
            char fname[8];
            //printf("%.3d.jpg", jpeg_count);
            //sprint is printf's equivalent, but instead it has you point to a char buffer (a string) so that it can start writing to it. You may consider using malloc() in the future if your string lengths will differ
            sprintf(fname, "%.3d.jpg", jpeg_count);

            //create and open the file name you just created for writing
            jay_peg = fopen(fname, "w");
            //now you can increment your jpeg count up for use in your next file's name
            jpeg_count += 1;
            //just a safety check so that we don't inadvertently write a NULL to a file. We should confirm if this is accurate.
            if (jay_peg == NULL)
            {
                return 1;
            }
            //now you can write that first 512 block to the newly created jpeg image file.
            else if (jay_peg != NULL)
            {
                fwrite(data_buff, 512, 1, jay_peg);
            }
        }
        //with this 512 byte chunk of data, you didn't find a Header that denotes the start of a new JPEG
        //so keep writing to the jpeg if you already have created one, else, move on to the next 512 byte block.
        else if (jay_peg != NULL)
        {
            fwrite(data_buff, 512, 1, jay_peg);
        }


    }


    fclose(raw);

    return 0;
}
