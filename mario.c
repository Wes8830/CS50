#include <cs50.h>
#include <stdio.h>

void brick_builder(int n);
int j;
void brick_builder_right(int n);
void brick_builder_left(int n);

int main(void)
{
    int n = 0;

    //Pompt user input. Prevent 0 and negative Numbers, Cap the input value 8, otherwise ask again
    while (n <= 0 || n > 8)
    {
        n = get_int("What size pyramid do you want to build? (Building code restricts pyramids taller than 8 stories.) \n");
    }

    brick_builder(n);

}



//Abstraction: Functions for Vertical contruction, Left side of Building, and Right Side of Building

void brick_builder(int n)
//This Function controls when the builders need to move onto the next Level of the construction as well as build the vertical shaft running through the middle
{
    //j is vertical
    for (j = 1; j <= n; j++)
    {
        //build the left side of the brick building
        brick_builder_left(n);

        //Create the Gap within the Brick Building
        printf("  ");

        //move to the right side of the brick building
        brick_builder_right(n);

        //move to next line for building the next layer, top to bottom
        printf("\n");

    }
}

void brick_builder_left(int n)
//This function is for the Left side of the building
{
    //horizontal space
    for (int z = n - j; z > 0; z--)
    {
        printf(" ");
    }
    //i is horizontal
    for (int i = j; i > 0; i--)
    {
        //Print one brick
        printf("#");
    }

}

void brick_builder_right(int n)
//This function is for the Right side of the building
{
    for (int i = j; i > 0; i--)
    {
        //Print one brick at a time
        printf("#");
    }
}
