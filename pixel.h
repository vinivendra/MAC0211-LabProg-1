#ifndef H_PIXEL_DEFINE
#define H_PIXEL_DEFINE

#include <stdlib.h>
#include <stdio.h>

typedef struct pixel{
  float velocidade;
  char tipo;
}pixel;

float velocidade(pixel*);
char tipo(pixel*);
void setaVelocidade(pixel*, float);
void setaTipo(pixel*, char);

#endif
