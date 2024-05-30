#include "../../include/validation.h"
#include "../../include/parser.h"
#include "../../include/gestor.h"
#include "../../include/gestorFlights.h"
#include "../../include/gestorPassengers.h"
#include "../../include/gestorReservations.h"
#include "../../include/gestorUsers.h"
#include "../../include/flight.h"
#include "../../include/passenger.h"
#include "../../include/reservation.h"
#include "../../include/user.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <glib-2.0/glib.h>
#include <stdio.h>
#include <locale.h>
#define DATA "2023/10/01"

/**
 * @brief This function is responsible for solving query 1.
 *
 * @param id Pointer to the user id.
 * @param cat_reservations Pointer to the reservations catalog.
 * @param cat_users Pointer to the users catalog.
 * @param cat_flights Pointer to the flights catalog.
 * @param cat_passengers Pointer to the passengers catalog.
 * @param output_file Pointer to the output file.
 *
 * @return void.
 */
void query1(char *id, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users, catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, FILE *output_file)
{
    get_info(id, cat_reservations, cat_users, cat_flights, cat_passengers, output_file);
}

/**
 * @brief This function is responsible for solving query 1 format.
 *
 * @param id Pointer to the user id.
 * @param cat_reservations Pointer to the reservations catalog.
 * @param cat_users Pointer to the users catalog.
 * @param cat_flights Pointer to the flights catalog.
 * @param cat_passengers Pointer to the passengers catalog.
 * @param output_file Pointer to the output file.
 *
 * @return void.
 */
void query1_format(char *id, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users, catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, FILE *output_file)
{
    get_info_format(id, cat_reservations, cat_users, cat_flights, cat_passengers, output_file);
}

/**
 * @brief This function is responsible for solving query 2.
 *
 * @param type Pointer to the type.
 * @param id2 Pointer to the id.
 * @param cat_reservations Pointer to the reservations catalog.
 * @param cat_users Pointer to the users catalog.
 * @param cat_flights Pointer to the flights catalog.
 * @param cat_passengers Pointer to the passengers catalog.
 * @param output_file2 Pointer to the output file.
 *
 * @return void.
 */
void query2(char *type, char *id2, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users, catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, FILE *output_file2)
{
    if (type != NULL && (strcmp(type, "reservations") == 0 || strcmp(type, "flights") == 0))
    {
        list_user_flights_or_reservations2(id2, type, output_file2, cat_reservations, cat_flights, cat_passengers, cat_users);
    }
    else
    {
        list_user_flights_or_reservations2(id2, NULL, output_file2, cat_reservations, cat_flights, cat_passengers, cat_users);
    }
}

/**
 * @brief This function is responsible for solving query 2 format.
 *
 * @param type Pointer to the type.
 * @param id2 Pointer to the id.
 * @param cat_reservations Pointer to the reservations catalog.
 * @param cat_users Pointer to the users catalog.
 * @param cat_flights Pointer to the flights catalog.
 * @param cat_passengers Pointer to the passengers catalog.
 * @param output_file2 Pointer to the output file.
 *
 * @return void.
 */
void query2_format(char *type, char *id2, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users, catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, FILE *output_file2)
{
    if (type != NULL && (strcmp(type, "reservations") == 0 || strcmp(type, "flights") == 0))
    {
        list_user_flights_or_reservations2_format(id2, type, output_file2, cat_reservations, cat_flights, cat_passengers, cat_users);
    }
    else
    {
        list_user_flights_or_reservations2_format(id2, NULL, output_file2, cat_reservations, cat_flights, cat_passengers, cat_users);
    }
}
/**
 * @brief This function is responsible for solving query 3 format.
 *
 * @param id3 Pointer to the id.
 * @param cat_reservations Pointer to the reservations catalog.
 * @param output_file3 Pointer to the output file.
 *
 * @return void.
 */
void query3_format(char *id3, catalogo_Reservations *cat_reservations, FILE *output_file3)
{
    fprintf(output_file3, "--- 1 ---\n");
    fprintf(output_file3, "rating: %.3f\n", average_rating_by_hotel_id(get_table_reservations(cat_reservations), id3));
}

/**
 * @brief This function is responsible for solving query 3.
 *
 * @param id3 Pointer to the id.
 * @param cat_reservations Pointer to the reservations catalog.
 * @param output_file3 Pointer to the output file.
 *
 * @return void.
 */
void query3(char *id3, catalogo_Reservations *cat_reservations, FILE *output_file3)
{
    fprintf(output_file3, "%0.3f\n", average_rating_by_hotel_id(get_table_reservations(cat_reservations), id3));
}

/**
 * @brief This function is responsible for solving query 4 format.
 *
 * @param id4 Pointer to the id.
 * @param cat_reservations Pointer to the reservations catalog.
 * @param output_file4 Pointer to the output file.
 *
 * @return void.
 */
void query4_format(char *id4, catalogo_Reservations *cat_reservations, FILE *output_file4)
{
    print_reservations_by_hotel_id_format(id4, cat_reservations, output_file4);
}

/**
 * @brief This function is responsible for solving query 4.
 *
 * @param id4 Pointer to the id.
 * @param cat_reservations Pointer to the reservations catalog.
 * @param output_file4 Pointer to the output file.
 *
 * @return void.
 */
void query4(char *id4, catalogo_Reservations *cat_reservations, FILE *output_file4)
{
    print_reservations_by_hotel_id(id4, cat_reservations, output_file4);
}

/**
 * @brief This function is responsible for solving query 5 format.
 *
 * @param origin Pointer to the origin.
 * @param beg_date Pointer to the begin date.
 * @param end_date Pointer to the end date.
 * @param cat_flights Pointer to the flights catalog.
 * @param output_file5 Pointer to the output file.
 *
 * @return void.
 */
void query5_format(char *origin, char *beg_date, char *end_date, catalogo_Flights *cat_flights, FILE *output_file5)
{
    print_matching_flights_format(origin, beg_date, end_date, get_table_flights(cat_flights), output_file5);
}

/**
 * @brief This function is responsible for solving query 5.
 *
 * @param origin Pointer to the origin.
 * @param beg_date Pointer to the begin date.
 * @param end_date Pointer to the end date.
 * @param cat_flights Pointer to the flights catalog.
 * @param output_file5 Pointer to the output file.
 *
 * @return void.
 */
void query5(char *origin, char *beg_date, char *end_date, catalogo_Flights *cat_flights, FILE *output_file5)
{
    print_matching_flights(origin, beg_date, end_date, get_table_flights(cat_flights), output_file5);
}

void query6(char *year, char *n, catalogo_Flights *cat_flights, FILE *output_file6)
{
    print_airport(n, year, cat_flights, output_file6);
}

/**
 * @brief This function is responsible for solving query 7 format.
 *
 * @param id7 Pointer to the id.
 * @param cat_flights Pointer to the flights catalog.
 * @param output_file7 Pointer to the output file.
 *
 * @return void.
 */
void query7_format(char *id7, catalogo_Flights *cat_flights, FILE *output_file7)
{
    print_flights_by_delay_format(id7, cat_flights, output_file7);
}

/**
 * @brief This function is responsible for solving query 7.
 *
 * @param id7 Pointer to the id.
 * @param cat_flights Pointer to the flights catalog.
 * @param output_file7 Pointer to the output file.
 *
 * @return void.
 */
void query7(char *id7, catalogo_Flights *cat_flights, FILE *output_file7)
{
    print_flights_by_delay(id7, cat_flights, output_file7);
}

/**
 * @brief This function is responsible for solving query 8.
 *
 * @param id8 Pointer to the id.
 * @param begin_date Pointer to the begin date.
 * @param end_date Pointer to the end date.
 * @param cat_reservations Pointer to the reservations catalog.
 * @param output_file8 Pointer to the output file.
 *
 * @return void.
 */
void query8(char *id8, char *begin_date, char *end_date, catalogo_Reservations *cat_reservations, FILE *output_file8)
{
    get_hotel_revenue_between_dates(id8, begin_date, end_date, cat_reservations, output_file8);
}

/**
 * @brief This function is responsible for solving query 8 format.
 *
 * @param id8 Pointer to the id.
 * @param begin_date Pointer to the begin date.
 * @param end_date Pointer to the end date.
 * @param cat_reservations Pointer to the reservations catalog.
 * @param output_file8 Pointer to the output file.
 *
 * @return void.
 */
void query8_format(char *id8, char *begin_date, char *end_date, catalogo_Reservations *cat_reservations, FILE *output_file8)
{
    get_hotel_revenue_between_dates_format(id8, begin_date, end_date, cat_reservations, output_file8);
}

/**
 * @brief This function is responsible for solving query 9 format.
 *
 * @param prefix Pointer to the prefix.
 * @param cat_users Pointer to the users catalog.
 * @param output_file9 Pointer to the output file.
 *
 * @return void.
 */
void query9_format(char *prefix, catalogo_Users *cat_users, FILE *output_file9)
{
    list_users_by_name_prefix_format(prefix, cat_users, output_file9);
}

/**
 * @brief This function is responsible for solving query 9.
 *
 * @param prefix Pointer to the prefix.
 * @param cat_users Pointer to the users catalog.
 * @param output_file9 Pointer to the output file.
 *
 * @return void.
 */
void query9(char *prefix, catalogo_Users *cat_users, FILE *output_file9)
{

    list_users_by_name_prefix(prefix, cat_users, output_file9);
}

/**
 * @brief This function is responsible for parsing queries.
 *
 * @param file_name Pointer to the file name.
 * @param cat_flights Pointer to the flights catalog.
 * @param cat_passengers Pointer to the passengers catalog.
 * @param cat_reservations Pointer to the reservations catalog.
 * @param cat_users Pointer to the users catalog.
 *
 * @return void.
 */
void parse_queries(char *file_name, catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users)
{
    FILE *queries = fopen(file_name, "r");
    if (queries == NULL)
    {
        printf("The respective file is empty.\n");
        return;
    }

    char buffer[1024];
    int line = 0;
    int o = 0;

    while (fgets(buffer, 1024, queries))
    {
        char output_file_name[256];
        line++;
        o++;
        char *field = strtok(buffer, " ");
        // printf("field[0]: %s\n", &field[0]);
        int query = atoi(&field[0]);

        snprintf(output_file_name, sizeof(output_file_name), "Resultados/command%d_output.txt", o);

        switch (query)
        {
        case 1:
            FILE *output_file = fopen(output_file_name, "w");
            char *id = strtok(NULL, " ");
            id[strcspn(id, "\n")] = '\0';
            if (id == NULL)
            {
                printf("\nError: missing id\n");
                break;
            }
            if (strlen(field) == 2)
            {
                // query1 com format
                query1_format(id, cat_reservations, cat_users, cat_flights, cat_passengers, output_file);
            }
            else
                query1(id, cat_reservations, cat_users, cat_flights, cat_passengers, output_file);

            fclose(output_file);

            break;
        case 2:
            FILE *output_file2 = fopen(output_file_name, "w");
            char *id2 = strtok(NULL, " ");
            // printf("id2:%s.\n", id2);
            char *type = strtok(NULL, " ");
            // printf("type:%s.\n", type);
            id2[strcspn(id2, "\n")] = '\0';
            id2[strcspn(id2, "\t")] = '\0';
            if (type != NULL)
            {
                type[strcspn(type, "\n")] = '\0';
            }
            if (strlen(field) == 2)
                query2_format(type, id2, cat_reservations, cat_users, cat_flights, cat_passengers, output_file2);
            else
                query2(type, id2, cat_reservations, cat_users, cat_flights, cat_passengers, output_file2);

            fclose(output_file2);
            break;
        case 3:
            FILE *output_file3 = fopen(output_file_name, "w");
            char *id3 = strtok(NULL, " ");
            id3[strcspn(id3, "\n")] = '\0';
            id3[strcspn(id3, "\t")] = '\0';
            if (!id3)
            {
                printf("\nError: missing id\n");
                break;
            }
            if (strlen(field) == 2)
                query3_format(id3, cat_reservations, output_file3);
            else
                query3(id3, cat_reservations, output_file3);

            fclose(output_file3);
            break;
        case 4:
            FILE *output_file4 = fopen(output_file_name, "w");
            char *id4 = strtok(NULL, " ");
            id4[strcspn(id4, "\n")] = '\0';
            if (!id4)
            {
                printf("\nError: missing hotel_id\n");
                break;
            }
            if (strlen(field) == 2)
                query4_format(id4, cat_reservations, output_file4);
            else
                query4(id4, cat_reservations, output_file4);

            fclose(output_file4);
            break;
        case 5:
            FILE *output_file5 = fopen(output_file_name, "w");
            char *origin = strtok(NULL, " \"");
            char *beg_date = strtok(NULL, "\"");
            char *end_date = strtok(NULL, "\"");
            end_date = strtok(NULL, "\"");
            if (origin == NULL || beg_date == NULL || end_date == NULL)
            {
                printf("\nError: missing origin, beg_date or end_date\n");
                break;
            }
            if (strlen(field) == 2)
                query5_format(origin, beg_date, end_date, cat_flights, output_file5);
            else
                query5(origin, beg_date, end_date, cat_flights, output_file5);

            fclose(output_file5);
            break;
        case 6:
            FILE *output_file6 = fopen(output_file_name, "w");
            char *year = strtok(NULL, " ");
            char *n = strtok(NULL, " ");
            year[strcspn(year, "\n")] = '\0';
            n[strcspn(n, "\n")] = '\0';
            if (!year || !n)
            {
                printf("\nError: missing year or n\n");
                break;
            }
            query6(year, n, cat_flights, output_file6);

            fclose(output_file6);
            break;
        case 7:
            FILE *output_file7 = fopen(output_file_name, "w");
            char *id7 = strtok(NULL, " ");
            id7[strcspn(id7, "\n")] = '\0';
            id7[strcspn(id7, "\t")] = '\0';
            if (!id7)
            {
                printf("\nError: missing id\n");
                break;
            }
            if (strlen(field) == 2)
                query7_format(id7, cat_flights, output_file7);
            else
                query7(id7, cat_flights, output_file7);

            fclose(output_file7);
            break;
        case 8:
            FILE *output_file8 = fopen(output_file_name, "w");
            char *id8 = strtok(NULL, " ");
            id8[strcspn(id8, "\n")] = '\0';
            char *begin_date1 = strtok(NULL, " ");
            begin_date1[strcspn(begin_date1, "\n")] = '\0';
            char *end_date1 = strtok(NULL, " ");
            end_date1[strcspn(end_date1, "\n")] = '\0';
            if (!id8 || !begin_date1 || !end_date1)
            {
                printf("\nError: missing id, or begin_date or end_date\n");
            }
            if (strlen(field) == 2)
            {
                query8_format(id8, begin_date1, end_date1, cat_reservations, output_file8);
            }
            else
            {
                query8(id8, begin_date1, end_date1, cat_reservations, output_file8);
            }
            fclose(output_file8);
            break;
        case 9:
            FILE *output_file9 = fopen(output_file_name, "w");
            char *prefix = strtok(NULL, "");
            prefix[strcspn(prefix, "\n")] = '\0';
            if (!prefix)
            {
                printf("\nError: missing prefix\n");
                break;
            }
            if (strlen(field) == 2)
                query9_format(prefix, cat_users, output_file9);
            else
                query9(prefix, cat_users, output_file9);
            fclose(output_file9);
            break;
        case 10:
            // ...
            printf("Line: %d\n", line);
            printf("\033[31mQuery10 not yet implemented\033[0m\n\n");
            break;
        default:
            break;
        }
    }
    fclose(queries);
}
