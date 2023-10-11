#include <omp.h>
#include <stdio.h>
static long num_steps = 100000;
double step;

void main (){
    int i; double x =3.3, pi, sum = 0.0;
    step = 1.0/(double) num_steps;
    #pragma omp parallel for  reduction(+:sum)
    for (i=0;i< num_steps; i++){
        x = (i+0.5)*step;
        sum = sum + 4.0/(1.0+x*x);
        printf( " temp X is equal to %f \n", x);
    }
    pi = step * sum;
    printf( "Pi is equal to %f \n", pi);
    printf( "X is equal to %f \n", x);
}