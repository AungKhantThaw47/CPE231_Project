#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int n = 1000;
    int* array = (int*)malloc(n * sizeof(int));

    // Initialize the array with some values
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 1000;
    }

    int max_val = -1;
    int max_idx = -1;

    #pragma acc parallel loop reduction(max:max_val) 
    for (int i = 0; i < n; i++) {
        if (array[i] > max_val) {
            max_val = array[i];
            max_idx = i;
        }
    }

    printf("Maximum value: %d\n", max_val);
    printf("Index of maximum value: %d\n", max_idx);

    free(array);
    return 0;
}
