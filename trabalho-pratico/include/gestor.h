#ifndef GESTOR_H
#define GESTOR_H

#include <glib-2.0/glib.h>
#include "gestorFlights.h"
#include "gestorPassengers.h"
#include "gestorReservations.h"
#include "gestorUsers.h"
#include "interface.h"

typedef struct AirportMedian AirportMedian;

GHashTable *new_hashtable();

double calculate_nights4(char *begin_date, char *end_date);
void get_info_format(char *id, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users, catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, FILE *output_file);
void get_info(char *id, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users, catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, FILE *output_file);
void list_user_flights_or_reservations2(char *id2, char *type, FILE *output_file2, catalogo_Reservations *cat_reservations, catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, catalogo_Users *cat_users);
void list_user_flights_or_reservations2_format(char *id2, char *type, FILE *output_file2, catalogo_Reservations *cat_reservations, catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, catalogo_Users *cat_users);
double average_rating_by_hotel_id(GHashTable *reservations, char *hotel_id);
void print_reservations_by_hotel_id_format(char *hotel_id, catalogo_Reservations *cat_reservations, FILE *output_file);
void print_reservations_by_hotel_id(char *hotel_id, catalogo_Reservations *cat_reservations, FILE *output_file);
void print_matching_flights(char *origin, char *beg_date, char *end_date, GHashTable *flights, FILE *output_file5);
void print_flights_by_delay_format(char *id7, catalogo_Flights *cat_flights, FILE *output_file7);
void print_flights_by_delay(char *id7, catalogo_Flights *cat_flights, FILE *output_file7);
void get_hotel_revenue_between_dates(char *hotel_id, char *start_date, char *end_date, catalogo_Reservations *cat_reservations, FILE *output_file);
void get_hotel_revenue_between_dates_format(char *hotel_id, char *start_date, char *end_date, catalogo_Reservations *cat_reservations, FILE *output_file);
void list_users_by_name_prefix_format(char *prefix, catalogo_Users *cat_users, FILE *output_file9);
void list_users_by_name_prefix(char *prefix, catalogo_Users *cat_users, FILE *output_file9);
void print_matching_flights_format(char *origin, char *beg_date, char *end_date, GHashTable *flights, FILE *output_file5);
void print_airport(char *id7, char *year, catalogo_Flights *cat_flights, FILE *output_file7);
void tokenize_flight(char **tokens, catalogo_Flights *cat_flights);
void tokenize_passenger(char **tokens, catalogo_Passengers *cat_passengers, catalogo_Flights *cat_flights, catalogo_Users *cat_users);
void tokenize_reservation(char **tokens, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users);
void tokenize_user(char **tokens, catalogo_Users *cat_users);
int compare_users_by_name2(const void *a, const void *b);
void increment_date(char *date);
GPtrArray *get_users_by_name_prefix2(GHashTable *users, char *prefix);
bool is_date_between(char *date, char *start_date, char *end_date);
GPtrArray *get_reservations_by_hotel_id2(GHashTable *reservations, const char *hotel_id);
int is_valid_user_id(char *user_id);
int calculate_age(char *birth_date);
int calculate_delay(Flight *flight);
double calculate_nights2(char *begin_date, char *end_date);
GList *get_reservations_by_hotel_id(GHashTable *reservations, char *hotel_id);
gint compare_reservations_by_begin_date_desc(gconstpointer a, gconstpointer b);
int compareByDelaysAscending(gconstpointer a, gconstpointer b);
char *get_AirportMedian_airport(AirportMedian *airportMedian);
void set_AiportMedian_airport(AirportMedian *airportMedian, char *airport);
double get_AirportMedian_median(AirportMedian *airportMedian);
void set_AiportMedian_median(AirportMedian *airportMedian, double median);

#endif