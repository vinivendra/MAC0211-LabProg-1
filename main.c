#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "Output.h"
#include "grade.h"
#include "util.h"

#define velocidadeDaAgua 10
#define alturaDaGrade 30
#define ProbabilidadeDeObstaculos 0.5
#define limiteDasMargens 0.2
#define distanciaEntreIlhas 10


int main (int argc, char *argv[]) {
    
  /*
    Declaração de variáveis
  */
  struct timespec tim2;
  struct timespec tim;
  int velocidadeDoBarco = 0;
  int larguraDoRio = 0;
  int seed = 0;
  int fluxoDesejado = 0;
  int verbose = 0;
  float **grade;
  int indice;
  int dIlha = distanciaEntreIlhas;
  float pIlha = ProbabilidadeDeObstaculos;
    
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
    seed = time(NULL);
  }
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
    
  criaPrimeiroFrame(grade, alturaDaGrade, larguraDoRio, limiteDasMargens, fluxoDesejado, dIlha, pIlha);
    
  outputArray(grade, alturaDaGrade, larguraDoRio, indice);
    
  /* printf("\n");*/
  clearScreen();
    
  /*
    Frames subsequentes
  */
    
  for(;;){
    indice = (indice - 1+alturaDaGrade) % alturaDaGrade;
        
    criaProximoFrame(grade, alturaDaGrade, larguraDoRio, limiteDasMargens, fluxoDesejado, indice, dIlha, pIlha);
        
    outputArray(grade, alturaDaGrade, larguraDoRio, indice);
    /*printf("\n");*/
    clearScreen();
        
    nanosleep(&tim, &tim2);
  }
    
  return 0;
}





