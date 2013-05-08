#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grade.h"

float **initGrade(int altura, int largura) { /* Malloca espaço para a grade */
    int i = 0;
    float **grade;
    
    grade = malloc(altura*sizeof(float *)); /* Primeira dimensão */
    
    for (i = 0; i < altura; i++) {          /* Linhas da segunda dimensão */
        grade[i] = malloc(largura*sizeof(float));
    }
    
    return grade;
}

void criaPrimeiroFrame(float **grade, int altura, int largura, float limiteDasMargens, int fluxoDesejado) { /* Popula a grade com os números do
                                                                                                                primeiro frame */
    int i = 1;
    
    primeiraLinha(grade[0], largura, limiteDasMargens, fluxoDesejado); /* Popula a primeira linha; as outras serão criadas em cima dela */
    
    for (i = 1; i < altura; i++) {
        proximaLinha (grade[i-1], grade[i], largura, limiteDasMargens, fluxoDesejado); /* Popula as próximas linhas, com base na 1a */
    }
    
}


void criaProximoFrame (float **grade, int altura, int largura, float limiteDasMargens, int fluxoDesejado, int *indice) {
    proximaLinha(grade[(*indice +1)%altura], grade[*indice], largura, limiteDasMargens, fluxoDesejado); /* Cria a linha nova do frame */
}


