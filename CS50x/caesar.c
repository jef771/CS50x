#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
    if (argc == 2)
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (!isdigit(argv[1][i]))
            {
                printf("./caesar key\n");
                return 1;
            }
        }
    }
    else
    {
        printf("./caesar key\n");
        return 1;
    }
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if ((plaintext[i] >= 'a' && plaintext[i] <= 'z'))
        {
            int c = (plaintext[i] - 97 + atoi(argv[1])) % 26 + 97;
            printf("%c", c);
        }
        if ((plaintext[i] >= 'A' && plaintext[i] <= 'Z'))
        {
            int c = (plaintext[i] - 65 + atoi(argv[1])) % 26 + 65;
            printf("%c", c);
        }
        if (!(isalpha(plaintext[i])))
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}
