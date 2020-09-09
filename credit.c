#include <cs50.h>
#include <stdio.h>

int main(void)
{

long cc_nbr = get_long("What is your credit card number");

int digit = cc_nbr % 10000;
//string length = length(cc_nbr);

printf(" %i", digit);

}


void validator(void)
{

}

void amex(void)
//15 digits, start with either 34 or 37
//	378282246310005
// 	371449635398431
{

}

void mastercard(void)
//16 digits, start with 51, 52, 53, 54, or 55
//	2221000000000009
// 	5555555555554444
{

}

void visa(void)
//13 or 16 digit, starts with 4
//	4111111111111111
//	4012888888881881
//	4222222222222
{

}

void parity(void)
//checks if an integer is odd or even using %
{
    int n = get_int("n: ");

    if (n % 2 == 0)
    {
        printf("even\n");
    }
    else
    {
        printf("odd\n");
    }
}