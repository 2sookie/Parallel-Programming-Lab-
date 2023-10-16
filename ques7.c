#include <stdio.h>
#include <omp.h>

int main()
{
    int n;
    int sum = 0;
    double start, end; 

    scanf("%d", &n);

    start = omp_get_wtime();
    #pragma omp parallel for
    for(int i = 1; i <= n; i++)
    {
        #pragma omp critical
        sum += i;
    }

    end = omp_get_wtime();
    printf("Sum : %d", sum);
}