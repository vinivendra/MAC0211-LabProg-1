#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grade.h"

pixel **initGrade(int altura, int largura) {    /* Malloca espaço para a grade */
  int i = 0;
    pixel **grade;
    
    grade = malloc(altura*sizeof(pixel*));     /* Primeira dimensão */
    
    for (i = 0; i < altura; i++) {              /* Linhas da segunda dimensão */
        grade[i] = malloc(largura*sizeof(pixel));
	/*for(j = 0; j < largura; j++)
	  grade[i][j] = malloc(sizeof(pixel));*/
    }
    
    return grade;
}

void criaPrimeiroFrame(pixel **grade, int altura, int largura, float limiteDasMargens, int fluxoDesejado, int distanciaEntreIlhas, float probIlha) { /* Popula a grade com os números do
                                                                                                             primeiro frame */
    int i = 1;
    
    primeiraLinha(grade[0], largura, limiteDasMargens, fluxoDesejado); /* Popula a primeira linha; as outras serão criadas em cima dela */
    
    for (i = 1; i < altura; i++) {
        proximaLinha (grade[i-1], grade[i], largura, limiteDasMargens, fluxoDesejado, distanciaEntreIlhas, probIlha); /* Popula as próximas linhas, com base na 1a */
    }
    
}


void criaProximoFrame (pixel **grade, int altura, int largura, float limiteDasMargens, int fluxoDesejado, int indice, int distanciaEntreIlhas, float probIlha) {
    proximaLinha(grade[(indice +1)%altura], grade[indice], largura, limiteDasMargens, fluxoDesejado, distanciaEntreIlhas, probIlha); /* Cria a linha nova do frame */
}

void freeGrade(pixel** grade, int altura, int largura){
  int i;
  for(i = 0; i < largura; i++)
    free(grade[i]);
  free(grade);
}


