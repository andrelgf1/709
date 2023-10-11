#include<stdio.h>
#include<math.h>
#include <omp.h>

/* Function for integration */
double f(double x){
//   return x*x*x;
    // return sqrt(x);
    return pow(3.0,x);
}

double simpsons(double f(double x),double a,double b,int n){
  double h,integral,x,sum=0;
  h=fabs(b-a)/n;
  for(int i=1;i<n;i++){
    x=a+i*h;
    if(i%2==0){
      sum=sum+2*f(x);
    }
    else{
      sum=sum+4*f(x);
    }
  }
  integral=(h/3)*(f(a)+f(b)+sum);
  return integral;
}

int main(){
    int n_interval,i;
    double a,b,h,x=0.0,sum=0,integral,integral_new;
    printf("\n***********************************");
    /*Ask the user for necessary input */
    printf("\nEnter the initial limit: ");
    scanf("%lf",&a);
    printf("\nEnter the final limit: ");
    scanf("%lf",&b);
    printf("\nEnter the number of intervals: ");
    scanf("%d",&n_interval);
    printf("\n***********************************");
    integral_new=simpsons(f,a,b,n_interval);

    printf("\nIntegral (series) %f \n", integral_new);


    h=fabs(b-a)/n_interval;
    #pragma omp parallel for  private(x) reduction(+:sum) 
    for(i=1;i<n_interval;i++){
        x=a+i*h;
        if(i%2==0) sum=sum+2*f(x);
        else sum=sum+4*f(x);
        int id = omp_get_thread_num();
        printf("\n thread  %d and x %f \n", i,x);
    }

    integral=(h/3)*(f(a)+f(b)+sum);
    printf("\nIntegral (Parallel) %f \n", integral);
    printf("\n x value %f \n", x);
    printf("--------------- END--------------------");

    return(0);
}