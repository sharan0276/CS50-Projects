#include "helpers.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE *temp = malloc(sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //int set = 0;
            float set = 0.0;

            *temp = image[i][j];

            set = (0.393 * (float) * (&(temp)->rgbtRed) + 0.769 * (float) * (&(temp)->rgbtGreen) + 0.189 * (float) * (&(temp)->rgbtBlue));

            if (set > 255)
            {
                image[i][j].rgbtRed = 255;
            }

            else
            {
                image[i][j].rgbtRed = (int)((set < 0) ? (set - 0.5) : (set + 0.5));
            }


            set = 0.0;

            set = (0.349 * (float) * (&(temp)->rgbtRed) + 0.686 * (float) * (&(temp)->rgbtGreen) + 0.168 * (float) * (&(temp)->rgbtBlue));

            if (set > 255)
            {
                image[i][j].rgbtGreen = 255;
            }

            else
            {
                image[i][j].rgbtGreen = (int)((set < 0) ? (set - 0.5) : (set + 0.5));
            }


            set = 0.0;

            set = (0.272 * (float) * (&(temp)->rgbtRed) + 0.534 * (float) * (&(temp)->rgbtGreen) + 0.131 * (float) * (&(temp)->rgbtBlue));

            if (set > 255)
            {
                image[i][j].rgbtBlue = 255;
            }

            else
            {
                image[i][j].rgbtBlue = (int)((set < 0) ? (set - 0.5) : (set + 0.5));
            }
        }

    }
    free(temp);
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
