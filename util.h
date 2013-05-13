#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define clearScreen() printf("%c[2J%c[1;1H", 27, 27)

int getArgs(int argc,char *argv[],int *, int *, int *, int *, int *, int *, float *);

