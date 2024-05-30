#include "../../include/reservation.h"
#include "../../include/gestorReservations.h"
#include "../../include/gestor.h"
#include <glib-2.0/glib.h>
#include <stdio.h>

struct catalogo_reservations
{
    GHashTable *table_reservations;
};
typedef struct catalogo_reservations catalogo_Reservations;

/**
 * @brief This function is responsible for initializing the reservations catalog.
 *
 * @return catalogo_Reservations*.
 */
catalogo_Reservations *init_catalogo_reservations()
{
    catalogo_Reservations *new_cat_reservations = malloc(sizeof(catalogo_Reservations));
    new_cat_reservations->table_reservations = new_hashtable();
    return new_cat_reservations;
}

/**
 * @brief This function is responsible for getting a reservation table.
 *
 * @param cat_reservations Pointer to the catalog.
 *
 * @return GHashTable*.
 */
GHashTable *get_table_reservations(catalogo_Reservations *cat_reservations)
{
    return cat_reservations->table_reservations;
}

/**
 * @brief This function is responsible for setting the reservation table.
 *
 * @param cat_reservations Pointer to the catalog.
 * @param table_reservations Pointer to the new table.
 *
 * @return void.
 */
void set_table_reservations(catalogo_Reservations *cat_reservations, GHashTable *table_reservations)
{
    cat_reservations->table_reservations = table_reservations;
}

/**
 * @brief This function is responsible for printing a reservation pair key.
 *
 * @param gpointer key The key of the reservation.
 * @param gpointer value The value of the reservation.
 *
 * @return void.
 */
void print_reservation_pair_key(gpointer key, gpointer value)
{
    printf("Key: %s\n", (char *)key);
    print_reservation((Reservation *)value);
    printf("\n");
}

/**
 * @brief This function is responsible for freeing a reservation.
 *
 * @param gpointer key The key of the reservation.
 * @param gpointer value The value of the reservation.
 *
 * @return void.
 */
void free_reservations_value(gpointer key, gpointer value)
{
    Reservation *reservation = (Reservation *)value;
    free_reservation(reservation);
}

/**
 * @brief This function is responsible for freeing the reservations catalog.
 *
 * @param cat_reservations Pointer to the catalog.
 *
 * @return void.
 */
void free_catalogo_reservations(catalogo_Reservations *cat_reservations)
{
    g_hash_table_foreach(cat_reservations->table_reservations, (GHFunc)free_reservations_value, NULL);
    g_hash_table_destroy(cat_reservations->table_reservations);
    free(cat_reservations);
}

/**
 * @brief This function is responsible for printing the reservations catalog.
 *
 * @param cat_reservations Pointer to the catalog.
 *
 * @return void.
 */
void print_catalogo_reservations(catalogo_Reservations *cat_reservations)
{
    g_hash_table_foreach(cat_reservations->table_reservations, (GHFunc)print_reservation_pair_key, NULL);
}
