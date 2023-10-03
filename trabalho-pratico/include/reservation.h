#ifndef RESERVATION_H
#define RESERVATION_H

#include <stdbool.h>

typedef struct reservation Reservation;

int get_reservation_id(Reservation *r);
int get_reservation_user_id(Reservation *r);
int get_reservation_hotel_id(Reservation *r);
int get_reservation_hotel_stars(Reservation *r);
double get_reservation_city_tax(Reservation *r);
char *get_reservation_adress(Reservation *r);
char *get_reservation_begin_date(Reservation *r);
char *get_reservation_end_date(Reservation *r);
double get_reservation_price_per_night(Reservation *r);
bool get_reservation_includes_breakfast(Reservation *r);
char *get_reservation_room_details(Reservation *r);
double get_reservation_rating(Reservation *r);
char *get_reservation_comment(Reservation *r);

#endif