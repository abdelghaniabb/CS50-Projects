#include "helpers.h"
float correct(float color);
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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float blue, green, red;
            //calculate the value of each color
            blue = 0.131 * image[i][j].rgbtBlue + 0.534 * image[i][j].rgbtGreen + 0.272 * image[i][j].rgbtRed;
            green = 0.168 * image[i][j].rgbtBlue + 0.686 * image[i][j].rgbtGreen + 0.349 * image[i][j].rgbtRed;
            red = 0.189 * image[i][j].rgbtBlue + 0.769 * image[i][j].rgbtGreen + 0.393 * image[i][j].rgbtRed;
            //make sur that the color is under 255
            image[i][j].rgbtBlue = (int)correct(blue + 0.5);
            image[i][j].rgbtGreen = (int)correct(green + 0.5);
            image[i][j].rgbtRed = (int)correct(red + 0.5);
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

// make sure that the color is under 255
float correct(float color)
{
    if (color > 255)
    {
        color = 255;
    }
    return (color);
}

