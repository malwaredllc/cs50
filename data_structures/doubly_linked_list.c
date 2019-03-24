#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// doubly linked list node structure
typedef struct _dllnode
{
    int val;
    struct _dllnode* prev;
    struct _dllnode* next;
} dllnode;

// prototypes
dllnode* create(int val);
dllnode* insert(dllnode* head, int val);
dllnode* find(dllnode* head, int val);
void destroy(dllnode* head);
void delete(dllnode* target);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: doubly_linked_list value\n");
        return 1;
    }

    int value = atoi(argv[1]);

    // create doubly linked list
    dllnode* head = create(0);

    // insert nodes for every even number less than 1000
    for (int i = head->val; i < 1000; i+=2)
    {
        head = insert(head, i);
    }

    // check if user inputted value exists in doubly linked list
    dllnode* target = find(head, value);

    // delete target node if value is found in doubly linked list
    if (target != NULL)
    {
        printf("Exists\n");
        delete(target);
        printf("Removed target node: %i\n", value);
    }
    else
    {
        printf("Does not exist\n");
    }

    // free memory allocated to doubly linked list
    destroy(head);

    // success
    return 0;
}

dllnode* create(int val)
{
    // allocate memory for node
    dllnode* node = malloc(sizeof(dllnode));

    // return error if unable to allocate memory
    if (!node)
    {
        printf("Error: unable to allocate memory\n");
    }
    // assign node value
    node->val = val;

    // point node to null
    node->prev = NULL;
    node->next = NULL;

    // return pointer to node
    return node;
}

dllnode* insert(dllnode* head, int val)
{
    // alloacte memory for node
    dllnode* node = malloc(sizeof(dllnode));

    // return error if unable to allocate memory
    if (!node)
    {
        printf("Error: unable to allocate memory\n");
    }
    // assign node value
    node->val = val;

    // point node to first node of the doubly linked list
    node->next = head;
    head->prev = node;

    return node;
}

dllnode* find(dllnode* head, int val)
{
    // create a traversal pointer at the head of the doubly linked list
    dllnode* trav = head;

    // traverse nodes of the doubly linked list
    while (true)
    {
        // return true if node value is equal to input value
        if (trav->val == val)
        {
            return trav;
        }
        // move traversal pointer to next node if pointer is not null
        if (trav->next != NULL)
        {
            trav = trav->next;
        }
        // return null if traversal pointer has reached end of the doubly linked list
        else
        {
            return NULL;
        }
    }
}

void destroy(dllnode* head)
{
    // create a traversal pointer at the head of the doubly linked list
    dllnode* trav = head;

    // traverse nodes of the doubly linked list
    while (true)
    {
        // recursively call destroy on the next node until traversal pointer reaches end of the doubly linked list
        if (trav->next != NULL)
        {
            destroy(trav->next);
        }

        // free the current node
        free(trav);
        break;
    }
}

void delete(dllnode* target)
{
    // fix pointers of surrounding nodes to "skip over" target node
    if (target->next != NULL && target->prev != NULL)
    {
        target->next->prev = target->prev;
    }
    if (target->prev != NULL && target->next != NULL)
    {
        target->prev->next = target->next;
    }
    // free target node
    free(target);
}