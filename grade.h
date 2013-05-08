#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rio.h"

float **initGrade(int altura, int largura);
void criaPrimeiroFrame(float **grade, int altura, int largura, float limiteDasMargens, int fluxoDesejado);
void criaProximoFrame (float **grade, int altura, int largura, float limiteDasMargens, int fluxoDesejado);