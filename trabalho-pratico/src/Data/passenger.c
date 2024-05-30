#include "../../include/passenger.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <glib-2.0/glib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <locale.h>


struct Passenger
{
    char *passenger_id;
    char *flight_id;
    char *user_id;
};

struct Passenger* create_passenger(){
    Passenger *new_passenger = malloc(sizeof(Passenger));
    new_passenger->passenger_id = NULL;
    new_passenger->flight_id = NULL;
    new_passenger->user_id = NULL;
    return new_passenger;
}

/**
 * @brief This function is responsible for returning the passenger id.
 *
 * @param p Pointer to the passenger.
 *
 * @return char*.
 */
char *get_passenger_id(Passenger *p)
{
    char *passenger_id = strdup(p->passenger_id);
    return passenger_id;
}

char *get_real_passenger_id(Passenger *p){
    return p->passenger_id;

}

/**
 * @brief This function is responsible for setting the passenger id.
 *
 * @param p Pointer to the passenger.
 * @param passenger_id Pointer to the new passenger id.
 *
 * @return void.
 */
void set_passenger_id(Passenger *p, char *passenger_id)
{
    if (p)
    {
        p->passenger_id = strdup(passenger_id);
    }
}

void setup_passenger_id(Passenger *p, size_t size_f, size_t size_u){
    p->passenger_id = malloc(size_f + size_u + 2);

}

/**
 * @brief This function is responsible for returning the passenger flight id.
 *
 * @param p Pointer to the passenger.
 *
 * @return char*.
 */
char *get_passenger_flight_id(Passenger *p)
{
    char *flight_id = strdup(p->flight_id);
    return flight_id;
}

/**
 * @brief This function is responsible for setting the passenger flight id.
 *
 * @param p Pointer to the passenger.
 * @param flight_id Pointer to the new flight id.
 *
 * @return void.
 */
void set_passenger_flight_id(Passenger *p, char *flight_id)
{
    if (p)
    {
        p->flight_id = strdup(flight_id);
    }
}

/**
 * @brief This function is responsible for returning the passenger user id.
 *
 * @param p Pointer to the passenger.
 *
 * @return char*.
 */
char *get_passenger_user_id(Passenger *p)
{
    char *user_id = strdup(p->user_id);
    return user_id;
}

char *get_real_passenger_user_id(Passenger *p){
    return p->user_id;
}

/**
 * @brief This function is responsible for setting the passenger user id.
 *
 * @param p Pointer to the passenger.
 * @param user_id Pointer to the new user id.
 *
 * @return void.
 */
void set_passenger_user_id(Passenger *p, char *user_id)
{
    if (p)
    {
        p->user_id = strdup(user_id);
    }
}

/**
 * @brief This function is responsible for freeing the passenger.
 *
 * @param p Pointer to the passenger.
 *
 * @return void.
 */
void free_passenger(Passenger *p)
{
    if (p)
    {
        free(p->flight_id);
        free(p->passenger_id);
        free(p->user_id);
        free(p);
    }
}

/**
 * @brief This function is responsible for printing the passenger.
 *
 * @param p Pointer to the passenger.
 *
 * @return void.
 */
void print_passenger(Passenger *p)
{
    printf("\nPassenger_id: %s\n", get_passenger_id(p));
    printf("Flight_id: %s\n", get_passenger_flight_id(p));
    printf("User_id: %s\n", get_passenger_user_id(p));
}