#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int arr[] = {2, 5, 1, 6, 4, 0, 8, 3, 9, 7};
    int len = sizeof(arr) / sizeof(int);

     // Print arr to stdout
    printf("unsorted: ");
    for (int n = 0; n < len; n++)
    {
        printf("%i ", arr[n]);
    }
    printf("\n");
    
    // Insertion sort
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

    // Display result and exit cleanly
    printf("sorted:   ");
    for (int n = 0; n < len; n++)
    {
        printf("%i ", arr[n]);
    }
    printf("\n");
    return 0;
}


