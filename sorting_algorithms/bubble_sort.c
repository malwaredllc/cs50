#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Prototypes
void bubble_sort(int arr[], int len);
void print_array(int arr[], int len);

int main(void)
{
    // initialize unsorted array
    int arr[] = {4, 7, 2, 1, 9, 6, 0, 8, 5, 3};

    // get length of array
    int len = sizeof(arr) / sizeof(int);

    // display unsorted array
    printf("unsorted: ");
    print_array(arr, len);

    // bubble sort
    bubble_sort(arr, len);

    // display sorted array
    printf("sorted:   ");
    print_array(arr, len);

    // success
    return 0;
}

void bubble_sort(int arr[], int len)
{
    int sorted = 0;
    while (!sorted)
    {
        sorted = 1;
        for (int i = 0; i < len - 1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                int x = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = x;
                sorted = 0;
            }
        }
    }
}

void print_array(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%i ", arr[i]);
    }
    printf("\n");
}