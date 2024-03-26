#include <cs50.h>
#include <stdio.h>

int is_valid(long);
int checksum(long);
string card_type(long);

int main(void)
{
    // Prompt the user for the card number
    long num = get_long("Number: ");

    if (is_valid(num))
    {
        if (checksum(num))
        {
            printf("%s\n", card_type(num));
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

int is_valid(long num)
{
    if ((num > 340000000000000 && num < 350000000000000) || (num > 370000000000000 && num < 380000000000000) ||
        (num > 4000000000000 && num < 5000000000000) || (num > 4000000000000000 && num < 5000000000000000) ||
        (num > 5100000000000000 && num < 5600000000000000))
    {
        return 1;
    }
    return 0;
}

int checksum(long num)
{
    int sum1 = 0, sum2 = 0;

    while (num > 0)
    {
        sum2 += num % 10;
        num /= 10;
        if (num % 10 * 2 > 9)
        {
            int temp = num % 10 * 2;
            sum1 += temp % 10;
            temp /= 10;
            sum1 += temp % 10;
        }
        else
        {
            sum1 += num % 10 * 2;
        }
        num /= 10;
    }

    return (sum1 + sum2) % 10 == 0;
}

string card_type(long num)
{
    if ((num > 340000000000000 && num < 350000000000000) || (num > 370000000000000 && num < 380000000000000))
    {
        return "AMEX";
    }
    if ((num > 4000000000000 && num < 5000000000000) || (num > 4000000000000000 && num < 5000000000000000))
    {
        return "VISA";
    }
    if (num > 5100000000000000 && num < 5600000000000000)
    {
        return "MASTERCARD";
    }
    return "INVALID";
}
