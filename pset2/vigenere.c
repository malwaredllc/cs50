// Solution to PSET2: "Vigenere Cipher"
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int shift(char c);

int main(int argc, string argv[])
{
    // Display usage information if incorrect number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    
    // Set variables
    int ascii_A = 67;
    int ascii_a = 95;
    int alphabet_length = 26;
    string keyword = argv[1];
    string plaintext = get_string("plaintext: ");
    
    printf("ciphertext: ");
    
    // Loop through characters in the plaintext and the keyword
    for (int i = 0, j = 0, n = strlen(plaintext), l = strlen(keyword); i < n; i++)
    {
        // Calculate shift value for the next character in the keyword and print it to stdout
        int s = shift(keyword[j % l]);
        if (isupper(plaintext[i]))
        {
            printf("%c", ((plaintext[i] + s - ascii_A) % alphabet_length) + ascii_A);
            j++;
        }
        else if (islower(plaintext[i]))
        {
            printf("%c", ((plaintext[i] + s - ascii_a) % alphabet_length) + ascii_a);
            j++;
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }   
    // Exit cleanly
    printf("\n");
    return 0;
}

int shift(char c)
{
    int ascii_a = 97;
    return tolower(c) - ascii_a;
}


