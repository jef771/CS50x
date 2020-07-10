#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // variável para calcular média artimética
            float average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            image[i][j].rgbtRed = round(average);
            image[i][j].rgbtGreen = round(average);
            image[i][j].rgbtBlue = round(average);
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
            float sepiaRed = (image[i][j].rgbtRed * 0.393) + (image[i][j].rgbtGreen * 0.769) + (image[i][j].rgbtBlue * 0.189);
            float sepiaGreen = (image[i][j].rgbtRed * 0.349) + (image[i][j].rgbtGreen * 0.686) + (image[i][j].rgbtBlue * 0.168);
            float sepiaBlue = (image[i][j].rgbtRed * 0.272) + (image[i][j].rgbtGreen * 0.534) + (image[i][j].rgbtBlue * 0.131);

            // if pois deve checar todas as variáveis
            if (sepiaRed > 255)
            {
                sepiaRed = 255.0;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255.0;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255.0;
            }

            image[i][j].rgbtRed = round(sepiaRed);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtBlue = round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // grupo de var para armazenar uma cópia do valor original
    int container0 = 0;
    int container1 = 0;
    int container2 = 0;
    int final_width = width - 1;
    // como meu algoritmo cálcula 2 ao mesmo tempo
    // só preciso checar metade dos termos
    float n = width / 2.0;


    for (int i = 0; i < height; i++)
    {
        final_width = width - 1;
        for (int j = 0; j < round(n); j++)
        {
            // se j é igual ao contador, ex.: 5 == 5, o loop pula para
            // o próximo
            if (j == final_width)
            {
                continue;
            }
            else
            {
                container0 = image[i][j].rgbtRed;
                container1 = image[i][j].rgbtGreen;
                container2 = image[i][j].rgbtBlue;
                image[i][j].rgbtRed = image[i][final_width].rgbtRed;
                image[i][j].rgbtGreen = image[i][final_width].rgbtGreen;
                image[i][j].rgbtBlue = image[i][final_width].rgbtBlue;
                image[i][final_width].rgbtRed = container0;
                image[i][final_width].rgbtGreen = container1;
                image[i][final_width].rgbtBlue = container2;

                final_width -= 1;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int final_width = width - 1;
    int final_height = height - 1;
    // cópia da árvore para armazenar os valores originais
    RGBTRIPLE copy_image[height][width];
    // copiando...
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            copy_image[k][l] = image[k][l];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int top_r = i - 1, bot_r = i + 1, next = j + 1, before = j - 1;

            if (i != 0 && i != final_height && j == 0)
            {
                float average_red = (copy_image[i][j].rgbtRed +
                                     copy_image[i][next].rgbtRed +
                                     copy_image[top_r][j].rgbtRed +
                                     copy_image[top_r][next].rgbtRed +
                                     copy_image[bot_r][j].rgbtRed +
                                     copy_image[bot_r][next].rgbtRed) / 6.0;

                float average_green = (copy_image[i][j].rgbtGreen +
                                       copy_image[i][next].rgbtGreen +
                                       copy_image[top_r][j].rgbtGreen +
                                       copy_image[top_r][next].rgbtGreen +
                                       copy_image[bot_r][j].rgbtGreen +
                                       copy_image[bot_r][next].rgbtGreen) / 6.0;

                float average_blue = (copy_image[i][j].rgbtBlue +
                                      copy_image[i][next].rgbtBlue +
                                      copy_image[top_r][j].rgbtBlue +
                                      copy_image[top_r][next].rgbtBlue +
                                      copy_image[bot_r][j].rgbtBlue +
                                      copy_image[bot_r][next].rgbtBlue) / 6.0;

                image[i][j].rgbtRed = round(average_red);
                image[i][j].rgbtGreen = round(average_green);
                image[i][j].rgbtBlue = round(average_blue);

            }
            else if (i != 0 && i != final_height && j == final_width)
            {
                float average_red = (copy_image[i][j].rgbtRed +
                                     copy_image[i][before].rgbtRed +
                                     copy_image[top_r][j].rgbtRed +
                                     copy_image[top_r][before].rgbtRed +
                                     copy_image[bot_r][j].rgbtRed +
                                     copy_image[bot_r][before].rgbtRed) / 6.0;

                float average_green = (copy_image[i][j].rgbtGreen +
                                       copy_image[i][before].rgbtGreen +
                                       copy_image[top_r][j].rgbtGreen +
                                       copy_image[top_r][before].rgbtGreen +
                                       copy_image[bot_r][j].rgbtGreen +
                                       copy_image[bot_r][before].rgbtGreen) / 6.0;

                float average_blue = (copy_image[i][j].rgbtBlue +
                                      copy_image[i][before].rgbtBlue +
                                      copy_image[top_r][j].rgbtBlue +
                                      copy_image[top_r][before].rgbtBlue +
                                      copy_image[bot_r][j].rgbtBlue +
                                      copy_image[bot_r][before].rgbtBlue) / 6.0;

                image[i][j].rgbtRed = round(average_red);
                image[i][j].rgbtGreen = round(average_green);
                image[i][j].rgbtBlue = round(average_blue);

            }
            else if (i == 0 && j != 0 && j != final_width)
            {
                float average_red = (copy_image[i][j].rgbtRed +
                                     copy_image[i][before].rgbtRed +
                                     copy_image[i][next].rgbtRed +
                                     copy_image[bot_r][j].rgbtRed +
                                     copy_image[bot_r][before].rgbtRed +
                                     copy_image[bot_r][next].rgbtRed) / 6.0;

                float average_green = (copy_image[i][j].rgbtGreen +
                                       copy_image[i][before].rgbtGreen +
                                       copy_image[i][next].rgbtGreen +
                                       copy_image[bot_r][j].rgbtGreen +
                                       copy_image[bot_r][before].rgbtGreen +
                                       copy_image[bot_r][next].rgbtGreen) / 6.0;

                float average_blue = (copy_image[i][j].rgbtBlue +
                                      copy_image[i][before].rgbtBlue +
                                      copy_image[i][next].rgbtBlue +
                                      copy_image[bot_r][j].rgbtBlue +
                                      copy_image[bot_r][before].rgbtBlue +
                                      copy_image[bot_r][next].rgbtBlue) / 6.0;

                image[i][j].rgbtRed = round(average_red);
                image[i][j].rgbtGreen = round(average_green);
                image[i][j].rgbtBlue = round(average_blue);
            }
            else if (i == final_height && j != 0 && j != final_width)
            {
                float average_red = (copy_image[i][j].rgbtRed +
                                     copy_image[i][before].rgbtRed +
                                     copy_image[i][next].rgbtRed +
                                     copy_image[top_r][j].rgbtRed +
                                     copy_image[top_r][before].rgbtRed +
                                     copy_image[top_r][next].rgbtRed) / 6.0;

                float average_green = (copy_image[i][j].rgbtGreen +
                                       copy_image[i][before].rgbtGreen +
                                       copy_image[i][next].rgbtGreen +
                                       copy_image[top_r][j].rgbtGreen +
                                       copy_image[top_r][before].rgbtGreen +
                                       copy_image[top_r][next].rgbtGreen) / 6.0;

                float average_blue = (copy_image[i][j].rgbtBlue +
                                      copy_image[i][before].rgbtBlue +
                                      copy_image[i][next].rgbtBlue +
                                      copy_image[top_r][j].rgbtBlue +
                                      copy_image[top_r][before].rgbtBlue +
                                      copy_image[top_r][next].rgbtBlue) / 6.0;

                image[i][j].rgbtRed = round(average_red);
                image[i][j].rgbtGreen = round(average_green);
                image[i][j].rgbtBlue = round(average_blue);
            }
            else if (i == final_height && j == 0)
            {
                float average_red = (copy_image[i][j].rgbtRed +
                                     copy_image[i][next].rgbtRed +
                                     copy_image[top_r][j].rgbtRed +
                                     copy_image[top_r][next].rgbtRed) / 4.0;

                float average_green = (copy_image[i][j].rgbtGreen +
                                       copy_image[i][next].rgbtGreen +
                                       copy_image[top_r][j].rgbtGreen +
                                       copy_image[top_r][next].rgbtGreen) / 4.0;

                float average_blue = (copy_image[i][j].rgbtBlue +
                                      copy_image[i][next].rgbtBlue +
                                      copy_image[top_r][j].rgbtBlue +
                                      copy_image[top_r][next].rgbtBlue) / 4.0;

                image[i][j].rgbtRed = round(average_red);
                image[i][j].rgbtGreen = round(average_green);
                image[i][j].rgbtBlue = round(average_blue);

            }
            else if (i == 0 && j == 0)
            {
                float average_red = (copy_image[i][j].rgbtRed +
                                     copy_image[i][next].rgbtRed +
                                     copy_image[bot_r][j].rgbtRed +
                                     copy_image[bot_r][next].rgbtRed) / 4.0;

                float average_green = (copy_image[i][j].rgbtGreen +
                                       copy_image[i][next].rgbtGreen +
                                       copy_image[bot_r][j].rgbtGreen +
                                       copy_image[bot_r][next].rgbtGreen) / 4.0;

                float average_blue = (copy_image[i][j].rgbtBlue +
                                      copy_image[i][next].rgbtBlue +
                                      copy_image[bot_r][j].rgbtBlue +
                                      copy_image[bot_r][next].rgbtBlue) / 4.0;

                image[i][j].rgbtRed = round(average_red);
                image[i][j].rgbtGreen = round(average_green);
                image[i][j].rgbtBlue = round(average_blue);

            }
            else if (i == final_height && j == final_width)
            {
                float average_red = (copy_image[i][j].rgbtRed +
                                     copy_image[i][before].rgbtRed +
                                     copy_image[top_r][j].rgbtRed +
                                     copy_image[top_r][before].rgbtRed) / 4.0;

                float average_green = (copy_image[i][j].rgbtGreen +
                                       copy_image[i][before].rgbtGreen +
                                       copy_image[top_r][j].rgbtGreen +
                                       copy_image[top_r][before].rgbtGreen) / 4.0;

                float average_blue = (copy_image[i][j].rgbtBlue +
                                      copy_image[i][before].rgbtBlue +
                                      copy_image[top_r][j].rgbtBlue +
                                      copy_image[top_r][before].rgbtBlue) / 4.0;

                image[i][j].rgbtRed = round(average_red);
                image[i][j].rgbtGreen = round(average_green);
                image[i][j].rgbtBlue = round(average_blue);
            }
            else if (i == 0 && j == final_width)
            {
                float average_red = (copy_image[i][j].rgbtRed +
                                     copy_image[i][before].rgbtRed +
                                     copy_image[bot_r][j].rgbtRed +
                                     copy_image[bot_r][before].rgbtRed) / 4.0;

                float average_green = (copy_image[i][j].rgbtGreen +
                                       copy_image[i][before].rgbtGreen +
                                       copy_image[bot_r][j].rgbtGreen +
                                       copy_image[bot_r][before].rgbtGreen) / 4.0;

                float average_blue = (copy_image[i][j].rgbtBlue +
                                      copy_image[i][before].rgbtBlue +
                                      copy_image[bot_r][j].rgbtBlue +
                                      copy_image[bot_r][before].rgbtBlue) / 4.0;

                image[i][j].rgbtRed = round(average_red);
                image[i][j].rgbtGreen = round(average_green);
                image[i][j].rgbtBlue = round(average_blue);

            }
            else
            {
                float average_red = (copy_image[i][j].rgbtRed +
                                     copy_image[i][next].rgbtRed +
                                     copy_image[i][before].rgbtRed +
                                     copy_image[bot_r][j].rgbtRed +
                                     copy_image[bot_r][next].rgbtRed +
                                     copy_image[bot_r][before].rgbtRed +
                                     copy_image[top_r][j].rgbtRed +
                                     copy_image[top_r][next].rgbtRed +
                                     copy_image[top_r][before].rgbtRed) / 9.0;

                float average_green = (copy_image[i][j].rgbtGreen +
                                       copy_image[i][next].rgbtGreen +
                                       copy_image[i][before].rgbtGreen +
                                       copy_image[bot_r][j].rgbtGreen +
                                       copy_image[bot_r][next].rgbtGreen +
                                       copy_image[bot_r][before].rgbtGreen +
                                       copy_image[top_r][j].rgbtGreen +
                                       copy_image[top_r][next].rgbtGreen +
                                       copy_image[top_r][before].rgbtGreen) / 9.0;

                float average_blue = (copy_image[i][j].rgbtBlue +
                                      copy_image[i][next].rgbtBlue +
                                      copy_image[i][before].rgbtBlue +
                                      copy_image[bot_r][j].rgbtBlue +
                                      copy_image[bot_r][next].rgbtBlue +
                                      copy_image[bot_r][before].rgbtBlue +
                                      copy_image[top_r][j].rgbtBlue +
                                      copy_image[top_r][next].rgbtBlue +
                                      copy_image[top_r][before].rgbtBlue) / 9.0;

                image[i][j].rgbtRed = round(average_red);
                image[i][j].rgbtGreen = round(average_green);
                image[i][j].rgbtBlue = round(average_blue);
            }

        }
    }
    return;
}
