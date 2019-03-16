#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Number: ");
    long n = number;
    int sum = 0;
    bool b;
    while (n > 0)
    {
        int last = n % 10;
        if (b)
        {
            int x2 = last * 2;
            while (x2 > 0)
            {
                int digit = x2 % 10;
                sum += digit;
                x2 /= 10;
            }
            b = false;
        }
        else
        {
            sum += last;
            b = true;
        }
        n /= 10;
    }
    if (sum % 10 == 0)
    {
        if ((number >= 340000000000000 && number < 350000000000000) || (number >= 370000000000000 && number < 380000000000000))
        {
            printf("AMEX\n");
        }
        else if (number >= 5100000000000000 && number < 5600000000000000)
        {
            printf("MASTERCARD\n");
        }
        else if ((number >= 4000000000000 && number < 5000000000000) || (number >= 4000000000000000 && number < 5000000000000000))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}

