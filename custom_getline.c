#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAILLE_TAMPON 1024

ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
    static char tampon[TAILLE_TAMPON];
    static size_t position_tampon = 0;
    static size_t taille_tampon = 0;
    char *nouveau_lineptr;
    size_t copie = 0;

    if (lineptr == NULL || n == NULL || stream == NULL)
        return -1;

    if (*lineptr == NULL)
    {
        *n = TAILLE_TAMPON;
        *lineptr = malloc(*n);
        if (*lineptr == NULL)
            return -1;
    }

    while (1)
    {
        if (position_tampon >= taille_tampon)
        {
            taille_tampon = read(fileno(stream), tampon, TAILLE_TAMPON);
            position_tampon = 0;
            if (taille_tampon <= 0)
            {
                if (copie == 0)
                    return -1;
                break;
            }
        }

        if (copie >= *n - 1)
        {
            *n *= 2;
            nouveau_lineptr = realloc(*lineptr, *n);
            if (nouveau_lineptr == NULL)
                return -1;
            *lineptr = nouveau_lineptr;
        }

        (*lineptr)[copie++] = tampon[position_tampon++];

        if ((*lineptr)[copie - 1] == '\n')
            break;
    }

    (*lineptr)[copie] = '\0';
    return copie;
}
