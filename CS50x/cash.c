#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    while (true)
    {
        int counter = (0);
        float n = get_float("n: ");
        int cents = round(n * 100);

        printf("Change owed: %.2f \n", n);

        if (cents > 0)
        {
            while (cents >= 25)
            {
                cents = (cents - 25);
                counter += 1;
            }
            while (cents < 25 && cents >= 10)
            {
                cents = (cents - 10);
                counter += 1;
            }
            while (cents < 10 && cents >= 5)
            {
                cents = (cents - 5);
                counter += 1;
            }
            while (cents < 5 && cents >= 1)
            {
                cents = (cents - 1);
                counter += 1;
            }
        }
        if (cents == 0)
        {
            printf("%i", counter);
            printf("\n");
            break;
        }
    }

}
