// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node {
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

int items = 0;

int strcicmp(char const *a, char const *b) {
    for (;; a++, b++) {
        int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        if (d != 0 || !*a)
            return d;
    }
}

// Returns true if word is in dictionary, else false
bool check(const char *word) {
    int idx = hash(word);
    for (node *cur = table[idx]; cur != NULL; cur = cur->next) {
        if (strcicmp(cur->word, word) == 0) {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) {
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {

    FILE *file = fopen(dictionary, "r");
    if (file == NULL) {

        unload();
        return false;
    }

    char str[LENGTH + 5];
    while (fgets(str, LENGTH + 5, file)) {

        int idx = hash(str);
        node *n = malloc(sizeof(node));
        if (n == NULL) {
            return false;
        }
        n->next = NULL;
        strcpy(n->word, strtok(str, "\n"));

        if (table[idx] == NULL) {
            table[idx] = n;
        } else {
            n->next = table[idx];
            table[idx] = n;
        }
        ++items;
    }
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {

    return items;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
    for (int i = 0; i < N; i++) {
        node *cur_next = NULL;
        for (node *cur = table[i]; cur != NULL;) {
            cur_next = cur->next;
            free(cur);
            cur = cur_next;
        }
    }
    return true;
}
