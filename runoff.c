#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        printf("Tie status value is %d\n", tie);
        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("Candidates Elimination Status: %d\n", candidates[i].eliminated);
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    //If 'name' is found in Array, Then update the position of that candidate in preferences with the rank specified (1, 2, 3)
    //return true;
    //repeat;
    bool valid_vote;
    for (int j = 0; j < candidate_count; j++)
    {
        if (rank <= candidate_count && strcmp(name, candidates[j].name) == 0)
        {
            preferences[voter][j] = rank;
            printf("voter %i, votes for %s, ranked %i\n", voter + 1, name, rank + 1);
            return true;

        }
        else
        {
            valid_vote = false;
        }
    }
    return valid_vote;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for(int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < voter_count; j++)
        {
            //declare n_rank as first preference vote.
            int n_rank = 0;
            //take value found in pref[i][j] and stick the column (j) into candidate[j]
            if (preferences[i][j] == n_rank )
            {
                if (candidates[j].eliminated == false)
                {
                    candidates[j].votes ++;
                    break;
                }
                else
                {
                    n_rank++;
                    j = -1;
                }

                //if cand has alreay been eliminated, check the voter's next favorite.
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // count total votes tabulated

    double vote_pct = 0.00;

    for (int i = 0; i < candidate_count; i++)
    {
        //calc i'th candidate's vote percentage, if over 50% then they're the winner.
        vote_pct = candidates[i].votes/voter_count;

        if (vote_pct > .50 )
        {
            string winner = candidates[i].name;
            printf("%s\n", winner);
            return true;
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{

    int swap_small_votes;
    string swap_small_name;
    bool swap_small_elim;


    // Sort your array
    for (int i = 0; i < candidate_count - 1; i++)
    {
        if( candidates[i].votes > candidates[i + 1].votes)
        {
            swap_small_votes = candidates[i + 1].votes;
            swap_small_name = candidates[i +1].name;
            swap_small_elim = candidates[i +1].eliminated;

            candidates[i + 1].votes = candidates[i].votes;
            candidates[i + 1].name = candidates[i].name;
            candidates[i + 1].eliminated = candidates[i].eliminated;

            candidates[i].votes = swap_small_votes;
            candidates[i].name = swap_small_name;
            candidates[i].eliminated = swap_small_elim;
        }
    }

    //iterate through checking the 0th first, IF eliminated = true, then check 1st
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].eliminated == false)
        {
            printf("My Minimum Value is %i\n", candidates[j].votes);
            return candidates[j].votes;
        }
    }

    return 0;
}

// Return true if the election is tied between all, non-eliminated candidates , false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes == candidates[candidate_count - 1].votes)
        {
            //check to see if the first non elminated candidate's votes match that of the last candidate's votes.
            //safe to assume all candidates between those two also have the same value because it's a sorted array and we're working with the found min value.

                //it's a tie!
                return 1;
        }
    }
    return 0;
}

// Eliminate the candidate (or candidates) that have a vote value that matches min value
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
