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
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


char *strtok_empty(char *str, const char *delim) {
    static char *next_token = NULL;
    if (str != NULL) {
        next_token = str;
    }
    if (next_token == NULL) {
        return NULL;
    }
    char *token = next_token;
    next_token = strpbrk(next_token, delim);
    if (next_token != NULL) {
        *next_token++ = '\0';
    }
    return token;
}

char *strtok_r_empty(char *str, const char *delim, char **saveptr) {
    if (str != NULL) {
        *saveptr = str;
    }
    if (*saveptr == NULL) {
        return NULL;
    }
    char *token = *saveptr;
    *saveptr = strpbrk(*saveptr, delim);
    if (*saveptr != NULL) {
        *(*saveptr)++ = '\0';
    }
    return token;
}

/**
 * @brief This function is responsible for storing a Flight's info, which is taken from
 * a csv file, in a hashtable.
 *
 * @param line Pointer to the line.
 * @param cat_flights Pointer to the catologo.
 *
 * @return void.
 */

void parse_flight_line2(char *line, catalogo_Flights *cat_flights)
{
    char *saveptr;
    const int MAX_TOKENS = 13; 
    char *tokens[MAX_TOKENS]; 
    int token_count = 0;

    char *token = strtok_r(line, ";", &saveptr);

    while (token != NULL && token_count < MAX_TOKENS)
    {
        tokens[token_count] = strdup(token); 
        token = strtok_r(NULL, ";", &saveptr);
        token_count++;
    }


    if (token_count < MAX_TOKENS)
    {
        printf("Insufficient fields in the line.\n");
        for (int i = 0; i < token_count; i++)
        {
            free(tokens[i]); 
        }
        return;
    }

    tokenize_flight(tokens, cat_flights);

    for (int i = 0; i < token_count; i++)
    {
        free(tokens[i]);
    }

}

void parse_passenger_line2(char *line, catalogo_Passengers *cat_passengers,catalogo_Flights *cat_flights, catalogo_Users *cat_users)
{
    char *saveptr;
    const int MAX_TOKENS = 2; 
    char *tokens[MAX_TOKENS]; 
    int token_count = 0;

    char *token = strtok_r(line, ";", &saveptr);

    while (token != NULL && token_count < MAX_TOKENS)
    {
        tokens[token_count] = strdup(token); 
        token = strtok_r(NULL, ";", &saveptr);
        token_count++;
    }


    if (token_count < MAX_TOKENS)
    {
        printf("Insufficient fields in the line.\n");
        for (int i = 0; i < token_count; i++)
        {
            free(tokens[i]); 
        }
        return;
    }

    tokenize_passenger(tokens,cat_passengers,cat_flights,cat_users);

    for (int i = 0; i < token_count; i++)
    {
        free(tokens[i]);
    }

}

void parse_reservation_line2(char *line, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users)
{
    char *saveptr;
    const int MAX_TOKENS = 14; 
    char *tokens[MAX_TOKENS]; 
    int token_count = 0;

    char *token = strtok_r_empty(line, ";", &saveptr);

    while (token != NULL && token_count < MAX_TOKENS)
    {
        tokens[token_count] = strdup(token); 
        token = strtok_r_empty(NULL, ";", &saveptr);
        token_count++;
    }


    if (token_count < MAX_TOKENS)
    {
        printf("Insufficient fields in the line.\n%d\n",token_count);
        for (int i = 0; i < token_count; i++)
        {
            free(tokens[i]); 
        }
        return;
    }

    tokenize_reservation(tokens,cat_reservations,cat_users);

    for (int i = 0; i < token_count; i++)
    {
        free(tokens[i]);
    }

}


void parse_user_line2(char *line, catalogo_Users *cat_users)
{
    char *saveptr;
    const int MAX_TOKENS = 12; 
    char *tokens[MAX_TOKENS]; 
    int token_count = 0;

    char *token = strtok_r(line, ";", &saveptr);

    while (token != NULL && token_count < MAX_TOKENS)
    {
        tokens[token_count] = strdup(token); 
        token = strtok_r(NULL, ";", &saveptr);
        token_count++;
    }


    if (token_count < MAX_TOKENS)
    {
        printf("Insufficient fields in the line.\n%d\n",token_count);
        for (int i = 0; i < token_count; i++)
        {
            free(tokens[i]); 
        }
        return;
    }

    tokenize_user(tokens,cat_users);

    for (int i = 0; i < token_count; i++)
    {
        free(tokens[i]);
    }

}



