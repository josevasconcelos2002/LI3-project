#include "../../include/flight.h"
#include "../../include/gestorFlights.h"
#include "../../include/gestor.h"
#include <glib-2.0/glib.h>
#include <stdio.h>

struct catalogo_flights
{
    GHashTable *table_flights;
};
typedef struct catalogo_flights catalogo_Flights;

/**
 * @brief This function is responsible for initializing the flights catalog.
 *
 * @return catalogo_Flights*
 */
catalogo_Flights *init_catalogo_flights()
{
    catalogo_Flights *new_cat_flights = malloc(sizeof(catalogo_Flights));
    new_cat_flights->table_flights = new_hashtable();
    return new_cat_flights;
}

/**
 * @brief This function is responsible for printing a flight.
 *
 * @param gpointer key The key of the flight.
 * @param gpointer value The value of the flight.
 *
 * @return void.
 */
void print_flight_pair_key(gpointer key, gpointer value)
{
    printf("Key: %s\n", (char *)key);
    print_flight((Flight *)value);
    printf("\n");
}

/**
 * @brief This function is responsible for freeing the flight.
 *
 * @param gpointer key The key of the flight.
 * @param gpointer value The value of the flight.
 *
 * @return void.
 */
void free_flights_value(gpointer key, gpointer value)
{
    Flight *flight = (Flight *)value;
    free_flight(flight);
}

/**
 * @brief This function is responsible for getting the flight catalog.
 *
 * @param cat_flights Pointer to the catalog.
 *
 * @return GHashTable*.
 */
GHashTable *get_table_flights(catalogo_Flights *cat_flights)
{
    return cat_flights->table_flights;
}

/**
 * @brief This function is responsible for inserting a new flight into the catalog.
 *
 * @param cat_flights Pointer to the catalog.
 * @param flight Pointer to the new flight table.
 *
 * @return void.
 */
void set_table_flights(catalogo_Flights *cat_flights, GHashTable *table_flights)
{
    cat_flights->table_flights = table_flights;
}

/**
 * @brief This function is responsible for printing the catalog.
 *
 * @param cat_flights Pointer to the catalog.
 *
 * @return void.
 */
void print_catalogo_flights(catalogo_Flights *cat_flights)
{
    g_hash_table_foreach(cat_flights->table_flights, (GHFunc)print_flight_pair_key, NULL);
}

/**
 * @brief This function is responsible for freeing the flightscatalog.
 *
 * @param cat_flights Pointer to the catalog.
 *
 * @return void.
 */
void free_catalogo_flights(catalogo_Flights *cat_flights)
{
    if (cat_flights->table_flights)
    {
        g_hash_table_foreach(cat_flights->table_flights, (GHFunc)free_flights_value, NULL);
        g_hash_table_destroy(cat_flights->table_flights);
    }
    free(cat_flights);
}
