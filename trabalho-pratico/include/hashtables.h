#ifndef HASHTABLES_H
#define HASHTABLES_H

#include <glib-2.0/glib.h>

typedef struct catalogo_flights catalogo_Flights;

typedef struct catalogo_passengers catalogo_Passengers;

typedef struct catalogo_reservations catalogo_Reservations;

typedef struct catalogo_users catalogo_Users;

catalogo_Flights *init_catalogo_flights();

catalogo_Passengers *init_catalogo_passengers();

catalogo_Reservations *init_catalogo_reservations();

catalogo_Users *init_catalogo_users();

void free_catalogo_flights(catalogo_Flights *cat_flights);

void free_catalogo_passengers(catalogo_Passengers *cat_passengers);

void free_catalogo_reservations(catalogo_Reservations *cat_reservations);

void free_catalogo_users(catalogo_Users *cat_users);

const GHashTable *get_table_flights(const catalogo_Flights *cat_flights);

const GHashTable *get_table_passengers(const catalogo_Passengers *cat_passengers);

const GHashTable *get_table_reservations(const catalogo_Reservations *cat_reservations);

const GHashTable *get_table_users(const catalogo_Users *cat_users);

#endif