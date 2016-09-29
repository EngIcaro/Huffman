#include <stdio.h>

typedef struct priorityqueue PriorityQueue;

struct priorityqueue
{
	Node *first;
};

PriorityQueue *creat_empty_queue();
int is_empty(PriorityQueue *Queue);
PriorityQueue *enqueue(PriorityQueue *Queue, Node *newNode);
PriorityQueue *creat_queue(PriorityQueue *Queue);
Node *dequeue(PriorityQueue *Queue, Node *newNode);
