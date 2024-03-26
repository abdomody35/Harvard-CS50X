// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 17577;
int s = 0;
FILE *f = NULL;

// Hash table
node *table[N] = {NULL};

char *strtoupr(const char *str)
{
    char *temp = malloc(strlen(str) + 1);
    int i = 0;
    strcpy(temp, str);
    while (temp[i] != '\0')
    {
        temp[i] = toupper(temp[i]);
        i++;
    }
    return temp;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *list = table[hash(word)];
    while (list)
    {
        char *upped1 = strtoupr(word), *upped2 = strtoupr(list->word);
        if (strcmp(upped1, upped2) == 0)
        {
            free(upped1);
            free(upped2);
            return true;
        }
        list = list->next;
        free(upped1);
        free(upped2);
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int i = 0;
    while (word[i] != '\0')
    {
        if (word[i++] == '\'')
        {
            return 17576;
        }
    }
    if (strlen(word) == 1)
    {
        return (toupper(word[0]) - 'A') * 676;
    }
    if (strlen(word) == 2)
    {
        return (toupper(word[0]) - 'A') * 676 + (toupper(word[1]) - 'A') * 26;
    }
    return (toupper(word[2]) - 'A') + (toupper(word[1]) - 'A') * 26 + (toupper(word[0]) - 'A') * 676;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    f = fopen(dictionary, "r");
    if (!f)
    {
        return false;
    }
    char buffer[LENGTH + 1];
    while (fgets(buffer, sizeof(buffer), f))
    {
        node *n = malloc(sizeof(node));
        if (!n)
        {
            return false;
        }
        strcpy(n->word, buffer);
        int newline = strlen(n->word) - 1;
        if (n->word[newline] == '\n')
        {
            n->word[newline] = '\0';
        }
        int hashed = hash(buffer);
        n->next = table[hashed];
        table[hashed] = n;
        s++;
    }
    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return s;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        while (table[i])
        {
            node *temp = table[i];
            table[i] = table[i]->next;
            free(temp);
        }
    }
    return true;
}
