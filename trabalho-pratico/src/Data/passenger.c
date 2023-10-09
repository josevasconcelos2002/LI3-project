#include "../../include/passenger.h"

struct passenger
{
    int flight_id;
    int user_id;
};

int get_passenger_flight_id(Passenger *p)
{
    return p->flight_id;
}

int get_passenger_user_id(Passenger *p)
{
    return p->user_id;
}