// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    int l = 0, u = 0, s = 0, n = 0;
    for (int i = 0; password[i] != '\0'; i++)
    {
        if (islower(password[i]))
        {
            l++;
        }
        if (isupper(password[i]))
        {
            u++;
        }
        if (isdigit(password[i]))
        {
            n++;
        }
        if (ispunct(password[i]))
        {
            s++;
        }
    }
    return s && n && u && l;
}
