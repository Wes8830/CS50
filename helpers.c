#include "helpers.h"
#include "stdio.h"
#include "math.h"

/* found in bmp.h
typedef struct
  {
        BYTE rgbtBlue;
        BYTE rgbtGreen;
        BYTE rgbtRed;
  } RGBTRIPLE;
*/

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    //file has been opened in main so you don't need to open the input file for reading or the output file for writing FILE* point_file = fopen(image, "r");

    //iterate through rows i
    for (int i = 0; i < height; i++)
    {

        //iterate through each column j in row i
        for (int j = 0; j < width; j++)
        {
            //calculate the average pixel value
            double avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;

            //printf("Red is: %i\n", image[i][j].rgbtRed);
            //printf("Green is: %i\n", image[i][j].rgbtGreen);
            //printf("Blue is: %i\n", image[i][j].rgbtBlue);
            printf("average is: %f\n", avg);
            //printf("H: %i\n",height);
            //printf("W: %i\n", width);

            //store that pixel back into the image value

            int round_avg = round(avg);
            image[i][j].rgbtBlue = round_avg;
            image[i][j].rgbtGreen = round_avg;
            image[i][j].rgbtRed = round_avg;

            //set each color value to the average pixel value


        }

    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {

        //iterate through each column j in row i
        for (int j = 0; j < width; j++)
        {
            //calculate the sepia values

            int sepiaRed = round((.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue));
            int sepiaGreen = round((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue));

            int sepiaBlue = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue));

            //cap at 50
            if (sepiaRed > 255)
                sepiaRed = 255;
            if (sepiaGreen > 255)
                sepiaGreen = 255;
            if (sepiaBlue > 255)
                sepiaBlue = 255;


            //printf("Red is: %i\n", image[i][j].rgbtRed);

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;

        }

    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //iterat through rows

    RGBTRIPLE temp[1][1];

    for (int i = 1; i < height; i++)
    {
        //iterate through columns, i wonder if I can use two variables here?
        for (int j = 1, m = width; j < width/2 ; j++, m--)
        {
            //take value in i,j place height -- and weight -- into it
            //printf("Height j : %i\n", i);
            //printf("Width: %i %i \n", j, m);


            temp[0][0].rgbtBlue = image[i][m].rgbtBlue;
            image[i][m].rgbtBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = temp[0][0].rgbtBlue;
            //printf("Blue is: %i \n", image[i][j].rgbtBlue);
            temp[0][0].rgbtGreen = image[i][m].rgbtGreen;
            image[i][m].rgbtGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = temp[0][0].rgbtGreen;

            temp[0][0].rgbtRed = image[i][m].rgbtRed;
            image[i][m].rgbtRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = temp[0][0].rgbtRed;

        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //iterat through rows

    RGBTRIPLE temp[height][width];
    double counter = 1;
    int summationBlue = 0;
    int summationGreen = 0;
    int summationRed = 0;


    //make a copy of image array
    for (int x = 0; x < height; x++)
    {
        //iterate through columns
        for (int z = 0; z < width; z++)
        {
            //pass the image array into temp so that you don't inadvertently use an already adjusted value in your summation
            temp[x][z].rgbtBlue = image[x][z].rgbtBlue;
            temp[x][z].rgbtGreen = image[x][z].rgbtGreen;
            temp[x][z].rgbtRed = image[x][z].rgbtRed;
            //printf("my temp blue value is: %i \n", temp[x][z].rgbtBlue);
        }
    }

    for (int i = 0; i < height; i++)
    {
        //iterate through columns
        for (int j = 0; j < width; j++)
        {
            counter = 1.0;
            //vert

            //establish upper, botton, left, right bounds
            int u = 1; //sets default upper bound
            int b = 1; //sets default bottom bound
            int l = 1; //sets default left bound
            int r = 1; //sets default right bound

            if(i == 0)
            {
                u = 0; //prevent againt upper ceiling overflow
                b = 1;
            }
            if (i == height)
            {
                u = 1; //prevent against 'b' bottom floor overflow
                b = 0;
            }


            for (int n = - u; n <= b; n++)
            {
                //reestablish left right bounds
                l = 1; //sets default left bound
                r = 1; //sets default right bound
                if (j == 0)
                {
                    l = 0; //prevent againt 'l' left edge overflow
                    r = 1;
                }
                if (j == width)
                {
                    l = 1; //prevent against 'r' right edge overflow
                    r = 0;
                }

                counter++;
                for (int m = - l; m <= r; m++)
                {

                    summationBlue = summationBlue + temp[i][j].rgbtBlue;
                    //printf("Blue Sum is: %i \n", summationBlue);
                    //printf("counter is: %i \n", counter);
                    //printf("i, j are: %i, %i \n", i, j);
                    summationGreen = summationGreen + temp[i][j].rgbtGreen;
                    summationRed = summationRed + temp[i][j].rgbtRed;
                    counter++;
                }

            }

            image[i][j].rgbtBlue = round(summationBlue / counter);
            image[i][j].rgbtGreen = round(summationGreen / counter);
            image[i][j].rgbtRed = round(summationRed / counter);
            //printf("Blue is: %i \n", image[i][j].rgbtBlue);
            //printf("Green is: %i \n", image[i][j].rgbtGreen);
            //printf("Blue is: %i \n", image[i][j].rgbtRed);
            //clear your summations
            summationBlue = 0;
            summationGreen = 0;
            summationRed = 0;

        }
    }
    return;
}
