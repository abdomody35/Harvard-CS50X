// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
} avg_temp;

avg_temp temps[NUM_CITIES];

void sort_cities(int, int);

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    sort_cities(0, 9);

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// TODO: Sort cities by temperature in descending order
void sort_cities(int start, int end)
{
    if (start >= end)
    {
        return;
    }
    int middle = (start + end) / 2;
    sort_cities(start, middle);
    sort_cities(middle + 1, end);
    avg_temp arr[end - start + 1];
    for (int i = start, j = middle + 1, k = end - start, l = 0; k >= 0; k--)
    {
        if (i > middle)
        {
            while (j <= end)
            {
                arr[l++] = temps[j++];
            }
            break;
        }
        if (j > end)
        {
            while (i <= middle)
            {
                arr[l++] = temps[i++];
            }
            break;
        }
        if (temps[i].temp > temps[j].temp)
        {
            if (i <= middle)
            {
                arr[l++] = temps[i++];
            }
        }
        else if (temps[i].temp < temps[j].temp)
        {
            if (j <= end)
            {
                arr[l++] = temps[j++];
            }
        }
        else
        {
            arr[l++] = temps[i++];
            arr[l++] = temps[j++];
        }
    }
    for (int i = start; i <= end; i++)
    {
        temps[i] = arr[i - start];
    }
}
