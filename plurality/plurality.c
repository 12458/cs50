#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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
void bubbleSort(int array[], int size);

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
    for (int i = 0; i < MAX; i++){
        if (strcmp(candidate[i].name, name) == 0)
        {
            candidate[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int size = sizeof(candidates) / sizeof(candidate);
    bubbleSort(candidates, size);
    int largest_vote = candidates[0].votes;
    for (int i = 0; i < MAX; i++){
        if (candidate[i].votes == largest_vote)
        {
            printf("%s\n", candidate[i].name);
        }
    }
    return;
}

void bubbleSort(candidate array[], int size) {

    for (int step = 0; step < size - 1; ++step) {

        int swapped = 0;

        for (int i = 0; i < size - step - 1; ++i) {
            if (array[i].votes < array[i + 1].votes) {
                //swap
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;

                swapped = 1;
            }
        }

        if (!swapped) break;

    }
}