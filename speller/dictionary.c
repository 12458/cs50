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
    // printf("LOADING DICTIONARY: %s\n", dictionary);
    FILE *file = fopen(dictionary, "r");
    if (file == NULL) {
        // printf("OPEN DICTIONARY FAILED\n");
        unload();
        return false;
    }
    // printf("OPEN DICTIONARY SUCCESS\n");
    char str[LENGTH + 5];
    while (fgets(str, LENGTH + 5, file)) {
        // printf("CURRENT STRING: %s\n", str);
        // if ((strcmp("\n", str) == 0)||!(strlen(str) > 0)){break;}
        int idx = hash(str);
        node *n = malloc(sizeof(node));
        if (n == NULL) {
            return false;
        }
        strcpy(n->word, strtok(str, "\n"));
        // printf("COPIED STRING\n");
        if (table[idx] == NULL) {
            table[idx] = n;
        } else {
            node *cur = NULL;
            for (cur = table[idx]; cur->next != NULL; cur = cur->next)
                ;
            cur->next = n;
        }
        ++items;
        // printf("%s\n", strtok(str, "\n"));
        // printf("\n");
    }
    fclose(file);

    // for (int i = 0; i < N; i++) {
    //     if (table[i] == NULL) {
    //         printf("[%i]: NULL\n", i);
    //     } else {
    //         printf("[%i]: %s", i, table[i]->word);
    //         for (node *tmp = table[i]->next; tmp != NULL; tmp = tmp->next) {
    //             printf(" %s", tmp->word);
    //         }
    //         printf("\n");
    //     }
    // }

    // printf("LOAD SUCCESS\n");
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {
    // int cum_sum = 0;
    // for (int i = 0; i < N; i++) {
    //     if (table[i] == NULL) {
    //         continue;
    //     } else {
    //         int size = 0;
    //         for (node *cur = table[i]; cur != NULL; cur = cur->next) {
    //             size++;
    //         }
    //         cum_sum += size;
    //     }
    // }
    return items;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
    for (int i = 0; i < N; i++) {
        for (node *cur = table[i]; cur != NULL; cur = cur->next) {
            free(cur);
        }
    }
    return true;
}
