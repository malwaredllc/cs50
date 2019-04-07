// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 10000

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// prototypes
void delete_sll(node *head);

// Represents a hash table
node *hashtable[N];
int wordcount = 0;

// dbj2 string hash function (http://www.cse.yorku.ca/~oz/hash.html)
unsigned int hash(const char* key)
{
    unsigned int h = 5381;
    int c;

    while ((c = *key++))
        h = ((h << 5) + h) + tolower(c);

    return h % N;
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

    // Insert words into hash table
    while (true)
    {
        // allocate memory for new node and check for error
        node *n = malloc(sizeof(node));
        if (!n)
        {
            fprintf(stderr, "Error: unable to allocate memory for node\n");
            free(n);
            return 1;
        }

        // scan next word from dictionary and assign values to new node
        fscanf(file, "%s", n->word);
        n->next = NULL;

        // break if end of file
        if (feof(file))
        {
            free(n);
            break;
        }

        // set key as hash code of word
        int key = hash(n->word);

        // if bucket is empty, set the key index node to the new node
        if (!hashtable[key])
        {
            hashtable[key] = n;
        }
        // if bucket is not empty, insert element at head of linked list at key index
        else
        {
            n->next = hashtable[key];
            hashtable[key] = n;
        }

        // increment wordcount
        wordcount++;
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
    // set key to hash code of word
    int key = hash(word);

    // initialize traversal pointer at key index of hashtable
    node *trav = hashtable[key];
    if (!trav)
    {
        return false;
    }
    while (true)
    {
        if (!strcasecmp(trav->word, word))
        {
            return true;
        }
        if (trav->next)
        {
            trav = trav->next;
        }
        else
        {
            break;
        }
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        delete_sll(hashtable[i]);
    }
    free(*hashtable);
    return true;
}

void delete_sll(node *head)
{
    // initialize traversal pointer
    node *trav = head;

    // recursively delete the rest of the singly linked list
    while (trav)
    {
        if (trav->next)
        {
            delete_sll(trav->next);
        }
        free(trav);
        break;
    }
}