#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Get Key at command line
// Validate the key
    //check key length
    // check for non-alphabetic chars
    // check for repeated chars (case-insensitive)
// get Plaintext from user
// encipher the text
// print cipher text

int error_check(string key, int key_length, int arg_count);

int main(int argc, string argv[])
{

    //specify [1] here becuase argv is a vector of arguments. It doesn't store one argument as a string, it stores multiple arguments in a list called argv!
    string key = argv[1];
    int key_length = strlen(argv[1]);
    int arg_count = argc;
    printf("your argument count is: %i ", argc);

    //check for errors in their Key
    //int no_error = error_check(key, key_length, argc);
        //check to make sure they user provided a 26 character Key
    int no_error = error_check(key, key_length, arg_count);


    if (no_error == 0) {
        //Prompt the user for Plaintext
        string plaintext = get_string("plaintext: ");

        int plntxt_len = strlen(plaintext);
        int plaintext_ucase = 0; //enum for 3 cases (uppercase, lowercase, non-alphabetic)

        string upper_alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        string lower_alpha = "abcdefghijklmnopqrstuvwxyz";
        int cyphertext[plntxt_len];

        //Check for Errors in the Command Line Argument Input

        //Index through Plaintext
        for (int i = 0; i < plntxt_len; i++)
        {
            int n = 0;

            //check upper case alphabet
          if (plaintext[i] >= 65 && plaintext [i] <= 90)
          {
           plaintext_ucase = 2;
            while (plaintext[i] != upper_alpha[n])
            {
                n++;
            }

          }//check lower case alphabet
          else if (plaintext[i] >= 97 && plaintext [i] <=122)
          {
            plaintext_ucase = 1;
            while (plaintext[i] != lower_alpha[n])
            {
                n++;
            }
          }
          else
          {
            plaintext_ucase = 0;
          }

            //check if PLAINTEXT index matches n index in the KEY

            if (plaintext_ucase == 2)
            {
               //ok, PLAINTEXT is uppercase, but the key could be in lowercase, if it is subtract 32 from it's ASCII string value
               if (key[n] >= 97 && key[n] <= 122)
                {
                    key[n] = key[n] - 32;
                }
                cyphertext[i] = key[n];
            } else if ( plaintext_ucase == 1)
            {
                //Plaintext is lowercase, but the key could be in uppercase, if it is, add 32 to it's ASCII string index value
                if (key[n] >= 65 && key[n] <= 90)
                {
                    key[n] = key[n] + 32;
                }
                cyphertext[i] = key[n];

            }
            else
            {
                cyphertext[i] = plaintext[i];
            }


        }

        printf("ciphertext: ");
        for (int j = 0; j < plntxt_len; j++)
        {
            printf("%c",cyphertext[j]);

        }
        printf("\n");
        return 0;
    }
}



int error_check(string key, int key_length, int arg_count)
{
    //check to make sure they user provided a 26 character Key
    if (arg_count != 2)
    {
        printf("Usage: ./substitution key\n");
        //no_error = 1;
        exit(1);
    }
    else if (key_length != 26)
    {
        printf("Key must contain 26 characters.\n");
        //no_error = 1;
        exit(1);
    }
    else //no errors found
    {
        //no_error = 0;
        return 0;
    }
}
