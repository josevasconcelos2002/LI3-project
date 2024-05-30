#ifndef GESTORPASSENGERS_H
#define GESTORPASSENGERS_H
#include <glib-2.0/glib.h>
#include "passenger.h"
#include <stdio.h>

typedef struct catalogo_passengers catalogo_Passengers;

catalogo_Passengers *init_catalogo_passengers();
GHashTable *get_table_passengers(catalogo_Passengers *cat_passengers);
void set_table_passengers(catalogo_Passengers *cat_passengers, GHashTable *table_passengers);
void print_passenger_pair_key(gpointer key, gpointer value);
void free_passengers_value(gpointer key, gpointer value);
void free_catalogo_passengers(catalogo_Passengers *cat_passengers);
// GHashTable *new_hash_table();

#endif