#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define clearScreen() printf("%c[2J%c[1;1H", 27, 27)

int getArgs(int argc,char *argv[],float *velocidadeDoBarco, int *larguraDoRio, int *seed, int *fluxoDesejado, int *verbose, int *dIlha, float *pIlha);
