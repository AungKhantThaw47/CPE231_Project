#include <openacc.h>

int main()
{
    int array[10];
    int max_value = -10;
    // Initialize the array
    for (int i = 0; i < 10; i++)
    {
        array[i] = i;
    }

#pragma acc parallel loop
    for (int i = 0; i < 10; i++)
    {
#pragma acc atomic
        array[i] += 1; // Atomic increment of array element
        if (array[i] > max_value)
        {
            max_value = array[i];
        }
    }
    printf("max: %d\n",max_value);
    // Print the updated array
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", array[i]);
    }

    return 0;
}
