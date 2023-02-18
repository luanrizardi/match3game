#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "recordes.h"
#define max_recordes 10

int *get_recordes_array()
{
    int i = 0;
    int j = 0;
    int *recordes = NULL;
    char title[9];
    FILE *recordes_file = fopen("recordes.txt", "r");

    if (!recordes_file || recordes_file == NULL)
    {
        // se o arquivo nao existir, cria um
        recordes_file = fopen("recordes.txt", "w");
        fprintf(recordes_file, "recordes:\n");
    }

    recordes = calloc(max_recordes, sizeof(int));

    fscanf(recordes_file, "%s\n", title);

    while (i < max_recordes && !feof(recordes_file))
    {
        fscanf(recordes_file, "%d:\t%d\n", &j, &recordes[i]);
        i++;
    }

    fclose(recordes_file);
    return recordes;
}

void save_recordes(int points)
{
    int i, j;
    int *recordes = get_recordes_array();
    int *recordes_copy;
    FILE *recordes_file = fopen("recordes.txt", "r+");

    if (!recordes_file || recordes_file == NULL)
    {
        fprintf(stderr, "erro ao abrir arquivo de pontuacao\n");
        return;
    }

    recordes_copy = calloc(max_recordes, sizeof(int));
    for (i = 0; i < max_recordes; i++)
        recordes_copy[i] = recordes[i];

    for (i = 0; i < max_recordes; i++)
    {
        if (points > recordes[i])
        {
            for (j = i; j < max_recordes - 1; j++)
                recordes[j + 1] = recordes_copy[j];
            recordes[i] = points;
            break;
        }
    }

    fprintf(recordes_file, "recordes:\n");
    for (i = 0; i < max_recordes; i++)
        fprintf(recordes_file, "%d:\t%d\n", i + 1, recordes[i]);

    fclose(recordes_file);
    free(recordes);
    free(recordes_copy);
}
