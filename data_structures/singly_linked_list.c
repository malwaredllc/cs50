#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// singly linked list node structure
typedef struct _sllnode
{
    int val;
    struct _sllnode* next;
} sllnode;

// prototypes
sllnode* create(int val);
bool find(sllnode* head, int val);
void insert(sllnode* head, int val);
void destroy(sllnode* head);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: singly_linked_list value\n");
        return 1;
    }

    int value = atoi(argv[1]);

    // create singly linked list
    sllnode* head = create(0);

    // insert nodes for every even number less than 1000
    for (int i = head->val; i < 1000; i+=2)
    {
        insert(head, i);
    }

    // check if user inputted value exists in singly linked list
    bool exists = find(head, value);

    // display result
    if (exists)
    {
        printf("Exists\n");
    }
    else
    {
        printf("Does not exist\n");
    }

    // free memory allocated to singly linked list
    destroy(head);

    // success
    return 0;
}

sllnode* create(int val)
{
    // allocate memory for node
    sllnode* node = malloc(sizeof(sllnode));

    // return error if unable to allocate memory
    if (!node)
    {
        printf("Error: unable to allocate memory\n");
    }
    // assign node value
    node->val = val;

    // point node to null
    node->next = NULL;

    // return pointer to node
    return node;
}

void insert(sllnode* head, int val)
{
    // alloacte memory for node
    sllnode* node = malloc(sizeof(sllnode));

    // return error if unable to allocate memory
    if (!node)
    {
        printf("Error: unable to allocate memory\n");
    }
    // assign node value
    node->val = val;

    // point node to first node of the singly linked list
    node->next = head->next;

    // point head to node
    head->next = node;
}

bool find(sllnode* head, int val)
{
    // create a traversal pointer at the head of the singly linked list
    sllnode* trav = head;

    // traverse nodes of the singly linked list
    while (true)
    {
        // return true if node value is equal to input value
        if (trav->val == val)
        {
            return true;
        }
        // move traversal pointer to next node if pointer is not null
        if (trav->next != NULL)
        {
            trav = trav->next;
        }
        // return false if traversal pointer has reached end of the singly linked list
        else
        {
            return false;
        }
    }
}

void destroy(sllnode* head)
{
    // create a traversal pointer at the head of the singly linked list
    sllnode* trav = head;

    // traverse nodes of the singly linked list
    while (true)
    {
        // recursively call destroy on the next node until traversal pointer reaches end of the singly linked list
        if (trav->next != NULL)
        {
            destroy(trav->next);
        }

        // free the current node
        free(trav);
        break;
    }
}

