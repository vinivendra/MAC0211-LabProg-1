#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "Output.h"
#include "grade.h"
#include "util.h"
#include "pixel.h"
#include "rotinasTeste.h"

int main(int argc, char* argv[]){

  pixel **grade;
  float velMin = 100000000, velMedia = 0, velMax = 0, margDirMedia = 0, margEsqMedia = 0;
  int margEsqMin = 10000000, margEsqMax = 0;
  int margDirMin = 10000000, margDirMax = 0;
  int indice = 0;
  int i, j;

  float velocidadeDoBarco = 1;
  int larguraDoRio = 16;
  int fluxoDesejado = 1;
  int dIlha = 15;
  float pIlha = 0.1;
  float limiteMargens = 0.2;
  int alturaDaGrade = 30;

  srand(time(NULL));

  for(i = 0; i < 10; i++){

    grade = initGrade(alturaDaGrade, larguraDoRio);

    criaPrimeiroFrame(grade, alturaDaGrade, larguraDoRio, limiteMargens, fluxoDesejado, dIlha, pIlha);

    calculaVariacoes(grade, larguraDoRio, alturaDaGrade,
		     &velMin, &velMedia,&velMax,
		     &margEsqMin,&margEsqMedia,&margEsqMax,
		     &margDirMin,&margDirMedia,&margDirMax);

    for(j = 0; j < 49; j++){
      indice = (indice - 1+alturaDaGrade) % alturaDaGrade;
      
      criaProximoFrame(grade, alturaDaGrade, larguraDoRio, limiteMargens, fluxoDesejado, indice, dIlha, pIlha);

      calculaVariacoes(grade, larguraDoRio, alturaDaGrade,
		     &velMin, &velMedia,&velMax,
		     &margEsqMin,&margEsqMedia,&margEsqMax,
		     &margDirMin,&margDirMedia,&margDirMax);
    
    }

    margDirMedia /= 50;
    margEsqMedia /= 50;
    velMedia /= 50;

    printf("Para uma largura de %d ,com fluxo Desejado %d, probabilidade de ilha %f e uma distancia minima entre "
	   " ilhas de %d, em um grid de altura %d, com cada margem ocupando no maximo %f de tal grid temos:\n"
	   "Velocidade Maxima = %f\nVelocidade Minima = %f\nVelocidade Media = %f\n"
	   "Comprimento maximo da margem direita = %d\nComprimento minimo da margem direita = %d\nComprimento medio da margem direita = %f\n"
	   "Comprimento maximo da margem esquerda = %d\nComprimento minimo da margem esquerda = %d\nComprimento medio da margem esquerda = %f\n\n",
	   larguraDoRio, fluxoDesejado, pIlha, dIlha, alturaDaGrade, limiteMargens, velMax, velMin, velMedia, margDirMax, margDirMin, margDirMedia,
	   margEsqMax, margEsqMin, margEsqMedia);

    velMin = 100000000; velMedia = 0; velMax = 0;
    margEsqMin = 10000000; margEsqMedia = 0; margEsqMax = 0;
    margDirMin = 10000000; margDirMedia = 0; margDirMax = 0;
    
    freeGrade(grade, alturaDaGrade, larguraDoRio);

    larguraDoRio += 10;
    fluxoDesejado *= 2;
    dIlha--;
    pIlha += 0.05;
    
  }
  
  return 0;
}
