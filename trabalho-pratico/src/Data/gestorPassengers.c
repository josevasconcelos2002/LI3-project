#include "../../include/passenger.h"
#include "../../include/gestorPassengers.h"
#include "../../include/gestor.h"
#include <glib-2.0/glib.h>
#include <stdio.h>

struct catalogo_passengers
{
    GHashTable *table_passengers;
};
typedef struct catalogo_passengers catalogo_Passengers;

/**
 * @brief This function is responsible for initializing the passengers catalog.
 *
 * @return catalogo_Passengers*.
 */
catalogo_Passengers *init_catalogo_passengers()
{
    catalogo_Passengers *new_cat_passengers = malloc(sizeof(catalogo_Passengers));
    new_cat_passengers->table_passengers = new_hashtable();
    return new_cat_passengers;
}

/**
 * @brief This function is responsible for printing a passenger pair key.
 *
 * @param gpointer key The key of the passenger.
 * @param gpointer value The value of the passenger.
 *
 * @return void.
 */
void print_passenger_pair_key(gpointer key, gpointer value)
{
    printf("Key: %s\n", (char *)key);
    print_passenger((Passenger *)value);
    printf("\n");
}

/**
 * @brief This function is responsible for freeing a passenger.
 *
 * @param gpointer key The key of the passenger.
 * @param gpointer value The value of the passenger.
 *
 * @return void.
 */
void free_passengers_value(gpointer key, gpointer value)
{
    Passenger *passenger = (Passenger *)value;
    free_passenger(passenger);
}

/**
 * @brief This function is responsible for freeing the passengers catalog.
 *
 * @param cat_passengers Pointer to the passengers catalog.
 *
 * @return void.
 */
void free_catalogo_passengers(catalogo_Passengers *cat_passengers)
{
    if (cat_passengers->table_passengers)
    {
        g_hash_table_foreach(cat_passengers->table_passengers, (GHFunc)free_passengers_value, NULL);
        g_hash_table_destroy(cat_passengers->table_passengers);
    }
    free(cat_passengers);
}

/**
 * @brief This function is responsible for returning the passengers table.
 *
 * @param cat_passengers Pointer to the passengers catalog.
 *
 * @return GHashTable*.
 */
GHashTable *get_table_passengers(catalogo_Passengers *cat_passengers)
{
    return cat_passengers->table_passengers;
}

/**
 * @brief This function is responsible for setting the passengers table.
 *
 * @param cat_passengers Pointer to the passengers catalog.
 * @param table_passengers Pointer to the new table.
 *
 * @return void.
 */
void set_table_passengers(catalogo_Passengers *cat_passengers, GHashTable *table_passengers)
{
    cat_passengers->table_passengers = table_passengers;
}
