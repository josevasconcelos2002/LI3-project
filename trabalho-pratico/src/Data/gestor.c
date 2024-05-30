#include "../../include/gestor.h"
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/gestorFlights.h"
#include "../../include/gestorPassengers.h"
#include "../../include/gestorReservations.h"
#include "../../include/gestorUsers.h"
#include <glib-2.0/glib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <locale.h>
#define DATA "2023/10/01"

GHashTable *new_hashtable()
{
    return g_hash_table_new(g_str_hash, g_str_equal);
}

typedef struct
{
    char *origin;
    int seatsTaken;
} FlightInfo;
typedef struct
{
    char airport[50];
    int delay;
    int count;
    int median;
    int delaySum;
    int medianDelay;
} AirportDelay;

struct AirportMedian
{
    char *airport;
    double median;
}; 

typedef AirportMedian AirportMedian;

char *get_AirportMedian_airport(AirportMedian *airportMedian)
{
    char *airport = strdup(airportMedian->airport);
    return airport;
}

void set_AiportMedian_airport(AirportMedian *airportMedian, char *airport)
{
    if (airportMedian)
    {
        airportMedian->airport = strdup(airport);
    }
}

double get_AirportMedian_median(AirportMedian *airportMedian)
{
    double median = airportMedian->median;
    return median;
}

void set_AiportMedian_median(AirportMedian *airportMedian, double median)
{
    if (airportMedian)
    {
        airportMedian->median = median;
    }
}

/**
 * @brief This function is responsible for checking if a user_id is valid.
 *
 * @param user_id Pointer to the user id.
 *
 * @return int.
 */
int is_valid_user_id(char *user_id)
{
    int len = strlen(user_id);
    int i = 4;
    if (len == 0)
    {
        i = 4;
    }
    else if (len > 0)
    {
        i = 1;
    }

    // Check if id is flight_id
    bool is_int = true;
    for (int i = 0; i < len; i++)
    {
        if (!isdigit(user_id[i]))
        {
            is_int = false;
            break;
        }
    }
    if (is_int)
    {
        i = 2;
    }

    // Check if id is of the form "BookXXXXXXXXXX"
    if (strncmp(user_id, "Book", 4) == 0)
    {
        i = 3;
    }

    // If none of the above conditions are met, id is invalid
    return i;
}

/**
 * @brief This function is responsible for calculating the number of nights between two dates.
 *
 * @param begin_date Pointer to the begin date.
 * @param end_date Pointer to the end date.
 *
 * @return double.
 */
double calculate_nights(char *begin_date, char *end_date)
{
    struct tm tm_begin_date = {0};
    strptime(begin_date, "%Y/%m/%d %H:%M:%S", &tm_begin_date);

    struct tm tm_end_date = {0};
    strptime(end_date, "%Y/%m/%d %H:%M:%S", &tm_end_date);

    time_t begin_time = mktime(&tm_begin_date);
    time_t end_time = mktime(&tm_end_date);

    double seconds_per_day = 24 * 60 * 60;
    double nights = difftime(end_time, begin_time) / seconds_per_day;

    return nights;
}

/**
 * @brief This function is responsible for calculating the average rating by hotel id.
 *
 * @param reservations Pointer to the reservations hash table.
 * @param hotel_id Pointer to the hotel id.
 *
 * @return double.
 */
double average_rating_by_hotel_id(GHashTable *reservations, char *hotel_id)
{
    double sum = 0.0;
    int count = 0;
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, reservations);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        Reservation *r = (Reservation *)value;
        char *reservation_hotel_id = get_reservation_hotel_id(r);
        if (strcmp(reservation_hotel_id, hotel_id) == 0)
        {
            sum += get_reservation_rating(r);
            count++;
        }
        free(reservation_hotel_id);
    }
    if (count == 0)
    {
        return 0.0;
    }
    else
    {
        return sum / count;
    }
}

/**
 * @brief This function is responsible for removing quotes from a string.
 *
 * @param str Pointer to the string.
 *
 * @return void.
 */
void remove_quotes(char *str)
{
    int len = strlen(str);
    if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
    {
        memmove(str, str + 1, len - 2);
        str[len - 2] = '\0';
    }
}

/**
 * @brief This function is responsible for getting users by name prefix.
 *
 * @param users Pointer to the users hash table.
 * @param prefix Pointer to the name prefix.
 *
 * @return GList*.
 */
GList *get_users_by_name_prefix(GHashTable *users, char *prefix)
{
    GList *result = NULL;
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, users);
    remove_quotes(prefix);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        User *user = (User *)value;
        char *user_account_status = get_user_account_status(user);
        char *user_name = get_user_name(user);
        user_account_status[strcspn(user_account_status, "\n")] = '\0';
        if ((strcasecmp(user_account_status, "active") == 0) && strncmp(user_name, prefix, strlen(prefix)) == 0)
        {
            result = g_list_append(result, user);
        }
    }
    return result;
}

GPtrArray *get_users_by_name_prefix2(GHashTable *users, char *prefix)
{
    GPtrArray *result = g_ptr_array_new();
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, users);
    remove_quotes(prefix);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        User *user = (User *)value;
        char *user_account_status = get_user_account_status(user);
        char *user_name = get_user_name(user);
        user_account_status[strcspn(user_account_status, "\n")] = '\0';
        if ((strcasecmp(user_account_status, "active") == 0) && strncmp(user_name, prefix, strlen(prefix)) == 0)
        {
            g_ptr_array_add(result, user);
        }
        free(user_account_status);
        free(user_name);
    }
    return result;
}

int compare_users_by_name2(const void *a, const void *b)
{
    setlocale(LC_COLLATE, "en_US.UTF-8");
    User *user_a = *(User **)a;
    User *user_b = *(User **)b;
    char *user_a_name = get_user_name(user_a);
    char *user_b_name = get_user_name(user_b);
    char *user_a_id = get_user_id(user_a);
    char *user_b_id = get_user_id(user_b);

    int name_comparison = -1;
    if (user_a_name != NULL && user_b_name != NULL)
    {
        name_comparison = strcoll(user_a_name, user_b_name);
        if (name_comparison == 0)
        {
            name_comparison = strcoll(user_a_id, user_b_id);
        }
    }

    // Free the memory allocated by the get functions
    free(user_a_name);
    free(user_b_name);
    free(user_a_id);
    free(user_b_id);

    return name_comparison;
}
/**
 * @brief This function is responsible for printing users by name prefix.
 *
 * @param prefix Pointer to the name prefix.
 * @param cat_users Pointer to the users hash table.
 * @param output_file9 Pointer to the output file.
 *
 * @return void.
 */
void list_users_by_name_prefix_format(char *prefix, catalogo_Users *cat_users, FILE *output_file9)
{
    GPtrArray *users = get_users_by_name_prefix2(get_table_users(cat_users), prefix);
    g_ptr_array_sort(users, compare_users_by_name2);
    guint i;
    for (i = 0; i < users->len; i++)
    {
        User *user = g_ptr_array_index(users, i);
        char *user_id = get_user_id(user);
        char *user_name = get_user_name(user);

        if (i == 0)
        {
            fprintf(output_file9, "--- %d ---\n", i + 1);
            fprintf(output_file9, "id: %s\n", user_id);
            fprintf(output_file9, "name: %s\n", user_name);
        }
        else
        {
            fprintf(output_file9, "\n--- %d ---\n", i + 1);
            fprintf(output_file9, "id: %s\n", user_id);
            fprintf(output_file9, "name: %s\n", user_name);
        }

        // Free the memory allocated by get_user_id()
        free(user_id);
        // Free the memory allocated by get_user_name()
        free(user_name);
    }

    g_ptr_array_free(users, TRUE);
}

/**
 * @brief This function is responsible for printing users by name prefix.
 *
 * @param prefix Pointer to the name prefix.
 * @param cat_users Pointer to the users hash table.
 * @param output_file9 Pointer to the output file.
 *´
 * @return void.
 */
void list_users_by_name_prefix(char *prefix, catalogo_Users *cat_users, FILE *output_file9)
{
    GPtrArray *users = get_users_by_name_prefix2(get_table_users(cat_users), prefix);
    g_ptr_array_sort(users, compare_users_by_name2);

    guint i;
    for (i = 0; i < users->len; i++)
    {
        User *user = g_ptr_array_index(users, i);
        char *user_id = get_user_id(user);
        char *user_name = get_user_name(user);
        fprintf(output_file9, "%s;%s\n", user_id, user_name);
        free(user_id);
        free(user_name);
    }
    g_ptr_array_free(users, TRUE);
}

/**
 * @brief This function is responsible for parsing date string to time_t.
 *
 * @param date_string Pointer to the date string.
 *
 * @return time_t.
 */
time_t parse_date_string(char *date_string)
{
    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));
    strptime(date_string, "%Y/%m/%d %H:%M:%S", &tm);
    time_t t = mktime(&tm);
    return t;
}

/**
 * @brief This function is responsible for calculating delay.
 *
 * @param flight Pointer to the flight.
 *
 * @return int.
 */
int calculate_delay(Flight *flight)
{
    char *schedule_departure_date = get_flight_schedule_departure_date(flight);
    char *real_departure_date = get_flight_real_departure_date(flight);

    time_t schedule_departure_time = parse_date_string(schedule_departure_date);
    time_t real_departure_time = parse_date_string(real_departure_date);

    // Verificação de datas nulas
    if (schedule_departure_time == -1 || real_departure_time == -1)
    {
        // Trate o caso de datas nulas, se necessário
        free(schedule_departure_date);
        free(real_departure_date);
        return 0; // Ou outro valor padrão
    }

    int delay = (int)difftime(real_departure_time, schedule_departure_time);

    // Free the memory allocated by strdup()
    free(schedule_departure_date);
    free(real_departure_date);

    return delay;
}

/**
 * @brief This function is responsible for calculating the number of nights between two dates.
 *
 * @param begin_date Pointer to the begin date.
 * @param end_date Pointer to the end date.
 *
 * @return double.
 */

double calculate_nights2(char *begin_date, char *end_date)
{
    struct tm tm_begin_date = {0};
    strptime(begin_date, "%Y/%m/%d", &tm_begin_date);

    struct tm tm_end_date = {0};
    strptime(end_date, "%Y/%m/%d", &tm_end_date);

    time_t begin_time = mktime(&tm_begin_date);
    time_t end_time = mktime(&tm_end_date);

    double seconds_per_day = 24 * 60 * 60;
    double nights = difftime(end_time, begin_time) / seconds_per_day;

    return nights;
}

/**
 * @brief This function is responsible for calculating age.
 *
 * @param birth_date Pointer to the birth date.
 *
 * @return int.
 */
int calculate_age(char *birth_date)
{
    struct tm tm_birth_date = {0};
    struct tm tm_reference_date = {0};

    strptime(birth_date, "%Y/%m/%d", &tm_birth_date);
    strptime(DATA, "%Y/%m/%d", &tm_reference_date);

    int age = tm_reference_date.tm_year - tm_birth_date.tm_year;

    if (tm_reference_date.tm_mon < tm_birth_date.tm_mon ||
        (tm_reference_date.tm_mon == tm_birth_date.tm_mon && tm_reference_date.tm_mday < tm_birth_date.tm_mday))
    {
        age--;
    }

    return age;
}

/**
 * @brief This function is responsible for getting reservations by hotel id.
 *
 * @param reservations Pointer to the reservations hash table.
 * @param hotel_id Pointer to the hotel id.
 *
 * @return GList*.
 */
GList *get_reservations_by_hotel_id(GHashTable *reservations, char *hotel_id)
{
    GList *reservations_for_hotel = NULL;

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, reservations);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        Reservation *reservation = (Reservation *)value;
        char *reservation_hotel_id = get_reservation_hotel_id(reservation);
        if (strcmp(reservation_hotel_id, hotel_id) == 0)
        {

            reservations_for_hotel = g_list_append(reservations_for_hotel, reservation);
        }
        free(reservation_hotel_id);
    }

    return reservations_for_hotel;
}

GPtrArray *get_reservations_by_hotel_id2(GHashTable *reservations, const char *hotel_id)
{
    GPtrArray *reservations_for_hotel = g_ptr_array_new();

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, reservations);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        Reservation *reservation = (Reservation *)value;
        char *reservation_hotel_id = get_reservation_hotel_id(reservation);
        if (strcmp(reservation_hotel_id, hotel_id) == 0)
        {
            g_ptr_array_add(reservations_for_hotel, reservation);
        }
        free(reservation_hotel_id);
    }

    return reservations_for_hotel;
}

/**
 * @brief This function is responsible for comparing two reservations by begin date in descending order.
 *
 * @param a Pointer to the first reservation.
 * @param b Pointer to the second reservation.
 *
 * @return gint.
 */
gint compare_reservations_by_begin_date_desc(gconstpointer a, gconstpointer b)
{
    Reservation *reservation_a = (Reservation *)a;
    Reservation *reservation_b = (Reservation *)b;
    char *begin_date_a = get_reservation_begin_date(reservation_a);
    char *begin_date_b = get_reservation_begin_date(reservation_b);
    char *reservation_id_a = get_reservation_id(reservation_a);
    char *reservation_id_b = get_reservation_id(reservation_b);
    int result;

    int date_comparison = strcmp(begin_date_b, begin_date_a);
    if (date_comparison != 0)
    {
        result = date_comparison;
    }
    else
    {
        result = strcmp(reservation_id_a, reservation_id_b);
    }
    free(begin_date_a);
    free(begin_date_b);
    free(reservation_id_a);
    free(reservation_id_b);
    return result;
}

/**
 * @brief This function is responsible for printing reservations by hotel id in descending order.
 *
 * @param hotel_id Pointer to the hotel id.
 * @param cat_reservations Pointer to the reservations catalog.
 * @param output_file Pointer to the output file.
 */
void print_reservations_by_hotel_id_format(char *hotel_id, catalogo_Reservations *cat_reservations, FILE *output_file)
{
    GList *reservations = get_reservations_by_hotel_id(get_table_reservations(cat_reservations), hotel_id);
    reservations = g_list_sort(reservations, compare_reservations_by_begin_date_desc);

    GList *iter;
    int i;
    for (iter = reservations, i = 1; iter != NULL; iter = iter->next, i++)
    {
        Reservation *reservation = (Reservation *)iter->data;
        char *reservation_id = get_reservation_id(reservation);
        char *begin_date = get_reservation_begin_date(reservation);
        char *end_date = get_reservation_end_date(reservation);
        char *user_id = get_reservation_user_id(reservation);
        double rating = get_reservation_rating(reservation);
        double total_price = get_reservation_total_price(reservation);

        if (i == 1)
        {
            fprintf(output_file, "--- %d ---\n", i);
            fprintf(output_file, "id: %s\n", reservation_id);
            fprintf(output_file, "begin_date: %s\n", begin_date);
            fprintf(output_file, "end_date: %s\n", end_date);
            fprintf(output_file, "user_id: %s\n", user_id);
            fprintf(output_file, "rating: %.0f\n", rating);
            fprintf(output_file, "total_price: %.3f\n", total_price);
        }
        else
        {
            fprintf(output_file, "\n--- %d ---\n", i);
            fprintf(output_file, "id: %s\n", reservation_id);
            fprintf(output_file, "begin_date: %s\n", begin_date);
            fprintf(output_file, "end_date: %s\n", end_date);
            fprintf(output_file, "user_id: %s\n", user_id);
            fprintf(output_file, "rating: %.0f\n", rating);
            fprintf(output_file, "total_price: %.3f\n", total_price);
        }

        // Free the memory allocated by get_reservation_id()
        free(reservation_id);
        // Free the memory allocated by get_reservation_begin_date()
        free(begin_date);
        // Free the memory allocated by get_reservation_end_date()
        free(end_date);
        // Free the memory allocated by get_reservation_user_id()
        free(user_id);
    }

    g_list_free(reservations);
}
/**
 * @brief This function is responsible for printing reservations by hotel id in descending order.
 *
 * @param hotel_id Pointer to the hotel id.
 * @param cat_reservations Pointer to the reservations catalog.
 * @param output_file Pointer to the output file.
 */
void print_reservations_by_hotel_id(char *hotel_id, catalogo_Reservations *cat_reservations, FILE *output_file)
{
    GList *reservations = get_reservations_by_hotel_id(get_table_reservations(cat_reservations), hotel_id);
    reservations = g_list_sort(reservations, compare_reservations_by_begin_date_desc);

    GList *iter;
    for (iter = reservations; iter != NULL; iter = iter->next)
    {
        Reservation *reservation = (Reservation *)iter->data;
        char *reservation_id = get_reservation_id(reservation);
        char *begin_date = get_reservation_begin_date(reservation);
        char *end_date = get_reservation_end_date(reservation);
        char *user_id = get_reservation_user_id(reservation);
        double rating = get_reservation_rating(reservation);
        double total_price = get_reservation_total_price(reservation);

        fprintf(output_file, "%s;%s;%s;%s;%.0f;%.3f\n", reservation_id, begin_date, end_date, user_id, rating, total_price);
        free(reservation_id);
        free(begin_date);
        free(end_date);
        free(user_id);
    }

    g_list_free(reservations);
}

/**
 * @brief This function is responsible for checking if a date range is valid.
 *
 * @param flight_date Pointer to the flight date.
 * @param beg_date Pointer to the beginning date.
 * @param end_date Pointer to the end date.
 *
 * @return bool.
 */
bool is_valid_date_range(char *flight_date, char *beg_date, char *end_date)
{
    struct tm flight_tm = {0};
    struct tm beg_tm = {0};
    struct tm end_tm = {0};

    strptime(flight_date, "%Y/%m/%d %H:%M:%S", &flight_tm);
    strptime(beg_date, "%Y/%m/%d %H:%M:%S", &beg_tm);
    strptime(end_date, "%Y/%m/%d %H:%M:%S", &end_tm);

    time_t flight_time = mktime(&flight_tm);
    time_t beg_time = mktime(&beg_tm);
    time_t end_time = mktime(&end_tm);

    return (flight_time >= beg_time && flight_time <= end_time);
}

/**
 * @brief This function is responsible for converting a string to uppercase.
 *
 * @param str Pointer to the string.
 *
 * @return void.
 */
void string_to_uppercase(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = toupper(str[i]);
    }
}

/**
 * @brief This function is responsible for comparing two flights.
 *
 * @param a Pointer to the first flight.
 * @param b Pointer to the second flight.
 *
 * @return int.
 */
int compare_flights(gconstpointer a, gconstpointer b)
{
    Flight *flight_a = (Flight *)a;
    Flight *flight_b = (Flight *)b;

    char *departure_date_a = get_flight_schedule_departure_date(flight_a);
    char *departure_date_b = get_flight_schedule_departure_date(flight_b);

    int result = strcmp(departure_date_a, departure_date_b);

    g_free(departure_date_a);
    g_free(departure_date_b);

    return result;
}
/**
 * @brief This function is responsible for printing matching flights in format.
 *
 * @param origin Pointer to the origin.
 * @param beg_date Pointer to the beginning date.
 * @param end_date Pointer to the end date.
 * @param flights Pointer to the flights catalog.
 * @param output_file5 Pointer to the output file.
 *
 * @return void.
 */
void print_matching_flights_format(char *origin, char *beg_date, char *end_date, GHashTable *flights, FILE *output_file)
{
    GList *flight_list = g_hash_table_get_values(flights);
    flight_list = g_list_sort(flight_list, compare_flights);
    flight_list = g_list_reverse(flight_list);

    int i = 1;
    GList *iter;
    for (iter = flight_list; iter != NULL; iter = iter->next)
    {
        Flight *flight = (Flight *)iter->data;
        char *flight_id = get_flight_id(flight);
        char *schedule_departure_date = get_flight_schedule_departure_date(flight);
        char *destination = get_flight_destination(flight);
        char *airline = get_flight_airline(flight);
        char *plane_model = get_flight_plane_model(flight);
        char *flight_origin = get_flight_origin(flight);

        if (strcasecmp(flight_origin, origin) == 0 && is_valid_date_range(schedule_departure_date, beg_date, end_date))
        {
            if (i == 1)
            {
                fprintf(output_file, "--- %d ---\n", i);
            }
            else
            {
                fprintf(output_file, "\n--- %d ---\n", i);
            }
            fprintf(output_file, "id: %s\n", flight_id);
            fprintf(output_file, "schedule_departure_date: %s\n", schedule_departure_date);
            string_to_uppercase(destination);
            fprintf(output_file, "destination: %s\n", destination);
            fprintf(output_file, "airline: %s\n", airline);
            fprintf(output_file, "plane_model: %s\n", plane_model);
            i++;
        }

        // Free the memory allocated by get_flight_id()
        free(flight_id);
        // Free the memory allocated by get_flight_schedule_departure_date()
        free(schedule_departure_date);
        free(destination);
        free(airline);
        free(plane_model);
        free(flight_origin);
    }

    g_list_free(flight_list);
}

/**
 * @brief This function is responsible for printing matching flights.
 *
 * @param origin Pointer to the origin.
 * @param beg_date Pointer to the beginning date.
 * @param end_date Pointer to the end date.
 * @param flights Pointer to the flights catalog.
 * @param output_file5 Pointer to the output file.
 *
 * @return void.
 */
void print_matching_flights(char *origin, char *beg_date, char *end_date, GHashTable *flights, FILE *output_file5)
{
    GList *flight_list = g_hash_table_get_values(flights);
    flight_list = g_list_sort(flight_list, compare_flights);
    flight_list = g_list_reverse(flight_list); // Reverse the order of the flight_list

    GList *iter;
    for (iter = flight_list; iter != NULL; iter = iter->next)
    {
        Flight *flight = (Flight *)iter->data;
        char *flight_id = get_flight_id(flight);
        char *schedule_departure_date = get_flight_schedule_departure_date(flight);
        char *airline = get_flight_airline(flight);
        char *plane_model = get_flight_plane_model(flight);
        char *flight_origin = get_flight_origin(flight);

        if (strcasecmp(flight_origin, origin) == 0 && is_valid_date_range(schedule_departure_date, beg_date, end_date))
        {
            char *destination = get_flight_destination(flight);
            string_to_uppercase(destination);
            fprintf(output_file5, "%s;%s;%s;%s;%s\n", flight_id, schedule_departure_date, destination, airline, plane_model);
            free(destination);
        }
        free(flight_id);
        free(schedule_departure_date);
        free(airline);
        free(plane_model);
        free(flight_origin);
    }

    g_list_free(flight_list);
}

/**
 * @brief This function is responsible for getting a list of flights by user id.
 *
 * @param flights Pointer to the flights hash table.
 * @param user_id Pointer to the user id.
 *
 * @return GList*.
 */

void g_ptr_array_reverse(GPtrArray *array)
{
    guint len = array->len;
    guint i, j;

    for (i = 0, j = len - 1; i < j; i++, j--)
    {
        gpointer temp = g_ptr_array_index(array, i);
        g_ptr_array_index(array, i) = g_ptr_array_index(array, j);
        g_ptr_array_index(array, j) = temp;
    }
}

void g_ptr_array_add_range(GPtrArray *array, gpointer *data, guint len)
{
    for (guint i = 0; i < len; i++)
    {
        g_ptr_array_add(array, data[i]);
    }
}

int compare_by_date2(gconstpointer a, gconstpointer b)
{
    Reservation *reservationA = *(Reservation **)a;
    Reservation *reservationB = *(Reservation **)b;
    Flight *flightA = *(Flight **)a;
    Flight *flightB = *(Flight **)b;
    char *reservationA_begin_date = get_reservation_begin_date(reservationA);
    char *reservationB_begin_date = get_reservation_begin_date(reservationB);
    char *flightA_schedule_departure_date = get_flight_schedule_departure_date(flightA);
    char *flightB_schedule_departure_date = get_flight_schedule_departure_date(flightB);

    const char *dateA = (reservationA != NULL) ? reservationA_begin_date : flightA_schedule_departure_date;
    const char *dateB = (reservationB != NULL) ? reservationB_begin_date : flightB_schedule_departure_date;
    int result = strcmp(dateA, dateB);
    free(reservationA_begin_date);
    free(reservationB_begin_date);
    free(flightA_schedule_departure_date);
    free(flightB_schedule_departure_date);

    return result;
}

void remove_newline(char *str)
{
    size_t length = strlen(str);
    if (length > 0 && str[length - 1] == '\n')
    {
        str[length - 1] = '\0';
    }
}

GPtrArray *get_reservations_by_user_id2(GHashTable *reservations, const char *user_id)
{
    GPtrArray *reservations_by_user = g_ptr_array_new();
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, reservations);

    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        Reservation *r = (Reservation *)value;
        char *user_id_real = get_reservation_user_id(r);
        user_id_real[strcspn(user_id_real, "\n")] = '\0';
        if (strncmp(user_id_real, user_id, strlen(user_id)) == 0)
        {
            g_ptr_array_add(reservations_by_user, r);
        }
        free(user_id_real);
    }

    return reservations_by_user;
}

GPtrArray *get_flights_by_user_id2(GHashTable *flights, GHashTable *passengers, const char *user_id)
{
    GPtrArray *flights_by_user = g_ptr_array_new();

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, passengers);

    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        Passenger *p = (Passenger *)value;
        char *user_id_real = get_passenger_user_id(p);
        user_id_real[strcspn(user_id_real, "\n")] = '\0';
        if (strncmp(user_id_real, user_id, strlen(user_id)) == 0)
        {
            char *flight_id = get_passenger_flight_id(p);
            Flight *f = (Flight *)g_hash_table_lookup(flights, flight_id);
            g_ptr_array_add(flights_by_user, f);
            free(flight_id);
        }
        free(user_id_real);
    }

    return flights_by_user;
}

int compare_flights_by_schedule_departure_date_desc2(gconstpointer a, gconstpointer b)
{
    Flight *flight_a = *(Flight **)a;
    Flight *flight_b = *(Flight **)b;
    char *schedule_departure_date_a = get_flight_schedule_departure_date(flight_a);
    char *schedule_departure_date_b = get_flight_schedule_departure_date(flight_b);

    // Compare the schedule departure dates in descending order
    int result = strcmp(schedule_departure_date_b, schedule_departure_date_a);

    // Free the memory allocated by get_flight_schedule_departure_date()
    free(schedule_departure_date_a);
    free(schedule_departure_date_b);

    return result;
}

int compare_reservations_by_begin_date_desc2(gconstpointer a, gconstpointer b)
{
    Reservation *reservation_a = *(Reservation **)a;
    Reservation *reservation_b = *(Reservation **)b;
    char *begin_date_a = get_reservation_begin_date(reservation_a);
    char *begin_date_b = get_reservation_begin_date(reservation_b);

    // Compare the begin dates in descending order
    int result = strcmp(begin_date_b, begin_date_a);

    // Free the memory allocated by get_reservation_begin_date()
    free(begin_date_a);
    free(begin_date_b);

    return result;
}

/**
 * @bget_flights_by_user_idrief This function is responsible for comparing two flights by schedule departure date in descending order.
 *
 * @param a Pointer to the first flight.
 * @param b Pointer to the second flight.
 *
 * @return gint.
 */
gint compare_flights_by_schedule_departure_date_desc(gconstpointer a, gconstpointer b)
{
    Flight *f1 = (Flight *)a;
    Flight *f2 = (Flight *)b;
    char *schedule_departure_date_f1 = get_flight_schedule_departure_date(f1);
    char *schedule_departure_date_f2 = get_flight_schedule_departure_date(f2);
    int date_comparison = strcmp(schedule_departure_date_f1, schedule_departure_date_f2);

    // Free the memory allocated by get_flight_schedule_departure_date()
    free(schedule_departure_date_f1);
    free(schedule_departure_date_f2);

    if (date_comparison != 0)
    {
        return date_comparison;
    }
    else
    {
        char *flight_id_f1 = get_flight_id(f1);
        char *flight_id_f2 = get_flight_id(f2);
        int id_comparison = strcmp(flight_id_f1, flight_id_f2);

        // Free the memory allocated by get_flight_id()
        free(flight_id_f1);
        free(flight_id_f2);

        return id_comparison;
    }
}

/**
 * @brief This function is responsible for comparing two reservations by begin date in descending order.
 *
 * @param a Pointer to the first reservation.
 * @param b Pointer to the second reservation.
 *
 * @return gint.
 */
gint compare_by_date_asc2(gconstpointer a, gconstpointer b)
{
    Reservation *r1 = (Reservation *)a;
    Reservation *r2 = (Reservation *)b;
    Flight *f1 = (Flight *)a;
    Flight *f2 = (Flight *)b;

    if (r1 && r2)
    {
        char *begin_date_r1 = get_reservation_begin_date(r1);
        char *begin_date_r2 = get_reservation_begin_date(r2);
        int date_comparison = strcmp(begin_date_r1, begin_date_r2);

        // Free the memory allocated by get_reservation_begin_date()
        free(begin_date_r1);
        free(begin_date_r2);

        return date_comparison;
    }
    else if (f1 && f2)
    {
        char *schedule_departure_date_f1 = get_flight_schedule_departure_date(f1);
        char *schedule_departure_date_f2 = get_flight_schedule_departure_date(f2);
        int date_comparison = strcmp(schedule_departure_date_f1, schedule_departure_date_f2);

        // Free the memory allocated by get_flight_schedule_departure_date()
        free(schedule_departure_date_f1);
        free(schedule_departure_date_f2);

        return date_comparison;
    }
    else if (r1 && f2)
    {
        char *begin_date_r1 = get_reservation_begin_date(r1);
        char *schedule_departure_date_f2 = get_flight_schedule_departure_date(f2);
        int date_comparison = strcmp(begin_date_r1, schedule_departure_date_f2);

        // Free the memory allocated by get_reservation_begin_date() and get_flight_schedule_departure_date()
        free(begin_date_r1);
        free(schedule_departure_date_f2);

        return date_comparison;
    }
    else if (f1 && r2)
    {
        char *schedule_departure_date_f1 = get_flight_schedule_departure_date(f1);
        char *begin_date_r2 = get_reservation_begin_date(r2);
        int date_comparison = strcmp(schedule_departure_date_f1, begin_date_r2);

        // Free the memory allocated by get_flight_schedule_departure_date() and get_reservation_begin_date()
        free(schedule_departure_date_f1);
        free(begin_date_r2);

        return date_comparison;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief This function is responsible for finding a user by id.
 *
 * @param users Pointer to the users hash table.
 * @param id Pointer to the user id.
 *
 * @return User*.
 */

int compare_by_date(const void *a, const void *b)
{
    Reservation *reservationA = (Reservation *)a;
    Reservation *reservationB = (Reservation *)b;
    Flight *flightA = (Flight *)a;
    Flight *flightB = (Flight *)b;

    const char *dateA = (reservationA != NULL) ? get_reservation_begin_date(reservationA) : get_flight_schedule_departure_date(flightA);
    const char *dateB = (reservationB != NULL) ? get_reservation_begin_date(reservationB) : get_flight_schedule_departure_date(flightB);

    return strcmp(dateA, dateB);
}

/**
 * @brief This function is responsible for freeing the memory used by an AirportMedian struct.
 *
 * @param data Pointer to the AirportMedian struct.
 *
 * @return void.
 */
void freeAirportMedian(gpointer data)
{
    AirportMedian *airportMedian = (AirportMedian *)data;
    free(airportMedian->airport);
    free(airportMedian);
}

/**
 * @brief This function is responsible for comparing two AirportMedian structs by median in descending order.
 *
 * @param a Pointer to the first AirportMedian struct.
 * @param b Pointer to the second AirportMedian struct.
 *
 * @return gint.
 */
int compareByMedianDescending(gconstpointer a, gconstpointer b)
{
    const AirportMedian *airportMedianA = (const AirportMedian *)a;
    const AirportMedian *airportMedianB = (const AirportMedian *)b;

    if (airportMedianA->median > airportMedianB->median)
    {
        return -1;
    }
    else if (airportMedianA->median < airportMedianB->median)
    {
        return 1;
    }
    else
    {
        return g_strcmp0(airportMedianA->airport, airportMedianB->airport);
    }
}

// Custom comparison function for sorting delays in descending order

/**
 * @brief This function is responsible for comparing two delays in descending order.
 *
 * @param a Pointer to the first delay.
 * @param b Pointer to the second delay.
 *
 * @return int.
 */
int compareByDelaysAscending(gconstpointer a, gconstpointer b)
{
    int delayA = GPOINTER_TO_INT(a);
    int delayB = GPOINTER_TO_INT(b);

    if (delayA < delayB)
        return -1;
    else if (delayA > delayB)
        return 1;
    else
        return 0;
}

char *extract_year(const char *datetime)
{
    char *year = malloc(5);     // Allocate memory for the year (YYYY) plus null terminator
    strncpy(year, datetime, 4); // Copy the first 4 characters (YYYY) to the year string
    year[4] = '\0';             // Add null terminator to the year string
    return year;
}

/**
 * @brief This function is responsible for printing flights by delay format.
 *
 * @param id7 Pointer to the flight id.
 * @param cat_flights Pointer to the flights catalog.
 * @param output_file7 Pointer to the output file.
 *
 * @return void.
 */
void print_flights_by_delay_format(char *id7, catalogo_Flights *cat_flights, FILE *output_file7)
{
    int N = atoi(id7);
    GHashTable *flights = get_table_flights(cat_flights);
    GHashTable *airportDelays = g_hash_table_new(g_str_hash, g_str_equal);
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, flights);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        Flight *flight = (Flight *)value;
        char *origin = get_flight_origin(flight);
        char *uppercaseOrigin = g_ascii_strup(origin, -1);
        int delay = calculate_delay(flight);

        GList *delaysList = g_hash_table_lookup(airportDelays, uppercaseOrigin);
        if (delaysList == NULL)
        {
            delaysList = g_list_append(NULL, GINT_TO_POINTER(delay));
            g_hash_table_insert(airportDelays, strdup(uppercaseOrigin), delaysList);
        }
        else
        {
            delaysList = g_list_append(delaysList, GINT_TO_POINTER(delay));
        }
        g_free(uppercaseOrigin);
        free(origin);
    }

    GList *airportMedianList = NULL;
    GHashTableIter iter2;
    g_hash_table_iter_init(&iter2, airportDelays);
    while (g_hash_table_iter_next(&iter2, &key, &value))
    {
        char *airport = (char *)key;
        GList *delaysList = (GList *)value;
        delaysList = g_list_sort(delaysList, compareByDelaysAscending);

        int listLength = g_list_length(delaysList);
        double median;
        if (listLength % 2 == 0)
        {
            GList *middle1 = g_list_nth(delaysList, listLength / 2 - 1);
            GList *middle2 = g_list_nth(delaysList, listLength / 2);
            int delay1 = GPOINTER_TO_INT(middle1->data);
            int delay2 = GPOINTER_TO_INT(middle2->data);
            median = (delay1 + delay2) / 2.0;
        }
        else
        {
            GList *middle = g_list_nth(delaysList, listLength / 2);
            median = GPOINTER_TO_INT(middle->data);
        }

        AirportMedian *airportMedian = g_new(AirportMedian, 1);
        airportMedian->airport = strdup(airport);
        airportMedian->median = median;
        airportMedianList = g_list_append(airportMedianList, airportMedian);
        g_free(airport);
        g_list_free(delaysList);
    }
    g_hash_table_destroy(airportDelays);
    airportMedianList = g_list_sort(airportMedianList, compareByMedianDescending);
    GList *iter3;
    int i;
    for (iter3 = airportMedianList, i = 1; iter3 != NULL && i <= N; iter3 = iter3->next)
    {
        AirportMedian *airportMedian = (AirportMedian *)iter3->data;
        if (strlen(airportMedian->airport) == 3)
        {
            fprintf(output_file7, "--- %d ---\n", i);
            fprintf(output_file7, "name: %s\n", airportMedian->airport);
            fprintf(output_file7, "median: %.0f\n", airportMedian->median);
            if (i == N || g_list_next(iter3) == NULL)
            {
                break;
            }
            i++;
            fprintf(output_file7, "\n");
        }
    }
    g_list_free_full(airportMedianList, freeAirportMedian);
}

int compare_flight_info_by_seats_taken(gconstpointer a, gconstpointer b)
{
    FlightInfo *flightInfoA = *(FlightInfo **)a;
    FlightInfo *flightInfoB = *(FlightInfo **)b;

    if (flightInfoA->seatsTaken < flightInfoB->seatsTaken)
        return 1;
    else if (flightInfoA->seatsTaken > flightInfoB->seatsTaken)
        return -1;
    else
        return 0;
}

void print_airport(char *id7, char *year, catalogo_Flights *cat_flights, FILE *output_file7)
{
}

/**
 * @brief This function is responsible for printing the flights by delay.
 *
 * @param id7 Pointer to the id.
 * @param cat_flights Pointer to the flights catalog.
 * @param output_file7 Pointer to the output file.
 *
 * @return void.
 */
void print_flights_by_delay(char *id7, catalogo_Flights *cat_flights, FILE *output_file7)
{
    int N = atoi(id7);
    GHashTable *flights = get_table_flights(cat_flights);
    GHashTable *airportDelays = g_hash_table_new(g_str_hash, g_str_equal);
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, flights);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        Flight *flight = (Flight *)value;
        char *origin = get_flight_origin(flight);
        char *uppercaseOrigin = g_ascii_strup(origin, -1);
        int delay = calculate_delay(flight);

        GList *delaysList = g_hash_table_lookup(airportDelays, uppercaseOrigin);
        if (delaysList == NULL)
        {
            delaysList = g_list_append(NULL, GINT_TO_POINTER(delay));
            g_hash_table_insert(airportDelays, strdup(uppercaseOrigin), delaysList);
        }
        else
        {
            delaysList = g_list_append(delaysList, GINT_TO_POINTER(delay));
        }
        g_free(uppercaseOrigin);
        free(origin);
    }
    GList *airportMedianList = NULL;
    GHashTableIter iter2;
    g_hash_table_iter_init(&iter2, airportDelays);
    while (g_hash_table_iter_next(&iter2, &key, &value))
    {
        char *airport = (char *)key;
        GList *delaysList = (GList *)value;
        delaysList = g_list_sort(delaysList, compareByDelaysAscending);

        int listLength = g_list_length(delaysList);
        double median;
        if (listLength % 2 == 0)
        {
            GList *middle1 = g_list_nth(delaysList, listLength / 2 - 1);
            GList *middle2 = g_list_nth(delaysList, listLength / 2);
            int delay1 = GPOINTER_TO_INT(middle1->data);
            int delay2 = GPOINTER_TO_INT(middle2->data);
            median = (delay1 + delay2) / 2.0;
        }
        else
        {
            GList *middle = g_list_nth(delaysList, listLength / 2);
            median = GPOINTER_TO_INT(middle->data);
        }

        AirportMedian *airportMedian = g_new(AirportMedian, 1);
        airportMedian->airport = strdup(airport);
        airportMedian->median = median;
        airportMedianList = g_list_append(airportMedianList, airportMedian);
        g_free(airport);
        g_list_free(delaysList);
    }

    airportMedianList = g_list_sort(airportMedianList, compareByMedianDescending);
    GList *iter3;
    int i = 0;
    for (iter3 = airportMedianList; iter3 != NULL && i < N; iter3 = iter3->next)
    {
        AirportMedian *airportMedian = (AirportMedian *)iter3->data;
        if (strlen(airportMedian->airport) == 3)
        {
            fprintf(output_file7, "%s;%.0f\n", airportMedian->airport, airportMedian->median);
        }
        i++;
    }
    g_hash_table_destroy(airportDelays);
    g_list_free_full(airportMedianList, freeAirportMedian);
}

/**
 * @brief This function is responsible for listing a user's flights or reservations.
 *
 * @param id2 Pointer to the id.
 * @param type Pointer to the type.
 * @param output_file2 Pointer to the output file.
 * @param cat_reservations Pointer to the reservations catalog.
 * @param cat_flights Pointer to the flights catalog.
 * @param cat_passengers Pointer to the passengers catalog.
 * @param cat_users Pointer to the users catalog.
 *
 * @return void.
 */
void list_user_flights_or_reservations2_format(char *id2, char *type, FILE *output_file2, catalogo_Reservations *cat_reservations, catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, catalogo_Users *cat_users)
{
    User *user = g_hash_table_lookup(get_table_users(cat_users), id2);
    if (user != NULL)
    {
        char *status = get_user_account_status(user);
        status[strcspn(status, "\n")] = '\0';
        if (strcasecmp(status, "inactive") == 0)
        {
            free(status);
            return;
        }
        free(status);
    }
    if (type != NULL && (strcmp(type, "reservations") == 0))
    {
        GPtrArray *reservations = get_reservations_by_user_id2(get_table_reservations(cat_reservations), id2);
        g_ptr_array_sort(reservations, compare_reservations_by_begin_date_desc2);
        int count = 1;

        guint i;
        if (reservations)
        {
            for (i = 0; i < reservations->len; i++)
            {
                Reservation *reservation = g_ptr_array_index(reservations, i);
                char *reservation_id = get_reservation_id(reservation);
                char *begin_date = get_reservation_begin_date(reservation);

                fprintf(output_file2, "--- %d ---\n", count);
                fprintf(output_file2, "id: %s\n", reservation_id);
                fprintf(output_file2, "date: %s\n", begin_date);
                if (i < reservations->len - 1)
                {
                    fprintf(output_file2, "\n");
                }
                count++;

                // Free the memory allocated by the get functions
                free(reservation_id);
                free(begin_date);
            }
        }

        g_ptr_array_free(reservations, TRUE);
    }
    else if (type && (strcmp(type, "flights") == 0))
    {
        GPtrArray *flights = get_flights_by_user_id2(get_table_flights(cat_flights), get_table_passengers(cat_passengers), id2);
        g_ptr_array_sort(flights, compare_flights_by_schedule_departure_date_desc2);
        int count = 1;
        guint i;
        char *copy = NULL;
        char *date = NULL;
        if (flights)
        {
            for (i = 0; i < flights->len; i++)
            {
                Flight *flight = g_ptr_array_index(flights, i);
                char *flight_departure_date = get_flight_schedule_departure_date(flight);
                copy = strdup(flight_departure_date);
                date = strtok(copy, " ");
                char *flight_id = get_flight_id(flight);

                fprintf(output_file2, "--- %d ---\n", count);
                fprintf(output_file2, "id: %s\n", flight_id);
                fprintf(output_file2, "date: %s\n", date);
                if (i < flights->len - 1)
                {
                    fprintf(output_file2, "\n");
                }
                count++;

                // Free the memory allocated by the get functions
                free(copy);
                free(flight_departure_date);
                free(flight_id);
            }
        }
        g_ptr_array_free(flights, TRUE);
    }
    else if (!type)
    {
        GPtrArray *reservations = get_reservations_by_user_id2(get_table_reservations(cat_reservations), id2);
        GPtrArray *flights = get_flights_by_user_id2(get_table_flights(cat_flights), get_table_passengers(cat_passengers), id2);
        GPtrArray *combinedList = g_ptr_array_new();
        g_ptr_array_add_range(combinedList, reservations->pdata, reservations->len);
        g_ptr_array_add_range(combinedList, flights->pdata, flights->len);
        g_ptr_array_sort(combinedList, compare_by_date2);

        int count = 1;
        for (gint i = combinedList->len - 1; i >= 0; i--)
        {
            Reservation *reservation = g_ptr_array_index(combinedList, i);
            Flight *flight = g_ptr_array_index(combinedList, i);
            char *reservation_id = get_reservation_id(reservation);

            if (reservation != NULL && strncmp(reservation_id, "Book", 4) == 0)
            {
                char *begin_date = get_reservation_begin_date(reservation);

                fprintf(output_file2, "--- %d ---\n", count);
                fprintf(output_file2, "id: %s\n", reservation_id);
                fprintf(output_file2, "date: %s\n", begin_date);
                fprintf(output_file2, "type: reservation\n");
                if (i == 0)
                {
                    free(begin_date);
                    free(reservation_id);
                    break;
                }
                fprintf(output_file2, "\n");
                count++;

                // Free the memory allocated by the get functions
                free(begin_date);
            }
            else if (flight != NULL)
            {
                char *begin_date_1 = get_reservation_begin_date(reservation);
                char *begin_date_real = strtok(begin_date_1, " ");

                fprintf(output_file2, "--- %d ---\n", count);
                fprintf(output_file2, "id: %s\n", reservation_id);
                fprintf(output_file2, "date: %s\n", begin_date_real);
                fprintf(output_file2, "type: flight\n");
                if (i == 0)
                {
                    free(begin_date_real);
                    free(reservation_id);
                    break;
                }
                fprintf(output_file2, "\n");
                count++;
                free(begin_date_real);

                // Free the memory allocated by the get functions
            }
            free(reservation_id);
        }
        g_ptr_array_free(reservations, TRUE);
        g_ptr_array_free(flights, TRUE);
        g_ptr_array_free(combinedList, TRUE);
    }
}

/**
 * @brief This function is responsible for checking if a date is between two other dates.
 *
 * @param start_date Pointer to the start date.
 * @param end_date Pointer to the end date.
 * @param begin_date Pointer to the begin date.
 * @param end_date2 Pointer to the end date.
 *
 * @return bool.
 */
bool is_date_between2(char *start_date, char *end_date, char *begin_date, char *end_date2)
{
    return (strcmp(start_date, begin_date) >= 0 && strcmp(start_date, end_date2) <= 0) &&
           (strcmp(end_date, begin_date) >= 0 && strcmp(end_date, end_date2) <= 0);
}

/**
 * @brief This function is responsible for checking if a date is between two other dates.
 *
 * @param date Pointer to the date.
 * @param start_date Pointer to the start date.
 * @param end_date Pointer to the end date.
 *
 * @return bool.
 */
bool is_date_between(char *date, char *start_date, char *end_date)
{
    return (strcmp(date, start_date) >= 0 && strcmp(date, end_date) <= 0);
}

/**
 * @brief This function is responsible for incrementing a date.
 *
 * @param date Pointer to the date.
 *
 * @return void.
 */
void increment_date(char *date)
{
    int day, month, year;
    sscanf(date, "%d/%d/%d", &year, &month, &day);

    day++;

    int max_days = 31;
    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        max_days = 30;
    }
    else if (month == 2)
    {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            max_days = 29;
        }
        else
        {
            max_days = 28;
        }
    }

    if (day > max_days)
    {
        day = 1;
        month++;

        if (month > 12)
        {
            month = 1;
            year++;
        }
    }

    sprintf(date, "%04d/%02d/%02d", year, month, day);
}

/**
 * @brief This function is responsible for printing hotel revenue between dates.
 *
 * @param hotel_id Pointer to the hotel id.
 * @param start_date Pointer to the start date.
 * @param end_date Pointer to the end date.
 * @param cat_reservations Pointer to the reservations catalog.
 * @return float
 */
void get_hotel_revenue_between_dates(char *hotel_id, char *start_date, char *end_date, catalogo_Reservations *cat_reservations, FILE *output_file)
{
    double total_revenue = 0.0;
    int j = 0;
    double nights = 0.0;
    GPtrArray *reservations = get_reservations_by_hotel_id2(get_table_reservations(cat_reservations), hotel_id);

    if (strcmp(start_date, end_date) == 0)
    {
        increment_date(end_date);
        j = 1;
    }

    for (int i = 0; i < reservations->len; i++)
    {
        Reservation *reservation = g_ptr_array_index(reservations, i);
        char *begin_date = get_reservation_begin_date(reservation);
        char *end_date2 = get_reservation_end_date(reservation);

        if (is_date_between(begin_date, start_date, end_date) && is_date_between(end_date2, start_date, end_date))
        {

            if (j == 1)
            {
                nights = 1;
            }
            else
            {
                nights = calculate_nights2(begin_date, end_date2);
            }

            if (nights > 0)
            {
                total_revenue += nights * get_reservation_price_per_night(reservation);
            }
        }
        free(begin_date);
        free(end_date2);
    }

    g_ptr_array_free(reservations, TRUE);
    fprintf(output_file, "%.0f\n", total_revenue);
}

/**
 * @brief This function is responsible for printing hotel revenue format between dates.
 *
 * @param hotel_id Pointer to the hotel id.
 * @param start_date Pointer to the start date.
 * @param end_date Pointer to the end date.
 * @param cat_reservations Pointer to the reservations catalog.
 * @param output_file Pointer to the output file.
 *
 * @return void.
 */
void get_hotel_revenue_between_dates_format(char *hotel_id, char *start_date, char *end_date, catalogo_Reservations *cat_reservations, FILE *output_file)
{
    int j = 0;
    double total_revenue = 0.0;
    double nights = 0.0;
    GPtrArray *reservations = get_reservations_by_hotel_id2(get_table_reservations(cat_reservations), hotel_id);

    if (strcmp(start_date, end_date) == 0)
    {
        increment_date(end_date);
        j = 1;
    }

    for (int i = 0; i < reservations->len; i++)
    {
        Reservation *reservation = g_ptr_array_index(reservations, i);
        char *begin_date = get_reservation_begin_date(reservation);
        char *end_date2 = get_reservation_end_date(reservation);

        if (is_date_between(begin_date, start_date, end_date) && is_date_between(end_date2, start_date, end_date))
        {

            if (j == 1)
            {
                nights = 1;
            }
            else
            {
                nights = calculate_nights2(begin_date, end_date2);
            }
            if (nights > 0)
            {
                total_revenue += nights * get_reservation_price_per_night(reservation);
            }
        }
        free(begin_date);
        free(end_date2);
    }

    g_ptr_array_free(reservations, TRUE);
    fprintf(output_file, "--- 1 ---\n");
    fprintf(output_file, "revenue: %.0f\n", total_revenue);
}

/**
 * @brief This function is responsible for solving query 1.
 *
 * @param id Pointer to the user id.
 * @param cat_reservations Pointer to the reservations catalog.
 * @param cat_users Pointer to the users catalog.
 * @param cat_flights Pointer to the flights catalog.
 * @param cat_passengers Pointer to the passengers catalog.
 * @param output_file Pointer to the output file.
 *
 * @return void.
 */
void get_info(char *id, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users, catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, FILE *output_file)
{
    char *real_account_status = NULL;
    if (is_valid_user_id(id) == 1)
    {
        User *user = g_hash_table_lookup(get_table_users(cat_users), id);
        if (user == NULL)
        {
            printf("\nError: user_id %s does not exist\n", id);
            return;
        }
        real_account_status = get_user_account_status(user);
        real_account_status[strcspn(real_account_status, "\n")] = '\0';
        if (strcasecmp(real_account_status, "inactive") == 0)
        {
            free(real_account_status);
            return;
        }

        char *user_name = get_user_name(user);
        char *user_sex = get_user_sex(user);
        char *user_age = get_user_birth_date(user);
        char *user_country_code = get_user_country_code(user);
        char *user_passport = get_user_passport(user);
        double user_number_of_flights = get_user_number_of_flights(user);
        double user_number_of_reservations = get_user_number_of_reservations(user);
        double user_total_spent = get_user_total_spent(user);

        fprintf(output_file, "%s;", user_name);
        fprintf(output_file, "%s;", user_sex);
        fprintf(output_file, "%d;", calculate_age(user_age));
        fprintf(output_file, "%s;", user_country_code);
        fprintf(output_file, "%s;", user_passport);
        fprintf(output_file, "%.0f;", user_number_of_flights);
        fprintf(output_file, "%.0f;", user_number_of_reservations);
        fprintf(output_file, "%.3f\n", user_total_spent);

        free(user_name);
        free(user_sex);
        free(user_age);
        free(user_country_code);
        free(user_passport);
        free(real_account_status);
    }
    else if (is_valid_user_id(id) == 2)
    {
        Flight *flight = g_hash_table_lookup(get_table_flights(cat_flights), id);
        if (flight == NULL)
        {
            printf("\nError: flight_id %s does not exist\n", id);
            return;
        }
        char *flight_airline = get_flight_airline(flight);
        char *flight_plane_model = get_flight_plane_model(flight);
        char *flight_origin = get_flight_origin(flight);
        char *flight_destination = get_flight_destination(flight);
        char *flight_schedule_departure_date = get_flight_schedule_departure_date(flight);
        char *flight_schedule_arrival_date = get_flight_schedule_arrival_date(flight);

        fprintf(output_file, "%s;", flight_airline);
        fprintf(output_file, "%s;", flight_plane_model);
        fprintf(output_file, "%s;", flight_origin);
        fprintf(output_file, "%s;", flight_destination);
        fprintf(output_file, "%s;", flight_schedule_departure_date);
        fprintf(output_file, "%s;", flight_schedule_arrival_date);
        fprintf(output_file, "%d;", get_flight_seats_taken(flight));
        fprintf(output_file, "%d\n", calculate_delay(flight));

        free(flight_airline);
        free(flight_plane_model);
        free(flight_origin);
        free(flight_destination);
        free(flight_schedule_departure_date);
        free(flight_schedule_arrival_date);
    }
    else if (is_valid_user_id(id) == 3)
    {
        Reservation *reservation = g_hash_table_lookup(get_table_reservations(cat_reservations), id);
        if (reservation == NULL)
        {
            printf("\nError: reservation user_id %s does not exist\n", id);
            return;
        }
        User *user_reservation = g_hash_table_lookup(get_table_users(cat_users), get_reservation_real_user_id(reservation));
        real_account_status = get_user_account_status(user_reservation);
        if (strcasecmp(real_account_status, "inactive") == 0)
        {
            printf("User %s Inactive", get_reservation_user_id(reservation));
            return;
        }

        char *reservation_hotel_id = get_reservation_hotel_id(reservation);
        char *reservation_hotel_name = get_reservation_hotel_name(reservation);
        int reservation_hotel_stars = get_reservation_hotel_stars(reservation);
        char *reservation_begin_date = get_reservation_begin_date(reservation);
        char *reservation_end_date = get_reservation_end_date(reservation);
        bool reservation_includes_breakfast = get_reservation_includes_breakfast(reservation);
        double reservation_total_price = get_reservation_total_price(reservation);

        fprintf(output_file, "%s;", reservation_hotel_id);
        fprintf(output_file, "%s;", reservation_hotel_name);
        fprintf(output_file, "%d;", reservation_hotel_stars);
        fprintf(output_file, "%s;", reservation_begin_date);
        fprintf(output_file, "%s;", reservation_end_date);
        fprintf(output_file, "%s;", reservation_includes_breakfast ? "True" : "False");
        fprintf(output_file, "%.0f;", calculate_nights2(reservation_begin_date, reservation_end_date));
        fprintf(output_file, "%.3f\n", reservation_total_price);

        free(reservation_hotel_id);
        free(reservation_hotel_name);
        free(reservation_begin_date);
        free(reservation_end_date);
        free(real_account_status);
    }
    else
    {
        printf("\nError: this id %s does not exist\n", id);
        return;
    }
}

/**
 * @brief This function is responsible for solving query 1 format.
 *
 * @param id Pointer to the user id.
 * @param cat_reservations Pointer to the reservations catalog.
 * @param cat_users Pointer to the users catalog.
 * @param cat_flights Pointer to the flights catalog.
 * @param cat_passengers Pointer to the passengers catalog.
 * @param output_file Pointer to the output file.
 *
 * @return void.
 */
void get_info_format(char *id, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users, catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, FILE *output_file)
{
    char *real_account_status2 = NULL;
    if (is_valid_user_id(id) == 1)
    {
        User *user = g_hash_table_lookup(get_table_users(cat_users), id);
        if (user == NULL)
        {
            printf("\nError: user_id %s does not exist\n", id);
            return;
        }
        real_account_status2 = get_user_account_status(user);
        real_account_status2[strcspn(real_account_status2, "\n")] = '\0';
        if (strcasecmp(real_account_status2, "inactive") == 0)
        {
            free(real_account_status2);
            return;
        }

        char *user_name = get_user_name(user);
        char *user_sex = get_user_sex(user);
        char *user_age = get_user_birth_date(user);
        char *user_country_code = get_user_country_code(user);
        char *user_passport = get_user_passport(user);
        double user_number_of_flights = get_user_number_of_flights(user);
        double user_number_of_reservations = get_user_number_of_reservations(user);
        double user_total_spent = get_user_total_spent(user);

        fprintf(output_file, "--- 1 ---\n");
        fprintf(output_file, "name: %s\n", user_name);
        fprintf(output_file, "sex: %s\n", user_sex);
        fprintf(output_file, "age: %d\n", calculate_age(user_age));
        fprintf(output_file, "country_code: %s\n", user_country_code);
        fprintf(output_file, "passport: %s\n", user_passport);
        fprintf(output_file, "number_of_flights: %.0f\n", user_number_of_flights);
        fprintf(output_file, "number_of_reservations: %.0f\n", user_number_of_reservations);
        fprintf(output_file, "total_spent: %.3f\n", user_total_spent);

        free(user_name);
        free(user_sex);
        free(user_age);
        free(user_country_code);
        free(user_passport);
        free(real_account_status2);
    }
    else if (is_valid_user_id(id) == 2)
    {
        Flight *flight = g_hash_table_lookup(get_table_flights(cat_flights), id);
        if (flight == NULL)
        {
            printf("\nError: flight_id %s does not exist\n", id);
            return;
        }

        char *flight_airline = get_flight_airline(flight);
        char *flight_plane_model = get_flight_plane_model(flight);
        char *flight_origin = get_flight_origin(flight);
        char *flight_destination = get_flight_destination(flight);
        char *flight_schedule_departure_date = get_flight_schedule_departure_date(flight);
        char *flight_schedule_arrival_date = get_flight_schedule_arrival_date(flight);

        fprintf(output_file, "--- 1 ---\n");
        fprintf(output_file, "airline: %s\n", flight_airline);
        fprintf(output_file, "plane_model: %s\n", flight_plane_model);
        fprintf(output_file, "origin: %s\n", flight_origin);
        fprintf(output_file, "destination: %s\n", flight_destination);
        fprintf(output_file, "schedule_departure_date: %s\n", flight_schedule_departure_date);
        fprintf(output_file, "schedule_arrival_date: %s\n", flight_schedule_arrival_date);
        fprintf(output_file, "passengers: %d\n", get_flight_seats_taken(flight));
        fprintf(output_file, "delay: %d\n", calculate_delay(flight));

        free(flight_airline);
        free(flight_plane_model);
        free(flight_origin);
        free(flight_destination);
        free(flight_schedule_departure_date);
        free(flight_schedule_arrival_date);
    }
    else if (is_valid_user_id(id) == 3)
    {
        Reservation *reservation = g_hash_table_lookup(get_table_reservations(cat_reservations), id);
        if (reservation == NULL)
        {
            printf("\nError: reservation user_id %s does not exist\n", id);
            return;
        }

        char *reservation_hotel_id = get_reservation_hotel_id(reservation);
        char *reservation_hotel_name = get_reservation_hotel_name(reservation);
        int reservation_hotel_stars = get_reservation_hotel_stars(reservation);
        char *reservation_begin_date = get_reservation_begin_date(reservation);
        char *reservation_end_date = get_reservation_end_date(reservation);
        bool reservation_includes_breakfast = get_reservation_includes_breakfast(reservation);
        double reservation_total_price = get_reservation_total_price(reservation);

        fprintf(output_file, "--- 1 ---\n");
        fprintf(output_file, "hotel_id: %s\n", reservation_hotel_id);
        fprintf(output_file, "hotel_name: %s\n", reservation_hotel_name);
        fprintf(output_file, "hotel_stars: %d\n", reservation_hotel_stars);
        fprintf(output_file, "begin_date: %s\n", reservation_begin_date);
        fprintf(output_file, "end_date: %s\n", reservation_end_date);
        fprintf(output_file, "includes_breakfast: %s\n", reservation_includes_breakfast ? "True" : "False");
        fprintf(output_file, "nights: %.0f\n", calculate_nights2(reservation_begin_date, reservation_end_date));
        fprintf(output_file, "total_price: %.3f\n", reservation_total_price);

        free(reservation_hotel_id);
        free(reservation_hotel_name);
        free(reservation_begin_date);
        free(reservation_end_date);
    }
    else
    {
        printf("\nError: this id %s does not exist\n", id);
        return;
    }
}

/**
 * @brief This function is responsible for listing user, flights or reservations.
 *
 * @param type Pointer to the type.
 * @param id2 Pointer to the id.
 * @param cat_reservations Pointer to the reservations catalog.
 * @param cat_users Pointer to the users catalog.
 * @param cat_flights Pointer to the flights catalog.
 * @param cat_passengers Pointer to the passengers catalog.
 * @param output_file2 Pointer to the output file.
 *
 * @return void.
 */
void list_user_flights_or_reservations2(char *id2, char *type, FILE *output_file2, catalogo_Reservations *cat_reservations, catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, catalogo_Users *cat_users)
{
    User *user = g_hash_table_lookup(get_table_users(cat_users), id2);
    if (user != NULL)
    {
        char *status = get_user_account_status(user);
        status[strcspn(status, "\n")] = '\0';
        if (strcasecmp(status, "inactive") == 0)
        {
            free(status);
            return;
        }
        free(status);
    }
    if (type != NULL && (strcmp(type, "reservations") == 0))
    {
        GPtrArray *reservations = get_reservations_by_user_id2(get_table_reservations(cat_reservations), id2);
        g_ptr_array_sort(reservations, compare_reservations_by_begin_date_desc2);

        guint i;
        if (reservations)
        {
            for (i = 0; i < reservations->len; i++)
            {
                Reservation *reservation = g_ptr_array_index(reservations, i);
                char *reservation_id = get_reservation_id(reservation);
                char *begin_date = get_reservation_begin_date(reservation);
                fprintf(output_file2, "%s;%s\n", reservation_id, begin_date);

                // Free the memory allocated by the get functions
                free(reservation_id);
                free(begin_date);
            }
        }

        g_ptr_array_free(reservations, TRUE);
    }
    else if (type && (strcmp(type, "flights") == 0))
    {
        GPtrArray *flights = get_flights_by_user_id2(get_table_flights(cat_flights), get_table_passengers(cat_passengers), id2);
        g_ptr_array_sort(flights, compare_flights_by_schedule_departure_date_desc2);

        guint i;
        char *copy = NULL;
        char *date = NULL;
        if (flights)
        {
            for (i = 0; i < flights->len; i++)
            {
                Flight *flight = g_ptr_array_index(flights, i);
                char *flight_id = get_flight_id(flight);
                char *flight_departure_date = get_flight_schedule_departure_date(flight);
                copy = strdup(flight_departure_date);
                date = strtok(copy, " ");
                fprintf(output_file2, "%s;%s\n", flight_id, date);

                // Free the memory allocated by the get functions
                free(flight_departure_date);
                free(flight_id);
                free(copy);
            }
        }

        g_ptr_array_free(flights, TRUE);
    }
    else if (!type)
    {
        GPtrArray *reservations = get_reservations_by_user_id2(get_table_reservations(cat_reservations), id2);
        GPtrArray *flights = get_flights_by_user_id2(get_table_flights(cat_flights), get_table_passengers(cat_passengers), id2);
        GPtrArray *combinedList = g_ptr_array_new();
        g_ptr_array_add_range(combinedList, reservations->pdata, reservations->len);
        g_ptr_array_add_range(combinedList, flights->pdata, flights->len);
        g_ptr_array_sort(combinedList, compare_by_date2);

        for (gint i = combinedList->len - 1; i >= 0; i--)
        {
            Reservation *reservation = g_ptr_array_index(combinedList, i);
            Flight *flight = g_ptr_array_index(combinedList, i);
            char *reservation_id = get_reservation_id(reservation);

            if (reservation != NULL && strncmp(reservation_id, "Book", 4) == 0)
            {
                char *begin_date = get_reservation_begin_date(reservation);
                fprintf(output_file2, "%s;%s;reservation\n", reservation_id, begin_date);

                // Free the memory allocated by the get functions
                free(begin_date);
            }
            else if (flight != NULL)
            {
                char *begin_date_1 = get_reservation_begin_date(reservation);
                char *begin_date_real = strtok(begin_date_1, " ");
                fprintf(output_file2, "%s;%s;flight\n", reservation_id, begin_date_real);
                free(begin_date_1);
            }
            free(reservation_id);
        }

        g_ptr_array_free(reservations, TRUE);
        g_ptr_array_free(flights, TRUE);
        g_ptr_array_free(combinedList, TRUE);
    }
}

void tokenize_flight(char **tokens, catalogo_Flights *cat_flights)
{
    Flight *f = create_flight();
    if (!f)
    {
        printf("Memory allocation failed for Flight.\n");
        return;
    }

    set_flight_id(f, tokens[0]);
    set_flight_airline(f, tokens[1]);
    set_flight_plane_model(f, tokens[2]);
    set_flight_total_seats(f, atoi(tokens[3]));
    set_flight_origin(f, tokens[4]);
    set_flight_destination(f, tokens[5]);
    set_flight_schedule_departure_date(f, tokens[6]);
    set_flight_schedule_arrival_date(f, tokens[7]);
    set_flight_real_departure_date(f, tokens[8]);
    set_flight_real_arrival_date(f, tokens[9]);
    set_flight_pilot(f, tokens[10]);
    set_flight_copilot(f, tokens[11]);
    set_flight_notes(f, tokens[12]);

    set_flight_seats_taken(f, 0);

    Flight *existing_flight = g_hash_table_lookup(get_table_flights(cat_flights), get_real_flight_id(f));
    if (existing_flight)
    {
        printf("Flight with id %s already exists. Skipping...\n", get_real_flight_id(f));
        return;
    }
    else
    {
        g_hash_table_insert(get_table_flights(cat_flights), get_real_flight_id(f), f);
    }
}

void tokenize_passenger(char **tokens, catalogo_Passengers *cat_passengers, catalogo_Flights *cat_flights, catalogo_Users *cat_users)
{
    Passenger *p = create_passenger();
    if (!p)
    {
        printf("Memory allocation failed for Passenger.\n");
        return;
    }

    set_passenger_flight_id(p, tokens[0]);
    set_passenger_user_id(p, tokens[1]);

    char *flight_id = get_passenger_flight_id(p);
    Flight *f = g_hash_table_lookup(get_table_flights(cat_flights), flight_id);
    if (f)
        set_flight_seats_taken(f, get_flight_seats_taken(f) + 1);

    char *passenger_user_id = get_real_passenger_user_id(p);

    passenger_user_id[strlen(passenger_user_id) - 1] = '\0';
    char *user_id = get_passenger_user_id(p);
    User *u = g_hash_table_lookup(get_table_users(cat_users), user_id);
    if (u)
        set_user_number_of_flights(u, get_user_number_of_flights(u) + 1);

    if (flight_id && user_id)
    {
        size_t flight_length = strlen(flight_id);
        size_t user_length = strlen(user_id);

        setup_passenger_id(p, flight_length, user_length);

        if (get_real_passenger_id(p))
        {
            strcpy(get_real_passenger_id(p), flight_id); // Copy flight_id to p->passenger_id
            strcat(get_real_passenger_id(p), "_");       // Append the '_' character at the end of p->passenger_id
            strcat(get_real_passenger_id(p), user_id);   // Concatenate p->user_id to p->passenger_id
        }
        else
        {
            printf("Memory allocation failed for passenger_id.\n");
        }
    }
    else
    {
        printf("Invalid input line for passenger.\n");
    }
    free(flight_id);
    free(user_id);

    if (get_real_passenger_id(p))
    {
        Passenger *existing_passenger = g_hash_table_lookup(get_table_passengers(cat_passengers), get_real_passenger_id(p));
        if (existing_passenger)
        {
            printf("Passenger with passenger_id %s already exists. Skipping...\n", get_real_passenger_id(p));
            return;
        }
        else
        {
            g_hash_table_insert(get_table_passengers(cat_passengers), get_real_passenger_id(p), p);
            // printf("Passenger with passenger_id %s successfully added.\n", p->passenger_id);
        }
    }
}

void tokenize_reservation(char **tokens, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users)
{
    Reservation *r = create_reservation();
    if (!r)
    {
        printf("Memory allocation failed for Reservation.\n");
        return;
    }

    set_reservation_id(r, tokens[0]);
    set_reservation_user_id(r, tokens[1]);
    set_reservation_hotel_id(r, tokens[2]);
    set_reservation_hotel_name(r, tokens[3]);
    set_reservation_hotel_stars(r, atoi(tokens[4]));
    set_reservation_city_tax(r, atof(tokens[5]));
    set_reservation_adress(r, tokens[6]);
    set_reservation_begin_date(r, tokens[7]);
    set_reservation_end_date(r, tokens[8]);
    set_reservation_price_per_night(r, atof(tokens[9]));

    if (strlen(tokens[10]) == 0 || strcmp(tokens[10], "0") == 0 || strcmp(tokens[10], "false") == 0 || strcmp(tokens[10], "f") == 0)
        set_reservation_includes_breakfast(r, false);
    else
        set_reservation_includes_breakfast(r, true);

    set_reservation_room_details(r, tokens[11]);
    set_reservation_rating(r, atoi(tokens[12]));
    set_reservation_comment(r, tokens[13]);

    char *reservation_id = get_reservation_id(r);
    Reservation *existing_reservation = g_hash_table_lookup(get_table_reservations(cat_reservations), reservation_id);
    if (existing_reservation)
    {
        printf("Reservation with id %s already exists. Skipping...\n", reservation_id);
        free(reservation_id);
        return;
    }
    else
    {
        char *reservation_begin_date = get_reservation_begin_date(r);
        char *reservation_end_date = get_reservation_end_date(r);
        char *reservation_user_id = get_reservation_user_id(r);
        double nights = calculate_nights2(reservation_begin_date, reservation_end_date);
        double total_price = get_reservation_price_per_night(r) * (1 + 0.01 * get_reservation_city_tax(r)) * nights;
        set_reservation_total_price(r, total_price);
        User *u = g_hash_table_lookup(get_table_users(cat_users), reservation_user_id);
        if (u)
        {
            set_user_number_of_reservations(u, get_user_number_of_reservations(u) + 1);
            set_user_total_spent(u, get_user_total_spent(u) + total_price);
        }
        g_hash_table_insert(get_table_reservations(cat_reservations), get_real_reservation_id(r), r);
        free(reservation_id);
        free(reservation_begin_date);
        free(reservation_end_date);
        free(reservation_user_id);
    }
}

void tokenize_user(char **tokens, catalogo_Users *cat_users)
{
    User *u = create_user();
    if (!u)
    {
        printf("Memory allocation failed for User.\n");
        return;
    }

    set_user_id(u, tokens[0]);
    set_user_name(u, tokens[1]);
    set_user_email(u, tokens[2]);
    set_user_phone_number(u, tokens[3]);
    set_user_birth_date(u, tokens[4]);
    set_user_sex(u, tokens[5]);
    set_user_passport(u, tokens[6]);
    set_user_country_code(u, tokens[7]);
    set_user_adress(u, tokens[8]);
    set_user_account_creation(u, tokens[9]);
    set_user_pay_method(u, tokens[10]);
    set_user_account_status(u, tokens[11]);
    set_user_number_of_reservations(u, 0);
    set_user_number_of_flights(u, 0);
    set_user_total_spent(u, 0);

    User *existing_user = g_hash_table_lookup(get_table_users(cat_users), get_real_user_id(u));
    if (existing_user)
    {
        printf("User with id %s already exists. Skipping...\n", get_real_user_id(u));
        return;
    }
    else
    {
        g_hash_table_insert(get_table_users(cat_users), get_real_user_id(u), u);
    }
}