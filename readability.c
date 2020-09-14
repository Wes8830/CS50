#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
//index = 0.0588 * L - 0.296 * S - 15.8
//where L = average number of letters per 100 words any character a-z or A-Z
//count the number of words, space delimited
// S = average number of sentences for 100 words in the text. ! ? .

//count your letters, divide by 100 to get your L score
//count your sentances, divide by 100 to get your S score
//run it through the algo
//round to the nearest WHOLE number

int count_letters(string text, int n);
int count_words(string text, int n);
bool is_letter(string text, int i);
int count_sentences(string text, int n);
bool is_end_sentence(string text, int i);
int grader(float letters, float words, float sentences);
int roundup(float value);

int main(void)
{

    string text = get_string("Text: ");
    int n = strlen(text);
    //16 or higher should print "Grade 16+""
    //if grade index is less than 1 print "Before Grade 1"
    //string grade = roundto(index)

    int letters = count_letters(text, n);
    int words = count_words(text, n);
    int sentences = count_sentences(text, n);
    int grade = grader(letters, words, sentences);

    if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}


int count_letters(string text, int n)
{
    int letterc = 0;
    for (int i = 0; i < n; i++)
    {
        //checks ascii table values for the string's character. specifying (int) allows us to return the integer of the character stored.
        if ((int) text[i] > 64 && text[i] < 126)
        {
            letterc++;
        }

    }
    return letterc;
}

int count_words(string text, int n)
{
// function to count words in the input text.
    int wordc = 0;
    bool prev_char = false;
    bool curr_char = false;
    for (int i = 0; i < n; i++)
    {
        prev_char = is_letter(text, i - 1);
        curr_char = is_letter(text, i);

        //checks to see if the prev char is not a letter and the current character is. if both true, then we have a word!
        if (!prev_char && curr_char)
        {
            wordc++;
        }
    }
    return wordc;
}

bool is_letter(string text, int i)
{
// function to check to see if the char is considered a letter
    if (((int) text[i] > 64 && text[i] < 126) || text[i] == 39 || text[i] == 45)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int count_sentences(string text, int n)
{
// function to check to see if it's a valid sentence.
    int sentencec = 0;
    for (int i = 0; i < n; i++)
    {
        if (is_end_sentence(text, i))
        {
            sentencec++;
        }
    }
    return sentencec;
}

bool is_end_sentence(string text, int i)
{
// function to check to see if something is at the end of the sentence.
    if ((int) text[i] == 33 || text[i] == 46 || text[i] == 63)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int grader(float letters, float words, float sentences)
{
    //function to determine the Grade level of the text by running it through the Coleman-Liau index algorithm
    float L = letters / words * 100;
    float S = sentences / words * 100;
    float c_l_index = (0.0588 * L) - (0.296 * S) - 15.8;
    int grade = roundup(c_l_index);

    return grade;

}


int roundup(float value)
{
//quick and dirty round up function
    int values_int = value;
    if (value - values_int >= 0.5)
    {
        value++;
    }
    return value;
}
