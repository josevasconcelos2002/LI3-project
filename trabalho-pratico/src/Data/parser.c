#include "../../include/parser.h"
#include "../../include/hashtables.h"
#include "../../include/flight.h"
#include <string.h>

/**
 * @brief This function is responsible for storing every Flight's info, which is taken from
 * a csv file, in a hashtable.
 *
 * @param file_name Path of the Valid folder.
 * @param catalogo_flights Pointer to the catologo.
 *
 * @return void.
 */
void parse_flights(const char *path, catalogo_Flights *cat_flights)
{
    if (path[strlen(path) - 1] != '/')
    {
        strcat(path, "/");
    }
    char file_path[256];
    snprintf(file_path, sizeof(file_path), "%sflights-valid.csv", path);
    FILE *fp = fopen(file_path, "r");
    if (!fp)
    {
        printf("Unable to open the Flight's file.\n");
        return;
    }

    char buffer[1024];
    int row_count = 0;

    while (fgets(buffer, 1024, fp))
    {
        row_count++;
        if (row_count <= 1)
            continue;

        Flight *f = malloc(sizeof(Flight));
        if (!f)
        {
            printf("Memory allocation failed for Flight.\n");
            continue;
        }

        int field_count = 0;
        int buffer_index = 0;
        char field[1024];
        int field_index = 0;
        while (buffer[buffer_index] != '\0')
        {
            if (buffer[buffer_index] == ';' || buffer[buffer_index] == '\n')
            {
                field[field_index] = '\0';
                switch (field_count)
                {
                case 0:
                    f->id = atoi(field);
                    break;
                case 1:
                    f->airline = strdup(field);
                    break;
                case 2:
                    f->plane_model = strdup(field);
                    break;
                case 3:
                    f->total_seats = atoi(field);
                    break;
                case 4:
                    f->origin = strdup(field);
                    break;
                case 5:
                    f->destination = strdup(field);
                    break;
                case 6:
                    f->schedule_departure_date = strdup(field);
                    break;
                case 7:
                    f->schedule_arrival_date = strdup(field);
                    break;
                case 8:
                    f->real_departure_date = strdup(field);
                    break;
                case 9:
                    f->real_arrival_date = strdup(field);
                    break;
                case 10:
                    f->pilot = strdup(field);
                    break;
                case 11:
                    f->copilot = strdup(field);
                    break;
                case 12:
                    f->notes = strdup(field);
                    break;
                }

                field_count++;
                field_index = 0;
            }
            else
            {
                field[field_index] = buffer[buffer_index];
                field_index++;
            }
            buffer_index++;
        }

        Flight *existing_flight = g_hash_table_lookup(get_table_flights(cat_flights), f->id);
        if (existing_flight)
        {
            printf("Flight with id %s already exists. Skipping...\n", f->id);
            free_flight(f);
            continue;
        }
        else
            g_hash_table_insert(get_table_flights(cat_flights), f->id, f);
    }
    fclose(fp);
}