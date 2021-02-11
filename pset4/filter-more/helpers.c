#include "helpers.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        float avg = 0.0;
        int set = 0 ;

        for (int j = 0; j < width; j++)
        {
            avg = (float) image[i][j].rgbtBlue + (float) image[i][j].rgbtRed + (float) image[i][j].rgbtGreen;
            avg /= 3;

            set = (int)((avg < 0) ? (avg - 0.5) : (avg + 0.5));

            image[i][j].rgbtRed = set;
            image[i][j].rgbtBlue = set;
            image[i][j].rgbtGreen = set;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    int set = width / 2;

    for (int i = 0; i < height; i++)
    {
        int j = 0;

        while (j < set)
        {
            int k = width - (j + 1);

            if (j == k)
            {
                break;
            }

            temp = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = temp;

            j++;
        }

    }
    return;
}

bool valid_pixel(i, j, height, width)
{
    return i >= 0 && i < height && j >= 0 && j < width;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }


    int new_i, new_j;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;

            int Red = 0, Green = 0, Blue = 0;

            for (int k1 = -1; k1 < 2; k1++)
            {
                new_i = i + k1;
                for (int k2 = -1; k2 < 2; k2++)
                {
                    new_j = j + k2;

                    if (valid_pixel(new_i, new_j, height, width))
                    {
                        count++;
                        Red += temp[new_i][new_j].rgbtRed;
                        Green += temp[new_i][new_j].rgbtGreen;
                        Blue += temp[new_i][new_j].rgbtBlue;
                    }
                }
            }

            image[i][j].rgbtRed = round((float) Red / count);
            image[i][j].rgbtGreen = round((float) Green / count);
            image[i][j].rgbtBlue = round((float) Blue / count);

        }
    }

    return;
}

// Compute the change of pixel values along the X and Y
RGBTRIPLE edge_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    int RedX = 0, GreenX = 0, BlueX = 0;

    int RedY = 0, GreenY = 0, BlueY = 0;

    // Gy matrix is a transpose of that of Gx.
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    int new_i, new_j;

    for (int d1 = -1; d1 < 2; d1++)
    {
        new_i = i + d1;

        for (int d2 = -1; d2 < 2; d2++)
        {

            new_j = j + d2;

            if (valid_pixel(new_i, new_j, height, width))
            {
                RedX += gx[d1 + 1][d2 + 1] * image[new_i][new_j].rgbtRed;
                GreenX += gx[d1 + 1][d2 + 1] * image[new_i][new_j].rgbtGreen;
                BlueX += gx[d1 + 1][d2 + 1] * image[new_i][new_j].rgbtBlue;

                RedY += gx[d2 + 1][d1 + 1] * image[new_i][new_j].rgbtRed;
                GreenY += gx[d2 + 1][d1 + 1] * image[new_i][new_j].rgbtGreen;
                BlueY += gx[d2 + 1][d1 + 1] * image[new_i][new_j].rgbtBlue;

            }
        }
    }


    int set = 0;
    set = round(sqrt(RedX * RedX + RedY * RedY));
    if (set  > 255)
    {
        temp.rgbtRed = 255;
    }
    else
    {
        temp.rgbtRed = set;
    }

    set = round(sqrt(GreenX * GreenX + GreenY * GreenY));
    if (set > 255)
    {
        temp.rgbtGreen = 255;
    }

    else
    {
        temp.rgbtGreen = set;
    }

    set = round(sqrt(BlueX * BlueX + BlueY * BlueY));
    if (set > 255)
    {
        temp.rgbtBlue = 255;
    }

    else
    {
        temp.rgbtBlue = set;
    }

    return temp;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new[i][j] = edge_pixel(i, j, height, width, image);

        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new[i][j];
        }
    }


    return;
}
