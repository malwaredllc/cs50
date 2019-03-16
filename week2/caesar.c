#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        // Display usage information and exit code 1 for error
        printf("Usage: ./caesar key");
        return 1;
    }
    
    // Declare key as integer and set variables
    int key = atoi(argv[1]);
    int ascii_a = 97;
    int ascii_A = 65;
    int alphabet_length = 26;
    
    // Prompt user for plaintext to encrypt
    string plaintext = get_string("plaintext: ");
    
    printf("ciphertext: ");
    
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isupper(plaintext[i]))
        {
            // Add key to uppercase letters
            printf("%c", ((plaintext[i] - ascii_A + key) % alphabet_length) + ascii_A);
        }
        else if (islower(plaintext[i]))
        {
            // Add key to lowercase letters
            printf("%c", ((plaintext[i] - ascii_a + key) % alphabet_length) + ascii_a);
        }
        else
        {
            // Make no change to other characters
            printf("%c", plaintext[i]);
        }
    }
    
    // Exit code 0 for success
    printf("\n");
    return 0;
}


