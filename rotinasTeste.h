#ifndef H_ROTINAS_DEFINE
#define H_ROTINAS_DEFINE

#include <stdio.h>
#include <stdlib.h>
#include "rio.h"
#include "grade.h"
#include "pixel.h"

int testaCorrecao(pixel*, int, int);
void calculaVariacoes(pixel **grade, int largura, int altura, float *velMin, float *velMedia, float *velMax, int *margEsqMin, float *margEsqMedia, int* margEsqMax, int *margDirMin, float *margDirMedia, int *margDirMax);

#endif
