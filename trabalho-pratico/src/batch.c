#include "../include/batch.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>

bool user_file_exists(char *path)
{
    bool result = false;
    return result;
}

bool reservation_file_exists(char *path)
{
    bool result = false;
    return result;
}

bool passenger_file_exists(char *path)
{
    bool result = false;
    return result;
}

bool flight_file_exists(char *path)
{
    bool result = false;
    return result;
}

bool files_exist(char *path)
{
    bool result = false;
    if (flight_file_exists(path) && passenger_file_exists(path) && reservation_file_exists(path) && user_file_exists(path))
        result = true;
    return result;
}

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
        else
        {
            printf("\033[1;32m");
            printf("\n\nO diretório %s existe!\n\n", dataset_path);
            printf("\033[0m");
            if (files_exist(dataset_path))
            {
                printf("\033[1;32m");
                printf("\n\nTodos os ficheiros foram encontrados!\n\n");
                printf("\033[0m");
            }
            else
            {
                printf("\033[1;31m");
                printf("\n\nErro! Não foi possível encontrar todos os ficheiros no diretório %s!\n\n", dataset_path);
                printf("\033[0m");
            }
        }
    }
}