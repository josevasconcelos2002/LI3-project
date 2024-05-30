#ifndef GESTORRESERVATIONS_H
#define GESTORRESERVATIONS_H
#include <glib-2.0/glib.h>
#include "reservation.h"
#include <stdio.h>

typedef struct catalogo_reservations catalogo_Reservations;

catalogo_Reservations *init_catalogo_reservations();
GHashTable *get_table_reservations(catalogo_Reservations *cat_reservations);
void set_table_reservations(catalogo_Reservations *cat_reservations, GHashTable *table_reservations);
void print_reservation_pair_key(gpointer key, gpointer value);
void free_reservations_value(gpointer key, gpointer value);
void free_catalogo_reservations(catalogo_Reservations *cat_reservations);
GHashTable *get_table_reservations(catalogo_Reservations *cat_reservations);

#endif