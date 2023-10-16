#include<stdio.h>
#include<omp.h>
#define NUM_THREADS 8

static long num_steps = 1000000;
double step;

void main()
{
    double x, pi, sum[NUM_THREADS] = {0};
    int i;
    double start_time, end_time;

    //calculate step
    step = 1.0 / (double)num_steps;

    //serial
    start_time = omp_get_wtime();

    for(i = 0; i < num_steps; i++)
    {
        x = ( i + 0.5) * step;
        sum[0] += 4 / (1 + x * x);
    }

    pi = sum[0] / step;
    end_time = omp_get_wtime();
    printf("Serial method : ");
    printf("PI : %f", pi);
    printf("Time taken : %f s", end_time - start_time);


    //parallel 
    start_time = omp_get_wtime();
    int id = 0;

    #pragma omp parallel private(i, x)
    {
        id = omp_get_thread_num();

        for(i = id, sum[id] = 0; i < num_steps; i += NUM_THREADS)
        {
            x = (i + 0.5) * step;
            sum[id] = 4 / (1 + x * x);
        }
    }

    for(i = 1; i < num_steps; i++)
        sum[0] += sum[i];
    pi = sum[0] / step;

    printf("Parallel : ");
    printf("PI : %f", pi);
    printf("Time taken : %f s", end_time - start_time); 


}