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
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

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

    //RGBTRIPLE temp[1][1];

    RGBTRIPLE temp[height][width];
    //double mid = width / 2.0;
    //printf("mid is %f  \n", mid);

    //make a copy of image array


    /*  for (int x = 0; x < height; x++)
      {
          //iterate through columns
          for (int z = 0; z < width; z++)
          {
            //pass the image array into temp
            temp[x][z].rgbtBlue = image[x][z].rgbtBlue;
            temp[x][z].rgbtGreen = image[x][z].rgbtGreen;
            temp[x][z].rgbtRed = image[x][z].rgbtRed;
            //printf("my temp blue value is: %i \n", temp[x][z].rgbtBlue);
            //printf("%i   ", temp[x][z].rgbtBlue);
          }
          //printf("\n");
      }*/

    //check for odd values

    for (int i = 0; i < height; i++)
    {
        //iterate through columns, i wonder if I can use two variables here?

        for (int j = 0, column = width; j < width / 2; j++)
        {
            //take value in i,j place height -- and weight -- into it
            //printf("Height j : %i\n", i);
            //printf("Width: %i %i \n", j, m);

            //column = column - j - 1;
            if ((width - 1) - j > 0)
            {
                temp[0][0].rgbtBlue = image[i][j].rgbtBlue;
                image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
                image[i][width - j - 1].rgbtBlue = temp[0][0].rgbtBlue;

                temp[0][0].rgbtGreen = image[i][j].rgbtGreen;
                image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
                image[i][width - j - 1].rgbtGreen = temp[0][0].rgbtGreen;

                temp[0][0].rgbtRed = image[i][j].rgbtRed;
                image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
                image[i][width - j - 1].rgbtRed = temp[0][0].rgbtRed;
            }



            //temp[0][0].rgbtBlue = image[i][m].rgbtBlue;
            //printf("column is: %i \n", column);
            //image[i][j].rgbtRed = temp[i][column].rgbtRed;
            //image[i][j].rgbtGreen = temp[i][column].rgbtGreen;
            //image[i][j].rgbtBlue = temp[i][column].rgbtBlue;
            //image[i][j].rgbtBlue = temp[0][0].rgbtBlue;
            //printf("Blue is: %i \n", image[i][j].rgbtBlue);
            //temp[0][0].rgbtGreen = image[i][m].rgbtGreen;
            //image[i][j].rgbtGreen = temp[0][0].rgbtGreen;

            //temp[0][0].rgbtRed = image[i][m].rgbtRed;
            //image[i][j].rgbtRed = temp[0][0].rgbtRed;


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
        for (int z = 0; z < width - 1; z++)
        {
            //pass the image array into temp so that you don't inadvertently use an already adjusted value in your summation
            temp[x][z].rgbtBlue = image[x][z].rgbtBlue;
            temp[x][z].rgbtGreen = image[x][z].rgbtGreen;
            temp[x][z].rgbtRed = image[x][z].rgbtRed;

        }
    }



    for (int i = 0; i < height - 1; i++)
    {
        //iterate through columns
        for (int j = 0; j < width - 1; j++)
        {
            counter = 0.0;
            //vert

            //establish upper, botton, left, right bounds
            int u = 1; //sets default upper bound
            int b = 1; //sets default bottom bound


            if (i == 0)
            {
                u = 0; //prevent againt upper ceiling overflow
                b = 1;
            }
            if (i == height - 1)
            {
                u = 1; //prevent against 'b' bottom floor overflow
                b = 0;
            }


            for (int n = - u; n <= b; n++)
            {

                //reestablish left right bounds
                int l = 1; //sets default left bound
                int r = 1; //sets default right bound
                if (j == 0)
                {
                    l = 0; //prevent againt 'l' left edge overflow
                    r = 1;
                }
                if (j == width - 1)
                {
                    l = 1; //prevent against 'r' right edge overflow
                    r = 0;
                }


                for (int m = -l; m <= r; m++)
                {

                    summationBlue = summationBlue + temp[i + n][j + m].rgbtBlue;
                    //printf("Blue Sum is: %i \n", summationBlue);
                    //printf("counter is: %i \n", counter);
                    //printf("i, j are: %i, %i \n", i, j);
                    summationGreen = summationGreen + temp[i + n][j + m].rgbtGreen;
                    summationRed = summationRed + temp[i + n][j + m].rgbtRed;
                    counter++;
                }

            }

            image[i][j].rgbtBlue = round(summationBlue / counter);
            image[i][j].rgbtGreen = round(summationGreen / counter);
            image[i][j].rgbtRed = round(summationRed / counter);

            if (image[i][j].rgbtBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            if (image[i][j].rgbtGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            if (image[i][j].rgbtRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
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
