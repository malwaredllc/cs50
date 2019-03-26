#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// queue array structure
typedef struct
{
    int arr[5];
    int size;
    int front;
} queue;

// prototypes
queue* create(void);
void enqueue(queue* q, int val);
int dequeue(queue* q);

int main(void)
{
    // create a new queue
    queue* q = create();

    // enqueue and dequeue integers 0-9
    enqueue(q, 0);
    enqueue(q, 1);
    enqueue(q, 2);
    int a = dequeue(q);
    enqueue(q, 3);
    int b = dequeue(q);
    int c = dequeue(q);
    enqueue(q, 4);
    enqueue(q, 5);
    enqueue(q, 6);
    enqueue(q, 7);
    enqueue(q, 8);
    int d = dequeue(q);
    int e = dequeue(q);
    int f = dequeue(q);
    int g = dequeue(q);
    int h = dequeue(q);
    int i = dequeue(q);

    // success
    return 0;
}

queue* create(void)
{
    // allocate memory for a queue array structure
    queue* q = malloc(sizeof(queue));

    // set size to 0
    q->size = 0;

    // set front to index 0
    q->front = 0;

    // return pointer to queue
    return q;
}

void enqueue(queue* q, int val)
{
    // determine capacity of queue
    int capacity = sizeof(q->arr) / sizeof(int);

    // "wraparound" front to prevent index out of bounds error
    int index = (q->front + q->size) % capacity;

    // check if queue is full
    if (q->size < capacity)
    {
        // assign value to index
        q->arr[index] = val;

        // increment queue size
        q->size++;

        printf("Enqueued: %i\n", val);
    }
    else
    {
        printf("Queue is full\n");
    }

}

int dequeue(queue* q)
{
    // determine capacity of queue
    int capacity = (sizeof(q->arr) / sizeof(int));

    // check if queue is empty
    if (q->size > 0)
    {
        // determine index to dequeue
        int index = q->front % capacity;

        // dequeue value at index
        int val = q->arr[index];

        // increment front and decrement size
        q->front++;
        q->size--;

        // return dequeued value
        printf("Dequeued: %i\n", val);
        return val;
    }
    else
    {
        printf("Queue is empty\n");
        return 0;
    }
}
