#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <openacc.h>

void selection_sort(int *arr, int length);
void selection_sort_acc(int *arr, int length);

int main()
{
    int size = 5;
    int *arr;
    int *arr1;
    arr = (int *)malloc(size * sizeof(int));
    arr1 = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        arr[i] = (rand() % 100) + 1;
        arr1[i] = arr[i];
        printf("%d ", arr[i]);
    }
    printf("\n");
    clock_t start_time = clock();

    // #pragma acc data copyinout(arr[0 : size])
    // {
    selection_sort_acc(arr, size);
// }
// #pragma acc update host(arr[0:size])
#pragma acc wait
    clock_t end_time = clock();
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("GPU Execution Time: %f seconds\n", execution_time);
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    start_time = clock();
    selection_sort(arr1, size);
    end_time = clock();
    execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("CPU Execution Time: %f seconds\n", execution_time);
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr1[i]);
    }
    printf("\n");
    return 0;
}

void selection_sort(int *arr, int length)
{
    int k, pos, temp, smallest;
    for (k = 0; k < length; k++)
    {
        smallest = arr[k];
        for (int i = k; i < length; i++)
        {
            if (arr[i] < smallest)
            {
                smallest = arr[i];
                pos = i;
            }
        }
        temp = arr[k];
        arr[k] = arr[pos];
        arr[pos] = temp;
    }
}

#pragma acc routine
void smallest_compute(int *data_cell, int *smallest, int *pos, int *data_index)
{
    if (*data_cell <= *smallest)
    {
        *smallest = *data_cell;
        *pos = *data_index;
    }
}

void selection_sort_acc(int *arr, int length)
{
#pragma acc data create(arr[0 : length])

    // #pragma acc enter data copyin(arr[0 : length])
    int k, pos, temp, smallest;
#pragma acc data create(pos, smallest, temp)
// #pragma acc loop seq
// clock_t start_time = clock();
#pragma acc loop seq
    for (k = 0; k < length; k++)
    {
        smallest = arr[k];
#pragma acc kernels
        for (int i = k; i < length; i++)
        {
            smallest_compute(&arr[i], &smallest, &pos, &i);
#pragma acc update self(smallest)
#pragma acc update self(pos)
        }

        // #pragma acc parallel loop
        //         for (int i = k; i < length; i++)
        //         {
        //             if (arr[i] < smallest)
        //             {
        //                 smallest = arr[i];
        // #pragma acc update self(smallest)
        //                 pos = i;
        // #pragma acc update self(pos)
        //             }
        //         }

        // printf("work\n");
        // #pragma acc parallel loop reduction(min : smallest)
        //         for (int i = k; i < length; i++)
        //         {
        //             smallest = arr[i];
        //         }
        //         // printf("work\n");
        // #pragma acc parallel loop
        //         for (int i = k; i < length; i++)
        //         {
        //             if (smallest == arr[i])
        //             {
        //                 pos = i;
        // #pragma acc update self(pos)
        //             }
        //         }
        // printf("work\n");
        temp = arr[k];
        printf("work : k: %d , smallest: %d , pos :%d\n", k, smallest, pos);
        arr[k] = arr[pos];
        // printf("work\n");
        arr[pos] = temp;
        // printf("work\n");
        for (int i = 0; i < length; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
        // printf("work\n");
    }
    // #pragma acc exit data copyout(arr[0:length])
    // clock_t end_time = clock();
    // double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    // printf("Execution Time: %f seconds\n", execution_time);

#pragma acc data copyout(arr[0 : length])
}