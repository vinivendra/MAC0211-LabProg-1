#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grade.h"

float **initGrade(int altura, int largura) {
    int i = 0;
    float **grade;
    
    grade = malloc(altura*sizeof(float *));
    
    for (i = 0; i < altura; i++) {
        grade[i] = malloc(largura*sizeof(float));
    }
    
    return grade;
}

void criaPrimeiroFrame(float **grade, int altura, int largura, float limiteDasMargens, int fluxoDesejado) {
    int i = 0;
    
    for (i = 0; i < altura; i++) {
        primeiraLinha(grade[i], largura, limiteDasMargens, fluxoDesejado);
    }
}


void criaProximoFrame (float **grade, int altura, int largura, float limiteDasMargens, int fluxoDesejado){
  
    float i,*tmp = grade[0];
  
  for (i = 0; i < largura - 1; i++)
      grade[i] = grade[i+1];
  
  aleatorizaMargem (grade[largura-1], tmp,limiteDasMargens);
  grade[largura -1] = tmp;
  
}

void aleatorizaMargem(float *lLine, float *fLine, int limiteDasMargens,largura){
    
    int tamanhoDaMargemEsquerda = margemEsquerda(lLine);
    int tamanhoDaMargemDireita = margemDireita(lLine, largura);
    int resultado1 = (rand()%3) - 1;
    int resultado2 = (rand()%3) - 1;
    int tempMargemEsq = tamanhoDaMargemEsquerda + resultado1;
    int tempMargemDir = tamanhoDaMargemDireita + resultado2;
    int i;
    
    for (i = 0; i < tempMargemEsq; i++) /* Insere nova margem esquerda */
	fline[i] = 0;
	

    for (i = largura - tempMargemDir; i < largura; i++) { /* Insere nova margem direita */
	fline[i] = 0;
  }
