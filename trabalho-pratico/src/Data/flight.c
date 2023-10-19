#include "../../include/flight.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *get_flight_id(Flight *f)
{
    char *flight_id = NULL;
    if (f)
    {
        flight_id = strdup(f->id);
    }
    return flight_id;
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

void free_flight(Flight *f)
{
    free(f->airline);
    free(f->plane_model);
    free(f->origin);
    free(f->destination);
    free(f->schedule_departure_date);
    free(f->schedule_arrival_date);
    free(f->real_departure_date);
    free(f->real_arrival_date);
    free(f->pilot);
    free(f->copilot);
    free(f->notes);
    free(f);
}

void print_flight(Flight *f)
{
    printf("id: %s\n", get_flight_id(f));
    printf("airline: %s\n", get_flight_airline(f));
    printf("plane model: %s\n", get_flight_plane_model(f));
    printf("total seats: %d\n", get_flight_total_seats(f));
    printf("origin: %s\n", get_flight_origin(f));
    printf("destination: %s\n", get_flight_destination(f));
    printf("schedule departure date: %s\n", get_flight_schedule_departure_date(f));
    printf("schedule arrival date: %s\n", get_flight_schedule_arrival_date(f));
    printf("real departure date: %s\n", get_flight_real_departure_date(f));
    printf("real arrival date: %s\n", get_flight_real_arrival_date(f));
    printf("pilot: %s\n", get_flight_pilot(f));
    printf("copilot: %s\n", get_flight_copilot(f));
    printf("notes: %s\n", get_flight_notes(f));
}