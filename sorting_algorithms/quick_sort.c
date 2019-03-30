#include <stdio.h>
#include <stdlib.h>

// prototypes
void swap(int* a, int* b);
int partition(int arr[], int start, int end);
void quick_sort(int arr[], int start, int end);

int main(void)
{
    // initialize unsorted array
    int arr[] = {4, 7, 2, 1, 9, 6, 0, 8, 5, 3};

    // get length of array
    int len = sizeof(arr) / sizeof(int);

    // print unsorted array to stdout
    printf("Unsorted: ");
    for (int i = 0; i < len; i++)
    {
        printf("%i ", arr[i]);
    }
    printf("\n");

    // sort array using quick sort
    quick_sort(arr, 0, len - 1);

    // print sorted array to stdout
    printf("Sorted:   ");
    for (int i = 0; i < len; i++)
    {
        printf("%i ", arr[i]);
    }
    printf("\n");

    // success
    return 0;
}

void quick_sort(int arr[], int start, int end)
{
    if (start < end)
    {
        // select right-most element in array as pivot value
        int pivot = arr[end];

        // partition the array
        int index = partition(arr, start, end);

        // quick sort elements to the left of pivot
        quick_sort(arr, start, index - 1);
        quick_sort(arr, index + 1, end);
    }
}

int partition(int arr[], int start, int end)
{
    // select right-most element in array as pivot value
    int pivot = arr[end];
    int index = start;

    // iterate through subarray
    for (int i = start; i < end; i++)
    {
        // if element at index i is less than or equal to the pivot then swap them in place
        if (arr[i] <= pivot)
        {
            swap(&arr[i], &arr[index]);
            index++;
        }
    }

    // swap index with pivot
    swap(&arr[index], &arr[end]);

    // return index of pivot
    return index;
}

void swap(int* a, int* b)
{
    // use temporary variable to swap 2 elements in array
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
