#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 Interface para colocar na tela o que o programa quiser. Escrita de forma genérica,
 para que possa ser usada com implementações de qualquer tipo (seja em ASCII na saída
 padrão, seja numa janela separada em cores.
*/

void outputArray (float **array, int altura, int largura);
void clearScreen();