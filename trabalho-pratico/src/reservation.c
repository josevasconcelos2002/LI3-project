#include "reservation.h"
#include <string.h>
#include <stdbool.h>

struct reservation
{
    int id;
    int user_id;
    int hotel_id;
    char *hotel_name;
    int hotel_stars; // int ou double ??
    double city_tax;
    char *adress;
    char *begin_date;
    char *end_date;
    double price_per_night;
    bool includes_breakfast;
    char *room_details;
    double rating;
    char *comment;
};

int get_reservation_id(Reservation *r)
{
    return r->id;
}

int get_reservation_user_id(Reservation *r)
{
    return r->user_id;
}

int get_reservation_hotel_id(Reservation *r)
{
    return r->hotel_id;
}

char *get_reservation_hotel_name(Reservation *r)
{
    char *hotel_name = strdup(r->hotel_name);
    return hotel_name;
}

int get_reservation_hotel_stars(Reservation *r)
{
    return r->hotel_stars;
}

double get_reservation_city_tax(Reservation *r)
{
    return r->city_tax;
}

char *get_reservation_adress(Reservation *r)
{
    char *adress = strdup(r->adress);
    return adress;
}

char *get_reservation_begin_date(Reservation *r)
{
    char *begin_date = strdup(r->begin_date);
    return begin_date;
}

char *get_reservation_end_date(Reservation *r)
{
    char *end_date = strdup(r->end_date);
    return end_date;
}

double get_reservation_price_per_night(Reservation *r)
{
    return r->price_per_night;
}

bool get_reservation_includes_breakfast(Reservation *r)
{
    return r->includes_breakfast;
}

char *get_reservation_room_details(Reservation *r)
{
    char *room_details = strdup(r->room_details);
    return room_details;
}

double get_reservation_rating(Reservation *r)
{
    return r->rating;
}

char *get_reservation_comment(Reservation *r)
{
    char *comment = strdup(r->comment);
    return comment;
}