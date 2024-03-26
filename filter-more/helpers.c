#include "helpers.h"
#include <math.h>
#define min(a, b) ((a) < (b) ? (a) : (b))

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][j].rgbtBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, n = width / 2; j < n; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            long sumRed = 0, sumGreen = 0, sumBlue = 0, count = 0;
            for (int x = i - 1; x <= i + 1; x++)
            {
                for (int y = j - 1; y <= j + 1; y++)
                {
                    if (x >= 0 && x <= height - 1 && y >= 0 && y <= width - 1)
                    {
                        sumRed += copy[x][y].rgbtRed;
                        sumGreen += copy[x][y].rgbtGreen;
                        sumBlue += copy[x][y].rgbtBlue;
                        count++;
                    }
                }
            }
            image[i][j].rgbtRed = round(sumRed / (float) count);
            image[i][j].rgbtGreen = round(sumGreen / (float) count);
            image[i][j].rgbtBlue = round(sumBlue / (float) count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    int Gx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1}, Gy[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int GxR = 0, GxG = 0, GxB = 0, GyR = 0, GyG = 0, GyB = 0, Gx_x = 0, Gy_y = 0;
            for (int x = i - 1; x <= i + 1; x++)
            {
                for (int y = j - 1; y <= j + 1; y++)
                {
                    if (x >= 0 && x <= height - 1 && y >= 0 && y <= width - 1)
                    {
                        GxR += Gx[Gx_x] * copy[x][y].rgbtRed;
                        GxG += Gx[Gx_x] * copy[x][y].rgbtGreen;
                        GxB += Gx[Gx_x++] * copy[x][y].rgbtBlue;
                        GyR += Gy[Gy_y] * copy[x][y].rgbtRed;
                        GyG += Gy[Gy_y] * copy[x][y].rgbtGreen;
                        GyB += Gy[Gy_y++] * copy[x][y].rgbtBlue;
                    }
                    else
                    {
                        Gx_x++;
                        Gy_y++;
                    }
                }
            }
            image[i][j].rgbtRed = min(255, round(sqrt(pow(GxR, 2) + pow(GyR, 2))));
            image[i][j].rgbtGreen = min(255, round(sqrt(pow(GxG, 2) + pow(GyG, 2))));
            image[i][j].rgbtBlue = min(255, round(sqrt(pow(GxB, 2) + pow(GyB, 2))));
        }
    }
    return;
}
