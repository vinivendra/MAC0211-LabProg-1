#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Output.h"
#include "rio.h"

#define charTerra "#"
#define charAgua  "."

/*
 Protótipos
 */

void outputLine (float *linha, int largura);
void outputArray (float **array, int altura, int largura, int indice);

/*
 Funções
 */

void outputArray (float **array, int altura, int largura, int indice) { /* Imprime a grade */
    int i;
    
    for (i = 0; i < altura; i ++) /* Imprime cada linha, de trás para frente */
        outputLine(array[(i+indice)%altura], largura);
}


void outputLine (float *linha, int largura) { /* Imprime a linha */
    int i = 0;
    
    for (i = 0; i < largura; i++) {
        if (linha[i] == TERRA)
            printf("%.2f ", linha[i]);
        else
            printf("%.2f ", linha[i]);
    }
    
    printf("\n");
}
