#include<stdio.h>
#include<string.h>
#include<math.h>
#include<cs50.h>
#include<ctype.h>

float round_num(float num)                  // round a number to nearest whole number
{
    float round_off = (int)(num * 100 + 0.5); //Considering only positive values

    return (round_off / 100);
}

int main(void)
{
    string text = get_string("Text:");

    int temp, letters = 0, words = 1, sentences = 0;

    float L, S, grade;



    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }

        else if (isspace(text[i]) && ((isalpha(text[i + 1])) || (text[i + 1] == '"'))) //certaain cases such as .... "are .......
        {
            words++;
        }

        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }

    }

    L = (float)(letters * 100.0) / words ;
    S = (float)(sentences * 100.0) / words ;



    grade = 0.0588 * L - 0.296 * S - 15.8;    //Coleman-Liau formula

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }

    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %.0f\n", round_num(grade));
    }


}