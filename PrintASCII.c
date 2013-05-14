#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Output.h"
#include "rio.h"
#include "pixel.h"

/*
  Protótipos
*/

void outputLine (pixel *linha, int largura);
void outputArray (pixel **array, int altura, int largura, int indice);

/*
  Funções
*/

void outputArray (pixel **array, int altura, int largura, int indice) { /* Imprime a grade */
  int i;
    
  for (i = 0; i < altura; i ++) /* Imprime cada linha, de trás para frente */
    outputLine(array[(i+indice)%altura], largura);
}


void outputLine (pixel *linha, int largura) { /* Imprime a linha */
  int i = 0;
    
  for (i = 0; i < largura; i++){
    printf ("%.3f%c ",velocidade(&linha[i]), tipo(&linha[i]));
  }
  printf("\n");
}
