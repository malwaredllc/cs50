#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Prototypes
void run100(void);
void run1000(void);
void run1000000(void);
void print_array(int arr[], int len);
void merge(int arr[], int l, int m, int r);
void merge_sort(int arr[], int l, int r);

// Main
int main(void)
{

    run100();
    run1000();
    run1000000();
    return 0;
}

// Functions
void run100(void)
{
    FILE *fp;
    fp = fopen("numbers100.txt","r");
    int arr[100];
    int len = sizeof(arr) / sizeof(arr[0]);
    
    for (int i = 0; i < len; i++)
    {
        fscanf(fp, "%d,", &arr[i]);
    }

    clock_t begin = clock();
    merge_sort(arr, 0, len - 1);
    clock_t end = clock();
    double runtime = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("%i elements\ntime: %f seconds\n\n", len, runtime);
}

void run1000(void)
{
    FILE *fp;
    fp = fopen("numbers1000.txt","r");
    int arr[1000];
    int len = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < len; i++)
    {
        fscanf(fp, "%d,", &arr[i]);
    }

    clock_t begin = clock();
    merge_sort(arr, 0, len - 1);
    clock_t end = clock();
    double runtime = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("%i elements\ntime: %f seconds\n\n", len, runtime);
}

void run1000000(void)
{
    FILE *fp;
    fp = fopen("numbers1000000.txt","r");
    int arr[1000000];
    int len = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < len; i++)
    {
        fscanf(fp, "%d,", &arr[i]);
    }
    clock_t begin = clock();
    merge_sort(arr, 0, len - 1);
    clock_t end = clock();
    double runtime = (double)(end - begin) / CLOCKS_PER_SEC;
    
    printf("%i elements\ntime: %f seconds\n\n", len, runtime);
}

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


