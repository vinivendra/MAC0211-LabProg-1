#include <stdio.h>
#include <stdlib.h>
#include "rio.h"

/*
 Protótipos
*/

int tamanhoDaPrimeiraMargem(int largura, float limiteDasMargens);
float velocidadeAleatoriaDaAgua (float velocidadeAnterior);
void normaliza(float *linha, int largura, int fluxoDesejado);



void proximaLinha (float *linhaAnterior, float *linha, int largura, float limiteDasMargens, int fluxoDesejado) {
    
    
    
}

int margemEsquerda (float *linha) {
    int n = 0;
    
    while (linha[n] == 0) {
        n++;
    }
    
    return n;
}

void primeiraLinha(float *linha, int largura, float limiteDasMargens, int fluxoDesejado) {
    int tamanhoDaMargemEsquerda = tamanhoDaPrimeiraMargem(largura, limiteDasMargens);
    int tamanhoDaMargemDireita = tamanhoDaPrimeiraMargem(largura, limiteDasMargens);
    
    int i = 0;
    
    for (i = 0; i < tamanhoDaMargemEsquerda; i++) { /* Insere a margem esquerda */
        linha[i] = 0;
    }
    for (i = tamanhoDaMargemEsquerda; i < largura - tamanhoDaMargemDireita; i++) { /* Insere a água */
        linha[i] = velocidadeAleatoriaDaAgua(linha[i-1]);
    }
    for (i = largura - tamanhoDaMargemDireita; i < largura; i++) { /* Insere a margem direita */
        linha[i] = 0;
    }
    
    normaliza(linha, largura, fluxoDesejado); /* Normaliza o fluxo da água */
        
}

int tamanhoDaPrimeiraMargem(int largura, float limiteDasMargens) {
    float limiteAleatorio = limiteDasMargens*rand()/RAND_MAX; /* float entre 0 e o limite das margens */
    int resultado = limiteAleatorio*largura;
    if (resultado == 0) resultado++;
    
    return resultado;
}

float velocidadeAleatoriaDaAgua (float velocidadeAnterior) {
    float i = velocidadeAnterior + 2.0*rand()/RAND_MAX - 1; /* velocidadeAnterior +- 1 */
    if (i <= 0) i++;
    return i;
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