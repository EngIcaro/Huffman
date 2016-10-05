#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#define MAX 256
typedef struct node Node;

struct node{

	int frequency;
	unsigned char caracter;
	Node *nextNode;
	Node *left;
	Node *right;
};


int is_bit_i_set(unsigned char c, int j)
{
	unsigned char mask = 1<<j;
	return mask & c;
}



void write_extract(unsigned char c, int i, Node *root)
{
	int bit_set, j;
	Node *aux = root;
	FILE *output = fopen("bla2", "wb");
	for(j=0; j<8; j++)
	{
		bit_set = is_bit_i_set('c', j);
		if(bit_set)
		{
			aux = aux->right;
			if(aux->right == NULL && aux->left == NULL)
			{
				printf("%c\n", aux->caracter);
				fputc(aux->caracter, output);
				aux = root;
			}
		}
		else
		{
			aux = aux->left;
			if(aux->right == NULL && aux->left == NULL)
			{
				printf("%c\n", aux->caracter);
				fputc(aux->caracter, output);
				aux = root;
			}
		}
	}
}

void extract (Node *root)
{
	int i;
	FILE *file;
	file = fopen("text", "rb");
	unsigned char positivo, current_char;
	char negativo;
	unsigned char frase[100];
	for(i=0; i<19; i++)
	{
		positivo = fgetc(file);
	}
	int last_char, bit_set;
	while( (negativo = (positivo = fgetc(file))) != EOF)
	{
		i=0;
		frase[i] = positivo;
		i++;
		while(( (negativo = (positivo = fgetc(file))) != EOF) && i<100)
		{
			frase[i] = positivo;
			i++;
		}
		if(i == 100)
		{
			for(i=0; i<=100; i++)
			{
				write_extract(frase[i], i, root);
			}
		}
		else	
		{
			last_char = (strlen(frase) - 1);
			
		}
	}

	
}


int main()
{
}














