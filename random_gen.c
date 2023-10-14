#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle(int *array, int n) {
    if (n > 1) {
        int i;
        for (i = 0; i < n - 1; i++) {
            int j = i + rand() / (RAND_MAX / (n - i) + 1);
            swap(&array[i], &array[j]);
        }
    }
}

int main() {
    int n = 100000;
    int *numbers = (int *)malloc(n * sizeof(int));
    if (numbers == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        numbers[i] = i + 1;
    }

    // Seed the random number generator with the current time
    srand(time(NULL));

    shuffle(numbers, n);

    // Create and open the file for writing
    FILE *file = fopen("100000.txt", "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        free(numbers);
        return 1;
    }

    // Write the unique random numbers to the file
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", numbers[i]);
    }

    // Close the file
    fclose(file);

    free(numbers);

    return 0;
}