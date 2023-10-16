#include <stdio.h>
#include <omp.h>

int main()
{
    int n;
    scanf("%d", &n);

    long long int fib[n];
    fib[0] = 0;
    fib[1] = 1;

    #pragma omp parallel
    {
        int i;

        #pragma omp for schedule(dynamic)
        {
            for(i = 2; i < n; i++)
            {
                fib[i] = fib[i - 1] + fib[i - 2];
                printf("\nThread %d for iteration %d", omp_get_thread_num(), i);
            }
        }
    }

    printf("Fibo series : ");
    for(int i = 0; i < n; i++)
        printf("%d", fib[i]);
}