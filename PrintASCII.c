#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Output.h"


void outputArray (float **array, int altura, int largura, int indice) {
    int i = indice;
    int j = 0;
    
    for (i = altura - 1; i >= 0; i --) {
        for (j = 0; j < largura; j++) {
            float aux =  array[(i+indice)%altura][j];
            if (aux == 0)
                printf("#");
            else
                printf("%d",(int)aux);
        }
        printf("\n");
    }
}


void outputLine (float *linha, int largura) {
    int i = 0;
    
    for (i = 0; i < largura; i++) {
        float aux =  linha[i];
        if (aux == 0)
            printf("#");
        else
            printf("%d",(int) linha[i]);
    }
    printf("\n");
}