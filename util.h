#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getArgs(int argc,char *argv[],int *, int *, int *, int *, int *, int *, float *);

struct timespec{
  long int tv_sec;
  long int tv_nsec;
};
