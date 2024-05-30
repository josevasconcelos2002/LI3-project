#ifndef INTERFACE_H
#define INTERFACE_H

#include "flight.h"
#include "passenger.h"
#include "reservation.h"
#include "user.h"

void menu_queries(catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users);
void menu_interativo(int argc, char **argv);
void logo(int argc, char **argv);

#endif