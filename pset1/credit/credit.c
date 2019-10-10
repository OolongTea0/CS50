#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int i = 0, x, sum = 0; //i is digits, x is random variable, sum is the total sum of alg
    long long num = get_long_long("Number: "), n = num;

    while (n) //Starting algorithm
    {
        x = n % 10;
        if (i % 2 == 0) //steps for every i+2n digits
        {
            sum = sum + x;
        }
        else //steps for every 2n digits
        {
            x = x * 2;
            if (x >= 10)
            {
                sum = sum + 1 + x % 10;
            }
            else
            sum = sum + x;
        }

        n /= 10, i++;
    }

    if (sum % 10 == 0)
    {
        printf("%i\n", i);
        switch(i) {
            case 13 : //VISA check
                n = num / 1000000000000;
                if (n == 4)
                    printf("VISA\n");
                else
                    printf("INVALID\n");
                break ;

            case 15 : //AMEX check
                n = num/10000000000000;
                if (n == 34 || n == 37)
                    printf("AMEX\n");
                else
                    printf("INVALID\n");
                break;

            case 16 : //Checks for VISA first then MASTERCARD
                n = num/100000000000000;
                if (n/10 == 4)
                    printf("VISA\n");
                else if (n >= 51 && n <= 55)
                    printf("MASTERCARD\n");
                else
                    printf("INVALID\n");
                break;
            default :
                printf("INVALID\n");
        }
    }
    else
        printf("INVALID\n");
}