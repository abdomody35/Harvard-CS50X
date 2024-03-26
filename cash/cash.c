#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int num, pen = 0;

    // Prompt the user for the change owed
    do
    {
        num = get_int("Change owed: ");
    }
    while (num < 0);

    while (num > 0)
    {
        if (num >= 25)
        {
            num -= 25;
            pen++;
        }
        else if (num >= 10)
        {
            num -= 10;
            pen++;
        }
        else if (num >= 5)
        {
            num -= 5;
            pen++;
        }
        else if (num >= 1)
        {
            num -= 1;
            pen++;
        }
    }

    printf("%d\n", pen);

    return 0;
}
