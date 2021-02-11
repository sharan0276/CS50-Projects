#include<stdio.h>

int main(void)
{

    int rows = 0;

    do
    {
        printf("\nEnter the number of rows :\n");
        scanf(" %d", &rows);
    }
    while (rows < 1 || rows > 8);  // to ensure the user enters row value between [1,8]

    for (int i = 1; i <= rows ; i++)
    {

        for (int j = 1; j <= rows - i; j++)
        {

            printf(" ");  //loop to print spaces

        }

        for (int k = 1; k <= i; k++)
        {

            printf("#");  //loop to print #

        }

        printf("\n");

    }


}