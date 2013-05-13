#include <stdio.h>
#include <stdlib.h>

#define TERRA -1

void primeiraLinha(float *linha, int largura, float limiteDasMargens, int fluxoDesejado);
void proximaLinha (float *linhaAnterior, float *linha, int largura, float limiteDasMargens, int fluxoDesejado, int distanciaEntreIlhas, float probIlha);
