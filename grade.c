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
    int i = 1;
    
    primeiraLinha(grade[0], largura, limiteDasMargens, fluxoDesejado);
    
    for (i = 1; i < altura; i++) {
        proximaLinha (grade[i-1], grade[i], largura, limiteDasMargens, fluxoDesejado);
    }
    
}


void criaProximoFrame (float **grade, int altura, int largura, float limiteDasMargens, int fluxoDesejado, int *indice) {
    
    printf("%d\n", altura);
    printf("%d\n", (*indice +1)%altura);
    proximaLinha(grade[(*indice +1)%altura], grade[*indice], largura, limiteDasMargens, fluxoDesejado);
    
}


