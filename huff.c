#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#define MAX 256

typedef struct priorityqueue PriorityQueue;
typedef struct node Node;
int array[MAX];
char auxi[MAX]; // vai ser usado pra colocar os bits na struct de bits(sequenc)
char string[8192];
int size_tree = 0;


struct node{

	int frequency;
	unsigned char caracter;
	Node *nextNode;
	Node *left;
	Node *right;
};



struct priorityqueue
{
	Node *first;
};

struct Sequenc{
    char bits[MAX];
}sequenc[MAX];

/*


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


*/


PriorityQueue *creat_empty_queue()
{
	PriorityQueue *newQueue = (PriorityQueue*) calloc(1, sizeof(PriorityQueue));
	newQueue->first = NULL;
	return newQueue;
}

/*


*/

int is_empty(PriorityQueue *Queue)
{
	return(Queue->first == NULL);
}

/*


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
			printf("frequency %d caracter %c\n", aux->frequency, aux->caracter);
			aux = aux->nextNode;
		}
	return Queue;
}

/*


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


*/

PriorityQueue *creat_father(PriorityQueue *Queue, Node *father, Node *left, Node *right)
{
	father->caracter = '*';
	father->frequency = (left->frequency + right->frequency);
	father->left = left;
	father->right = right;
	printf("esquerda %c  direita %c frequency pai %d\n", left->caracter, right->caracter, father->frequency);
	Queue = enqueue(Queue,father);
	return Queue;
}

/*


*/

PriorityQueue *creat_tree(PriorityQueue *Queue)
{
	if((!is_empty(Queue)) && Queue->first->nextNode != NULL)
	{
		Node *left = dequeue(Queue, left);
		Node *right = dequeue(Queue, right);
		Node *father = (Node*) calloc(1,sizeof(Node));
		Queue = creat_father(Queue, father, left, right);
		creat_tree(Queue);
	}
	
	return Queue;
}

/*


*/

void pre_order(Node *atual)
{

	if(atual != NULL)
	{
		if(atual->caracter == '*' && atual->left == NULL && atual->right == NULL)
		{
			string[size_tree++] = '\\';
			string[size_tree++] = '*';
		}
		else if (atual->caracter == '\\'  && atual->left == NULL && atual->right == NULL)
		{
			string[size_tree++] = '\\';
			string[size_tree++] = '\\';
		}
		else
		{
			string[size_tree++] = atual->caracter;
			pre_order(atual->left);
			pre_order(atual->right);
		}
	}
}

/*


*/

void crearebits(Node *first, int idx){
    if(first->left != NULL)
    {
        auxi[idx] = '0';
        crearebits(first->left, idx+1);
    }
    if(first->right != NULL)
    {
        auxi[idx] = '1';
        crearebits(first->right, idx+1);
    }
    if(first->left == NULL && first->right == NULL)
    {    
    memcpy(sequenc[first->caracter].bits, auxi, idx);
    }
}

void creat_Header(int trash, Node *root)
{
	FILE *file;
	int i;
	pre_order (root);
	unsigned char first_byte = 0;
	first_byte = trash<<5;
	first_byte |= ((cou>>8)&(0xFF));
	unsigned char second_byte = 0;
	second_byte = (size_tree)&(0xFF);
	file = fopen("text", "wb");
	fputc(first_byte, file);
	fputc(second_byte, file);
		while(string[i] != '\0')
		{
			fputc(string[i], file); // valor do formato inteiro , file
			++i;
		}
}

void descomprimir()
{
	FILE *file
	file = fopen("text", "rb");
	unsigned char first_byte, second_byte;
	first_byte = fgetc(file);
	int trash = 0;
	trash = first_byte>>5;
	int tree  = 0;
	tree |= (first_byte<<3)&(0xFF);
	tree = tree<<5;  
	second_byte = fgetc(file);
	tree |= second_byte;
	printf("lixo%d Arvore%d\n", trash, tree);


}



int main()
{
	PriorityQueue *Queue;
	int i;
	FILE *file;
	file = fopen("bla", "rb"); //rb = abre o arquivo em modo de leitura como binario 
	if(file == NULL)
	{
		printf("arquivo inexistente");
	}
	char negativo;
	unsigned char positivo; 
	for(i=0; i<MAX; i++)
	{
		array[i] = 0;
	}
	while( (negativo = (positivo = fgetc(file))) != EOF)
	{
		array[positivo]++;
	}
	fclose(file);
	Queue = creat_queue(Queue);
	Queue = creat_tree(Queue);
	Node *root= Queue->first;
	//pre_order(Queue->first);
	crearebits(Queue->first, 0); //creando a struct de bits
	printf("\n");
	for(i = 0; i < MAX; i++)
    {
    	if(array[i] != 0)
    	{
    		printf("%c ", i);
        	puts(sequenc[i].bits);  
    	}
    }
	creat_Header(5, root);	 
}




//http://www.inf.pucrs.br/~pinho/LaproI/Arquivos/ArquivosBinarios.htm
//http://www.ime.usp.br/~pf/estruturas-de-dados/aulas/huffman.html#Node
//http://fig.if.usp.br/~esdobay/c/arquivos.pdf