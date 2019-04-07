#include <stdlib.h>
#include <stdio.h>

// prototypes
void selection_sort(int arr[], int len);
void print_array(int arr[], int len);

int main(void)
{
    // initialize unsorted array
    int arr[] = {2, 5, 1, 6, 4, 0, 8, 3, 9, 7};

    // get length of array
    int len = sizeof(arr) / sizeof(int);
    
    // display unsorted array
    printf("unsorted: ");
    print_array(arr, len);

    // selection sort
    selection_sort(arr, len);

    // dislay sorted array
    printf("sorted:   ");
    print_array(arr, len);

    // success
    return 0;
}

void selection_sort(int arr[], int len)
{
   for (int i = 0; i < len - 1; i++)
    {
        int x = arr[i];
        int y = arr[i + 1];
        int k = i + 1;
        
        for (int j = i + 1; j < len; j++)
        {
            if (arr[j] < y)
            {
                y = arr[j];
                k = j;
            }
        }

        if (y < x)
        {
            arr[i] = y;
            arr[k] = x;
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

