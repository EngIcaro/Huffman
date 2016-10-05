#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#define MAX 256

int array[MAX];
char auxi[MAX]; // vai ser usado pra colocar os bits na struct de bits(sequenc)
char string[8192];
int size_tree = 0;
FILE *output;
