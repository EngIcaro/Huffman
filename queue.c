#include "queue.h"
/*
	A função creat_empty_queue, cria uma fila vazia.

*/

PriorityQueue *creat_empty_queue()
{
	PriorityQueue *newQueue = (PriorityQueue*) calloc(1, sizeof(PriorityQueue));
	newQueue->first = NULL;
	return newQueue;
}

/*
	A função is_empty, recebe como parâmetro o primeiro nó da fila
	e retorna verdadeiro caso a fila esteja vazia
*/

int is_empty(PriorityQueue *Queue)
{
	return(Queue->first == NULL);
}

/*
 	A função creat_node, recebe como parâmetro dois inteiros um é a
 	frequência do caracter e outro é a posição do caracter na tabela
 	ASCII  

*/

Node *creat_node(int caracter , int frequency)
{
	Node *newNode = (Node*) calloc(1,sizeof(Node));
	newNode->frequency = frequency;
	newNode->caracter = caracter;
	newNode->nextNode = NULL;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

/*
 	A função enqueue, recebe como parâmetro a fila e o novo nó a ser 
 	adicionado. Esse novo nó é adicionado na fila deacordo com sua 
 	frequência. Onde quem tem a menor frequência tem a maior prioridade. 
	Retornando a nova fila.
*/

PriorityQueue *enqueue(PriorityQueue *Queue, Node *newNode)
{
	if(is_empty(Queue) || newNode->frequency < Queue->first->frequency)
	{
		newNode->nextNode = Queue->first;
		Queue->first = newNode;
	}
	else
	{
		Node *aux = Queue->first;
		while(aux->nextNode != NULL && aux->nextNode->frequency < newNode->frequency)
		{
			aux = aux->nextNode;
		}
		newNode->nextNode = aux->nextNode;
		aux->nextNode = newNode;
	}
	return Queue;

}

/*
	A função creat_queue vai receber como parâmetro a fila. Sua função é pecorrer 
	todo array mapeado, criando uma fila de prioridade. Retornado a nova fila criada.
*/

PriorityQueue *creat_queue(PriorityQueue *Queue)
{
	Queue = creat_empty_queue();
	int i =0;
	for(i=0; i<MAX; i++)
	{
		if(array[i] != 0)
		{
			Node *newNode = creat_node(i, array[i]);
			enqueue(Queue, newNode);
		}
	}
		Node *aux = Queue->first;
		while(aux!= NULL)
		{
			//printf("frequency %d caracter %c\n", aux->frequency, aux->caracter);
			aux = aux->nextNode;
		}
	return Queue;
}

/*
	A função dequeue vai receber como parâmetro a fila e o nó que se quer
	remover. Sua função é retirar ele da lista e retorna-lo.
	
*/

Node *dequeue(PriorityQueue *Queue, Node *newNode)
{
		newNode = (Node*) calloc(1,sizeof(Node));
        Node *aux = Queue->first;
        newNode->caracter = Queue->first->caracter;
        newNode->frequency = Queue->first->frequency;
        if(Queue->first->left != NULL && Queue->first->right != NULL)
        {
        	newNode->left = Queue->first->left;
        	newNode->right = Queue->first->right;
       	}
       	else
       	{
       		newNode->left = NULL;
        	newNode->right = NULL;
       	}
       	Queue->first = Queue->first->nextNode;
        free (aux);
   		return newNode;
}
 

/*
	A função recursiva creat_tree recebe como parâmetro a fila. E sua função é criar uma 
	árvore desenfileirando dois nós e enfileirando o novo pai na fila. Ao final da função
	o primeiro nó da fila será a raiz da árvore. Retorna a nova fila 

*/

PriorityQueue *creat_tree(PriorityQueue *Queue)
{
	if((!is_empty(Queue)) && Queue->first->nextNode != NULL)
	{
		Node *left = dequeue(Queue, left);
		Node *right = dequeue(Queue, right);
		Queue = creat_father(Queue, left, right);
		creat_tree(Queue);
	}
	
	return Queue;
}


/*
	A função creat_father recebe como parâmetro a fila, dois nós que vão ser os respectivos
	filhos. Sua função é criar um novo nó chamado fahter, onde sua frequência vai ser a soma
	dos seus filhos e enfileira de acordo com sua prioridade. Essa função Retorna a nova fila.

*/

PriorityQueue *creat_father(PriorityQueue *Queue, Node *left, Node *right)
{
	Node *father = (Node*) calloc(1,sizeof(Node));
	father->caracter = '*';
	father->frequency = (left->frequency + right->frequency);
	father->left = left;
	father->right = right;
	printf("esquerda %c  direita %c frequency pai %d\n", left->caracter, right->caracter, father->frequency);
	Queue = enqueue(Queue,father);
	return Queue;
}