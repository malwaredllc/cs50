#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int arr[] = {2, 5, 1, 6, 4, 8, 3, 7};
    int len = sizeof(arr) / sizeof(int);
    
    // Print arr to stdout
    printf("unsorted: ");
    for (int n = 0; n < len; n++)
    {
        printf("%i ", arr[n]);
    }
    printf("\n");

    // Selection sort
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

    // Dislay result and exit cleanly
    printf("sorted:   ");
    for (int n = 0; n < len; n++)
    {
        printf("%i ", arr[n]);
    }
    printf("\n");
    return 0;
}


