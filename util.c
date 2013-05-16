#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#define maxCaracter 30

/*
 Implementações
*/


static void clear_newlines()
{
    int c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
/*Faz a leitura dos parâmetros e permite a usuário corrigir alguma entrada incorreta*/
int getArgs(int argc,char *argv[],float *velocidadeDoBarco, int *larguraDoRio, int *seed, int *fluxoDesejado, int *verbose, int *dIlha, float *pIlha, float *limiteMargens) {
  int read = 0;
  char decision, input[maxCaracter];
  
  while(--argc){
      if (sscanf(argv[argc], "-b%f", velocidadeDoBarco)) read++;
      else if (sscanf(argv[argc], "-l%d", larguraDoRio)) read++;
      else if (sscanf(argv[argc], "-s%d", seed)) read++;
      else if (sscanf(argv[argc], "-f%d", fluxoDesejado)) read++;
      else if (sscanf(argv[argc], "-pI%f", pIlha)) read++;
      else if (sscanf(argv[argc], "-dI%d", dIlha)) read++;
      else if (sscanf(argv[argc], "-lM%f", limiteMargens)) read++;
      else if (strcmp(argv[argc],"-v") == 0) *verbose = 1;
      else {
	printf ("\t \t Opcoes disponiveis: \n"
		"-b  - Velocidade do barco\n"
		"-l  - Largura do Rio\n"
		"-s  - semente para o gerador aleatorio\n"
		"-f  - Fluxo da agua\n"
		"-pI - Probabilidade de haver obstaculos\n"
		"-dI - Distancia minima entre obstaculos\n"
		"-lM - Limite das margens\n"
		"-v  - Verbose\n"
		"Voce gostaria de entrar novamente com os parametros? \n"
		"S - Sim \t\t outro caracter - Nao\n");
	scanf ("%c",&decision);
	clear_newlines();
	if(decision == 'S' || decision == 's'){
	    while (1){
		printf ("Insira os parametros ou digite -q  para sair :\n");
		fgets(input,maxCaracter-1,stdin);
		if (sscanf(input, "-b%f", velocidadeDoBarco)) read++;
		else if (sscanf(input, " -l%d ", larguraDoRio)) read++;
		else if (sscanf(input, " -s%d ", seed)) read++;
		else if (sscanf(input, " -f%d ", fluxoDesejado)) read++;
		else if (sscanf(input, " -pI%f ", pIlha)) read++;
		else if (sscanf(input, " -dI%d ", dIlha)) read++;
		else if (sscanf(argv[argc], "-lM%f", limiteMargens)) read++;
		else if (strcmp(input,"-v\n") == 0) *verbose = 1;
		else if (strcmp(input,"-q\n") == 0) return read;
		else {
		    
		    printf ("\t \t Opcoes disponiveis: \n"
		    "-b  - Velocidade do barco\n"
		    "-l  - Largura do Rio\n"
		    "-s  - semente para o gerador aleatorio\n"
		    "-f  - Fluxo da agua\n"
		    "-pI - Probabilidade de haver obstaculos\n"
		    "-dI - Distancia minima entre obstaculos\n"
		    "-lM - Limite das margens\n"
		    "-v  - Verbose\n");
		}
		
	    }
	}
	else
	    exit(-1);
      }
  }
  return read;
}

void corrigeArgs (int argc,char *argv[],float *velocidadeDoBarco, int *larguraDoRio, int *seed, int *fluxoDesejado, int *verbose, int *dIlha, float *pIlha, float *limiteMargens) {
    
    if (*larguraDoRio < 16) {
        *larguraDoRio = 16;
        printf("A largura do rio deve ser um int maior que 16.\n"
               "Pressione Enter para continuar...\n");
        getchar();
    }
    
    if (*velocidadeDoBarco < 0.11) {
        *velocidadeDoBarco = 0.11;
        printf("A velocidade do barco deve ser um float maior ou igual a 0.11.\n"
               "Pressione Enter para continuar...\n");
        getchar();
    }
    
    if (*seed <= 0) {
        *seed = 1;
        printf("A seed deve ser positiva.\n"
               "Pressione Enter para continuar...\n");
        getchar();
    }
    
    if (*fluxoDesejado <= 0) {
        *fluxoDesejado = 1;
        printf("O fluxo desejado deve ser um inteiro maior que 0.\n"
               "Pressione Enter para continuar...\n");
        getchar();
    }
    
    if (*pIlha < 0) {
        *pIlha = 0;
        printf("A probabilidade de ilhas deve ser entre 0 e 1.\n"
               "Pressione Enter para continuar...\n");
        getchar();
    }
    else if (*pIlha > 1) {
        *pIlha = 1;
        printf("A probabilidade de ilhas deve ser entre 0 e 1.\n"
               "Pressione Enter para continuar...\n");
        getchar();
    }
    
}