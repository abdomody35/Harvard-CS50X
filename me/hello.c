#include <stdio.h>

int main()
{
    char name[15];
    printf("What's your name? ");
    scanf("%s", name);
    printf("hello, %s\n", name);
    return 0;
}
