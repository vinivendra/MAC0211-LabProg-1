#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grade.h"

int **initGrade(int altura, int largura) {
    int i = 0;
    int **grade;
    
    grade = malloc(altura*sizeof(int *));
    
    for (i = 0; i < altura; i++) {
        grade[i] = malloc(largura*sizeof(int));
    }
    
    return grade;
}
