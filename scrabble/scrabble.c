#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);
int compute_score_char(char letter);
void convert_to_lowercase(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    convert_to_lowercase(word1);
    convert_to_lowercase(word2);

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 == score2){printf("Tie!\n");}
    else{printf(score1 > score2 ? "Player 1 wins!\n" : "Player 2 wins!\n");}
}

int compute_score(string word)
{
    int cumulative = 0;
    for (int i = 0; i < strlen(word); i++){
        cumulative += compute_score_char(word[i]);
    }
    return cumulative;
    // TODO: Compute and return score for string
}

int compute_score_char(char letter){
    if (!islower(letter)){return 0;}
    return POINTS[(int)letter-97];
}

void convert_to_lowercase(string word){
    for (int i = 0; i < strlen(word); i++){
        word[i] = tolower(word[i]);
    }
}