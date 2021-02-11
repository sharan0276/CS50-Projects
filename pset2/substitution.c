#include<stdio.h>
#include<math.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>


int main(int argc, string argv[])
{

    if (argc != 2)      //inputs should be file call and string
    {
        printf("Usage: ./substitution key\n");
        return (1);
    }

    if (strlen(argv[1]) != 26)           // if key isnt of desired length (26)
    {
        printf("Key must contain 26 characters\n");
        return (1);
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isalpha(argv[1][i]) == false)   // if invalid characters / non alphabetic characters in key
        {
            printf("Key contains a non alphabetic character ");
            return (1);
        }

        for (int k = 0; k < i ; k++)        //To check for duplicate enteries in key
        {
            if (argv[1][i] == argv[1][k])
            {
                printf("Key contains duplicate characters");
                return (1);
            }
        }
    }



    string plain_text;

    plain_text = get_string("plaintext: ");

    for (int j = 0; j < strlen(plain_text); j++)
    {
        if (islower(plain_text[j]))
        {
            plain_text[j] = tolower(argv[1][((plain_text[j] - 97) % 26)]);      // the start ASCII value for a is 97
        }

        else if (isupper(plain_text[j]))
        {
            plain_text[j] = toupper(argv[1][((plain_text[j] - 65) % 26)]);       // the start ASCII value for A is 65
        }
    }

    printf("ciphertext: %s\n", plain_text);

}