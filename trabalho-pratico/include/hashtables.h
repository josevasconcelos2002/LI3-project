#ifndef HASHTABLES_H
#define HASHTABLES_H

#include <glib-2.0/glib.h>

typedef struct catalogo_flights catalogo_Flights;

typedef struct catalogo_passengers catalogo_Passengers;

typedef struct catalogo_reservations catalogo_Reservations;

typedef struct catalogo_users catalogo_Users;

const GHashTable *get_table_flights(const catalogo_Flights *cat_flights);

const GHashTable *get_table_passengers(const catalogo_Passengers *cat_passengers);

const GHashTable *get_table_reservations(const catalogo_Reservations *cat_reservations);

const GHashTable *get_table_users(const catalogo_Users *cat_users);

#endif