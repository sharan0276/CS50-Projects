#include<stdio.h>
#include<cs50.h>
#include<string.h>

int checksum(string buffer, int start)       //luhn algo
{
    int sum = 0;
    for (int i = start ; i < strlen(buffer); i += 2)
    {
        int digit = buffer[i] - 48;

        if (digit * 2 > 9)
        {
            int temp = digit * 2;     //if digit has a tens place
            while (temp > 0)
            {
                sum += temp % 10;
                temp /= 10;
            }
        }

        else
        {
            sum += digit * 2;
        }

        sum +=  buffer[(i + 1)] - 48;
    }

    if (start == 1)
    {
        sum += buffer[0] - 48;
    }

    return (sum % 10) ;
}


void checkcomp(long credit)
{
    char buffer[16];
    sprintf(buffer, "%lu", credit);      //convert to string for extracting the first two digits
    int digit1 = buffer[0] - 48;
    int digit2 = buffer[1] - 48;
    if (digit1 == 4)
    {
        printf("VISA\n");
    }
    else
    {
        if (digit1 == 3 && (digit2 == 4 || digit2 == 7))
        {
            printf("AMEX\n");
        }

        else if (digit1 == 5 && (digit2 == 1 || digit2 == 2 || digit2 == 3 || digit2 == 4 || digit2 == 5))
        {
            printf("MASTERCARD\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }


}


int main(void)
{
    int sum;

    long credit = get_long("Enter the credit card number :\n");   // long input

    char buffer[16];

    sprintf(buffer, "%lu", credit);

    if (strlen(buffer) < 13)
    {
        printf("INVALID\n");
    }

    else
    {
        if (strlen(buffer) % 2 == 0)
        {
            sum = checksum(buffer, 0);
        }

        else
        {
            sum = checksum(buffer, 1);
        }

        if (sum != 0)
        {
            printf("INVALID\n");
        }

        else
        {
            checkcomp(credit);    //function call
        }

    }


}






