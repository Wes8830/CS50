#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    //checks if you didn't enter an additional argument
    if (argc != 2)
    {
        printf("You didn't enter enough arguments \n");
        return 1;
    }
    return 0;
}
