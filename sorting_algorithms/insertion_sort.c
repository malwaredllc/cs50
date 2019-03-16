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

    // Insertion sort
    for (int i = 0; i < len - 1; i ++)
    {
        int x = arr[i];
        int y = arr[i + 1];
        int ii = i + 1;
 
        // Iterate over arr to find next lowest value
        for (int j = i; j < len; j++)
        {
            if (arr[j] < y)
            {
                y = arr[j];
                ii = j;
            }
        }
        
        // Copy values from arr between indexes i and ii to temporary array
        int tmplen = ii - i;
        if (tmplen > 0)
        {
            int tmp[tmplen];
            for (int k = 0; k < ii; k++)
            {
                tmp[k] = arr[k];
            }

            // Copy next lowest value to index i
            arr[i] = y;

            for (int l = i; l < ii; l ++)
            {
                arr[l + 1] = tmp[l];
            }
        }
    }

    // Display result and exit cleanly
    printf("sorted:   ");
    for (int n = 0; n < len; n++)
    {
        printf("%i ", arr[n]);
    }
    printf("\n");
    return 0;
}


