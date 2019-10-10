#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n, j;

    do
    {
        n = get_int("Height: ");
    }
    while (n < 0 || n > 23);

    if (n == 0)
    {
        printf("\n");
    }
    else
        for (int i = 1; i <= n; i++)
        {
            printf("%*s", n - i, ""); //creates first set of spaces

            for (j = 0; j < i; j++)
            {
                printf("#"); //creates first pyramid
            }

            printf(" ");

            for (j = 0; j < i; j++)
            {
                printf("#");    //creates second pyramid
            }
            printf("\n"); //makes new line
        }
}