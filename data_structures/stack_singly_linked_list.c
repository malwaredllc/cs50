#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// stack node structure (singly linked list implementation)
typedef struct _stack
{
    int val;
    struct _stack* next;
} stack;

// prototypes
stack* create(int val);
int pop(stack* s);
void push(stack* s, int val);

int main(void)
{

    // create stack
    stack* s = create(0);

    // push integers 0-3 onto the stack
    for (int i = s->val; i < 4; i++)
    {
        push(s, i);
        printf("Pushed: %i\n", i);
    }

    // pop all items off the stack and print each item to stdout
    while (true)
    {
        int n = pop(s);
        printf("Popped: %i\n", n);
        if (n == s->val)
        {
            break;
        }
    }

    // success
    return 0;
}

stack* create(int val)
{
    // allocate memory for node
    stack* node = malloc(sizeof(stack));

    // assign value to node
    node->val = val;
    node->next = NULL;

    // return pointer to node
    return node;
}

void push(stack* s, int val)
{
    // allocate memory for node
    stack* node = malloc(sizeof(stack));

    // assign value to node
    node->val = val;

    // point node to top of stack
    node->next = s->next;

    // point top of stack to node
    s->next = node;
}

int pop(stack* s)
{
    // get value of top node on stack
    stack* node = s->next;
    int val = node->val;

    // point top node of the stack to the next node
    s->next = s->next->next;

    // free the top node of the stack
    free(node);

    // return value of node popped off the stack
    return val;
}


