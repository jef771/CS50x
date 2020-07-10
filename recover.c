#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// definindo o número máximo de dados
#define MAX_DATA 512

// die function para treinar como fazer funções
void die(const char *message);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        die("Usage: ./recover image");
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        die("");
    }

    unsigned char buffer[MAX_DATA];
    int open_counter = 0;
    int img_counter = 0;
    char filename[8];
    FILE *img;

    while (fread(&buffer, MAX_DATA, 1, file) != 0)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
            && (buffer[3] & 0xf0) == 0xe0)
        {
            if (open_counter == 1)
            {
                fclose(img);
                img_counter++;
            }

            else
            {
                // uma flag para indicar um arquivo aberto
                open_counter = 1;
            }

            // title de um novo jpeg
            sprintf(filename, "%03i.jpg", img_counter);
            // abrir o arquivo com o nome dado pelo sprintf
            img = fopen(filename, "w");
        }
        /* se a flag estiver on então copia os dados do endereço buffer
           para o FILE img */
        if (open_counter == 1)
        {
            fwrite(&buffer, MAX_DATA, 1, img);
        }

    }

    fclose(file);
    fclose(img);

    return 0;
}
/* Function to return a custom or default error message, from Zed A. Shaw
   book Learn C the Hard way. I thought it was a cool function and also
   relevant to this project */
void die(const char *message)
{
    if (errno)
    {
        perror(message);
    }
    else
    {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

// estrutura para files: fread(data, size, number, inptr)
