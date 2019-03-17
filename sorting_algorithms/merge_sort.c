#include <stdlib.h>
#include <stdio.h>

// Prototypes
void print_array(int arr[], int len);
void merge(int arr[], int l, int m, int r);
void merge_sort(int arr[], int l, int r);

// Main
int main(void)
{
    int arr[] = {2, 5, 1, 6, 4, 8, 3, 9, 7};
    int len = sizeof(arr) / sizeof(arr[0]);

    // Print unsorted array to stdout
    printf("unsorted: ");
    print_array(arr, len);

    // Merge sorting algorithm
    merge_sort(arr, 0, len - 1);
    
    // Display result and exit cleanly
    printf("sorted:   ");
    print_array(arr, len);

    return 0;
}

// Functions
void print_array(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%i ", arr[i]);
    }
    printf("\n");
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    // Copy elements from arr into temporary arrays L and R
    for (i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
    }

    for (j = 0; j < n2; j++)
    {
        R[j] = arr[m + 1 + j];
    }
    
    i = 0; // Initial index of first sub-array
    j = 0; // Initial index of second sub-array
    k = l; // Initial index of merged sub-array
    
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements from L, if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copy remaining elements from R, if there are any
    while (j < n2) 
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Calculate midpoint of array
        int m = (l + r) / 2;
        
        // Sort left half of array
        merge_sort(arr, l, m);
        
        // Sort right half of array
        merge_sort(arr, m + 1, r);
        
        // Merge sorted sub-arrays
        merge(arr, l, m, r);
    }
}


