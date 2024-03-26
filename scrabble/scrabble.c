// A scrabble like game

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int points(string); // A function to calculate the points of the word

int main(void)
{
    // Prompt the user for player1's word
    string word1 = get_string("Player 1: ");

    // Prompt the user for player2's word
    string word2 = get_string("Player 2: ");

    // Calculate player1's points
    int points1 = points(word1);

    // Calculate player2's points
    int points2 = points(word2);

    // Compare between the 2 word to determine who wins
    if (points1 > points2)
    {
        printf("Player 1 wins!\n");
    }
    else if (points2 > points1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

    // Return 0 for successful execution
    return 0;
}

int points(string str)
{
    int score = 0;

    // Iterate through the string to get the sum of the points of each letter
    for (int i = 0; str[i] != '\0'; i++)
    {
        switch (toupper(str[i]))
        {
            case 'A':
            case 'E':
            case 'I':
            case 'L':
            case 'N':
            case 'O':
            case 'R':
            case 'S':
            case 'T':
            case 'U':
            {
                score += 1;
                break;
            }
            case 'D':
            case 'G':
            {
                score += 2;
                break;
            }
            case 'B':
            case 'C':
            case 'M':
            case 'P':
            {
                score += 3;
                break;
            }
            case 'F':
            case 'H':
            case 'V':
            case 'W':
            case 'Y':
            {
                score += 4;
                break;
            }
            case 'K':
            {
                score += 5;
                break;
            }
            case 'J':
            case 'X':
            {
                score += 8;
                break;
            }
            case 'Q':
            case 'Z':
            {
                score += 10;
                break;
            }
        }
    }
    return score;
}
