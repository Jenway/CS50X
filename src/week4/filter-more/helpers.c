#include "helpers.h"
#include <math.h>
#include <stdio.h>

#define LESS255(a) ((a) > 255 ? 255 : (a))

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    uint8_t rawRed, rawGreen, rawBlue, result;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            rawRed = image[i][j].rgbtRed;
            rawGreen = image[i][j].rgbtGreen;
            rawBlue = image[i][j].rgbtBlue;

            result = round((rawRed + rawGreen + rawBlue) / 3.0);
            image[i][j].rgbtRed = result;
            image[i][j].rgbtGreen = result;
            image[i][j].rgbtBlue = result;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE row[width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            row[j] = image[i][j];
        }
        for (int j = 0; j < width; j++)
        {
            image[i][width - j - 1] = row[j];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float targetRed, targetGreen, targetBlue, count = 0;
    RGBTRIPLE temp_Image[height][width];
    for (int i = 0; i < height; i += 1)
    {
        for (int j = 0; j < width; j += 1)
        {
            targetBlue = 0, targetGreen = 0, targetRed = 0, count = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if ((i + k > height - 1) || (j + l) > width - 1 || (i + k) < 0 || (j + l) < 0)
                    {
                        continue;
                    }
                    count++;
                    targetRed += image[i + k][j + l].rgbtRed;
                    targetGreen += image[i + k][j + l].rgbtGreen;
                    targetBlue += image[i + k][j + l].rgbtBlue;
                }
            }

            temp_Image[i][j] = (RGBTRIPLE){.rgbtRed = round(targetRed / count),
                                           .rgbtGreen = round(targetGreen / count),
                                           .rgbtBlue = round(targetBlue / count)};
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp_Image[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE tempImage[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            tempImage[h][w] = image[h][w];
        }
    }

    int sobel_y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int sobel_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    for (int i = 0; i < height; i += 1)
    {
        for (int j = 0; j < width; j += 1)
        {

            float temp_x_Red = 0, temp_x_Blue = 0, temp_x_Green = 0, temp_y_Red = 0, temp_y_Blue = 0, temp_y_Green = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {

                    if ((i + k > height - 1) || (j + l) > width - 1 || (i + k) < 0 || (j + l) < 0)
                    {
                        continue;
                    }
                    temp_x_Red += tempImage[i + k][j + l].rgbtRed * sobel_x[k + 1][l + 1];
                    temp_x_Green += tempImage[i + k][j + l].rgbtGreen * sobel_x[k + 1][l + 1];
                    temp_x_Blue += tempImage[i + k][j + l].rgbtBlue * sobel_x[k + 1][l + 1];
                    temp_y_Red += tempImage[i + k][j + l].rgbtRed * sobel_y[k + 1][l + 1];
                    temp_y_Green += tempImage[i + k][j + l].rgbtGreen * sobel_y[k + 1][l + 1];
                    temp_y_Blue += tempImage[i + k][j + l].rgbtBlue * sobel_y[k + 1][l + 1];
                }
            }

            image[i][j].rgbtRed = LESS255(round(sqrt(temp_x_Red * temp_x_Red + temp_y_Red * temp_y_Red)));
            image[i][j].rgbtGreen = LESS255(round(sqrt(temp_x_Green * temp_x_Green + temp_y_Green * temp_y_Green)));
            image[i][j].rgbtBlue = LESS255(round(sqrt(temp_x_Blue * temp_x_Blue + temp_y_Blue * temp_y_Blue)));
        }
    }
}