#ifndef H_RIO_DEFINE
#define H_RIO_DEFINE

#include <stdio.h>
#include <stdlib.h>
#include "pixel.h"

#define TERRA '#'
#define AGUA '.'

void primeiraLinha(pixel** linha, int largura, float limiteDasMargens, int fluxoDesejado);
void aleatorizaMargem(pixel** linhaAnterior, pixel **linha, float limiteDasMargens, int largura);
void proximaLinha (pixel** linhaAnterior, pixel **linha, int largura, float limiteDasMargens, int fluxoDesejado, int distanciaEntreIlhas, float probIlha);

#endif
