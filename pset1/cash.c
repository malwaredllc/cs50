// Solution to PSET1: "Cash"
#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    float dollars = get_float("Change owed: ");
    int cents = round(dollars * 100);
    int coins = 0;
    
    while (cents > 0)
    {
        if (cents >= 25)
        {
            cents -= 25;
            coins += 1;
        }
        else if (cents >= 10)
        {
            cents -= 10;
            coins += 1;
        }
        else if (cents >= 5)
        {
            cents -= 5;
            coins += 1;
        }
        else
        {
            cents -= 1;
            coins += 1;
        }
    }
    
    printf("%i", coins);
}


