#include<stdio.h>
#include<math.h>
#include <omp.h>
#include <stdlib.h>
/* Function for integration */
double f(double x){
  return x*x*x;
    // return sqrt(x);
    // return pow(3.0,x);
}


double simpson13(double *f,double a,double b, double h, int n){
  printf( "\n***Simpson 1/3 Calculation\n");
  double  sum =0.0;
  #pragma omp parallel for reduction(+:sum) 
  for(int i=1;i<n;i++){
      double x=a+i*h;
      if(i%2==0) sum=sum+2*f[i];
      else sum=sum+4*f[i];
      int id = omp_get_thread_num();
      printf("Thread  %d ----- i %d and x %f \n", id,i,x);
  }
  printf("Number of interval 1/3 : %d \n" ,n);
  printf ("From X   %f to %f\n", a,a+n*h);
  double result = (h/3)*(f[0]+f[n]+sum);
  printf("Result 1/3 : %f \n " ,result);
  return result ;
}

double simpson38(double *f,double a,double b, double h, int n){
  printf("\n***Simpson 3/8 Calculation\n");
  printf("Number of interval 3/8 : %d \n" ,3);
  printf ("From X %f to %f\n", b-3*h,b);
  double result = 3*h/8 *( f[n] + 3*f[n-1] + 3*f[n-2] + f[n-3] );
  printf("Result 3/8 : %f \n" ,result);
  return result ;
}

double trap(double a,double b, double h){
  return h * (f(a) + f(b)) / 2;
}
int main(){
    int n_interval;
    double a,b,h,sum=0.0,integral,integral_new;
    printf("\n***********************************");
    /*Ask the user for necessary input */
    printf("\nEnter the initial limit: ");
    scanf("%lf",&a);
    printf("\nEnter the final limit: ");
    scanf("%lf",&b);
    printf("\nEnter the number of intervals: ");
    scanf("%d",&n_interval);
    printf("\n***********************************");
 

    h=fabs(b-a)/n_interval ;
    double *F ;
    int size = (n_interval+1);
    F=(double*)malloc( size* sizeof(double));


    for (int i=0; i<size ; i++) F[i] = f(a+i*h);
    // for (int i=0; i<size ; i++) printf("Element %f: %f\n", a+i*h, F[i]);

    printf("\nh is : %f \n", h);
    if(n_interval <=1) integral = trap(a,b,h);
    else if (n_interval%2 == 0) integral = simpson13(F,a,b,h,n_interval);
    else {
      integral = simpson38(F,a,b,h,n_interval);
      integral+= simpson13(F,a,b,h,n_interval-3);
    }

    printf("\n\n***Integral (Parallel) %f \n", integral);
    printf("--------------- END--------------------\n");

    free(F);
    return(0);
}