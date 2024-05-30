#ifndef PARSERQUERIES_H
#define PARSERQUERIES_H

#include <glib-2.0/glib.h>
#include "gestorFlights.h"
#include "gestorPassengers.h"
#include "gestorReservations.h"
#include "gestorUsers.h"

#include "flight.h"
#include "passenger.h"
#include "reservation.h"
#include "user.h"

typedef struct
{
    char airport[50];
    int delay;
    int count;
    int median;
    int delaySum;
    int medianDelay;
} AirportDelay;

typedef struct
{
    char *airport;
    double median;
} AirportMedian;

int is_valid_user_id(char *user_id);
double sum_reservation_prices_by_user_id(GHashTable *reservations, char *user_id);
double calculate_nights(char *begin_date, char *end_date);
time_t parse_date_string(char *date_string);
int calculate_delay(Flight *flight);
double calculate_nights2(char *begin_date, char *end_date);
int calculate_age(char *birth_date);
Reservation *find_reservation_by_user_id(GHashTable *reservations, char *user_id);
Passenger *find_passenger_by_user_id(GHashTable *passengers, char *user_id);
int count_reservations_by_user_id(GHashTable *reservations, char *user_id);
int count_passengers_by_flight_id(GHashTable *passengers, char *flight_id);
int count_passengers_by_user_id(GHashTable *passengers, char *user_id);
Reservation *find_reservation_by_user_id(GHashTable *reservations, char *user_id);
Passenger *find_passenger_by_user_id(GHashTable *passengers, char *user_id);
GPtrArray *get_reservations_by_hotel_id2(GHashTable *reservations, const char *hotel_id);
void parse_queries(char *queries_path, catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users);
void increment_date(char *date);
bool is_date_between(char *date, char *start_date, char *end_date);
GPtrArray *get_users_by_name_prefix2(GHashTable *users, char *prefix);
int compare_users_by_name2(const void *a, const void *b);
int compareByDelaysAscending(gconstpointer a, gconstpointer b);
int compareByMedianDescending(gconstpointer a, gconstpointer b);
void freeAirportMedian(gpointer data);
GPtrArray *get_reservations_by_user_id2(GHashTable *reservations, const char *user_id);
int compare_reservations_by_begin_date_desc2(gconstpointer a, gconstpointer b);
GPtrArray *get_flights_by_user_id2(GHashTable *flights, GHashTable *passengers, const char *user_id);
int compare_flights_by_schedule_departure_date_desc2(gconstpointer a, gconstpointer b);
GList *get_reservations_by_hotel_id(GHashTable *reservations, char *hotel_id);
gint compare_reservations_by_begin_date_desc(gconstpointer a, gconstpointer b);

#endif