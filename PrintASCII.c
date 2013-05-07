#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Output.h"


void outputArray (char *array, int n) {
    int i = 0;
    
    for (i = 0; i < n; i ++) {
        printf("%c", array[i]);
    }
    printf("\n");
}