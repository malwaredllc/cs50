#include <stdio.h>
#include <stdlib.h>

// node structure
typedef struct _node
{
    int val;
    struct _node *next;
} node;

// queue structure
typedef struct _queue
{
    int size;
    struct _node *head;
    struct _node *tail;
} queue;

//prototypes
queue* init(void);
int isempty(queue* q);
int dequeue(queue* q);
void enqueue(queue* q, int val);

int main(void)
{
    // initialize queue
    queue* q = init();

    // enqueue and dequeue integers 0-3
    enqueue(q, 0);
    enqueue(q, 1);
    int a = dequeue(q);
    enqueue(q, 2);
    enqueue(q, 3);
    int b = dequeue(q);
    int c = dequeue(q);

    // success
    return 0;
}

queue* init(void)
{
    // initialize queue
    queue* q = malloc(sizeof(queue));

    // assign initial values to queue attributes
    q->size = 0;
    q->head = NULL;
    q->tail = NULL;

    // return pointer to queue
    return q;
}

int isempty(queue* q)
{
    return (q->tail == NULL);
}

void enqueue(queue* q, int val)
{
    // allocate memory for new node
    node* n = malloc(sizeof(node));

    // return error if unable to allocate memory
    if (!n)
    {
        printf("Unable to allocate memory for new node\n");
    }

    // assign value to new node
    n->val = val;
    n->next = NULL;

    // check if queue is not empty
    if (!isempty(q))
    {
        // link tail node to new node
        q->tail->next = n;

        // assign tail pointer to new node
        q->tail = n;
    }
    else
    {
        // point head and tail to new node
        q->head = n;
        q->tail = n;
    }

    // increment size of queue
    q->size++;
}

int dequeue(queue* q)
{
    // get value of the head node of the queue
    int val = q->head->val;

    // create temporary node pointing to head of queue
    node* tmp = q->head;

    // move head of queue to next node
    q->head = q->head->next;

    // free temporary node (previous head of queue)
    free(tmp);

    // decrement queue size
    q->size--;

    // return dequeued value
    return val;
}
