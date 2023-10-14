#include <stdio.h>
#include <stdlib.h>

int main()
{
    int size = 5;
    int *arr;
    arr = (int *)malloc(size * sizeof(int));
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = (rand() % 2000) + 1;
        printf("%d ", arr[i]);
    }
    printf("\n");
    int max_data;
    int pos = -10;

    // #pragma acc parallel loop reduction(max:max_data)
    // for (int i = 0; i < size; i++)
    // {
    //     max_data = arr[i];
    //     // pos = i;
    // }

    // #pragma acc parallel loop reduction(max:max_data) present(arr)
    // for (int i = 0; i < size; i++) {
    //     if (arr[i] > max_data) {
    //         max_data = arr[i];
    //     }
    // }

    // #pragma acc parallel loop present(arr)
    // for (int i = 0; i < size; i++) {
    //     // Find the maximum value
    //     #pragma acc atomic
    //     if (arr[i] > max_data) {
    //         max_data = arr[i];
    //     }
    // }

#pragma acc parallel loop
    for (int i = 0; i < size; i++)
    {
        if (arr[i] > max_data)
        {
            max_data = arr[i];
        }
    }
#pragma acc data create(pos)
#pragma acc parallel loop
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == max_data)
        {
#pragma acc atomic write
            {
                printf("%d\n", i);
                pos = i;
#pragma acc update self(pos)
            }
        }
    }

    printf("max: %d\n", max_data);
    printf("max: %d\npos: %d\n", max_data, pos);
    return 0;
}