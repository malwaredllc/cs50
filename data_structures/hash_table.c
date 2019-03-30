#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


// singly linked list node structure
typedef struct _node
{
    unsigned char* str;
    struct _node* next;
} node;

// hash table structure
typedef struct
{
    node* arr[10];
} hash_table;


// prototypes
hash_table* init(void);
unsigned long hash(unsigned char *str);
int find(hash_table* h, unsigned char* str);
void insert(hash_table* h, unsigned char* str);

int main(void)
{
    // initialize hash table
    hash_table* h = init();

    // insert test strings into hash table
    insert(h, (unsigned char*) "Aaron");
    insert(h, (unsigned char*) "Aaron"); // collision test
    insert(h, (unsigned char*) "Charlie");

    // lookup test strings
    find(h, (unsigned char*) "Aaron"); // exists
    find(h, (unsigned char*) "Bradley"); // does not exist
    find(h, (unsigned char*) "Charlie"); // exists

    // success
    return 0;
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
        n->str = NULL;
        n->next = NULL;
        h->arr[i] = n;
    }

    // return pointer to hash table
    return h;
}

void insert(hash_table* h, unsigned char* str)
{
    // get length of hash table array
    int len = sizeof(h->arr) / sizeof(node*);

    // generate hash code of string and mod by array length to keep it within bounds
    int index = hash(str) % len;

    // check if node at index has a value
    if (!h->arr[index]->str)
    {
        // assign value to node
        h->arr[index]->str = str;
    }
    else
    {
        // allocate memory for new node
        node* n = malloc(sizeof(node));

        // assign value to new node
        n->str = str;

        // return error if unable to allocate memory
        if (!n)
        {
            printf("Error: unable to allocate memory\n");
        }

        // point new node to first node of the singly linked list
        n->next = h->arr[index]->next;

        // point head to new node
        h->arr[index]->next = n;
    }

    // print debugging information to stdout
    printf("Added: ");
    for (int i = 0; str[i] != '\0'; i++)
    {
        printf("%c", str[i]);
    }
    printf("\n");
}

int find(hash_table *h, unsigned char* str)
{
    // get length of hash table array
    int len = sizeof(h->arr) / sizeof(node*);

    // generate hash code of string and mod by array length to keep it within bounds
    int index = hash(str) % len;

    // init a traversal pointer at the head of the singly linked list
    node* trav = h->arr[index];

    // traverse nodes of the singly linked list
    while (1)
    {
        // return true if node value is equal to input value
        if (trav->str == str)
        {
            printf("Found: ");
            for (int i = 0; str[i] != '\0'; i++)
            {
                printf("%c", str[i]);
            }
            printf("\n");
            return 1;
        }
        // move traversal pointer to next node if pointer is not null
        if (trav->next != NULL)
        {
            trav = trav->next;
        }

        // return false if traversal pointer has reached end of the singly linked list
        else
        {
            printf("Not found: ");
            for (int i = 0; str[i] != '\0'; i++)
            {
                printf("%c", str[i]);
            }
            printf("\n");
            return 0;
        }
    }
}

// dbj2 string hash function (http://www.cse.yorku.ca/~oz/hash.html)
unsigned long hash(unsigned char *str)
{
    unsigned long h = 5381;
    int c;

    while ((c = *str++))
        h = ((h << 5) + h) + c; /* h * 33 + c */

    return h;
}
