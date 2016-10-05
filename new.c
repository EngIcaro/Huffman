#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#define MAX 256

int is_bit_i_set(unsigned char c, int j)
{
	unsigned char mask = 1<<j;
	return mask & c;
}

int main()
{

	int i;
	int val;
	for(i=0; i<8; i++)
	{
		val = is_bit_i_set(E, i);
		printf("%d\n");
	}
}