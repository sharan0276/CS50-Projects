#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

int main(int argc, string argv[])
{

    if (argc != 2)    // if key  doesntv match standard
    {
        printf("Usage: ./caesar key\n");
        return (1);
    }


    int cipher = atoi(argv[1]);   // to convert string to integer

    int num = (int) argv[1];

    for (int j = 0; j < strlen(argv[1]); j++)
    {
        if (isdigit(argv[1][j]) == false)
        {
            printf("Usage: ./caesar key\n");
            return (1);
        }
    }

    string plain_text;

    plain_text = get_string("Plain text: ");

    for (int i = 0; i < strlen(plain_text); i++)
    {
        if (islower(plain_text[i]))                   // 96 is the base for lower case characters
        {
            plain_text[i] = (char)(((plain_text[i] - 96) + cipher) % 26) + 96;
        }

        else if (isupper(plain_text[i]))              // 65 is the base for upper case characters
        {
            plain_text[i] = (char)(((plain_text[i] - 65) + cipher) % 26) + 65;
        }
    }

    printf("ciphertext: %s\n", plain_text);
    return (0);

}