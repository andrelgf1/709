
#include"omp.h"
#include <stdio.h>
#define NUM_THREADS 3
static long num_steps = 100000;
double step;
int main ()
{
    int nthreads; 
    double  pi=0, sum[NUM_THREADS];
    step = 1.0/(double) num_steps;

    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel
    {   
        int id = omp_get_thread_num();
        int nthrds = omp_get_num_threads();
        double x ;
        sum[id] = 0.0;
        if (id == 0) nthreads = nthrds;

        for (int i=id ;i<num_steps; i+=nthrds){
            x = (i+0.5)*step;
            sum[id] += 4.0/(1.0+x*x);
        }
    }
    printf( "Number of threads used %d \n", nthreads);
    for(int i=0; i<nthreads; i++) {
        pi += sum[i] * step;
        printf( "Partial sum[%d] == %f \n", i,sum[i] * step);
    }
    printf( "Pi is equal to %f \n", pi);
    
    
   
}