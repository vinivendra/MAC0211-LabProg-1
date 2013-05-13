#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rio.h"
#include "pixel.h"

pixel **initGrade(int altura, int largura);
void criaPrimeiroFrame(pixel **grade, int altura, int largura, float limiteDasMargens, int fluxoDesejado, int distanciaEntreIlhas, float probIlha);
void criaProximoFrame (pixel **grade, int altura, int largura, float limiteDasMargens, int fluxoDesejado, int indice, int distanciaEntreIlhas, float probIlha);
void freeGrade(pixel**, int, int);
