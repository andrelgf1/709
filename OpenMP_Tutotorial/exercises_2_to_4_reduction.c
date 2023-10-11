
#include"omp.h"
#include <stdio.h>
#define NUM_THREADS 3
static long num_steps = 100000;
double step;
int main ()
{
    double  pi=0.0, sum=0.0;
    step = 1.0/(double) num_steps;

    #pragma omp parallel for reduction(+:sum)   
        for (int i=0 ;i<num_steps; i++){
            double x = (i+0.5)*step;
            sum += 4.0/(1.0+x*x);
        }
    
    pi = sum * step;
    printf( "Pi is equal to %f \n", pi);
    
    
   
}