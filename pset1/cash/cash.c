#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float f;
    int c, r; //coins, remainder,

    do
    {
        f = get_float("Change owed: ");
    }
    while (f < 0);

    f = f * 100;
    r = round(f);

    c = r / 25; //Quarters
    r = r % 25;

    c = c + r / 10; //Dimes
    r = r % 10;

    c = c + r / 5; //Nickes
    r = r % 5;

    c = c + r; //Pennies

    printf("%i\n", c);
}