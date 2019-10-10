#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n, j;

    do
    {
        n = get_int("Height: ");
    }
    while (n < 0 || n > 23); //grabs an integer between the numbers 0 and 23

    if (n == 0)
    {
        printf("\n"); //Creates a line with no blocks
    }
    else
        for (int i = 1; i <= n; i++)
        {
            printf("%*s", n - i, ""); //Creates the spaces needed for the line
            for (j = 0; j < i; j++)
            {
                printf("#");
            }  //This loop adds in the blocks for the program
            printf("#\n"); // Adds in 1 last block and creates a new line for neatness
        }
}