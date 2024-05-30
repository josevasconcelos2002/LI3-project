#ifndef VALIDATION_H
#define VALIDATION_H
#include "gestorFlights.h"
#include "gestorPassengers.h"
#include "gestorReservations.h"
#include "gestorUsers.h"

void limpar_dados_validos(char *dataset_path, catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users);

#endif