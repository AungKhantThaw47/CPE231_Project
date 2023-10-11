#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 

void merge(int arr[], int left[], int leftSize, int right[], int rightSize)
{
    int i = 0, j = 0, k = 0;
    while (i < leftSize && j < rightSize)
    {
        if (left[i] < right[j])
        {
            arr[k++] = left[i++];
        }
        else
        {
            arr[k++] = right[j++];
        }
    }
    while (i < leftSize)
    {
        arr[k++] = left[i++];
    }
    while (j < rightSize)
    {
        arr[k++] = right[j++];
    }
}

void mergeSort(int arr[], int size)
{
    if (size < 2)
    {
        return;
    }
    int mid = size / 2;
    int left[mid];
    int right[size - mid];
    for (int i = 0; i < mid; i++)
    {
        left[i] = arr[i];
    }
    for (int i = mid; i < size; i++)
    {
        right[i - mid] = arr[i];
    }
    mergeSort(left, mid);
    mergeSort(right, size - mid);
    merge(arr, left, mid, right, size - mid);
}

int main()
{
    int arr[] = {75, 31, 64, 82, 93, 54, 66, 89};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("Before sorting: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    mergeSort(arr, size);
    printf("\nSorted array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}