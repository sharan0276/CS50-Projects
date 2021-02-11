#include<stdio.h>

int main(void)
{

    char answer[100];     //string rep

    printf("What is your name?\n");
    scanf("%[^\n]", answer);  // scan all values until a new line character

    printf("hello, %s\n", answer);

}