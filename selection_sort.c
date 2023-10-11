#include <stdio.h>
// 89 45 68 5 90 34 17 25

void selection_sort(int *arr, int length);

int main()
{
    int num;
    printf("Please enter lenght of array: ");
    scanf("%d", &num);
    int data[num];
    printf("Now enter data: ");
    for (int i = 0; i < num; i++)
    {
        scanf("%d", &data[i]);
    }
    printf("Output: ");
    for (int i = 0; i < num; i++)
    {
        printf("%d , ", data[i]);
    }
    selection_sort(data, num);
    printf("Output: ");
    for (int i = 0; i < num; i++)
    {
        printf("%d , ", data[i]);
    }
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