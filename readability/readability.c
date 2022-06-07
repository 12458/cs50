/*
According to Scholastic, E.B. White’s Charlotte’s Web is between a second- and fourth-grade reading level, and Lois Lowry’s The Giver is between an eighth- and twelfth-grade reading level. What does it mean, though, for a book to be at a particular reading level?

Well, in many cases, a human expert might read a book and make a decision on the grade (i.e., year in school) for which they think the book is most appropriate. But an algorithm could likely figure that out too!

So what sorts of traits are characteristic of higher reading levels? Well, longer words probably correlate with higher reading levels. Likewise, longer sentences probably correlate with higher reading levels, too.

A number of “readability tests” have been developed over the years that define formulas for computing the reading level of a text. One such readability test is the Coleman-Liau index. The Coleman-Liau index of a text is designed to output that (U.S.) grade level that is needed to understand some text. The formula is

## index = 0.0588 * L - 0.296 * S - 15.8 ##

where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.
*/


#include <cs50.h>
#include <stdio.h>
#include <string.h>

int get_letter_count(string text);
int get_word_count(string text);
int get_sentence_count(string text);

int main(void)
{
    string text = get_string("Text: ");
    printf("%s\n", text);
    //printf("Letter count: %i\n", get_letter_count(text));
    //printf("Word count: %i\n", get_word_count(text));
    //printf("Sentence count: %i\n", get_sentence_count(text));
    int letter_count = get_letter_count(text);
    int word_count = get_word_count(text);
    int sentence_count = get_sentence_count(text);
    int L, S;
    L = letter_count / ((float) word_count / 100.0);
    S = sentence_count / ((float) word_count / 100.0);
    
    return 0;
}

int get_letter_count(string text){
    // any character that is not special character and space is a letter
    // basically any ascii codes between 65 to 90 and 97 to 122
    int i = 0;
    for (int itr = 0, len = strlen(text); itr < len; itr++){
        if ((text[itr] >= 'a' && text[itr] <= 'z') || (text[itr] >= 'A' && text[itr] <= 'Z'))
        {
            i++;
        }
    }
    return i;
}

int get_word_count(string text){
    // any sequence of characters separated by spaces should count as a word
    // need to find the 'edges' of words
    // space counting approach
    // no of spaces + 1
    int spaces = 0;
    for (int i = 0, len = strlen(text); i < len; i++){
        if (text[i] == ' '){
            while (text[i+1] == ' '){
                i++;
            }
            spaces++;
            }
    }
    return spaces + 1;
}

int get_sentence_count(string text){
    // count the number of ? ! .
    int count = 0;
    for (int i = 0, len = strlen(text); i < len; i++){
        if (text[i] == '?' || text[i] == '.' || text[i] == '!'){
            count++;
        }
    }
    return count;
}