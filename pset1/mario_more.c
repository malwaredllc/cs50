// Solution to PSET1: "Mario (more)"
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
        for (int j=height-1; j>i; j--)
        {
            printf(" ");
        }
        
        for (int j=0; j<=i; j++) 
        {
            printf("#");
        }
        
        printf("  ");
        
        for (int j=i; j>=0; j--)
        {
            printf("#");
        }
        
        printf("\n");
    }
}


