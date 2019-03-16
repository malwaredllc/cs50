#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int arr[] = {2, 5, 1, 6, 4, 8, 3};
    int len = sizeof(arr) / sizeof(int);
    int sorted = 0;

    // Bubble sort
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

    // Display result and exit cleanly
    for (int i = 0; i < len; i++)
    {
        printf("%i ", arr[i]);
    }
    printf("\n");
    return 0;
}
