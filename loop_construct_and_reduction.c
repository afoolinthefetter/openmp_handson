#include <omp.h>
#include <stdio.h>


int main()
{
    double pi = 0.0, sum = 0.0 ;
    int num_steps = 10000000;
    double step = 1.0 / (double) num_steps;

    double start = omp_get_wtime();
    //omp set schedule(dynamic, 1000)
    #pragma omp parallel
    {   
        double x = 0.0;
        #pragma omp parallel for schedule(static) reduction(+:sum)
        for (int i = 0; i < num_steps; i += 1)
        {
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
        
    }
    pi = step * sum;
    double end = omp_get_wtime();
    printf("Time: %f\n", end - start);
    printf("pi = %f\n", pi);
}