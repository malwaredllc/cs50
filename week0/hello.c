// Solution to PSET0: "Hello"
#include <cs50.h>
#include <stdio.h>

int main(int c, string argv[])
{
    string name = "world";

    if (c > 1)
    {
        name = argv[1];
    }

    printf("hello, %s!\n", name);

}
