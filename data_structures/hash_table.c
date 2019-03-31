#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define BUF 128
#define TOT 10000
#define VERBOSE 0

// singly linked list node structure
typedef struct node
{
    struct node* next;
    char* data;
} node;

// hash table structure
typedef struct
{
    node* arr[100];
} hash_table;

// prototypes
hash_table* init(void);
unsigned long hash(unsigned char* str);
int find(hash_table* h, char data[]);
int load(hash_table* h, char filename[]);
void insert(hash_table* h, char* data);
void delete(hash_table* h, char data[]);
void destroy(hash_table* h);
void destroy_sll(node* head);

int main(int argc, char* argv[])
{
    // display usage information and exit if not correct number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./hash_table wordlist\n");
        return 1;
    }
    // initialize hash table
    hash_table* h = init();

    // load wordlist into hash table
    if (!load(h, argv[1]))
    {

        // lookup test strings
        find(h, "arm");
        find(h, "wasp");
        find(h, "zoology");
        find(h, "biology");

        // delete test strings
        delete(h, "wasp");

        // lookup deleted test string
        find(h, "abacus");

        // destroy hash table
        destroy(h);

        // success
        return 0;
    }
    return 1;
}

hash_table* init(void)
{
    // allocate memory for hash table
    hash_table* h = malloc(sizeof(hash_table));

    // return error if unable to allocate memory
    if (!h)
    {
        printf("Unable to allocate memory for hash table\n");
    }

    // initialize linked list nodes at each index of hash table array
    for (int i = 0, len = sizeof(h->arr) / sizeof(node*); i < len; i++)
    {
        node* n = malloc(sizeof(node));
        if (!h)
        {
            printf("Unable to allocate memory for node\n");
        }
        n->next = NULL;
        h->arr[i] = n;
    }

    // return pointer to hash table
    return h;
}

void insert(hash_table* h, char* data)
{
    // get length of hash table array
    int len = sizeof(h->arr) / sizeof(node*);

    // generate hash code of string and mod by array length to keep it within bounds
    int index = hash((unsigned char*) data) % len;

    // allocate memory for new node
    node* n = malloc(sizeof(node));

    // assign value to new node
    n->data = data;

    // return error if unable to allocate memory
    if (!n)
    {
        printf("Error: unable to allocate memory\n");
    }

    // point new node to first node of the singly linked list
    n->next = h->arr[index]->next;

    // point head to new node
    h->arr[index]->next = n;

    // print output to stdout if verbose mode enabled
    if (VERBOSE)
    {
        printf("Added: ");
        for (int i = 0; data[i] != '\0'; i++)
        {
            printf("%c", data[i]);
        }
        printf("\n");
    }
}

int find(hash_table *h, char data[])
{
    // get length of hash table array
    int len = sizeof(h->arr) / sizeof(node*);

    // generate hash code of string and mod by array length to keep it within bounds
    int index = hash((unsigned char*) data) % len;

    // init a traversal pointer at the head of the singly linked list
    node* trav = h->arr[index];

    // traverse nodes of the singly linked list
    while ((trav = trav->next))
    {
        // return true if node value is equal to input value
        if (!strcmp(trav->data, data))
        {
            // print output to stdout
            printf("Found:      ");
            for (int i = 0; data[i] != '\0'; i++)
            {
                printf("%c", data[i]);
            }
            printf("\n");
            return 1;
        }
    }

    // return false if traversal pointer has reached end of the singly linked list
    printf("Not found:  ");
    for (int i = 0; data[i] != '\0'; i++)
    {
        printf("%c", data[i]);
    }
    printf("\n");

    return 0;
}

void delete(hash_table* h, char data[])
{
    // get length of hash table array
    int len = sizeof(h->arr) / sizeof(node*);

    // generate hash code of string and mod by array length to keep it within bounds
    int index = hash((unsigned char*) data) % len;

    // init traversal pointers at the head of the singly linked list
    node* trav = h->arr[index];
    node* prev = h->arr[index];

    // traverse nodes of the singly linked list
    while ((trav = trav->next))
    {
        // delete node from linked list if node value is equal to input value
        if (!strcmp(trav->data, data))
        {
            prev->next = trav->next;
            free(trav);

            // print output to stdout
            printf("Deleted:    ");
            for (int i = 0; data[i] != '\0'; i++)
            {
                printf("%c", data[i]);
            }
            printf("\n");
            break;
        }

        // move previous node traversal pointer to next node
        prev = prev->next;
    }

    // return false if traversal pointer has reached end of the singly linked list
    printf("Not found:  ");
    for (int i = 0; data[i] != '\0'; i++)
    {
        printf("%c", data[i]);
    }
    printf("\n");
}

int load(hash_table* h, char filename[])
{
    // initialize temporary array
    char line[TOT][BUF];
    int i = 0;

    // get pointer to open file
    FILE* plist = fopen(filename, "r");

    // error if file not found
    if (!plist)
    {
        printf("Error: file '%s' not found\n", filename);
        return 1;
    }
    else
    {
        // read lines from file into array
        while(fgets(line[i], BUF, plist))
        {
            // replace '\n' from fgets
            line[i][strlen(line[i]) - 1] = '\0';

            // insert string into hash table
            insert(h, line[i]);
            i++;
        }
        return 0;
    }
}

void destroy(hash_table* h)
{
    // iterate through hash table array calling destroy on each singly linked list
    for (int i = 0, len = sizeof(h->arr) / sizeof(node*); i < len; i++)
    {
        destroy_sll(h->arr[i]);
    }
    free(h);
}

void destroy_sll(node* head)
{
    // initialize a traversal pointer at the head of the singly linked list
    node* trav = head;

    // recursively call destroy on the next node until traversal pointer reaches end of the singly linked list
    while (1)
    {
        if (trav->next)
        {
            destroy_sll(trav->next);
        }
        free(trav);
        break;
    }
}

// dbj2 string hash function (http://www.cse.yorku.ca/~oz/hash.html)
unsigned long hash(unsigned char* key)
{
    unsigned long h = 5381;
    int c;

    while ((c = *key++))
        h = ((h << 5) + h) + c; /* h * 33 + c */

    return h;
}

