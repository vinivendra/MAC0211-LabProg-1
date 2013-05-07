#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Output.h"


void outputArray (float **array, int altura, int largura) {
    int i = 0;
    int j = 0;
    
    for (i = 0; i < altura; i ++) {
        for (j = 0; j < largura; j++) {
            int bla = array[i][j];
            printf("%d", bla);
        }
        printf("\n");
    }
}