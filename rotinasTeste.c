#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pixel.h"
#include "rio.h"
#include "grade.h"
#include "rotinasTeste.h"

int testaCorrecao(pixel *linha, int fluxoDesejado, int largura){
    /*verifica se para uma dada linha o fluxo obtido eh igual ao fluxo desejado*/
    
    int i;
    float fluxo = 0;
    int fluxoObtido;
    for(i = 0; i < largura; i++)
        fluxo += velocidade( &linha[i] );
    
    fluxoObtido = (int)fluxo;
    
    return fluxoObtido == fluxoDesejado;
}

void calculaVariacoes(pixel **grade, int largura, int altura,
                      float *velMin, float *velMedia, float *velMax,
                      int *margEsqMin, float *margEsqMedia, int* margEsqMax,
                      int *margDirMin, float *margDirMedia, int *margDirMax){
    
    
    int i, j;
    float velAux = 0;
    int margDirAux = 0;
    int margEsqAux = 0;
    
    for(i = 0; i < largura; i++){
        
        margEsqAux = margemEsquerda(grade[i]);
        margDirAux = margemDireita(grade[i], largura);
        
        if (margEsqAux > *margEsqMax) *margEsqMax = margEsqAux;
        if (margEsqAux < *margEsqMin) *margEsqMin = margEsqAux;
        if (margDirAux > *margDirMax) *margDirMax = margDirAux;
        if (margDirAux < *margDirMin) *margDirMin = margDirAux;
        
        *margEsqMedia += 1.0* margEsqAux/altura;
        *margDirMedia += 1.0* margDirAux/altura;
        
        for(j = 0; j < altura; j++){
            
            velAux = velocidade(&grade[i][j]);
            
            if (velAux > *velMax) *velMax = velAux;
            if (velAux < *velMin) *velMin = velAux;
            
            if (tipo(&grade[i][j]) == AGUA)
                *velMedia += velAux/largura*altura;
                
                }
                }
                }
