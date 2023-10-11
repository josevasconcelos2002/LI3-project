#include "../include/batch.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>

bool folderExists(char *path)
{
    bool result = false;
    DIR *dir = opendir(path);
    if (dir)
        result = true;
    return result;
}

void batch(int argc, char **argv)
{
    // sabemos que já recebemos 3 argumentos, argv[]
    int sys = system("clear");
    if (sys == 0)
    {
        for (int i = 0; i < 3; i++)
        {
            printf("argv[%d] -> %s\n", i, argv[i]);
        }
        char *dataset_path = argv[1];
        // char *input = argv[2];
        if (!folderExists(dataset_path))
        {
            printf("\033[1;31m");
            printf("\n\nErro! Diretório %s não existe!\n\n", dataset_path);
            printf("\033[0m");
        }
    }
}