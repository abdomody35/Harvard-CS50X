// A program to determine the grade level needed to comprehend given text

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

float get_grade(string); // Function to calculate the grade of the text

int main(void)
{
    // Prompt the user for the text
    string txt = get_string("Text: ");

    // deterimne the grade using grade() function
    int grade = round(get_grade(txt));

    // print the grade
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }

    // Return 0 for successful execution
    return 0;
}

float get_grade(string txt)
{
    // Calculate the length of the text
    int length = strlen(txt) + 1;

    // Calculate the average number of letters and sentences per 100 word
    float L = 0, S = 0, W = 0;

    /*
    L : total number of letters
    S : total number of sentences
    W : total number of words
    */

    for (int i = 0; i < length; i++)
    {
        if (isalnum(txt[i]))
        {
            L++;
        }
        else if (ispunct(txt[i]))
        {
            if (txt[i] == '.' || txt[i] == '?' || txt[i] == '!')
            {
                S++;
            }
        }
        else if (isspace(txt[i]) || !txt[i])
        {
            W++;
        }
    }

    L = L / W * 100;
    S = S / W * 100;

    // return grade index
    return 0.0588 * L - 0.296 * S - 15.8;
}
