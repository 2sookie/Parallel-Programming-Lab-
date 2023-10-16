#include<stdio.h>
#include<omp.h>

bool isPrime(int n)
{
    if(n <= 1)
        return false;
    
    else if(n <= 3)
        return true;

    if(num % 2 == 0 || num % 3 == 0)
        return false;

    for(int i = 5; i * i <= n; i += 6)
    {
        if(n % i == 0 || num % (i + 2) == 0)
            return false;
    }

    return true;
}

int main()
{
    int n;
    double start_time, end_time;
    scanf("%d", &n);

    //serial
    start_time = omp_get_wtime();
    for(int i = 1; i <= n; i++)
    {
        if(isPrime(i))
            printf("%d ", i);
        printf("\n");
    }
    end_time = omp_get_wtime();

    printf("Total time taken : %f s", end_time - start_time);

    //parallel
    start_time = omp_get_wtime();

    #pragma omp parallel
    {
        for(int i = 1; i <= n; i++)
        {
            if(isPrime(i))
                printf("%d", i);
        }
    }

    end_time = omp_get_wtime();
    printf("Total time taken : %f s", end_time - start_time);
}