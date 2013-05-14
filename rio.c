#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rio.h"
#include "Output.h"
#include "pixel.h"

#define limiteDasIlhas 0.8

/*
 Variável gloabal
 */

static int  distanciaAtualEntreIlhas = 0;

/*
 Protótipos
 */

float velocidadeDaAguaPrimeiraLinha (float velocidadePontoAnterior);
int tamanhoDaPrimeiraMargem(int largura, float limiteDasMargens);
void normaliza(pixel *linha, int largura, int fluxoDesejado);
int margemEsquerda (pixel *linha);
int margemDireita (pixel *linha, int largura);
void aleatorizaMargem(pixel *linhaAnterior, pixel *linha, float limiteDasMargens, int largura);
int insereIlha(pixel *linha, int distanciaMinimaEntreIlhas, float probIlha, int margemEsquerda, int margemDireita, int largura);
void velocidadeProximaLinha (pixel *linha, pixel *linhaAnterior, int fluxoDesejado, int largura);

/*
 Implementações
 */

void proximaLinha (pixel *linhaAnterior, pixel *linha, int largura, float limiteDasMargens, int fluxoDesejado, int distanciaEntreIlhas, float probIlha) {
    /* Calcula como deve ser a nova linha do frame */
    
    int tamanhoDaMargemEsquerda;
    int tamanhoDaMargemDireita;
    
    aleatorizaMargem(linhaAnterior, linha, limiteDasMargens, largura);  /* Insere as novas margens aleatorizadas */
    
    tamanhoDaMargemEsquerda = margemEsquerda(linha);
    tamanhoDaMargemDireita = margemDireita(linha, largura);
    
    insereIlha(linha, distanciaEntreIlhas, probIlha, tamanhoDaMargemEsquerda, tamanhoDaMargemDireita, largura);
    
    velocidadeProximaLinha(linha, linhaAnterior, fluxoDesejado, largura);
    
    normaliza(linha, largura, fluxoDesejado);
    
    
}

int margemEsquerda (pixel *linha) {     /* Retorna o tamanho da margem esquerda da linha */
    int n = 0;
    
    while ( tipo(&linha[n]) == TERRA)
        n++;
    
    return n;
}

int margemDireita (pixel *linha, int largura) {     /* Retorna o tamanho da margem direita da linha de tamanho 'largura' */
    int n = largura-1;
    
    while ( tipo(&linha[n]) == TERRA)
        n--;
    
    n++;
    
    return largura-n;
}

void primeiraLinha(pixel *linha, int largura, float limiteDasMargens, int fluxoDesejado, int distanciaEntreIlhas, float probIlha) {
    /* Insere os valores da primeira linha do programa */
    
    int tamanhoDaMargemEsquerda = tamanhoDaPrimeiraMargem(largura, limiteDasMargens);
    int tamanhoDaMargemDireita = tamanhoDaPrimeiraMargem(largura, limiteDasMargens);
    
    int i = 0;
    float v;
    
    for (i = 0; i < tamanhoDaMargemEsquerda; i++) {     /* Insere a margem esquerda */
        setaTipo(&linha[i],  TERRA);
        setaVelocidade(&linha[i], 0);
    }
    for (i = tamanhoDaMargemEsquerda; i < largura - tamanhoDaMargemDireita; i++)    /* Insere a água */
        setaTipo(&linha[i], AGUA);
    
    for (i = largura - tamanhoDaMargemDireita; i < largura; i++) {  /* Insere a margem direita */
        setaTipo(&linha[i], TERRA);
        setaVelocidade(&linha[i], 0);
    }
    
    for (i = tamanhoDaMargemEsquerda; i < largura - tamanhoDaMargemDireita; i++) {  /* Insere a velocidade água */
        if (linha[i-1].tipo == TERRA || linha[i+1].tipo == TERRA)
            setaVelocidade(&linha[i],0);
        else{
            v = velocidadeDaAguaPrimeiraLinha (linha[i-1].velocidade);
            setaVelocidade(&linha[i], v);
        }
    }
    
    /* Consideramos a probabilidade de a primeira linha ter ilhas */
    insereIlha(linha, distanciaEntreIlhas, probIlha, tamanhoDaMargemEsquerda, tamanhoDaMargemDireita, largura);
    normaliza(linha, largura, fluxoDesejado);
}

int tamanhoDaPrimeiraMargem(int largura, float limiteDasMargens) {  /* Calcula um valor aleatório para o tamanho das margens da primeira linha */
    int resultado = (limiteDasMargens*largura - 1)*rand()/RAND_MAX + 1;     /* Valor entre 1 e o limite das margens */
    
    return resultado;
}




void velocidadeProximaLinha (pixel *linha, pixel *linhaAnterior, int fluxoDesejado, int largura) {
    
    int i = 0;
    
    int tamanhoDaMargemEsquerda = margemEsquerda(linha);
    int tamanhoDaMargemDireita = margemDireita(linha, largura);
    
    setaVelocidade(&linha[tamanhoDaMargemEsquerda], 0);
    setaVelocidade(&linha[largura-tamanhoDaMargemDireita-1], 0);
    
    for (i = tamanhoDaMargemEsquerda + 1; i < largura-tamanhoDaMargemDireita - 1; i++) {
        if (tipo(&linha[i]) == AGUA) {
            float velocidadeNova = (velocidade(&linha[i-1])+velocidade(&linhaAnterior[i]))/2;
            float aleatorio = 0.2*rand()/RAND_MAX + 1;
            velocidadeNova *= aleatorio;
            if (velocidadeNova == 0) {
                velocidadeNova = aleatorio*fluxoDesejado/(largura*8);
            }
            setaVelocidade(&linha[i], velocidadeNova);
        }
    }
    
}

float velocidadeDaAguaPrimeiraLinha (float velocidadePontoAnterior) {
    /*Adotamos que apenas nas margens do rio e das ilhas a velocidade admite ser zero*/
    /* Calcula um valor aleatório para ser a velocidade da água */
    
    float aleatorio = 1.0*rand()/RAND_MAX - 0.5;    /*Gera um número aleatório entre [-0.5,0.5]*/
    float v;
    
    if (velocidadePontoAnterior == 0)
        return 1.0*rand()/RAND_MAX;
    
    v = aleatorio + velocidadePontoAnterior;
    if( v < 0 ) v = -v;
    if(v == 0) v = 1.0*rand()/RAND_MAX;
    
    return v;
}

void normaliza(pixel *linha, int largura, int fluxoDesejado) {  /* Normaliza a linha para ter o fluxo desejado */
    int i = 0;
    float fluxoObtido = 0;
    float novaVel, vel;
    
    for (i = 0; i < largura; i++)       /* O fluxo obtido é a soma de todas as velocidades */
        if ( tipo(& linha[i] ) != TERRA  )
            fluxoObtido += velocidade(&linha[i]);
    
    for (i = 0; i < largura; i++) {     /* Transforma a linha numa que tenha o fluxo desejado */
        if ( tipo(&linha[i]) != TERRA){
            vel = velocidade(&linha[i]);
            novaVel = 1.0*vel*fluxoDesejado/fluxoObtido;
            setaVelocidade(&linha[i], novaVel);
        }
    }
}

void aleatorizaMargem(pixel *linhaAnterior, pixel *linha, float limiteDasMargens, int largura){
    /* Calcula o novo tamanho das margens, baseado na linha anterior */
    
    int tamanhoDaMargemEsquerda = margemEsquerda(linhaAnterior);
    int tamanhoDaMargemDireita = margemDireita(linhaAnterior, largura);
    int variacaoEsquerda = (rand()%3) - 1;  /* O tamanho da margem nova vai variar da antiga de -1, 0 ou 1 */
    int variacaoDireita = (rand()%3) - 1;
    int i;
    
    tamanhoDaMargemEsquerda = tamanhoDaMargemEsquerda + variacaoEsquerda;
    tamanhoDaMargemDireita = tamanhoDaMargemDireita + variacaoDireita;
    
    if (tamanhoDaMargemEsquerda <= 0) tamanhoDaMargemEsquerda = 1;  /* Evita que as novas margens sejam 0 ou passem do limite */
    else if (tamanhoDaMargemEsquerda > limiteDasMargens * largura) tamanhoDaMargemEsquerda = limiteDasMargens * largura;
    if (tamanhoDaMargemDireita <= 0) tamanhoDaMargemDireita = 1;
    else if (tamanhoDaMargemDireita > limiteDasMargens * largura) tamanhoDaMargemDireita = limiteDasMargens * largura;
    
    for (i = 0; i < tamanhoDaMargemEsquerda; i++){  /* Insere nova margem esquerda */
        setaTipo(&linha[i], TERRA);
        setaVelocidade(&linha[i], 0);
    }
    for (i = tamanhoDaMargemEsquerda; i < largura - tamanhoDaMargemDireita; i++) {  /* Insere água no meio, para evitar erros. VAI DAR PAU */
        setaVelocidade(&linha[i], 1);
        setaTipo(&linha[i], AGUA);
    }
    for (i = largura - tamanhoDaMargemDireita; i < largura; i++) {  /* Insere nova margem direita */
        setaTipo(&linha[i], TERRA);
        setaVelocidade(&linha[i], 0);
    }
}

int insereIlha(pixel *linha, int distanciaMinimaEntreIlhas, float probIlha, int tmargemEsquerda, int tmargemDireita, int largura){
    int q, i;
    int sorteio;
    int comecoIlha, finalIlha;
    int aux, aux2;
    
    if( distanciaAtualEntreIlhas < distanciaMinimaEntreIlhas - 1){
        distanciaAtualEntreIlhas++;
        return 0;
    }
    
    q = (int) ( probIlha*1000000 - 1 );
    sorteio = rand()%1000000;
    
    if(sorteio > q){    /*Com probabilidade 1-p, sorteio sera maior que q*/
        distanciaAtualEntreIlhas++;
        return 0;
    }
    
    if(sorteio <= q){   /*Sorteio sera menor ou igual a  q com probabilidade probIlha*/
        int tamanhoMaximoDaIlha = (largura - tmargemEsquerda - tmargemDireita) * limiteDasIlhas;
        int comecoMaximoDaIlha = tmargemEsquerda + (((1-limiteDasIlhas)/2)*(largura - tmargemEsquerda - tmargemDireita));
        
        distanciaAtualEntreIlhas = 0;
        
        aux = rand()%tamanhoMaximoDaIlha;
        aux = comecoMaximoDaIlha + aux;
        aux2 = rand()%tamanhoMaximoDaIlha;
        aux2 = comecoMaximoDaIlha + aux2;
        
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
            setaTipo(&linha[i], TERRA);
            setaVelocidade(&linha[i], 0);
        }
    }
    return 1;
}





