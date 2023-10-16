#include <stdio.h>
#include <omp.h>

int main()
{
    int n;
    double start, end;
    scanf("%d", &n);

    int a[n], b[n], res[n];
    for(int i = 0; i < n; i++)
    {
        a[i] = rand()%1000;
        b[i] = rand()&1000;
    }

    printf("Vector A");
    for(int i = 0; i < n; i++)
        printf("%d", a[i]);
    
    printf("Vector B");
    for(int i = 0; i < n; i++)
        printf("%d", b[i]);

    start = omp_get_wtime();

    #pragma omp parallel for
    for(int i = 0; i < n ; i++)
        res[i] = a[i] + b[i];

    end = omp_get_wtime();
    printf("Resultant vector : ");
    for(int i = 0; i < n; i++)
        printf("%d", res[i]);

    printf("Time taken : %d s", end - start);
}