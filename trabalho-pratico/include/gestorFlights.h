#ifndef GESTORFLIGHTS_H
#define GESTORFLIGHTS_H

#include "flight.h"
#include <stdio.h>
#include <glib-2.0/glib.h>

typedef struct catalogo_flights catalogo_Flights;

catalogo_Flights *init_catalogo_flights();
GHashTable *get_table_flights(catalogo_Flights *cat_flights);
void set_table_flights(catalogo_Flights *cat_flights, GHashTable *table_flights);
void print_flight_pair_key(gpointer key, gpointer value);
void print_catalogo_flights(catalogo_Flights *cat_flights);
void print_Flight(Flight flight);
void free_flights_value(gpointer key, gpointer value);
void free_catalogo_flights(catalogo_Flights *cat_flights);

#endif // GESTORFLIGHTS_H