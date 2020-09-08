#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Prompt user for their name, pass it into 'name' string variable
    string name = get_string("What is your name?\n");

    //Output of name using a string placeholder
    printf("hello, %s\n", name);
}