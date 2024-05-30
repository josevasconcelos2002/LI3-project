#include "../include/batch.h"
#include "../include/validation.h"
#include "../include/parser.h"
#include "../include/gestorFlights.h"
#include "../include/gestorPassengers.h"
#include "../include/gestorReservations.h"
#include "../include/gestorUsers.h"
#include "../include/reservation.h"
#include "../include/user.h"
#include "../include/passenger.h"
#include "../include/flight.h"
#include "../include/parserqueries.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

/**
 * @brief This function is responsible for checking if a file exists.
 *
 * @param path Pointer to the path.
 *
 * @return bool.
 */
bool file_exist(const char *path)
{
    bool result = false;
    FILE *fp = fopen(path, "r");
    if (fp)
    {
        fclose(fp);
        result = true;
    }
    return result;
}

/**
 * @brief This function is responsible for checking if a folder exists.
 *
 * @param path Pointer to the path.
 *
 * @return bool.
 */
bool folderExists(char *path)
{
    bool result = false;
    DIR *dir = opendir(path);
    if (dir)
        result = true;
    return result;
}

/**
 * @brief This function is responsible for finding a csv file.
 *
 * @param dir_path Pointer to the path.
 *
 * @return bool.
 */
bool find_csv(char *dir_path, char *name)
{
    DIR *dir = opendir(dir_path);
    struct dirent *ent;
    char *csv_path = NULL;

    if (dir != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (strcmp(ent->d_name, name) == 0)
            {
                csv_path = strdup(ent->d_name);
                if (csv_path == NULL)
                {
                    closedir(dir);
                    return "\033[31mError: Memory allocation failed.\033[0m";
                }
                break;
            }
        }
        closedir(dir);
    }
    else
    {
        return "\033[31mError: Could not open directory.\033[0m";
    }

    if (csv_path)
    {
        char *full_path;
        full_path = calloc(strlen(dir_path) + strlen(csv_path) + 2, sizeof(char));
        if (full_path == NULL)
        {
            free(csv_path);
            return "\033[31mError: Memory allocation failed.\033[0m";
        }
        snprintf(full_path, strlen(dir_path) + strlen(csv_path) + 2, "%s/%s", dir_path, csv_path);
        printf("\n\033[32mFile found:\033[0m %s\n", full_path);
        free(csv_path);
        free(full_path);
        return true;
    }
    else
    {
        printf("\033[31mError: No file with the given name found in directory.\033[0m\n");
        return false;
    }
}

/**
 * @brief This function is responsible for running the batch mode.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 *
 * @return void
 */
void batch(int argc, char **argv)
{
    // sabemos que já recebemos 3 argumentos, argv[]
    for (int i = 0; i < 3; i++)
    {
        printf("argv[%d] -> %s\n", i, argv[i]);
    }
    char *dataset_path = argv[1];
    char *input_path = strdup(argv[2]);

    if (!file_exist(input_path))
    {
        printf("\033[1;31m");
        printf("\n\nErro! Ficheiro %s não existe!\n\n", input_path);
        printf("\033[0m");
        return;
    }

    bool flight_csv = find_csv(dataset_path, "flights.csv");
    bool passengers_csv = find_csv(dataset_path, "passengers.csv");
    bool reservations_csv = find_csv(dataset_path, "reservations.csv");
    bool users_csv = find_csv(dataset_path, "users.csv");

    if (dataset_path[strlen(dataset_path) - 1] != '/')
    {
        strcat(dataset_path, "/");
    }

    if (flight_csv && passengers_csv && reservations_csv && users_csv)
    {
        clock_t start, end;
        double cpu_time_used;
        start = clock();
        printf("\033[1;32m");
        printf("\n\nTodos os ficheiros foram encontrados!\n\n");
        printf("\033[0m");
        catalogo_Flights *cat_flights = init_catalogo_flights();
        catalogo_Passengers *cat_passengers = init_catalogo_passengers();
        catalogo_Reservations *cat_reservations = init_catalogo_reservations();
        catalogo_Users *cat_users = init_catalogo_users();
        limpar_dados_validos(dataset_path, cat_flights, cat_passengers, cat_reservations, cat_users);
        parse_queries(input_path, cat_flights, cat_passengers, cat_reservations, cat_users);
        free_catalogo_flights(cat_flights);
        free_catalogo_reservations(cat_reservations);
        free_catalogo_passengers(cat_passengers);
        free_catalogo_users(cat_users);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Execution time: %f seconds\n", cpu_time_used);
    }
    else
    {
        printf("\033[1;31m");
        printf("\n\nErro! Não foi possível encontrar todos os ficheiros no diretório %s!\n\n", dataset_path);
        printf("\033[0m");
    }
    free(input_path);
}
