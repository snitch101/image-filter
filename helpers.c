#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            long average = round((image[i][k].rgbtBlue + image[i][k].rgbtGreen + image[i][k].rgbtRed) / 3.0);

            if (average > 255)
            {
                average = 255;
            }
            else if (average < 0)
            {
                average = 0;
            }

            image[i][k].rgbtBlue = average;
            image[i][k].rgbtGreen = average;
            image[i][k].rgbtRed = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            float tmpRed = (float)image[i][k].rgbtRed;
            float tmpGreen = (float)image[i][k].rgbtGreen;
            float tmpBlue = (float)image[i][k].rgbtBlue;

            if (round(0.393 * tmpRed + 0.769 * tmpGreen + 0.189 * tmpBlue) > 255)
            {
                image[i][k].rgbtRed = 255;
            }
            else
            {
                image[i][k].rgbtRed = round(0.393 * tmpRed + 0.769 * tmpGreen + 0.189 * tmpBlue);
            }

            if (round(0.349 * tmpRed + 0.686 * tmpGreen + 0.168 * tmpBlue) > 255)
            {
                image[i][k].rgbtGreen = 255;
            }
            else
            {
                image[i][k].rgbtGreen = round(0.349 * tmpRed + 0.686 * tmpGreen + 0.168 * tmpBlue);
            }

            if (round(0.272 * tmpRed + 0.534 * tmpGreen + 0.131 * tmpBlue) > 255)
            {
                image[i][k].rgbtBlue = 255;
            }
            else
            {
                image[i][k].rgbtBlue = round(0.272 * tmpRed + 0.534 * tmpGreen + 0.131 * tmpBlue);
            }
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmpPixel = image[i][j];

            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = tmpPixel;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int j = 0; j < height; j++)
    {
        for (int h = 0; h < width; h++)
        {
            copy[j][h] = image[j][h];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            int avgRed = copy[i][k].rgbtRed;
            int avgGreen = copy[i][k].rgbtGreen;
            int avgBlue = copy[i][k].rgbtBlue;
            float divider = 1.00;

            if (k - 1 >= 0)
            {
                avgRed += copy[i][k - 1].rgbtRed;
                avgGreen += copy[i][k - 1].rgbtGreen;
                avgBlue += copy[i][k - 1].rgbtBlue;
                divider++;

                if (i + 1 < height)
                {
                     avgRed += copy[i + 1][k - 1].rgbtRed;
                     avgGreen += copy[i + 1][k - 1].rgbtGreen;
                     avgBlue += copy[i + 1][k - 1].rgbtBlue;
                    divider++;
                }
                if (i - 1 >= 0)
                {
                    avgRed += copy[i - 1][k - 1].rgbtRed;
                    avgGreen += copy[i - 1][k - 1].rgbtGreen;
                    avgBlue += copy[i - 1][k - 1].rgbtBlue;
                    divider++;
                }
            }


            if (k + 1 < width)
            {
                avgRed += copy[i][k + 1].rgbtRed;
                avgGreen += copy[i][k + 1].rgbtGreen;
                avgBlue += copy[i][k + 1].rgbtBlue;
                divider++;

                if (i + 1 < height)
                {
                    avgRed += copy[i + 1][k + 1].rgbtRed;
                    avgGreen += copy[i + 1][k + 1].rgbtGreen;
                    avgBlue += copy[i + 1][k + 1].rgbtBlue;
                    divider++;
                }
                if (i - 1 >= 0)
                {
                    avgRed += copy[i - 1][k + 1].rgbtRed;
                    avgGreen += copy[i - 1][k + 1].rgbtGreen;
                    avgBlue += copy[i - 1][k + 1].rgbtBlue;
                    divider++;
                }
            }


            if (i - 1 >= 0)
            {
                avgRed += copy[i - 1][k].rgbtRed;
                avgGreen += copy[i - 1][k].rgbtGreen;
                avgBlue += copy[i - 1][k].rgbtBlue;
                divider++;
            }
            if (i + 1 < height)
            {
                avgRed += copy[i + 1][k].rgbtRed;
                avgGreen += copy[i + 1][k].rgbtGreen;
                avgBlue += copy[i + 1][k].rgbtBlue;
                divider++;
            }

            if (round(avgRed / divider) > 255)
            {
                image[i][k].rgbtRed = 255;
            }
            else
            {
                image[i][k].rgbtRed = round(avgRed / divider);
            }
            if (round(avgGreen / divider) > 255)
            {
                image[i][k].rgbtGreen = 255;
            }
            else
            {
                image[i][k].rgbtGreen = round(avgGreen / divider);
            }
            if (round(avgBlue / divider) > 255)
            {
                image[i][k].rgbtBlue = 255;
            }
            else
            {
                image[i][k].rgbtBlue = round(avgBlue / divider);
            }

        }
    }
}
