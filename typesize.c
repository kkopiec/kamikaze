#include <stdio.h>
#include <stdlib.h>

int main(){

  int f = sizeof(float);
  int d = sizeof(double);

  printf ("Float: %d, Double: %d\n",f,d);

  float fv = 0.05f;
  double dv = (double) fv;

  printf("F value: %f, D value: %f\n", fv, dv);
  return 0;  
}
