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
char* find(node* root, char key[]);
void insert(node* root, char key[], char value[]);

int main(void)
{
    // initialize root node of trie
    node* root = init();

    // insert test key/value pairs
    insert(root, "1636", "Harvard");
    insert(root, "1701", "Yale");
    insert(root, "1739", "Dartmouth");

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
