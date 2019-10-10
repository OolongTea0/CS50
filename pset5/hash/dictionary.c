// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

//
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

//word counter
int counter = 0;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
//It's a function to make it easier to replace with a better hash function
unsigned int hash(const char *word)
{
    return ((word[0]) - 'a');
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));

        int i = hash(word); //returns an unsigned int

        strcpy(n->word, word);
        n->next = hashtable[i]; //sets the point for next to the old starting location

        //sets start to new node
        hashtable[i] = n;
        counter++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return(counter);
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char copy[LENGTH + 1];
    //strcpy(copy,word);

    //Creates a copy of word while changing letters to lowercase
    for (int i = 0; i < strlen(word); i++)
    {
        copy[i] = tolower(word[i]);
    }

    //Adds the NUL character to complete each string
    copy[strlen(word)] = '\0';

    int i = hash(copy);

    node *ptr = hashtable[i];
    while (ptr)
    {
        if (strcmp(copy, ptr->word) == 0)
        {
            return true;
        }

        ptr = ptr->next;

    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *ptr = hashtable[i]; //Sets cursor at beginning of lists
        while(ptr)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }

        //Checks to see if it unloaded
        if (i == (N - 1) && !ptr)
            return true;
    }

    return false;
}