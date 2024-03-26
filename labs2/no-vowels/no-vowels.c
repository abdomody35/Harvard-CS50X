// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>

string replace(string);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }

    argv[1] = replace(argv[1]);

    printf("%s\n", argv[1]);
}

string replace(string str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        switch (str[i])
        {
            case 'a':
            case 'A':
            {
                str[i] = '6';
                break;
            }
            case 'e':
            case 'E':
            {
                str[i] = '3';
                break;
            }
            case 'i':
            case 'I':
            {
                str[i] = '1';
                break;
            }
            case 'o':
            case 'O':
            {
                str[i] = '0';
                break;
            }
        }
    }
    return str;
}
