// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = ('z' * 45);

// Number of words read from the dictionary
int count = 0;

// Hash table
node *table[N];



// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        index += tolower(word[i]);
    }

    index %= N;

    node *temp = table[index];

    while (temp != NULL)
    {
        //to check if the word is in the hash table
        if (strcasecmp(temp->word, word) == 0)
        {
            return true;
        }

        temp = temp -> next;
    }

    return false;

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // using sum of all letters to compute hash value

    int index = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        index += tolower(word[i]);
    }
    return (index % N);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Initializing the table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    FILE *f = fopen(dictionary, "r");

    if (f == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(f, "%s", word) != EOF)
    {
        //A count for number of words read
        count++;

        //Create new node
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, word);
        n->next = NULL;

        int index = hash(word);

        if (table[index] == NULL)
        {
            table[index] = n;
        }

        else
        {
            node *temp = table[index];

            while (temp->next != NULL)
            {
                temp = temp->next;
            }

            temp -> next = n;
        }

    }
    fclose(f);
    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // the total number of words stored in variable count

    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    node *cursor;
    node *tmp;

    for (int i = 0; i < N; i++)
    {
        tmp = table[i];
        cursor = table[i];
        while (tmp != NULL)
        {
            cursor = cursor -> next;
            free(tmp);
            tmp = cursor;
        }

        table[i] = NULL;
    }

    return true;
}
