#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char rotate(char c, int n);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    // Make sure every character in argv[1] is a digit
    // Convert argv[1] from a `string` to an `int`
    // Prompt user for plaintext
    // For each character in the plaintext:
    // Rotate the character if it's a letter
    if (argc != 2){
        printf("Usage: ./caesar key\n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++){
        if (!isdigit(argv[1][i])){
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    int key = atoi(argv[1]);
    string plaintext = get_string("plaintext: ");
    for (int i = 0; i < strlen(plaintext); i++){
        plaintext[i] = rotate(plaintext[i], key);
    }
    printf("ciphertext: %s\n", plaintext);
    return 0;
}

char rotate(char c, int n){
    if (!isalpha(c)){return c;}
    if (islower(c)){
        int pos = c - 'a';
        pos = (pos + n) % 26;
        c = pos + 'a';
    }else{
        int pos = c - 'A';
        pos = (pos + n) % 26;
        c = pos + 'A';
    }
    return c;
}
