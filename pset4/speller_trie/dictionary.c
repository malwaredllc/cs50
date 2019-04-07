// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27
#define ASCII_a 97

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// prototypes
int index(char c);
void free_node(node *n);

// Represents a trie
node *root;
int wordcount = 0;

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

        // increment wordcount
        wordcount++;

        // initialize a traversal pointer at root
        node *trav = root;

        // loop through characters of word
        for (int i = 0, len = strlen(word); i < len; i++)
        {
            // get index of child node for next character
            int x = index(word[i]);

            // move traversal pointer to next character on path if it exists
            if (trav->children[x])
            {
                trav = trav->children[x];
            }
            // create a new node for next character on path if it does not exist
            else
            {
                // allocate memory for new node
                node *n = malloc(sizeof(node));

                // set is_word to true if last character, otherwise false
                n->is_word = i == len - 1 ? true : false;

                // set pointers to children nodes to null
                for (int j = 0; j < N; j++)
                {
                    n->children[j] = NULL;
                }

                // add new node to trie
                trav->children[x] = n;

                // move traversal pointer to new node
                trav = trav->children[x];
            }
        }
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordcount;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // initialize traversal pointer
    node *trav = root;

    // loop through characters of word
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        // get index of child node for next character
        int x = index(word[i]);

        // return false if child node for next character does not exist
        if (!trav->children[x])
        {
            return false;
        }

        // return true if last character and is_word is true
        else if (i == len - 1 && trav->children[x]->is_word == true)
        {
            return true;
        }

        // else move traversal pointer to next child node
        else
        {
            trav = trav->children[x];
        }
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // free child nodes that exist
    for (int i = 0; i < N; i++)
    {
        if (root->children[i])
        {
            free_node(root->children[i]);
        }
    }
    // free root
    free(root);

    // success
    return true;
}

// Get index of node child for a character
int index(char c)
{
    // map ASCII value of character to child node index value
    return tolower(c) != 39 ? tolower(c) - ASCII_a : 26;
}

// Free child nodes
void free_node(node *n)
{
    // recursively free child nodes that exist
    for (int i = 0; i < N; i++)
    {
        if (n->children[i])
        {
            free_node(n->children[i]);

        }
    }

    // free node
    free(n);
}
