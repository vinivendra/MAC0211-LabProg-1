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


void criaProximoFrame (float **grade, int altura, int largura, float limiteDasMargens, int fluxoDesejado){
    
    int i;
    float *tmp = grade[0];
    
    for (i = 0; i < largura - 1; i++)
        grade[i] = grade[i+1];
    
    /*aleatorizaMargem (grade[largura-1], tmp,limiteDasMargens);*/
    grade[largura -1] = tmp;
    
}


