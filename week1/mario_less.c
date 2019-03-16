#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 0;
    while (height < 1 || height > 8) 
    {
        height = get_int("Height: ");
    }
    for (int i=0; i<height; i++) 
    {
        for (int k=height-1; k>i; k--)
        {
            printf(" ");
        }
        for (int j=0; j<=i; j++) 
        {
            printf("#");
        }
        printf("\n");
    }
}


