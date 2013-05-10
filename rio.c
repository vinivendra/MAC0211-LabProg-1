#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rio.h"
#include "Output.h"

/*
  Variavel gloabal
 */

int  distanciaAtualEntreIlhas = 0;

/*
 Protótipos
 */

int tamanhoDaPrimeiraMargem(int largura, float limiteDasMargens);
float velocidadeAleatoriaDaAgua(int, int, int, int, float);
void normaliza(float *linha, int largura, int fluxoDesejado);
int margemEsquerda (float *linha);
int margemDireita (float *linha, int largura);
int insereIlha(float *linha, int distanciaMinimaEntreIlhas, float probIlha, int margemEsquerda, int margemDireita, int largura);

/*
 Implementações
 */

void proximaLinha (float *linhaAnterior, float *linha, int largura, float limiteDasMargens, int fluxoDesejado, int distanciaEntreIlhas, float probIlha) { /* Calcula como deve ser a nova
																			     linha do frame */
    int tamanhoDaMargemEsquerda;
    int tamanhoDaMargemDireita;
    int i = 0;
    
    aleatorizaMargem(linhaAnterior, linha, limiteDasMargens, largura); /* Insere as novas margens aleatorizadas */
    
    tamanhoDaMargemEsquerda = margemEsquerda(linha);
    tamanhoDaMargemDireita = margemDireita(linha, largura);
    
    for (i = tamanhoDaMargemEsquerda; i < largura - tamanhoDaMargemDireita; i++) { /* Insere a água */
        linha[i] = velocidadeAleatoriaDaAgua(i, tamanhoDaMargemDireita, tamanhoDaMargemEsquerda, largura, limiteDasMargens);
    }
    
    normaliza(linha, largura, fluxoDesejado);
    insereIlha(linha, distanciaEntreIlhas, probIlha, tamanhoDaMargemEsquerda, tamanhoDaMargemDireita, largura);
    
}

int margemEsquerda (float *linha) { /* Retorna o tamanho da margem esquerda da linha */
    int n = 0;
    
    while (linha[n] == 0) {
        n++;
    }
    
    return n;
}

int margemDireita (float *linha, int largura) { /* Retorna o tamanho da margem direita da linha de tamanho 'largura' */
    int n = largura-1;
    
    while (linha[n] == 0) {
        n--;
    }
    
    n++;
    
    return largura-n;
}

void primeiraLinha(float *linha, int largura, float limiteDasMargens, int fluxoDesejado) { /* Insere os valores da primeira linha do programa */
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

int tamanhoDaPrimeiraMargem(int largura, float limiteDasMargens) { /* Calcula um valor aleatório para o tamanho das margens da primeira linha */
    int resultado = (limiteDasMargens*largura - 1)*rand()/RAND_MAX + 1; /* Valor entre 1 e o limite das margens */
    
    return resultado;
}


float velocidadeAleatoriaDaAgua (int posicaoNaLinha, int margemDireita, int margemEsquerda, int largura, float limiteDasMargens) {
    /* Calcula um valor aleatório para ser a velocidade da água */
    
    float velocidadeNova = 1;
    
    if(abs(largura - posicaoNaLinha - margemDireita) <= 2 || abs(posicaoNaLinha - margemEsquerda) < 2) /* Se está perto de alguma margem */
        velocidadeNova = 1.0*rand()/RAND_MAX;
    
    else velocidadeNova = 1.0*rand()/RAND_MAX + 1;
    
    return velocidadeNova;
}

void normaliza(float *linha, int largura, int fluxoDesejado) { /* Normaliza a linha para ter o fluxo desejado */
    int i = 0;
    float fluxoObtido = 0;
    
    for (i = 0; i < largura; i++) { /* O fluxo obtido é a soma de todas as velocidades */
        fluxoObtido += linha[i];
    }
    for (i = 0; i < largura; i++) { /* Transforma a linha numa que tenha o fluxo desejado */
        linha[i] = 1.0*linha[i]*fluxoDesejado/fluxoObtido;
    }
}

void aleatorizaMargem(float *linhaAnterior, float *linha, float limiteDasMargens, int largura){ /* Calcula o novo tamanho das margens, baseado
                                                                                                 na linha anterior */
    int tamanhoDaMargemEsquerda = margemEsquerda(linhaAnterior);
    int tamanhoDaMargemDireita = margemDireita(linhaAnterior, largura);
    int variacaoEsquerda = (rand()%3) - 1; /* O tamanho da margem nova vai variar da antiga de -1, 0 ou 1 */
    int variacaoDireita = (rand()%3) - 1;
    int i;
    
    tamanhoDaMargemEsquerda = tamanhoDaMargemEsquerda + variacaoEsquerda;
    tamanhoDaMargemDireita = tamanhoDaMargemDireita + variacaoDireita;
    
    if (tamanhoDaMargemEsquerda <= 0) tamanhoDaMargemEsquerda = 1; /* Evita que as novas margens sejam 0 ou passem do limite */
    else if (tamanhoDaMargemEsquerda > limiteDasMargens * largura) tamanhoDaMargemEsquerda = limiteDasMargens * largura;
    if (tamanhoDaMargemDireita <= 0) tamanhoDaMargemDireita = 1;
    else if (tamanhoDaMargemDireita > limiteDasMargens * largura) tamanhoDaMargemDireita = limiteDasMargens * largura;
    
    for (i = 0; i < tamanhoDaMargemEsquerda; i++) /* Insere nova margem esquerda */
        linha[i] = 0;
    for (i = tamanhoDaMargemEsquerda; i < largura - tamanhoDaMargemDireita; i++) { /* Insere água no meio, para evitar erros */
        linha[i] = 1;
    }
    for (i = largura - tamanhoDaMargemDireita; i < largura; i++) { /* Insere nova margem direita */
        linha[i] = 0;
    }
}

int insereIlha(float *linha, int distanciaMinimaEntreIlhas, float probIlha, int tmargemEsquerda, int tmargemDireita, int largura){
  int q, i;
  int sorteio;
  int comecoIlha, finalIlha;
  int aux, aux2;
  if( distanciaAtualEntreIlhas < distanciaMinimaEntreIlhas ){
    distanciaAtualEntreIlhas++;
    return 0;
  }

  q = (int) ( probIlha*1000000 - 1 );
  sorteio = rand()%1000000;
  
  if(sorteio > q){
    /*com probabilidade 1-p, sorteio sera maior que q*/
    distanciaAtualEntreIlhas++;
    return 0;
  }

  if(sorteio <= q){
    /*sorteio sera menor ou igual a  q com probabilidade probIlha*/
    distanciaAtualEntreIlhas = 0;
    aux = rand()%largura;
    aux2 = rand()%largura;

    comecoIlha = aux < aux2 ? aux : aux2;
    finalIlha = aux < aux2 ? aux2 : aux;

    if(comecoIlha <= tmargemEsquerda || comecoIlha <= tmargemEsquerda + 1) comecoIlha = tmargemEsquerda + 3;
    if(finalIlha >= largura - tmargemDireita || finalIlha >= largura - tmargemDireita - 2) finalIlha = largura - tmargemDireita - 3;

    if(comecoIlha > finalIlha){
      aux = comecoIlha;
      comecoIlha = finalIlha;
      finalIlha = aux;
    }

    for(i = comecoIlha; i <= finalIlha; i++){
      linha[i] = 0;
    }
  }
    return 1;
}
    
  

  
    
