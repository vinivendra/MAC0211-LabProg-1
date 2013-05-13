#include <stdio.h>
#include <stdlib.h>

#define TERRA -1

void primeiraLinha(float *linha, int largura, float limiteDasMargens, int fluxoDesejado);
void aleatorizaMargem(float *linhaAnterior, float *linha, float limiteDasMargens, int largura);
void proximaLinha (float *linhaAnterior, float *linha, int largura, float limiteDasMargens, int fluxoDesejado, int distanciaEntreIlhas, float probIlha);
