#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{


    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int red = image[h][w].rgbtRed;
            int green = image[h][w].rgbtGreen;
            int blue = image[h][w].rgbtBlue;

            float average = ((round(red) + round(green) + round(blue)) / 3);

            image[h][w].rgbtRed = round(average);
            image[h][w].rgbtGreen = round(average);
            image[h][w].rgbtBlue = round(average);
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)

        {
            int red = image[h][w].rgbtRed;
            int green = image[h][w].rgbtGreen;
            int blue = image[h][w].rgbtBlue;

            int sRed =  round(.393 * red + .769 * green + .189 * blue);
            int sGreen = round(.349 * red + .686 * green + .168 * blue);
            int sBlue = round(.272 * red + .534 * green + .131 * blue);

            if (sRed < 256)
            {
                image[h][w].rgbtRed = sRed;
            }
            else
            {
                image[h][w].rgbtRed = 255;
            }

            if (sGreen < 256)
            {
                image[h][w].rgbtGreen = sGreen;
            }
            else
            {
                image[h][w].rgbtGreen = 255;
            }

            if (sBlue < 256)
            {
                image[h][w].rgbtBlue = sBlue;
            }
            else
            {
                image[h][w].rgbtBlue = 255;
            }
        }
    }

}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++)
        {
            int sRed = image[h][w].rgbtRed;
            int sGreen = image[h][w].rgbtGreen;
            int sBlue = image[h][w].rgbtBlue;

            image[h][w].rgbtRed = image[h][width - 1 - w].rgbtRed;
            image[h][w].rgbtGreen = image[h][width - 1 - w].rgbtGreen;
            image[h][w].rgbtBlue = image[h][width - 1 - w].rgbtBlue;

            image[h][width - 1 - w].rgbtRed = sRed;
            image[h][width - 1 - w].rgbtGreen = sGreen;
            image[h][width - 1 - w].rgbtBlue = sBlue;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Save original colors
    RGBTRIPLE original[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            original[h][w] = image[h][w];
        }
    }


    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            float count = 0; //helps determine average.
            int aveR = 0;
            int aveB = 0;
            int aveG = 0;

            if (r >= 0 && c >= 0)
            {
                aveR += original[r][c].rgbtRed;
                aveB += original[r][c].rgbtBlue;
                aveG += original[r][c].rgbtGreen;
                count++;
            }

            if (r >= 0 && c - 1 >= 0)
            {
                aveR += original[r][c - 1].rgbtRed;
                aveB += original[r][c - 1].rgbtBlue;
                aveG += original[r][c - 1].rgbtGreen;
                count++;
            }

            if (r - 1 >= 0 && c >= 0)
            {
                aveR += original[r - 1][c].rgbtRed;
                aveB += original[r - 1][c].rgbtBlue;
                aveG += original[r - 1][c].rgbtGreen;
                count++;
            }

            if ((r >= 0 && c + 1 >= 0) && (r >= 0 && c + 1 < width))
            {
                aveR += original[r][c + 1].rgbtRed;
                aveB += original[r][c + 1].rgbtBlue;
                aveG += original[r][c + 1].rgbtGreen;
                count++;
            }

            if ((r + 1 >= 0 && c >= 0) && (r + 1 < height && c >= 0))
            {
                aveR += original[r + 1][c].rgbtRed;
                aveB += original[r + 1][c].rgbtBlue;
                aveG += original[r + 1][c].rgbtGreen;
                count++;
            }

            if ((r - 1 >= 0 && c + 1 >= 0) && (r - 1 >= 0 && c + 1 < width))
            {
                aveR += original[r - 1][c + 1].rgbtRed;
                aveB += original[r - 1][c + 1].rgbtBlue;
                aveG += original[r - 1][c + 1].rgbtGreen;
                count++;
            }

            if ((r + 1 >= 0 && c - 1 >= 0) && (r + 1 < height && c - 1 >= 0))
            {
                aveR += original[r + 1][c - 1].rgbtRed;
                aveB += original[r + 1][c - 1].rgbtBlue;
                aveG += original[r + 1][c - 1].rgbtGreen;
                count++;
            }

            if ((r - 1 >= 0 && c - 1 >= 0))
            {
                aveR += original[r - 1][c - 1].rgbtRed;
                aveB += original[r - 1][c - 1].rgbtBlue;
                aveG += original[r - 1][c - 1].rgbtGreen;
                count++;
            }

            if ((r + 1 >= 0 && c + 1 >= 0) && (r + 1 < height && c + 1 < width))
            {
                aveR += original[r + 1][c + 1].rgbtRed;
                aveB += original[r + 1][c + 1].rgbtBlue;
                aveG += original[r + 1][c + 1].rgbtGreen;
                count++;
            }

            image[r][c].rgbtRed = round(aveR / count);
            image[r][c].rgbtGreen = round(aveG / count);
            image[r][c].rgbtBlue = round(aveB / count);

        }
    }

}
