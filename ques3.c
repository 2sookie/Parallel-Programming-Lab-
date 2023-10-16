#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    int n;
    scanf("%d", &n);

    #pragma omp parallel
    {
        int i;
        #pragma omp schedule(static, 2)
        {
            for(i = 0; i < n; i++)
                printf("\nThread Number - %d Iteration number - %d", omp_get_thread_num(), i);
        }
    }

    return 0;
}