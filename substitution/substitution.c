// Program to encrypt using substitution key

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool is_valid(string);

int main(int argc, string argv[])
{
    // check if command lines are correct
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // check if key is invalid
    if (!is_valid(argv[1]))
    {
        return 1;
    }

    // prompt user for plaintext
    string txt = get_string("plaintext:  ");

    // encrypt the text
    for (int i = 0, n = strlen(txt); i < n; i++)
    {
        if (islower(txt[i]))
        {
            txt[i] = tolower(argv[1][txt[i] - 'a']);
        }
        else if (isupper(txt[i]))
        {
            txt[i] = toupper(argv[1][txt[i] - 'A']);
        }
    }

    // print the encrypted text
    printf("ciphertext: %s\n", txt);

    // return 0 for successful excution
    return 0;
}

bool is_valid(string str)
{
    int l = strlen(str), count[26] = {0};
    if (l != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }
    for (int i = 0, j; i < l; i++)
    {
        j = toupper(str[i]) - 'A';
        if (!isalpha(str[i]))
        {
            printf("A non alphabetical character was entered.\n");
            return false;
        }
        count[j]++;
        if (count[j] > 1)
        {
            printf("%c was entered more than once.\n", str[i]);
            printf("Every character should be entered once.\n");
            return false;
        }
    }
    return true;
}
