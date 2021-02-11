#include<stdio.h>
#include<stdlib.h>
#include<cs50.h>
#include<string.h>

#define MAX 9

typedef struct
{
    char name[100];
    int votes;
} Candidate;

Candidate candidates[MAX];
int size;

bool vote(char name[100])
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }

    return false;
}


int max()
{
    int high_vote = 0;

    for (int i = 0; i < size; i++)
    {
        if (high_vote < candidates[i].votes)
        {
            high_vote = candidates[i].votes;
        }
    }

    return high_vote;
}


void print_winner()
{
    int vote = max();

    for (int i = 0; i < size; i++)
    {
        if (candidates[i].votes == vote)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}

int main(int argc, char **argv)
{
    int voters, i = 0;
    char name[100];

    if (argc > MAX)
    {
        printf("\nError.......!!!! Only %d candidates at MAX", MAX);
    }

    else if (argc == 1)
    {
        printf("\nCandidates aren't mentioned");
    }

    else
    {
        for (int j = 0; j < argc - 1; j++)
        {
            strcpy(candidates[j].name, argv[j + 1]);
        }

        size = argc;

        printf("Number of voters:");
        scanf("%d", &voters);

        while (i < voters)
        {
            printf("\nVote: ");
            scanf(" %[^\n]", name);

            if (vote(name))
            {
                i++;
            }

            else
            {
                printf("\nInvalid Vote");
            }
        }

        print_winner();
    }

    return 0;
}