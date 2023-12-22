#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float gray = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0 + 0.5;
            image[i][j].rgbtBlue = (int)gray;
            image[i][j].rgbtGreen = (int)gray;
            image[i][j].rgbtRed = (int)gray;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int blue[width], green[width], red[width];
        for (int j = 0; j < width; j++)
        {
            blue[j] = image[i][width - 1 - j].rgbtBlue ;
            green[j] = image[i][width - 1 - j].rgbtGreen;
            red[j] = image[i][width - 1 - j].rgbtRed;
        }
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = blue[j];
            image[i][j].rgbtGreen = green[j];
            image[i][j].rgbtRed = red[j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy_image[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float blue, green, red, count;
            blue = copy_image[i][j].rgbtBlue;
            green = copy_image[i][j].rgbtGreen;
            red = copy_image[i][j].rgbtRed;
            count = 1.0;

            if (i - 1 >= 0 && j - 1 >= 0)
            {
                blue = blue + copy_image[i - 1][j - 1].rgbtBlue;
                green = green + copy_image[i - 1][j - 1].rgbtGreen;
                red = red + copy_image[i - 1][j - 1].rgbtRed;
                count += 1;
            }

            if (i - 1 >= 0)
            {
                blue = blue + copy_image[i - 1][j].rgbtBlue;
                green = green + copy_image[i - 1][j].rgbtGreen;
                red = red + copy_image[i - 1][j].rgbtRed;
                count += 1;
            }

            if (j - 1 >= 0)
            {
                blue = blue + copy_image[i ][j - 1].rgbtBlue;
                green = green + copy_image[i][j - 1].rgbtGreen;
                red = red + copy_image[i][j - 1].rgbtRed;
                count += 1;
            }

            if (i + 1 <= height - 1 && j - 1 >= 0)
            {
                blue = blue + copy_image[i + 1][j - 1].rgbtBlue;
                green = green + copy_image[i + 1][j - 1].rgbtGreen;
                red = red + copy_image[i + 1][j - 1].rgbtRed;
                count += 1;
            }

            if (i - 1 >= 0 && j + 1 <= width - 1)
            {
                blue = blue + copy_image[i - 1][j + 1].rgbtBlue;
                green = green + copy_image[i - 1][j + 1].rgbtGreen;
                red = red + copy_image[i - 1][j + 1].rgbtRed;
                count += 1;
            }

            if (i + 1 <= height - 1)
            {
                blue = blue + copy_image[i + 1][j].rgbtBlue;
                green = green + copy_image[i + 1][j].rgbtGreen;
                red = red + copy_image[i + 1][j].rgbtRed;
                count += 1;
            }

            if (j + 1 <= width - 1)
            {
                blue = blue + copy_image[i][j + 1].rgbtBlue;
                green = green + copy_image[i][j + 1].rgbtGreen;
                red = red + copy_image[i][j + 1].rgbtRed;
                count += 1;
            }

            if (i + 1 <= height - 1 && j + 1 <= width - 1)
            {
                blue = blue + copy_image[i + 1][j + 1].rgbtBlue;
                green = green + copy_image[i + 1][j + 1].rgbtGreen;
                red = red + copy_image[i + 1][j + 1].rgbtRed;
                count += 1;
            }

            image[i][j].rgbtBlue = (int)(((float)blue / (float)count) + 0.5);
            image[i][j].rgbtGreen = (int)(((float)green / (float)count) + 0.5);
            image[i][j].rgbtRed = (int)(((float)red / (float)count) + 0.5);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy_image[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float Gx_blue = 0, Gx_green = 0, Gx_red = 0, Gy_blue = 0, Gy_green = 0, Gy_red = 0;
            int blue, green, red;
            
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                Gx_blue = Gx_blue - copy_image[i - 1][j - 1].rgbtBlue;
                Gx_green = Gx_green - copy_image[i - 1][j - 1].rgbtGreen;
                Gx_red = Gx_red - copy_image[i - 1][j - 1].rgbtRed;
                Gy_blue = Gy_blue - copy_image[i - 1][j - 1].rgbtBlue;
                Gy_green = Gy_green - copy_image[i - 1][j - 1].rgbtGreen;
                Gy_red = Gy_red - copy_image[i - 1][j - 1].rgbtRed;
            }
            if (j - 1 >= 0)
            {
                Gx_blue = Gx_blue - 2 * copy_image[i][j - 1].rgbtBlue;
                Gx_green = Gx_green - 2 * copy_image[i][j - 1].rgbtGreen;
                Gx_red = Gx_red - 2 * copy_image[i][j - 1].rgbtRed;
            }
            if (i + 1 <= height - 1 && j - 1 >= 0)
            {
                Gx_blue = Gx_blue - copy_image[i + 1][j - 1].rgbtBlue;
                Gx_green = Gx_green - copy_image[i + 1][j - 1].rgbtGreen;
                Gx_red = Gx_red - copy_image[i + 1][j - 1].rgbtRed;
                Gy_blue = Gy_blue + copy_image[i + 1][j - 1].rgbtBlue;
                Gy_green = Gy_green + copy_image[i + 1][j - 1].rgbtGreen;
                Gy_red = Gy_red + copy_image[i + 1][j - 1].rgbtRed;
            }
            if (i - 1 >= 0)
            {
                Gy_blue = Gy_blue - 2 * copy_image[i - 1][j].rgbtBlue;
                Gy_green = Gy_green - 2 * copy_image[i - 1][j].rgbtGreen;
                Gy_red = Gy_red - 2 * copy_image[i - 1][j].rgbtRed;
            }
            if (i - 1 >= 0 && j + 1 <= width - 1)
            {
                Gx_blue = Gx_blue + copy_image[i - 1][j +1].rgbtBlue;
                Gx_green = Gx_green + copy_image[i - 1][j + 1].rgbtGreen;
                Gx_red = Gx_red + copy_image[i - 1][j + 1].rgbtRed;
                Gy_blue = Gy_blue - copy_image[i - 1][j + 1].rgbtBlue;
                Gy_green = Gy_green - copy_image[i - 1][j + 1].rgbtGreen;
                Gy_red = Gy_red - copy_image[i - 1][j + 1].rgbtRed;
            }
            if (j + 1 <= width - 1)
            {
                Gx_blue = Gx_blue + 2 * copy_image[i][j + 1].rgbtBlue;
                Gx_green = Gx_green + 2 * copy_image[i][j + 1].rgbtGreen;
                Gx_red = Gx_red + 2 * copy_image[i][j + 1].rgbtRed;
            }
            if (i + 1 <= height - 1 && j + 1 <= width - 1)
            {
                Gx_blue = Gx_blue + copy_image[i + 1][j + 1].rgbtBlue;
                Gx_green = Gx_green + copy_image[i + 1][j + 1].rgbtGreen;
                Gx_red = Gx_red + copy_image[i + 1][j + 1].rgbtRed;
                Gy_blue = Gy_blue + copy_image[i + 1][j + 1].rgbtBlue;
                Gy_green = Gy_green + copy_image[i + 1][j + 1].rgbtGreen;
                Gy_red = Gy_red + copy_image[i + 1][j + 1].rgbtRed;
            }
            if (i + 1 <= height - 1)
            {
                Gy_blue = Gy_blue + 2 * copy_image[i + 1][j].rgbtBlue;
                Gy_green = Gy_green + 2 * copy_image[i + 1][j].rgbtGreen;
                Gy_red = Gy_red + 2 * copy_image[i + 1][j].rgbtRed;
            }
            
            blue = (int)(sqrtf(Gx_blue * Gx_blue + Gy_blue * Gy_blue) + 0.5);
            green = (int)(sqrtf(Gx_green * Gx_green + Gy_green * Gy_green) + 0.5);
            red = (int)(sqrtf(Gx_red * Gx_red + Gy_red * Gy_red) + 0.5);

            if (blue > 255)
            {
                blue = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (red > 255)
            {
                red = 255;
            }
            image[i][j].rgbtBlue = blue;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtRed = red;
        }
    }
    return;
}
