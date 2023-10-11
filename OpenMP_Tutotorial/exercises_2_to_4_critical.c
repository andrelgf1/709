
#include"omp.h"
#include <stdio.h>
#define NUM_THREADS 10
static long num_steps = 100000;
double step;
int main ()
{
    int nthreads; 
    double  pi=0;
    step = 1.0/(double) num_steps;

    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel
    {   
        int id = omp_get_thread_num();
        int nthrds = omp_get_num_threads();
        double x, sum=0.0;
        if (id == 0) nthreads = nthrds;

        for (int i=id ;i<num_steps; i+=nthrds){
            x = (i+0.5)*step;
            sum += 4.0/(1.0+x*x);
        }
        #pragma omp critical
        {
            pi += sum * step;
            printf( "Partial Pi is equal to %f \n", pi);
        }
        printf( "Partial sum[%d] == %f \n", id ,sum * step);
    }
    printf( "Number of threads used %d \n", nthreads);
    printf( "Pi is equal to %f \n", pi);
    
    
   
}