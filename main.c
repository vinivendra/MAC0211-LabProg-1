#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "Output.h"
#include "grade.h"
#include "util.h"
#include "pixel.h"

#define velocidadeDoBarcoInicial 1
#define larguraDoRioInicial 100
#define fluxoDesejadoInicial 50
#define alturaDaGrade 30
#define distanciaEntreIlhasInicial 10
#define probabilidadeDeObstaculosInicial 0.5

#define limiteDasMargens 0.2


int main (int argc, char *argv[]) {
    
  /*
    Declaração de variáveis
  */

  float velocidadeDoBarco = velocidadeDoBarcoInicial;
  int larguraDoRio = larguraDoRioInicial;
  int fluxoDesejado = fluxoDesejadoInicial;
  int dIlha = distanciaEntreIlhasInicial;
  float pIlha = probabilidadeDeObstaculosInicial;
    
  struct timespec tim2;
  struct timespec tim;
    
  int seed = 0;
  int verbose = 0;
  int indice = 0;
  pixel **grade;
    
  /*
    Leitura de parametros
  */
    
  getArgs(argc, argv, &velocidadeDoBarco, &larguraDoRio, &seed, &fluxoDesejado, &verbose, &dIlha, &pIlha);
    
  if (verbose) {
    printf ("\t \t Opcoes disponiveis: \n"
            "-b = %f  - Velocidade do barco\n"
            "-l = %d  - Largura do Rio\n"
            "-s = %d  - semente para o gerador aleatorio\n"
            "-f = %d  - Fluxo da agua\n"
            "-v = %d  - Verbose\n"
            "-pI = %f - Probabilidade de haver obstaculos\n"
            "-dI = %d - Distancia minima entre obstaculos\n"
            "Pressione Enter para continuar...\n", velocidadeDoBarco, larguraDoRio, seed, fluxoDesejado, verbose, pIlha, dIlha);
    getchar();
  }
    
  /*
    Inicialização
  */
    
  tim.tv_sec  = 0;
  tim.tv_nsec = 100000000/velocidadeDoBarco;
    
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
    
  freeGrade(grade, alturaDaGrade, larguraDoRio);

  return 0;
}





