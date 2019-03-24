#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Prototypes
void run100(void);
void run1000(void);
void run1000000(void);
void bubble_sort(int arr[], int len);

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
    bubble_sort(arr, len);
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
    bubble_sort(arr, len);
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
    bubble_sort(arr, len);
    clock_t end = clock();
    double runtime = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("%i elements\ntime: %f seconds\n\n", len, runtime);
}

void bubble_sort(int arr[], int len)
{

    int sorted = 0;
    while (sorted == 0)
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
