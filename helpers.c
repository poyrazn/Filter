#include "helpers.h"
#include <math.h>
#include <stdbool.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
// Traverse the 2D image array pixel by pixel, each pixel containing RGB values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate the average of Red, Green and Blue values to find the shade of gray.
            float avg = ((float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)) / 3;

            // set all values to the calculated average to obtain a grayscale effect
            image[i][j].rgbtRed = round(avg);
            image[i][j].rgbtGreen = round(avg);
            image[i][j].rgbtBlue = round(avg);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int originalRed;
    int originalGreen;
    int originalBlue;
    int sepiaRed;
    int sepiaGreen;
    int sepiaBlue;

// Traverse the 2D image array pixel by pixel, each pixel containing RGB values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get the original color values of the pixel
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            // provided algorithm to calculate sepia color values based on the original RGB values
            sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // check whether the calculated value is greater than 255. if so, assign 255 (the upper-limit of a byte)
            if (sepiaRed > 255)
            {
                sepiaRed = 255.0;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // set the color values to their corresponding sepia values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
// Traverse the 2D image array containing pixel RGB values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // swap the pixel values of two pixels (vertically symmetrical)
            RGBTRIPLE original = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = original;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
// Temporary array to hold the average RGB values
    RGBTRIPLE average[height][width];

// Traverse the 2D image array containing pixel RGB values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // summations of pixel color values
            int sumRed = image[i][j].rgbtRed;
            int sumGreen = image[i][j].rgbtGreen;
            int sumBlue = image[i][j].rgbtBlue;
            int count = 1;

            // boolean variables to check for edges
            bool backw = false;
            bool forw = false;
            bool up = false;
            bool down = false;

            // check if there is another pixel above this
            if (i - 1 >= 0)
            {
                // mark the direction as valid for future control
                up = true;
                // increase sum values and the pixel count
                sumRed += image[i - 1][j].rgbtRed;
                sumGreen += image[i - 1][j].rgbtGreen;
                sumBlue += image[i - 1][j].rgbtBlue;
                count++;
            }

            // check if there is another pixel below this
            if (i + 1 < height)
            {
                // mark the direction as valid for future control
                down = true;
                // increase sum values and the pixel count
                sumRed += image[i + 1][j].rgbtRed;
                sumGreen += image[i + 1][j].rgbtGreen;
                sumBlue += image[i + 1][j].rgbtBlue;
                count++;
            }

            // check if there is another pixel to the left
            if (j - 1 >= 0)
            {
                // mark the direction as valid for future control
                backw = true;
                // increase sum values and the pixel count
                sumRed += image[i][j - 1].rgbtRed;
                sumGreen += image[i][j - 1].rgbtGreen;
                sumBlue += image[i][j - 1].rgbtBlue;
                count++;
            }

            // check if there is another pixel to the right
            if (j + 1 < width)
            {
                // mark the direction as valid for future control
                forw = true;
                // increase sum values and the pixel count
                sumRed += image[i][j + 1].rgbtRed;
                sumGreen += image[i][j + 1].rgbtGreen;
                sumBlue += image[i][j + 1].rgbtBlue;
                count++;
            }
            if (backw)
            {
                // top-left corner of the neighboring pixels
                if (up)
                {
                    // increase sum values and the pixel count
                    sumRed += image[i - 1][j - 1].rgbtRed;
                    sumGreen += image[i - 1][j - 1].rgbtGreen;
                    sumBlue += image[i - 1][j - 1].rgbtBlue;
                    count++;
                }

                // bottom-left corner of the neighboring pixels
                if (down)
                {
                    // increase sum values and the pixel count
                    sumRed += image[i + 1][j - 1].rgbtRed;
                    sumGreen += image[i + 1][j - 1].rgbtGreen;
                    sumBlue += image[i + 1][j - 1].rgbtBlue;
                    count++;
                }

            }

            if (forw)
            {
                // top-right corner of the neighboring pixels
                if (up)
                {
                    // increase sum values and the pixel count
                    sumRed += image[i - 1][j + 1].rgbtRed;
                    sumGreen += image[i - 1][j + 1].rgbtGreen;
                    sumBlue += image[i - 1][j + 1].rgbtBlue;
                    count++;
                }
                // bottom-right corner of the neighboring pixels
                if (down)
                {
                    // increase sum values and the pixel count
                    sumRed += image[i + 1][j + 1].rgbtRed;
                    sumGreen += image[i + 1][j + 1].rgbtGreen;
                    sumBlue += image[i + 1][j + 1].rgbtBlue;
                    count++;
                }
            }

            // calculate the average RGB values
            average[i][j].rgbtRed = round((float) sumRed / count);
            average[i][j].rgbtGreen = round((float) sumGreen / count);
            average[i][j].rgbtBlue = round((float) sumBlue / count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // replace actual image pixel color values with average values
            image[i][j] = average[i][j];
        }
    }

    return;
}
