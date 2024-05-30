#ifndef PASSENGER_H
#define PASSENGER_H
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <locale.h>




typedef struct Passenger Passenger;
struct Passenger* create_passenger();

char *get_passenger_id(Passenger *p);
char *get_real_passenger_id(Passenger *p);
void set_passenger_id(Passenger *p, char *passenger_id);
void setup_passenger_id(Passenger *p, size_t size_f, size_t size_u);
char *get_passenger_flight_id(Passenger *p);
void set_passenger_flight_id(Passenger *p, char *flight_id);
char *get_passenger_user_id(Passenger *p);
char *get_real_passenger_user_id(Passenger *p);
void set_passenger_user_id(Passenger *p, char *user_id);
void free_passenger(Passenger *p);
void print_passenger(Passenger *p);

#endif