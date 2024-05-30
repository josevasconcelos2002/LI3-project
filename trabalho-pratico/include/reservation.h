#ifndef RESERVATION_H
#define RESERVATION_H

#include <stdbool.h>


typedef struct Reservation Reservation;

struct Reservation* create_reservation();


char *get_reservation_id(Reservation *r);
char *get_real_reservation_id(Reservation *r);
void set_reservation_id(Reservation *r, char *reservation_id);
char *get_reservation_user_id(Reservation *r);
char *get_reservation_real_user_id(Reservation *r);
void set_reservation_user_id(Reservation *r, char *user_id);
char *get_reservation_hotel_id(Reservation *r);
void set_reservation_hotel_id(Reservation *r, char *hotel_id);
int get_reservation_hotel_stars(Reservation *r);
void set_reservation_hotel_stars(Reservation *r, int hotel_stars);
char *get_reservation_hotel_name(Reservation *r);
void set_reservation_hotel_name(Reservation *r, char *hotel_name);
double get_reservation_city_tax(Reservation *r);
void set_reservation_city_tax(Reservation *r, double city_tax);
char *get_reservation_adress(Reservation *r);
void set_reservation_adress(Reservation *r, char *adress);
char *get_reservation_begin_date(Reservation *r);
void set_reservation_begin_date(Reservation *r, char *begin_date);
char *get_reservation_end_date(Reservation *r);
void set_reservation_end_date(Reservation *r, char *end_date);
double get_reservation_price_per_night(Reservation *r);
void set_reservation_price_per_night(Reservation *r, double price_per_night);
bool get_reservation_includes_breakfast(Reservation *r);
void set_reservation_includes_breakfast(Reservation *r, bool includes_breakfast);
char *get_reservation_room_details(Reservation *r);
void set_reservation_room_details(Reservation *r, char *room_details);
double get_reservation_rating(Reservation *r);
void set_reservation_rating(Reservation *r, double rating);
double get_reservation_total_price(Reservation *r);
void set_reservation_total_price(Reservation *r, double total_price);
void set_reservation_comment(Reservation *r, char *comment);
void free_reservation(Reservation *r);
void print_reservation(Reservation *r);

#endif