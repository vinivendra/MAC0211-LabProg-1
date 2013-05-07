#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Output.h"


void outputArray (float **array, int altura, int largura) {
    int i = 0;
    int j = 0;
    
    for (i = altura - 1; i >= 0; i --) {
        for (j = 0; j < largura; j++) {
            int aux = array[i][j];
            if (aux == 0)
                printf("#", aux);
            else
                printf("%d", aux + 1);
        }
        printf("\n");
    }
}