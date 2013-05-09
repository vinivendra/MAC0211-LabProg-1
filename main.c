#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Output.h"
#include "grade.h"

#define velocidadeDaAgua 10
#define alturaDaGrade 41
#define ProbabilidadeDeObstaculos 1
#define limiteDasMargens 0.2
#define distanciaEntreIlhas 10

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
    
  for (i = 1; i < argc; i ++) {   /* Percorre todos os parâmetros passados */
    parametro = argv[i];
        
    if (parametro[1] == 'b') {  /* Atribui o valor do parâmetro à variável adequada */
      velocidadeDoBarco = atoi(&parametro[2]);
    }
    else if (parametro[1] == 'l') {
      larguraDoRio = atoi(&parametro[2]);
    }
    else if (parametro[1] == 's') {
      seed = atoi(&parametro[2]);
    }
    else if (parametro[1] == 'f') {
      fluxoDesejado = atoi(&parametro[2]);
    }
    else if (parametro[1] == 'v') {
      verbose = 1;
    }
  }
    
  /*
    Seed
  */
    
  if (seed == 0) {
    /* Aleatoriza a seed baseado no time */
  }
  srand(seed);
    
  /*
    Leitura dos parametros que faltarem
  */
    
  if (larguraDoRio == 0) {
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







