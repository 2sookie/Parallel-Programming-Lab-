#include <stdio.h>
#include <omp.h>

void merge(int A[], int low, int mid, int high)
{
    int n1 = mid - low + 1, n2 = high - mid;
    int L[n1], R[n2];

    for(int i = 0; i < n1; i++)
        L[i] = A[i];
    for(int j = 0; j < n2; j++)
        R[j] = A[j];

    int i = 0, j = 0, k = low;

    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
        {
            A[k] = L[i];
            i++;
            k++;
        }

        else
        {
            A[k] = R[j];
            j++;
            k++;
        }
    }

    while(i < n1)
    {
        A[k] = L[i];
        i++;
        k++;
    }

    while(j < n2)
    {
        A[k] = R[j];
        j++;
        k++;
    }
}

void merge_seq(int A[], int low, int high)
{
    if(low < high)
    {
        int mid = (low + high)/2;

        merge_seq(A, low, mid);
        merge_seq(A, mid + 1, high);

        merge(A, low, mid, high);
    }
}

void merge_parallel(int A[], int low, int high)
{
    if(low < high)
    {
        int mid = (low + high)/2;

        #pragma omp parallel sections
        {
            #pragma omp section
            merge_parallel(A, low, mid);
            #pragma omp section
            merge_parallel(A, mid + 1, high);
        }

        merge(A, low, mid, high);
    }    
}

int main()
{
    int n;
    scanf("%d", &n);

    int a[n], copy_a[n];
    for(int i = 0; i < n; i++)
    {
        a[i] = rand()%1000;
        copy_a[i] = a[i];
    }

    double start, end;

    printf("Original Array : ");
    for(int i = 0; i < n; i++)
        printf("%d", a[i]);

    //serial
    start = omp_get_wtime();
    merge_seq(a, 0, n - 1);
    end = omp_get_wtime();

    printf("Sorted array : ");
    for(int i = 0; i < n; i++)
        printf("%d", a[i]);
    printf("Time taken : %d", (end - start))

    for(int i = 0; i < n; i++)
        a[i] = copy_a[i];

    //parallel
    start = omp_get_wtime();
    merge_parallel(a, 0, n - 1);
    end = omp_get_wtime();

    printf("Sorted array : ");
    for(int i = 0; i < n; i++)
        printf("%d", a[i]);
    printf("Time taken : %d", (end - start))
}