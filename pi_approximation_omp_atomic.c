#include <omp.h>
#include <stdio.h>

static long num_steps = 100000;
double step;
#define NUM_THREADS 1000

int main()
{
    int number_of_threads;
    double pi = 0.0;
    step = 1.0 / (double) num_steps;
    double sum[NUM_THREADS];
    omp_set_num_threads(NUM_THREADS);

    double start = omp_get_wtime();
    #pragma omp parallel
    {   
        int id, nthrds;
        double x;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        sum[id]=0.0;
        //if the actual number of recieved threads is different from the number of threads you have asked for
        //the head thread will change the number of threads we have obtained
        if (id == 0)
        {
            number_of_threads = nthrds;
        }
        for (int i = id; i < num_steps; i += nthrds)
        {
            x = (i + 0.5) * step;
            sum[id] += 4.0 / (1.0 + x * x);
        }
        #pragma omp atomic
        {
            pi += sum[id] * step;
        }
    }
    double end = omp_get_wtime();
    printf("Time: %f\n", end - start);
    printf("pi = %f\n", pi);
}