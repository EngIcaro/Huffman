#include <stdio.h>
#include <stdlib.h>
typedef struct priorityqueue PriorityQueue;
typedef struct node Node;


struct priorityqueue
{
	Node *first;
};

struct node{

	int frequency;
	unsigned char caracter;
	Node *nextNode;
	Node *left;
	Node *right;
};


PriorityQueue *creat_empty_queue();

int is_empty(PriorityQueue *Queue);

PriorityQueue *enqueue(PriorityQueue *Queue, Node *newNode);

PriorityQueue *creat_queue(PriorityQueue *Queue);

Node *dequeue(PriorityQueue *Queue, Node *newNode);

Node *creat_node(int caracter , int frequency);

PriorityQueue *creat_tree(PriorityQueue *Queue);

PriorityQueue *creat_father(PriorityQueue *Queue, Node *left, Node *right);