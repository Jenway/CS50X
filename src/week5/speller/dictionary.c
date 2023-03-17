// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26;

unsigned int dic_size = 0;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    for (node *temp = table[hash(word)]; temp != NULL; temp = temp->next)
    {
        if (strcasecmp(word, temp->word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // It was ugly and ... if set to 26*26*26 will use way too much memory
    if (strlen(word) == 1)
    {
        return (toupper(word[0]) - 'A') * 26;
    }
    else
    {
        return (toupper(word[0]) - 'A') * 26 + toupper(word[1]) - 'A';
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        return false;
    }
    char buffer[LENGTH + 1];
    node *temp = NULL;
    for (; fscanf(dic, "%s", buffer) != EOF;)
    {
        temp = (node *)malloc(sizeof(node));
        int num = hash(buffer);
        temp->next = table[num];
        table[num] = temp;
        strcpy(temp->word, buffer);

        dic_size += 1;
    }
    // and don't forget to close the file
    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dic_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *temp = table[i];
        for (; temp != NULL;)
        {
            node *deleter = temp;
            temp = temp->next;
            free(deleter);
        }
        if (i == N - 1 && temp == NULL)
        {
            return true;
        }
    }

    return false;
}
