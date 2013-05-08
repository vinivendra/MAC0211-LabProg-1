#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rio.h"
#include "Output.h"

/*
 Protótipos
 */

int tamanhoDaPrimeiraMargem(int largura, float limiteDasMargens);
float velocidadeAleatoriaDaAgua(int, int, int, int, float);
void normaliza(float *linha, int largura, int fluxoDesejado);
int margemEsquerda (float *linha);
int margemDireita (float *linha, int largura);

void proximaLinha (float *linhaAnterior, float *linha, int largura, float limiteDasMargens, int fluxoDesejado) {
    int tamanhoDaMargemEsquerda;
    int tamanhoDaMargemDireita;
    int i = 0;
        
    aleatorizaMargem(linhaAnterior, linha, limiteDasMargens, largura);
    
    tamanhoDaMargemEsquerda = margemEsquerda(linha);
    tamanhoDaMargemDireita = margemDireita(linha, largura);
    
    for (i = 0; i < tamanhoDaMargemEsquerda; i++) { /* Insere a margem esquerda */
        linha[i] = 0;
    }
    for (i = tamanhoDaMargemEsquerda; i < largura - tamanhoDaMargemDireita; i++) { /* Insere a água */
        linha[i] = velocidadeAleatoriaDaAgua(i, tamanhoDaMargemDireita, tamanhoDaMargemEsquerda, largura, limiteDasMargens);
    }
    for (i = largura - tamanhoDaMargemDireita; i < largura; i++) { /* Insere a margem direita */
        linha[i] = 0;
    }
    normaliza(linha, largura, fluxoDesejado);
    
}

int margemEsquerda (float *linha) {
    int n = 0;
    
    while (linha[n] == 0) {
        n++;
    }
        
    return n;
}

int margemDireita (float *linha, int largura) {
    int n = largura-1;
        
    while (linha[n] == 0) {
        n--;
    }
    
    n++;
        
    return largura-n;
}

void primeiraLinha(float *linha, int largura, float limiteDasMargens, int fluxoDesejado) {
    int tamanhoDaMargemEsquerda = tamanhoDaPrimeiraMargem(largura, limiteDasMargens);
    int tamanhoDaMargemDireita = tamanhoDaPrimeiraMargem(largura, limiteDasMargens);
    
    int i = 0;
    
    for (i = 0; i < tamanhoDaMargemEsquerda; i++) { /* Insere a margem esquerda */
        linha[i] = 0;
    }
    for (i = tamanhoDaMargemEsquerda; i < largura - tamanhoDaMargemDireita; i++) { /* Insere a água */
        linha[i] = velocidadeAleatoriaDaAgua(i, tamanhoDaMargemDireita, tamanhoDaMargemEsquerda, largura, limiteDasMargens);
    }
    for (i = largura - tamanhoDaMargemDireita; i < largura; i++) { /* Insere a margem direita */
        linha[i] = 0;
    }
    normaliza(linha, largura, fluxoDesejado);
}

int tamanhoDaPrimeiraMargem(int largura, float limiteDasMargens) {
    float limiteAleatorio = limiteDasMargens*rand()/RAND_MAX; /* float entre 0 e o limite das margens */
    int resultado = limiteAleatorio*largura;
    if (resultado == 0) resultado++;
    
    return resultado;
}


float velocidadeAleatoriaDaAgua (int posicaoNaLinha, int margemDireita, int margemEsquerda, int largura, float limiteDasMargens) {
    float velocidadeNova = 1;
    
    if(abs(largura - posicaoNaLinha - margemDireita) <= 2 || abs(posicaoNaLinha - margemEsquerda) < /*largura*limiteDasMargens*/2 )
        velocidadeNova = 1.0*rand()/RAND_MAX;
    
    else velocidadeNova = 1.0*rand()/RAND_MAX + 1;
    
    return velocidadeNova;
}

void normaliza(float *linha, int largura, int fluxoDesejado) {
    int i = 0;
    float fluxoObtido = 0;
    
    for (i = 0; i < largura; i++) { /* O fluxo obtido é a soma de todas as velocidades */
        fluxoObtido += linha[i];
    }
    for (i = 0; i < largura; i++) { /* Transforma a linha numa que tenha o fluxo desejado */
        linha[i] = 1.0*linha[i]*fluxoDesejado/fluxoObtido;
    }
}

void aleatorizaMargem(float *linhaAnterior, float *linha, float limiteDasMargens, int largura){
    
    int tamanhoDaMargemEsquerda = margemEsquerda(linhaAnterior);
    int tamanhoDaMargemDireita = margemDireita(linhaAnterior, largura);
    int resultado1 = (rand()%3) - 1;
    int resultado2 = (rand()%3) - 1;
    int i;
        
    tamanhoDaMargemEsquerda = tamanhoDaMargemEsquerda + resultado1;
    tamanhoDaMargemDireita = tamanhoDaMargemDireita + resultado2;
    
    if (tamanhoDaMargemEsquerda <= 0) tamanhoDaMargemEsquerda = 1;
    else if (tamanhoDaMargemEsquerda > limiteDasMargens * largura) tamanhoDaMargemEsquerda = limiteDasMargens * largura;
    if (tamanhoDaMargemDireita <= 0) tamanhoDaMargemDireita = 1;
    else if (tamanhoDaMargemDireita > limiteDasMargens * largura) tamanhoDaMargemDireita = limiteDasMargens * largura;
        
    for (i = 0; i < tamanhoDaMargemEsquerda; i++) /* Insere nova margem esquerda */
        linha[i] = 0;
    for (i = tamanhoDaMargemEsquerda; i < largura - tamanhoDaMargemDireita; i++) { /* Insere nova margem direita */
        linha[i] = 1;
    }
    for (i = largura - tamanhoDaMargemDireita; i < largura; i++) { /* Insere nova margem direita */
        linha[i] = 0;
    }
    
}