#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// node structure
typedef struct _node
{
    char* value;
    struct _node* paths[10];
} node;

// prototypes
node* init(void);
char* lookup(node* root, char key[]);
int find(node* root, char key[], char value[]);
void insert(node* root, char key[], char value[]);

int main(void)
{
    // initialize root node of trie
    node* root = init();

    // insert key/value pairs
    char* key = "1636", * value = "Harvard";
    insert(root, key, value);
    insert(root, "1701", "Yale");
    insert(root, "1739", "Dartmouth");
    printf("Added: (%s, %s)\n", key, value);
    printf("Added: (%s, %s)\n", "1701", "Yale");
    printf("Added: (%s, %s)\n", "1739", "Dartmouth");

    // find key/value pairs
    char* result;
    result = find(root, key, value) ? "Found" : "Not found";
    printf("(%s, %s): %s\n", key, value, result);
    result = find(root, "1739", "Yale") ? "Found" : "Not found";
    printf("(%s, %s): %s\n", "1739", "Yale", result);

    // lookup values by key
    result = lookup(root, "1800");
    printf("%s\n", result);

    // success
    return 0;

}

node* init(void)
{
    // allocate memory for new node
    node* n = malloc(sizeof(node));

    // set path pointers to null
    for (int i = 0, len = sizeof(n->paths) / sizeof(node*); i < len; i++)
    {
        n->paths[i] = NULL;
    }

    // return pointer to node
    return n;
}

void insert(node* root, char key[], char value[])
{
    // initialize traversal pointer at root of trie
    node* trav = root;

    // iterate through digits of key adding nodes to trie as necessary for path
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        // convert digit to integer
        int d = (int) key[i] - '0';

        // check if node exists on path
        if (trav->paths[d])
        {
            trav = trav->paths[d];
        }
        // create new node on path if no node exists
        else
        {
            trav->paths[d] = init();
            trav = trav->paths[d];
        }
    }
    // set value at end of path
    trav->value = value;
}

int find(node* root, char key[], char value[])
{
    // initialize a traversal pointer
    node* trav = root;

    // iterate through characters in key
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        // convert digit to integer
        int d = (int) key[i] - '0';

        // return false if pointer to next node on path is null
        if (!trav->paths[d])
        {
            return 0;
        }
        // move traversal pointer to next node on path
        trav = trav->paths[d];
    }
    // return true if final node on path is equal to input value, otherwise return false
    return (strcmp(trav->value, value) == 0);

}

char* lookup(node* root, char key[])
{
    // initialize a traversal pointer
    node* trav = root;

    // allocate memory for result
    char* result = malloc(sizeof(char));

    // iterate through characters in key
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        // convert digit to integer
        int d = (int) key[i] - '0';

        // return null byte if pointer to next node on path is null
        if (!trav->paths[d])
        {
            return result;
        }
        // move traversal pointer to next node on path
        trav = trav->paths[d];
    }

    // return value at final node on path
    return trav->value;
}
