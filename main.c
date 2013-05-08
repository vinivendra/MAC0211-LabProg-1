#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Output.h"
#include "grade.h"

#define velocidadeDaAgua 10
#define alturaDaGrade 20
#define ProbabilidadeDeObstaculos 0
#define limiteDasMargens 0.4

int main (int argc, char *argv[]) {
    
    /*
     Declaração de variáveis
    */
    
    int velocidadeDoBarco = 0;
    int larguraDoRio = 0;
    int seed = 0;
    int fluxoDesejado = 0;
    int verbose = 0;
    float **grade;
    int *indice = malloc(sizeof(int));
    
    int i = 0;
    
    char *parametro;
    
    
    /*
     Inicialização
     */
    
    *indice = 0;
    
    /*
     Leitura de parametros
     */
    
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
    
    /*
     Seed
     */
    
    if (seed == 0) {
        /* Aleatoriza a seed baseado no time */
    }
    srand(seed);
    
    /*
     Leitura dos parametros que faltarem
     */
    
    if (larguraDoRio == 0) {
        printf("Por favor, insira um valor para a largura do rio:\n");
        scanf("%d", &larguraDoRio);
    }
    
    /*
     Primeiro frame
     */
    
    grade = initGrade(alturaDaGrade, larguraDoRio);
    
    criaPrimeiroFrame(grade, alturaDaGrade, larguraDoRio, limiteDasMargens, fluxoDesejado);
    
    outputArray(grade, alturaDaGrade, larguraDoRio, *indice);
    
    printf("\n");
    
    /*
     Frames subsequentes
     */
    
    for(;;){
        *indice = (*indice - 1+alturaDaGrade) % alturaDaGrade;
        
        criaProximoFrame(grade, alturaDaGrade, larguraDoRio, limiteDasMargens, fluxoDesejado, indice);
        
        outputArray(grade, alturaDaGrade, larguraDoRio, *indice);
        printf("\n");
        
        sleep(1);
    }
    
    return 0;
}







