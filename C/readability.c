#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    int cont = 0, cont2 = 1, cont3 = 0;
    string txt = get_string("Text: ");
    for (int i = 0, n = strlen(txt); i < n; i++)
    {
        if ((txt[i] >= 'a' && txt[i] <= 'z') || (txt [i] >= 'A' && txt[i] <= 'Z'))
        {
            cont++;
        }
        if (txt [i] == ' ')
        {
            cont2++;
        }
        if ((txt [i] == '.' || txt[i] == '!' || txt[i] == '?') && (txt [i + 1] == ' ' || txt [i + 1] == txt[n]))
        {
            cont3++;
        }
    }

    float l = (cont * 100 / (float) cont2);
    float s = (cont3 * 100 / (float) cont2);
    float index = 0.0588 * l - 0.296 * s - 15.8;

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    if (index <= 1)
    {
        printf("Before Grade 1\n");
    }
    if (index > 1 && index < 16)
    {
        printf("Grade %.0f\n", round(index));
    }
}
