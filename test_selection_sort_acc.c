#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

void selectionSort(int *arr, int n)
{
#pragma acc enter data copyin(arr[0 : n])
    {
        for (int i = 0; i < n - 1; i++)
        {
            int min_index = i;

#pragma acc parallel loop
            for (int j = i + 1; j < n; j++)
            {
                if (arr[j] < arr[min_index])
                {
                    min_index = j;
                }
            }

            if (min_index != i)
            {
                int temp = arr[i];
                arr[i] = arr[min_index];
                arr[min_index] = temp;
            }
        }
    }
#pragma acc exit data copyout(arr[0 : n])
}

int main()
{
    int n = 10;
    int *array = (int *)malloc(n * sizeof(int));

    // Initialize the array with random values
    for (int i = 0; i < n; i++)
    {
        array[i] = rand() % 100;
    }

    printf("Unsorted Array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    selectionSort(array, n);

    printf("Sorted Array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);

    return 0;
}