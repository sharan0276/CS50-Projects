#include<stdio.h>
#include<math.h>
#include<cs50.h>
#include<ctype.h>

int main(void)
{
    int rem, coins, temp ;
    float change ;

    do
    {
        change = get_float("Enter the Change :");
    }
    while (change < 0);

    rem = round(change * 100);

    //printf(" %d", rem);

    coins = round(rem / 25);
    rem -= coins * 25;

    while (rem > 0)
    {
        if (rem >= 10)
        {
            temp = round(rem / 10);
            rem -= (temp * 10);
        }

        else if (rem >= 5 && rem < 10)
        {
            temp = round(rem / 5);
            rem -= (temp * 5);
        }

        else
        {
            temp = rem / 1;
            rem -= (temp * 1);
        }

        coins += temp;
    }

    printf(" %i\n", coins) ;
}