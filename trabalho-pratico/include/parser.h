#ifndef PARSER_H
#define PARSER_H
#include "gestorFlights.h"
#include "gestorPassengers.h"
#include "gestorReservations.h"
#include "gestorUsers.h"
#include <stdio.h>

void parse_flight_line2(char *line, catalogo_Flights *cat_flights);
void parse_passenger_line2(char *line, catalogo_Passengers *cat_passengers,catalogo_Flights *cat_flights, catalogo_Users *cat_users);
void parse_reservation_line2(char *line, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users);
void parse_user_line2(char *line, catalogo_Users *cat_users);

#endif