#include <stdio.h>
#include <cs50.h>

int main(void)
{
    while (true)
    {
        int height = get_int("n: ");
        if (height <= 8 & height >= 1)
        {
            for (int i = 0; i < height; i++)
            {
                //se o for estiver na mesma linha ele printa junto
                for (int k = (height - 1); k > i ; k--)
                {
                    printf(" ");
                }
                for (int j = 0; j <= i; j++)
                {
                    printf("#");
                }
                printf("\n");
            }
            break;
        }
    }
}
