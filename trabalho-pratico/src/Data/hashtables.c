#include "../../include/hashtables.h"
#include "../../include/flight.h"
#include <glib-2.0/glib.h>
#include <stdio.h>

struct catalogo_passengers
{
    GHashTable *table_passengers;
};

struct catalogo_reservations
{
    GHashTable *table_reservations;
};

struct catalogo_users
{
    GHashTable *table_users;
};

catalogo_Flights *init_catalogo_flights()
{
    catalogo_Flights *new_cat_flights = malloc(sizeof(catalogo_Flights));
    return new_cat_flights;
}

catalogo_Passengers *init_catalogo_passengers()
{
    catalogo_Passengers *new_cat_passengers = malloc(sizeof(catalogo_Passengers));
    return new_cat_passengers;
}

catalogo_Reservations *init_catalogo_reservations()
{
    catalogo_Reservations *new_cat_reservations = malloc(sizeof(catalogo_Reservations));
    return new_cat_reservations;
}

catalogo_Users *init_catalogo_users()
{
    catalogo_Users *new_cat_users = malloc(sizeof(catalogo_Users));
    return new_cat_users;
}

void free_flights_value(gpointer key, gpointer value)
{
    Flight *flight = (Flight *)value;

    free(get_flight_airline(flight));
    free(get_flight_plane_model(flight));
    free(get_flight_origin(flight));
    free(get_flight_destination(flight));
    free(get_flight_schedule_departure_date(flight));
    free(get_flight_schedule_arrival_date(flight));
    free(get_flight_real_departure_date(flight));
    free(get_flight_real_arrival_date(flight));
    free(get_flight_pilot(flight));
    free(get_flight_copilot(flight));
    free(get_flight_notes(flight));
    free(flight);
}

void free_catalogo_flights(catalogo_Flights *cat_flights)
{
    if (cat_flights->table_flights)
    {
        g_hash_table_foreach(cat_flights->table_flights, (GHFunc)free_flights_value, NULL);
        g_hash_table_destroy(cat_flights->table_flights);
    }
    free(cat_flights);
}

void free_catalogo_passengers(catalogo_Passengers *cat_passengers)
{
    g_hash_table_destroy(cat_passengers->table_passengers);
    free(cat_passengers);
}

void free_catalogo_reservations(catalogo_Reservations *cat_reservations)
{
    g_hash_table_destroy(cat_reservations->table_reservations);
    free(cat_reservations);
}

void free_catalogo_users(catalogo_Users *cat_users)
{
    g_hash_table_destroy(cat_users->table_users);
    free(cat_users);
}

GHashTable *get_table_flights(catalogo_Flights *cat_flights)
{
    return cat_flights->table_flights;
}

const GHashTable *get_table_passengers(const catalogo_Passengers *cat_passengers)
{
    return cat_passengers->table_passengers;
}

const GHashTable *get_table_reservations(const catalogo_Reservations *cat_reservations)
{
    return cat_reservations->table_reservations;
}

const GHashTable *get_table_users(const catalogo_Users *cat_users)
{
    return cat_users->table_users;
}

void print_flight_pair_key(gpointer key, gpointer value)
{
    printf("Key: %s\n", (char *)key);
    print_flight((Flight *)value);
    printf("\n");
}

void print_catalogo_flights(catalogo_Flights *cat_flights)
{
    g_hash_table_foreach(cat_flights->table_flights, (GHFunc)print_flight, NULL);
}

GHashTable *new_hashtable()
{
    return g_hash_table_new(g_str_hash, g_str_equal);
}
