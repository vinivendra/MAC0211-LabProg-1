#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Output.h"


void outputArray (float **array, int altura, int largura, int indice) {
    int i = indice;
    int j = 0;
    
    for (i = altura - 1; i >= 0; i --) {
        for (j = 0; j < largura; j++) {
	  float aaux =  array[(i+indice)%altura][j];
	  /*if (aux == 0)
                printf("#");
		else*/
	      printf("%f ", array[(indice+i)%altura][j]);
        }
        printf("\n");
    }
}
