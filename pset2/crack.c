#include <cs50.h>
#include <crypt.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, string argv[])
{
    string letters = "\0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int letters_count = 53;
    
    if (argc != 2)
    {
        printf("Usage: ./crypt hash\n");
        return 1;
    }

    string hash = argv[1];
    char salt[3];
    memcpy(salt, hash, 2);
    salt[2] = '\0';
    char candidates[6] = "\0\0\0\0\0\0";
   
    for (int fifth = 0; fifth < letters_count; fifth++)
    {
        for (int fourth = 0; fourth < letters_count; fourth++)
        {
            for (int third = 0; third < letters_count; third++)
            {
                for (int second = 0; second < letters_count; second++)
                {
                    for (int first = 1; first < letters_count; first++)
                    {
                        candidates[0] = letters[first];
                        candidates[1] = letters[second];
                        candidates[2] = letters[third];
                        candidates[3] = letters[fourth];
                        candidates[4] = letters[fifth];
                        
                        if (strcmp(crypt(candidates, salt), hash) == 0)
                        {
                            printf("%s\n", candidates);
                            return 0;
                        }
                    }
                }
            }
        }
    }
    
    printf("Password could not be cracked\n");
    return 2;
}


