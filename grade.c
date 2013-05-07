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
