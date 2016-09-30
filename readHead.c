#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct stack Stack;
typedef struct node_stack Node;

/*struct node_stack{

	unsigned char caracter;
	Node *left;
	Node *right;
	Node *bottom;
};

struct stack{                                        //STRUCT PARA UMA PILHA
    int size;
    Node *top;
};

Node *creat_node_stack(unsigned char caracter)
{
	Node *newNode = (Node*) calloc(1,sizeof(Node));
	newNode->caracter = caracter;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

Stack *stack()                                                 //CRIA UMA PILHA VAZIA DE TAMANHO 0
{
    Stack *newStack = (Stack*) calloc(1, sizeof(Stack));
    newStack->size = 0;
    newStack->top = NULL;
    return newStack;
}

Node *peek(Stack *stack)                                       //RETORNA O  TOP
{
    return stack->top;
}

void push(Stack *stack, unsigned char caracter)                            //ADICIONA UM NÓ AO TOPO DA PILHA.                  
{
    Node *temp = creat_node(caracter);                           // TEMP VAI SER UM NOVO NÓ COM CONTEUDO == VALOR E O DE BAIXO DELE É NULL
    temp->bottom = stack->top;                                //AGORA EU FAÇO O DE BAIXO(BUTTOM) DO NOVO Nó APONTAR PARA O TOPO DA PILHA
    stack->top = temp;                                        // AGORA O TOPO DA PILHA VAI APONTAR PARA O NOVO ŃÓ
    stack->size++;                                            // TAMANHO CRESCE EM UMA UNIDADE
}

bool isEmpty(Stack *stack)
{
    return !stack->size;
}

Node *pop(Stack *stack)										  // VAI RETORNAR O NÓ QUE RETIROU DA PILHA
{
    Node *aux = stack->top;                                   //CRIO UM NOVO NÓ QUE VAI APONTAR PARA O TOP DA PILHA
    stack->top = stack->top->bottom;                          // AGORA O TOPO DA PILHA VAI APONTAR PARA O BOTTOM DO NÓ QUE ESTÁ NO TOPO
    stack->size--;                                            //TAMANHO DIMINUI EM UM
    aux->bottom = NULL;
    return aux;
}
*/

void descomprimir()
{
	int i;
	FILE *file;
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
	char string_tree[tree];
	for(i=0; i<tree; i++)
	{
		string_tree[i] = fgetc(file);
		printf("%c\n", string_tree[i]);
	}

}
