#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t BYTE;
//void file_namer(int jpeg_count);

int main(int argc, char *argv[])
{

    //checks if you didn't enter an additional argument
    if (argc != 2)
    {
        printf("You didn't enter enough arguments \n");
        return 1;
    }

    //Open memory Card
    FILE* raw = fopen(argv[1], "r");
    //initialize an image file for writing to, but set it to NULL because you don't know its size.
    FILE* jay_peg = NULL;

    //0xff 0xd8 0xff && 0xe0...f are the Headers of a start of a new JPEG file


    //read 512 bytes into a buffer[]
    unsigned char data_buff[512];

    //Loop through bytes of size 4, so replace 128 with an i variable, in Raw, then write them to databuff
    //See if the byte matches 0xff, then if 0xd8, then if 0xff, AND finally see if it matches 0xe0...f
    int jpeg_count = 0;
    while (fread(data_buff, 512, 1, raw) == 1) //use instead of for loop here as it's simpler
    {
        //check first 4 elements within first 512 byte chunk
        if ((data_buff[0] == 0xff) && (data_buff[1] == 0xd8) && (data_buff[2] == 0xff) && ((data_buff[3] & 0xf0) == 0xe0))
        {
            //check to see if you previously had a file Open for writing, and then terminate it.
            if (jay_peg != NULL)
            {
                //printf("am I closing Files? YES!!!\n");
                fclose(jay_peg);
            }

            //name your new file
            //file_namer(jpeg_count);

            char fname[8];
            sprintf(fname,"%.3d.jpg", jpeg_count);
            //printf("%.3d.jpg", jpeg_count);

            //create and open the file name for writing
            jay_peg = fopen(fname ,"w");
            jpeg_count += 1;
            //just a safety check so that we don't inadvertently write a NULL to a file
            if (jay_peg == NULL)
            {
                return 1;
            }
            else if (jay_peg != NULL)
            {
                fwrite(data_buff, 512, 1, jay_peg);
            }
        }
        //keep writing to the jpeg if you already have found one
        else if (jay_peg != NULL)
        {
          fwrite(data_buff, 512, 1, jay_peg);
        }


    }


    fclose(raw);

    //repeat until end of card

        //if start of new JPEG (detect by looking at first 4 bytes of the JPEG and determining if they match the JPEG format)
            //if First JPEG, write to 000.JPEG and start writing to it
            //Else, if new JPEG is found, based on the header, then you need to open up this new file you're going to start writing to
        //Else if you already found a JPEG, you need to keep writing to it
    //at end of Memory, CLOSE any remaining files
    return 0;
}


/*void file_namer(int jpeg_count)
{
    //create a name buffer for holding the filename, then store it in as an integer
    char* fname = NULL;
    sprintf(fname,"jay_peg%.3d.jpg", jpeg_count);
    printf("jay_peg%.3d.jpg", jpeg_count);

    return;
}*/