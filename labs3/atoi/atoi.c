#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string, int);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input, strlen(input) - 1));
}

int convert(string input, int n)
{
    int num = 0;
    if (n != 0)
    {
        num = convert(input, n - 1);
    }
    return input[n] - '0' + num * 10;
}
