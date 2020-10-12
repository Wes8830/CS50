#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void recursive_sort(int n);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    //
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    // IF name matches a name in candidates, then add to vot and return true to caller
    // IF name is not in candidates[i].name, then return False to caller main
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }

    }
    return false;

}

// Print the winner (or winners) of the election
void print_winner(void)
{
    recursive_sort(candidate_count);

    if (candidates[candidate_count - 1].votes == candidates[candidate_count - 2].votes)
    {
        if (candidates[candidate_count - 1].votes == candidates[0].votes)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                printf("%s\n", candidates[i].name);
            }
        }
        else
        {
            string winner2 = candidates[candidate_count - 2].name;
            printf("%s\n", winner2);
        }
    }

    string winner = candidates[candidate_count - 1].name;
    printf("%s\n", winner);
    return;
}

void recursive_sort(int n)
{
// function that recursively iterates a swap/sort function.
    int swap_smaller_num;
    int swap_larger_num;
    string swap_smaller_name;
    string swap_larger_name;

    if (n == 1)
    {
        return;
    }
    else
    {
        for (int i = 0; i < n - 1; i++)
        {
            if (candidates[i].votes > candidates[i + 1].votes)
            {
                swap_smaller_num = candidates[i + 1].votes;
                swap_smaller_name = candidates[i + 1].name;
                swap_larger_num = candidates[i].votes;
                swap_larger_name = candidates[i].name;

                candidates[i].votes = swap_smaller_num;
                candidates[i].name = swap_smaller_name;
                candidates[i + 1].votes = swap_larger_num;
                candidates[i + 1].name = swap_larger_name;
            }
        }
        recursive_sort(n - 1);
    }
}

