#include "../include/batch.h"
#include "../include/validation.h"
#include "../include/hashtables.h"
#include "../include/flight.h"
#include "../include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <string.h>

bool users_file_exists(const char *path)
{
    bool result = false;
    char file_path[256];
    snprintf(file_path, sizeof(file_path), "%susers.csv", path);
    FILE *fp = fopen(file_path, "r");
    if (fp)
    {
        fclose(fp);
        result = true;
    }
    return result;
}

bool reservations_file_exists(const char *path)
{
    bool result = false;
    char file_path[256];
    snprintf(file_path, sizeof(file_path), "%sreservations.csv", path);
    FILE *fp = fopen(file_path, "r");
    if (fp)
    {
        fclose(fp);
        result = true;
    }
    return result;
}

bool passengers_file_exists(const char *path)
{
    bool result = false;
    char file_path[256];
    snprintf(file_path, sizeof(file_path), "%spassengers.csv", path);
    FILE *fp = fopen(file_path, "r");
    if (fp)
    {
        fclose(fp);
        result = true;
    }
    return result;
}

bool flights_file_exists(const char *path)
{
    bool result = false;
    char file_path[256];
    snprintf(file_path, sizeof(file_path), "%sflights.csv", path);
    FILE *fp = fopen(file_path, "r");
    if (fp)
    {
        fclose(fp);
        result = true;
    }
    return result;
}

bool files_exist(char *path)
{
    bool result = false;
    if (flights_file_exists(path) && passengers_file_exists(path) && reservations_file_exists(path) && users_file_exists(path))
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
        if (dataset_path[strlen(dataset_path) - 1] != '/')
        {
            strcat(dataset_path, "/");
        }
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
                limpar_dados_invalidos(dataset_path);
                catalogo_Flights *cat_flights = init_catalogo_flights();
                cat_flights->table_flights = new_hashtable();
                parse_flights("Valid", cat_flights);
                print_catalogo_flights(cat_flights);
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