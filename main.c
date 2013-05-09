#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Output.h"
#include "grade.h"

#define velocidadeDaAgua 10
#define alturaDaGrade 41
#define ProbabilidadeDeObstaculos 0.5
#define limiteDasMargens 0.2
#define distanciaEntreIlhas 10

void getArgs(int argc,char *argv[],int *, int *, int *, int *, int *, int *, float *);

int main (int argc, char *argv[]) {
    
  /*
    Declaração de variáveis
  */
  struct timespec tim, tim2;
  int velocidadeDoBarco = 0;
  int larguraDoRio = 0;
  int seed = 0;
  int fluxoDesejado = 0;
  int verbose = 0;
  float **grade;
  int indice;
  int dIlha = distanciaEntreIlhas;
  float pIlha = ProbabilidadeDeObstaculos;
    
  int i = 0;
    
  char *parametro;
    
    
  /*
    Inicialização
  */
    
  indice = 0;
  tim.tv_sec  = 0;
  tim.tv_nsec = 100000000L;
    
  /*
    Leitura de parametros
  */
    
  getArgs(argc, argv, &velocidadeDoBarco, &larguraDoRio, &seed, &fluxoDesejado, &verbose, &dIlha, &pIlha);
  
  printf ("\t \t Opcoes disponiveis: \n"
		"-b = %d  - Velocidade do barco\n"
		"-l = %d  - Largura do Rio\n"
		"-s = %d  - semente para o gerador aleatorio\n"
		"-f = %d  - Fluxo da agua\n"
		"-v = %d  - Verbose\n"
		"-pI = %f - Probabilidade de haver obstaculos\n"
		"-dI = %d - Distancia minima entre obstaculos\n",velocidadeDoBarco, larguraDoRio, seed, fluxoDesejado, verbose, pIlha, dIlha);
    
  /*
    Seed
  */
    
  if (seed == 0) {
    /* Aleatoriza a seed baseado no time */
  }-
  srand(seed);
    
  /*
    Leitura dos parametros que faltarem
  */
    
  if (larguraDoRio == -1) {
    printf("Por favor, insira um valor para a largura do rio:\n");
    scanf("%d", &larguraDoRio);
  }
    
  /*
    Primeiro frame
  */
    
  grade = initGrade(alturaDaGrade, larguraDoRio);
    
  criaPrimeiroFrame(grade, alturaDaGrade, larguraDoRio, limiteDasMargens, fluxoDesejado, distanciaEntreIlhas, ProbabilidadeDeObstaculos);
    
  outputArray(grade, alturaDaGrade, larguraDoRio, indice);
    
  printf("\n");
    
  /*
    Frames subsequentes
  */
    
  for(;;){
    indice = (indice - 1+alturaDaGrade) % alturaDaGrade;
        
    criaProximoFrame(grade, alturaDaGrade, larguraDoRio, limiteDasMargens, fluxoDesejado, indice, distanciaEntreIlhas, ProbabilidadeDeObstaculos);
        
    outputArray(grade, alturaDaGrade, larguraDoRio, indice);
    printf("\n");
        
    nanosleep(&tim, &tim2);
  }
    
  return 0;
}

void getArgs(int argc,char *argv[],int *velocidadeDoBarco, int *larguraDoRio, int *seed, int *fluxoDesejado, 
	     int *verbose, int *larguraDoRio, int *dIlha, float *pIlha)
{
    while(--argc){
      if (sscanf(argv[argv], "-b%d",velocidadeDoBarco)
      else if (sscanf(argv[argv], "-l%d",larguraDoRio)
      else if (sscanf(argv[argv], "-s%d",seed)
      else if (sscanf(argv[argv], "-f%d",fluxo)
      else if (sscanf(argv[argv], "-pI%d",pIlha)
      else if (sscanf(argv[argv], "-dI%d",dIlha)
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






