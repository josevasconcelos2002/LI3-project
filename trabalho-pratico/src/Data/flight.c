#include "../../include/flight.h"
#include <string.h>

struct flight
{
    int id;
    char *airline;
    char *plane_model;
    int total_seats;
    char *origin;
    char *destination;
    char *schedule_departure_date;
    char *schedule_arrival_date;
    char *real_departure_date;
    char *real_arrival_date;
    char *pilot;
    char *copilot;
    char *notes;
};

int get_flight_id(Flight *f)
{
    return f->id;
}

char *get_flight_airline(Flight *f)
{
    char *airline = strdup(f->airline);
    return airline;
}

char *get_flight_plane_model(Flight *f)
{
    char *plane_model = strdup(f->plane_model);
    return plane_model;
}

int get_flight_total_seats(Flight *f)
{
    return f->total_seats;
}

char *get_flight_origin(Flight *f)
{
    char *origin = strdup(f->origin);
    return origin;
}

char *get_flight_destination(Flight *f)
{
    char *destination = strdup(f->destination);
    return destination;
}

char *get_flight_schedule_departure_date(Flight *f)
{
    char *schedule_departure_date = strdup(f->schedule_departure_date);
    return schedule_departure_date;
}

char *get_flight_schedule_arrival_date(Flight *f)
{
    char *schedule_arrival_date = strdup(f->schedule_arrival_date);
    return schedule_arrival_date;
}

char *get_flight_real_departure_date(Flight *f)
{
    char *real_departure_date = strdup(f->real_departure_date);
    return real_departure_date;
}

char *get_flight_real_arrival_date(Flight *f)
{
    char *real_arrival_date = strdup(f->real_arrival_date);
    return real_arrival_date;
}

char *get_flight_pilot(Flight *f)
{
    char *pilot = strdup(f->pilot);
    return pilot;
}

char *get_flight_copilot(Flight *f)
{
    char *copilot = strdup(f->copilot);
    return copilot;
}

char *get_flight_notes(Flight *f)
{
    char *notes = strdup(f->notes);
    return notes;
}