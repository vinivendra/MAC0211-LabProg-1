#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Output.h"
#include "grade.h"

#define velocidadeDaAgua 10
#define alturaDaGrade 20
#define ProbabilidadeDeObstaculos 0
#define limiteDasMargens 0.3

int main (int argc, char *argv[]) {
    /*
     velocidade do barco
     largura do rio
     #velocidade da água
     #tamanho da grade
     #probabilidade de obstáculos
     limite esquerda
     limite direita
     seed (param ou time)
     fluxo (param)
     
     F desejado, O obtido, Vi
     O = EVi
     Vi = Vi*F/O
     
     ########               ###         #####
     0000000001223545434321000001234321000000
     
    */
    
    int velocidadeDoBarco = 0;
    int larguraDoRio = 0;
    int seed = 0;
    int fluxoDesejado = 0;
    int verbose = 0;
    float **grade;
    
    int i = 0;
    int j = 0;
    
    char *parametro;
    
    for (i = 1; i < argc; i ++) { /* Percorre todos os parâmetros passados */
        parametro = argv[i];
        
        if (parametro[1] == 'b') { /* Atribui o valor do parâmetro à variável adequada */
            velocidadeDoBarco = atoi(&parametro[2]);
        }
        else if (parametro[1] == 'l') {
            larguraDoRio = atoi(&parametro[2]);
        }
        else if (parametro[1] == 's') {
            seed = atoi(&parametro[2]);
        }
        else if (parametro[1] == 'f') {
            fluxoDesejado = atoi(&parametro[2]);
        }
        else if (parametro[1] == 'v') {
            verbose = 1;
        }
    }
    
    if (seed == 0) {
        /* Aleatoriza a seed baseado no time */
        srand(seed);
    }
    
    if (larguraDoRio == 0) {
        printf("Por favor, insira um valor para a largura do rio:\n");
        scanf("%d", &larguraDoRio);
    }
    
    grade = initGrade(alturaDaGrade, larguraDoRio);
    
    criaPrimeiroFrame(grade, alturaDaGrade, larguraDoRio, limiteDasMargens, fluxoDesejado);
    
    outputArray(grade, alturaDaGrade, larguraDoRio);
    
    return 0;
}






