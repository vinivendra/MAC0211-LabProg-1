#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

int getArgs(int argc,char *argv[],int *velocidadeDoBarco, int *larguraDoRio, int *seed, int *fluxoDesejado, 
	     int *verbose, int *dIlha, float *pIlha)
{
  int read = 0;
  
  while(--argc){
    if (sscanf(argv[argc], "-b%d",velocidadeDoBarco)) read++;
    else if (sscanf(argv[argc], "-l%d",larguraDoRio)) read++;
    else if (sscanf(argv[argc], "-s%d",seed)) read++;
    else if (sscanf(argv[argc], "-f%d",fluxoDesejado)) read++;
    else if (sscanf(argv[argc], "-pI%f",pIlha)) read++;
    else if (sscanf(argv[argc], "-dI%d",dIlha)) read++;
    else if (strcmp(argv[argc],"-L") == 0)
      *verbose = 1;
    else {
      printf ("\t \t Opcoes disponiveis: \n"
	      "-bxxx  - Velocidade do barco\n"
	      "-lxxx  - Largura do Rio\n"
	      "-sxxx  - semente para o gerador aleatorio\n"
	      "-fxxx  - Fluxo da agua\n"
	      "-pIxxx - Probabilidade de haver obstaculos\n"
	      "-dIxxx - Distancia minima entre obstaculos\n");
      exit (-1);
    }
  }
  return read;
}
