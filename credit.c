#include <cs50.h>
#include <stdio.h>

//string cardtype = "INVALID";

void checksum_validator(long cc_nbr_input);
void cardlength_validator(int size, long cc_nbr_input);
void digit_validator(long cc_nbr_input);


int sum_first = 0;
int second_multiplier = 0;
int sum_second = 0;
int digit = 0;
int count = 0;


int main(void)
{

    long cc_nbr_input = get_long("What is your credit card number");

    //Let's first run the checksum validation to check if this could be a valid card
    checksum_validator(cc_nbr_input);

    //Within check_sum Validator > Let's second run the cardlength validation to see which card type this could be
    //cardlength_validator(count, cc_nbr); is within checksum_validator

    //    //Lastly, within cardlenght validator, lets check to make sure that the first digits of the credit card number match the starting digit requirements for the given card_type
    //   // digit_validator is within cardlength_validator

}


//Working well
void checksum_validator(long cc_nbr_input)
{
    //checksum Validation should be 0 if valid

    long digit_iterator = cc_nbr_input;

    do
    {

        digit = digit_iterator % 10;
        sum_first = digit + sum_first;
        digit_iterator = digit_iterator / 10;
        count++;
        //printf("your current First digit is: %i\n", digit);
        printf("your current First digit summation is: %i\n", sum_first);
        digit = digit_iterator % 10;
        second_multiplier = (digit * 2);
        //printf("your current Second digit is: %i\n", digit);
        if (second_multiplier > 9)
        {
            sum_second = (second_multiplier / 10) + (second_multiplier % 10) + sum_second;
        }
        else
        {
            sum_second = (digit * 2) + sum_second;
        }
        printf("your current Second digit summation is: %i\n", sum_second);
        //printf("your new number is: %li\n", cc_nbr);
        digit_iterator = digit_iterator / 10;
        count++;
        printf("count is: %i\n", count);

    }
    while (digit_iterator > 0);

    //Logic above will incorrectly increment count by an extra amount
    if (count % 2 == 0)
    {
        count--;
    }

    int checksum = (sum_first + sum_second) % 10;
    //first validation check of whether or not it's a legit number
    printf("Checksum is %i\n", checksum);
    if (checksum == 0)
    {
        printf("Your checksum looks good! It is: %i\n", checksum);
        cardlength_validator(count, cc_nbr_input);
    } 
    else
    {
        string card_type = "INVALID";
        printf("%s\n", card_type);
    }
}

void cardlength_validator(int size, long cc_nbr_input)
{
    printf("count within cardlength validator is: %i\n", size);
    if (size == 13)
    {
        //string card_type = "VISA";
        digit_validator(cc_nbr_input);

    }
    //let's check if its length could be AMEX
    else if (size == 15)
    {
        //string card_type  = "AMEX";
        digit_validator(cc_nbr_input);
    }
    //now we have to check if it's visa or mastercard
    else if (size == 16)
    {
        //string card_type  = "VISA OR MASTERCARD";
        digit_validator(cc_nbr_input);
    }
    else
    {
        string card_type  = "INVALID";
        printf("%s\n", card_type);
    }
}

void digit_validator(long cc_nbr_input)
{
    string card_type = "N/A";

    long left_digits = cc_nbr_input;
    printf("Your Left digits are: %li\n", left_digits);
    while (left_digits > 55)
    {
        left_digits = left_digits / 10;
        printf("left digits are: %li\n", left_digits);

    }

    if (left_digits == 34 || left_digits == 37)
    {
        card_type = "AMEX";
        printf("%s\n", card_type);
    } 
    else if (left_digits == 51 || left_digits == 52 || left_digits == 53 || left_digits == 54 || left_digits == 55)
    {
        card_type = "MASTERCARD";
        printf("%s\n", card_type);
    } 
    else
    {
        // strip away the second remaining digit and check for visa
        while (left_digits > 10)
        {
            left_digits = left_digits / 10;
            //printf("first digit is: %li\n", left_digits);
        }
        if (left_digits == 4)
        {
            card_type = "VISA";
            printf("%s\n", card_type);
        }
        else 
        {
            card_type = "INVALID";
            printf("%s\n", card_type);
        }

    }

}

string card_type = "INVALID";

/*void amex(void)
//15 digits, start with either 34 or 37
//378282246310005
//371449635398431
//378734493671000
{
    printf("AMEX\n");
}

void mastercard(void)
//16 digits, start with 51, 52, 53, 54, or 55
//2221000000000009
//5555555555554444
//5105105105105100
{
    printf("MASTERCARD\n");
}

void visa(void)
//13 or 16 digit, starts with 4
//4111111111111111
//4012888888881881
//4222222222222
{
    printf("VISA\n");
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
}*/