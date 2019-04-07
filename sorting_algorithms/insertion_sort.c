#include <stdlib.h>
#include <stdio.h>

// prototypes
void insertion_sort(int arr[], int len);
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
    
    // insertion sort
    insertion_sort(arr, len);

    // display sorted array
    printf("sorted:   ");
    print_array(arr, len);

    // success
    return 0;
}

void insertion_sort(int arr[], int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        int ii = i + 1;
        int x  = arr[i];
        int y  = arr[ii];

        // Iterate over arr to find next lowest value
        for (int j = i; j < len; j++)
        {
            if (arr[j] < y)
            {
                y = arr[j];
                ii = j;
            }
        }
        
        int tmplen = ii - i;
        if (tmplen > 0)
        {
            // Copy values from arr between indexes i and ii to tmp
            int tmp[tmplen];
            for (int k = i, j = 0; k < ii && j < tmplen; k++, j++)
            {
                tmp[j] = arr[k];
            }

            // Copy next lowest value to index i
            arr[i] = y;

            // Copy values from tmp into arr with indexes offset +1
            for (int l = i, m = 0; l < ii && m < tmplen ; l++, m++)
            {
                arr[l + 1] = tmp[m];
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

