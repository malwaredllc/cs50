#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// stack array structure
typedef struct _stack
{
    int arr[100];
    int top;
} stack;


// prototypes
int pop(stack* s);
void push(stack* s, int val);

int main(void)
{

    // create stack
    stack s;
    s.top = -1;

    // push integers 0-3 onto the stack
    for (int i = 0; i < 4; i++)
    {
        push(&s, i);
        printf("Pushed: %i\n", i);
    }

    // pop all items off the stack and print each item to stdout
    while (true)
    {
        int n = pop(&s);
        if (s.top == -1)
        {
            break;
        }
        else
        {
            printf("Popped: %i\n", n);
        }
    }

    // success
    return 0;
}

void push(stack* s, int val)
{
    // increment stack top index
    s->top++;

    // use modulo of array length to "wraparound" and avoid index out of bounds
    int index = s->top % (sizeof(s->arr) / sizeof(int));

    // add value to top of stack
    s->arr[index] = val;
}

int pop(stack* s)
{

    // use modulo of array length to "wraparound" and avoid index out of bounds
    int index = s->top % (sizeof(s->arr) / sizeof(int));

    // get value from top of stack
    int val = s->arr[index];

    // decrement stack top index
    s->top--;

    // return value popped off the stack
    return val;
}

