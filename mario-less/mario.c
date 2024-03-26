#include <stdio.h>

int main()
{
    int num;

    // Prompt the user for the pyramid's height

    do
    {
        printf("Height: ");
        scanf("%d", &num);
    }
    while (num <= 0 || num > 8);

    // Print a pyramid of that height

    for (int i = 1; i <= num; i++)
    {

        // Print the rows

        for (int j = num - i, k = 0; k < num; k++)
        {
            if (k >= j)
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}
