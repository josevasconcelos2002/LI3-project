#include "../../include/reservation.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


struct Reservation
{
    char *id;
    char *user_id;
    char *hotel_id;
    char *hotel_name;
    int hotel_stars;
    double city_tax;
    char *adress;
    char *begin_date;
    char *end_date;
    double price_per_night;
    bool includes_breakfast;
    char *room_details;
    double rating;
    char *comment;
    double total_price;
};

struct Reservation* create_reservation(){
    Reservation *new_reservation = (Reservation *)malloc(sizeof(Reservation));
    if(new_reservation){
        new_reservation->id = NULL;
        new_reservation->user_id = NULL;
        new_reservation->hotel_id = NULL;
        new_reservation->hotel_name = NULL;
        new_reservation->hotel_stars = 0;
        new_reservation->city_tax = 0;
        new_reservation->adress = NULL;
        new_reservation->begin_date = NULL;
        new_reservation->end_date = NULL;
        new_reservation->price_per_night = 0;
        new_reservation->includes_breakfast = false;
        new_reservation->room_details = NULL;
        new_reservation->rating = 0;
        new_reservation->comment = NULL;
        new_reservation->total_price = 0;
    }
    return new_reservation;

}
/**
 * @brief This function is responsible for returning the reservation id.
 *
 * @param r Pointer to the reservation.
 *
 * @return char*.
 */
char *get_reservation_id(Reservation *r)
{
    char *reservation_id = strdup(r->id);
    return reservation_id;
}

char *get_real_reservation_id(Reservation *r)
{
    return r->id;
}
/**
 * @brief This function is responsible for setting the reservation id.
 *
 * @param r Pointer to the reservation.
 * @param reservation_id Pointer to the new reservation id.
 *
 * @return void.
 */
void set_reservation_id(Reservation *r, char *reservation_id)
{
    if (r)
    {
        r->id = strdup(reservation_id);
    }
}

/**
 * @brief This function is responsible for returning the reservation user id.
 *
 * @param r Pointer to the reservation.
 *
 * @return char*.
 */
char *get_reservation_user_id(Reservation *r)
{
    char *user_id = strdup(r->user_id);
    return user_id;
}

char *get_reservation_real_user_id(Reservation *r)
{
    return r->user_id;
}

/**
 * @brief This function is responsible for setting the reservation user id.
 *
 * @param r Pointer to the reservation.
 * @param user_id Pointer to the new user id.
 *
 * @return void.
 */
void set_reservation_user_id(Reservation *r, char *user_id)
{
    if (r)
    {
        r->user_id = strdup(user_id);
    }
}

/**
 * @brief This function is responsible for returning the reservation hotel id.
 *
 * @param r Pointer to the reservation.
 *
 * @return char*.
 */
char *get_reservation_hotel_id(Reservation *r)
{
    char *hotel_id = strdup(r->hotel_id);
    return hotel_id;
}

/**
 * @brief This function is responsible for setting the reservation hotel id.
 *
 * @param r Pointer to the reservation.
 * @param hotel_id Pointer to the new hotel id.
 *
 * @return void.
 */
void set_reservation_hotel_id(Reservation *r, char *hotel_id)
{
    if (r)
    {
        r->hotel_id = strdup(hotel_id);
    }
}

/**
 * @brief This function is responsible for returning the reservation hotel name.
 *
 * @param r Pointer to the reservation.
 *
 * @return char*.
 */
char *get_reservation_hotel_name(Reservation *r)
{
    char *hotel_name = strdup(r->hotel_name);
    return hotel_name;
}

/**
 * @brief This function is responsible for setting the reservation hotel name.
 *
 * @param r Pointer to the reservation.
 * @param hotel_name Pointer to the new hotel name.
 *
 * @return void.
 */
void set_reservation_hotel_name(Reservation *r, char *hotel_name)
{
    if (r)
    {
        r->hotel_name = strdup(hotel_name);
    }
}

/**
 * @brief This function is responsible for returning the reservation hotel stars.
 *
 * @param r Pointer to the reservation.
 *
 * @return int.
 */
int get_reservation_hotel_stars(Reservation *r)
{
    return r->hotel_stars;
}

/**
 * @brief This function is responsible for setting the reservation hotel stars.
 *
 * @param r Pointer to the reservation.
 * @param hotel_stars New hotel stars.
 *
 * @return void.
 */
void set_reservation_hotel_stars(Reservation *r, int hotel_stars)
{
    if (r)
    {
        r->hotel_stars = hotel_stars;
    }
}

/**
 * @brief This function is responsible for returning the reservation city tax.
 *
 * @param r Pointer to the reservation.
 *
 * @return double.
 */
double get_reservation_city_tax(Reservation *r)
{
    return r->city_tax;
}

/**
 * @brief This function is responsible for setting the reservation city tax.
 *
 * @param r Pointer to the reservation.
 * @param city_tax New city tax.
 *
 * @return void.
 */
void set_reservation_city_tax(Reservation *r, double city_tax)
{
    if (r)
    {
        r->city_tax = city_tax;
    }
}

/**
 * @brief This function is responsible for returning the reservation adress.
 *
 * @param r Pointer to the reservation.
 *
 * @return char*.
 */
char *get_reservation_adress(Reservation *r)
{
    char *adress = strdup(r->adress);
    return adress;
}

/**
 * @brief This function is responsible for setting the reservation adress.
 *
 * @param r Pointer to the reservation.
 * @param adress Pointer to the new adress.
 *
 * @return void.
 */
void set_reservation_adress(Reservation *r, char *adress)
{
    if (r)
    {
        r->adress = strdup(adress);
    }
}

/**
 * @brief This function is responsible for returning the reservation begin date.
 *
 * @param r Pointer to the reservation.
 *
 * @return char*.
 */
char *get_reservation_begin_date(Reservation *r)
{
    char *begin_date = strdup(r->begin_date);
    return begin_date;
}

/**
 * @brief This function is responsible for setting the reservation begin date.
 *
 * @param r Pointer to the reservation.
 * @param begin_date Pointer to the new begin date.
 *
 * @return void.
 */
void set_reservation_begin_date(Reservation *r, char *begin_date)
{
    if (r)
    {
        r->begin_date = strdup(begin_date);
    }
}

/**
 * @brief This function is responsible for returning the reservation end date.
 *
 * @param r Pointer to the reservation.
 *
 * @return char*.
 */
char *get_reservation_end_date(Reservation *r)
{
    char *end_date = strdup(r->end_date);
    return end_date;
}

/**
 * @brief This function is responsible for setting the reservation end date.
 *
 * @param r Pointer to the reservation.
 * @param end_date Pointer to the new end date.
 *
 * @return void.
 */
void set_reservation_end_date(Reservation *r, char *end_date)
{
    if (r)
    {
        r->end_date = strdup(end_date);
    }
}

/**
 * @brief This function is responsible for returning the reservation price per night.
 *
 * @param r Pointer to the reservation.
 *
 * @return double.
 */
double get_reservation_price_per_night(Reservation *r)
{
    return r->price_per_night;
}

/**
 * @brief This function is responsible for setting the reservation price per night.
 *
 * @param r Pointer to the reservation.
 * @param price_per_night New price per night.
 *
 * @return void.
 */
void set_reservation_price_per_night(Reservation *r, double price_per_night)
{
    if (r)
    {
        r->price_per_night = price_per_night;
    }
}

/**
 * @brief This function is responsible for returning the reservation includes breakfast.
 *
 * @param r Pointer to the reservation.
 *
 * @return bool.
 */
bool get_reservation_includes_breakfast(Reservation *r)
{
    return r->includes_breakfast;
}

/**
 * @brief This function is responsible for setting the reservation includes breakfast.
 *
 * @param r Pointer to the reservation.
 * @param includes_breakfast New includes breakfast.
 *
 * @return void.
 */
void set_reservation_includes_breakfast(Reservation *r, bool includes_breakfast)
{
    if (r)
    {
        r->includes_breakfast = includes_breakfast;
    }
}

/**
 * @brief This function is responsible for returning the reservation room details.
 *
 * @param r Pointer to the reservation.
 *
 * @return char*.
 */
char *get_reservation_room_details(Reservation *r)
{
    char *room_details = strdup(r->room_details);
    return room_details;
}

/**
 * @brief This function is responsible for setting the reservation room details.
 *
 * @param r Pointer to the reservation.
 * @param room_details Pointer to the new room details.
 *
 * @return void.
 */
void set_reservation_room_details(Reservation *r, char *room_details)
{
    if (r)
    {
        r->room_details = strdup(room_details);
    }
}

/**
 * @brief This function is responsible for returning the reservation rating.
 *
 * @param r Pointer to the reservation.
 *
 * @return double.
 */
double get_reservation_rating(Reservation *r)
{
    return r->rating;
}

/**
 * @brief This function is responsible for setting the reservation rating.
 *
 * @param r Pointer to the reservation.
 * @param rating New rating.
 *
 * @return void.
 */
void set_reservation_rating(Reservation *r, double rating)
{
    if (r)
    {
        r->rating = rating;
    }
}

/**
 * @brief This function is responsible for returning the reservation comment.
 *
 * @param r Pointer to the reservation.
 *
 * @return char*.
 */
char *get_reservation_comment(Reservation *r)
{
    char *comment = strdup(r->comment);
    return comment;
}

/**
 * @brief This function is responsible for setting the reservation comment.
 *
 * @param r Pointer to the reservation.
 * @param comment Pointer to the new comment.
 *
 * @return void.
 */
void set_reservation_comment(Reservation *r, char *comment)
{
    if (r)
    {
        r->comment = strdup(comment);
    }
}

/**
 * @brief This function is responsible for returning the reservation total price.
 *
 * @param r Pointer to the reservation.
 *
 * @return double.
 */
double get_reservation_total_price(Reservation *r)
{
    return r->total_price;
}

/**
 * @brief This function is responsible for setting the reservation total price.
 *
 * @param r Pointer to the reservation.
 * @param total_price New total price.
 *
 * @return void.
 */
void set_reservation_total_price(Reservation *r, double total_price)
{
    if (r)
    {
        r->total_price = total_price;
    }
}

/**
 * @brief This function is responsible for freeing the reservation.
 *
 * @param r Pointer to the reservation.
 *
 * @return void.
 */
void free_reservation(Reservation *r)
{
    free(r->id);
    free(r->user_id);
    free(r->hotel_id);
    free(r->hotel_name);
    free(r->adress);
    free(r->begin_date);
    free(r->end_date);
    free(r->room_details);
    free(r->comment);
    free(r);
}

/**
 * @brief This function is responsible for printing the reservation.
 *
 * @param r Pointer to the reservation.
 *
 * @return void.
 */
void print_reservation(Reservation *r)
{
    printf("ID: %s\n", get_reservation_id(r));
    printf("User ID: %s\n", get_reservation_user_id(r));
    printf("Hotel ID: %s\n", get_reservation_hotel_id(r));
    printf("Hotel name: %s\n", get_reservation_hotel_name(r));
    printf("Hotel stars: %d\n", get_reservation_hotel_stars(r));
    printf("City tax: %.2f\n", get_reservation_city_tax(r));
    printf("Adress: %s\n", get_reservation_adress(r));
    printf("Begin date: %s\n", get_reservation_begin_date(r));
    printf("End date: %s\n", get_reservation_end_date(r));
    printf("Price per night: %.2f\n", get_reservation_price_per_night(r));
    printf("Includes breakfast: %d\n", get_reservation_includes_breakfast(r));
    printf("Room details: %s\n", get_reservation_room_details(r));
    printf("Rating: %.2f\n", get_reservation_rating(r));
    printf("Total Price: %.3f\n", get_reservation_total_price(r));
}