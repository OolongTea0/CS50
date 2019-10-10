// Implements a dictionary's functionality
// ./speller dictionaries/small texts/cat.txt
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

//
#include <string.h>
#include <ctype.h>

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Dictionary word counter
int counter = 0;
// Represents a trie
node *root;

//Create node base, old is location in load
node *make_n(node *old, int ind)
{
    node *n = malloc(sizeof(node));

    n->is_word = false;

    for (int i = 0; i < N; i++)
    {
        n->children[i] = NULL;
    }

    old->children[ind] = n;
    return(n);
}

//Indexes the letter for arrays
unsigned int index(const char letter)
{
    if (letter == '\'')
        return(26);
    else
        return (letter - 'a');
}

//Recursion unload
void gone(node *n)
{
    for (int i = 0; i < N; i++)
    {
        if (n->children[i] != NULL)
            gone(n->children[i]);
    }
    free(n);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
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

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        node *ptr = root;

        for (int i = 0; i < strlen(word); i++)
        {
            //Cursor moves to children[ index of current letter]
            int ind = index(word[i]);

            if (ptr->children[ind] != NULL)
                ptr = ptr->children[ind];
            else
                ptr = make_n(ptr, ind);

            //Sets end-of-word letter bool 'is_word' to true
            if  (i == strlen(word) - 1)
            {
                ptr->is_word = true;
            }
            //
        }
        //Keeps track of number of words loaded from dictionary
        counter++;
    }



    // Close dictionary
    fclose(file);

    // Indicate success
    printf("LOAD");
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    //Returns counter which should add up the number of words in load. Starting value is 0
    return(counter);
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO

    char copy[LENGTH + 1];
    //strcpy(copy,word);

    //Creates a copy of word while changing letters to lowercase
    for (int i = 0; i < strlen(word); i++)
    {

        copy[i] = tolower(word[i]);
    }

    copy[strlen(word)] = '\0';

    node *ptr = root;
    for (int i = 0; i < strlen(copy); i++)
    {
        //TODO This FOR loop is causing a segfault
        int ind = index(copy[i]);

        //Travelling
        if (ptr->children[ind] == NULL)
            return false;

        ptr = ptr->children[ind];

        //If we make it to the end and the bool is true, it's a word
        if (i == strlen(copy)-1)
        {
            if (ptr->is_word == true)
                return true;
        }
    }

    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    gone(root);
    if (root)
        return false
    else
        return true
}
