#include "../../include/flight.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


struct Flight
{
    char *id;
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
    int seats_taken;
};

struct Flight* create_flight(){
    Flight *f = (Flight *)malloc(sizeof(Flight));
    if(f){

        f->id = NULL;
        f->airline = NULL;
        f->plane_model = NULL;
        f->total_seats = 0;
        f->origin = NULL;
        f->destination = NULL;
        f->schedule_departure_date = NULL;
        f->schedule_arrival_date = NULL;
        f->real_departure_date = NULL;
        f->real_arrival_date = NULL;
        f->pilot = NULL;
        f->copilot = NULL;
        f->notes = NULL;
        f->seats_taken = 0;
    }
    return f;
}
/**
 * @brief This function is responsible for returning the flight id.
 *
 * @param f Pointer to the flight.
 *
 * @return char*.
 */
char *get_flight_id(Flight *f)
{
    char *flight_id = NULL;
    if (f)
    {
        flight_id = strdup(f->id);
    }
    return flight_id;
}

char *get_real_flight_id(Flight *f){
    return f->id;
}

/**
 * @brief This function is responsible for setting the flight id.
 *
 * @param f Pointer to the flight.
 * @param id Pointer to the id.
 *
 * @return void.
 */
void set_flight_id(Flight *f, char *id)
{
    if (f)
    {
        f->id = strdup(id);
    }
}

/**
 * @brief This function is responsible for returning the flight airline.
 *
 * @param f Pointer to the flight.
 *
 * @return char*.
 */
char *get_flight_airline(Flight *f)
{
    char *airline = strdup(f->airline);
    return airline;
}

/**
 * @brief This function is responsible for setting the flight airline.
 *
 * @param f Pointer to the flight.
 * @param airline Pointer to the airline.
 *
 * @return void.
 */
void set_flight_airline(Flight *f, char *airline)
{
    if (f)
    {
        f->airline = strdup(airline);
    }
}

/**
 * @brief This function is responsible for returning the flight plane model.
 *
 * @param f Pointer to the flight.
 *
 * @return char*.
 */
char *get_flight_plane_model(Flight *f)
{
    char *plane_model = strdup(f->plane_model);
    return plane_model;
}

/**
 * @brief This function is responsible for setting the flight plane model.
 *
 * @param f Pointer to the flight.
 * @param plane_model Pointer to the plane model.
 *
 * @return void.
 */
void set_flight_plane_model(Flight *f, char *plane_model)
{
    if (f)
    {
        f->plane_model = strdup(plane_model);
    }
}

/**
 * @brief This function is responsible for returning the flight total seats.
 *
 * @param f Pointer to the flight.
 *
 * @return int.
 */
int get_flight_total_seats(Flight *f)
{
    return f->total_seats;
}

/**
 * @brief This function is responsible for setting the flight total seats.
 *
 * @param f Pointer to the flight.
 * @param total_seats
 *
 * @return void.
 */
void set_flight_total_seats(Flight *f, int total_seats)
{
    if (f)
    {
        f->total_seats = total_seats;
    }
}

/**
 * @brief This function is responsible for returning the flight origin.
 *
 * @param f Pointer to the flight.
 *
 * @return char*.
 */
char *get_flight_origin(Flight *f)
{
    char *origin = strdup(f->origin);
    return origin;
}

/**
 * @brief This function is responsible for setting the flight origin.
 *
 * @param f Pointer to the flight.
 * @param origin Pointer to the origin.
 *
 * @return void.
 */
void set_flight_origin(Flight *f, char *origin)
{
    if (f)
    {
        f->origin = strdup(origin);
    }
}

/**
 * @brief This function is responsible for returning the flight destination.
 *
 * @param f Pointer to the flight.
 *
 * @return char*.
 */
char *get_flight_destination(Flight *f)
{
    char *destination = strdup(f->destination);
    return destination;
}

/**
 * @brief This function is responsible for setting the flight destination.
 *
 * @param f Pointer to the flight.
 * @param destination Pointer to the destination.
 *
 * @return void.
 */
void set_flight_destination(Flight *f, char *destination)
{
    if (f)
    {
        f->destination = strdup(destination);
    }
}

/**
 * @brief This function is responsible for returning the flight schedule departure date.
 *
 * @param f Pointer to the flight.
 *
 * @return char*.
 */
char *get_flight_schedule_departure_date(Flight *f)
{
    char *schedule_departure_date = strdup(f->schedule_departure_date);
    return schedule_departure_date;
}

/**
 * @brief This function is responsible for setting the flight schedule departure date.
 *
 * @param f Pointer to the flight.
 * @param schedule_departure_date Pointer to the schedule departure date.
 *
 * @return void.
 */
void set_flight_schedule_departure_date(Flight *f, char *schedule_departure_date)
{
    if (f)
    {
        f->schedule_departure_date = strdup(schedule_departure_date);
    }
}

/**
 * @brief This function is responsible for returning the flight schedule arrival date.
 *
 * @param f Pointer to the flight.
 *
 * @return char*.
 */
char *get_flight_schedule_arrival_date(Flight *f)
{
    char *schedule_arrival_date = strdup(f->schedule_arrival_date);
    return schedule_arrival_date;
}

/**
 * @brief This function is responsible for setting the flight schedule arrival date.
 *
 * @param f Pointer to the flight.
 * @param schedule_arrival_date Pointer to the schedule arrival date.
 *
 * @return void.
 */
void set_flight_schedule_arrival_date(Flight *f, char *schedule_arrival_date)
{
    if (f)
    {
        f->schedule_arrival_date = strdup(schedule_arrival_date);
    }
}

/**
 * @brief This function is responsible for returning the flight real departure date.
 *
 * @param f Pointer to the flight.
 *
 * @return char*.
 */
char *get_flight_real_departure_date(Flight *f)
{
    char *real_departure_date = strdup(f->real_departure_date);
    return real_departure_date;
}

/**
 * @brief This function is responsible for setting the flight real departure date.
 *
 * @param f Pointer to the flight.
 * @param real_departure_date Pointer to the real departure date.
 *
 * @return void.
 */
void set_flight_real_departure_date(Flight *f, char *real_departure_date)
{
    if (f)
    {
        f->real_departure_date = strdup(real_departure_date);
    }
}

/**
 * @brief This function is responsible for returning the flight real arrival date.
 *
 * @param f Pointer to the flight.
 *
 * @return char*.
 */
char *get_flight_real_arrival_date(Flight *f)
{
    char *real_arrival_date = strdup(f->real_arrival_date);
    return real_arrival_date;
}

/**
 * @brief This function is responsible for setting the flight real arrival date.
 *
 * @param f Pointer to the flight.
 * @param real_arrival_date Pointer to the real arrival date.
 *
 * @return void.
 */
void set_flight_real_arrival_date(Flight *f, char *real_arrival_date)
{
    if (f)
    {
        f->real_arrival_date = strdup(real_arrival_date);
    }
}

/**
 * @brief This function is responsible for returning the flight pilot.
 *
 * @param f Pointer to the flight.
 *
 * @return char*.
 */
char *get_flight_pilot(Flight *f)
{
    char *pilot = strdup(f->pilot);
    return pilot;
}

/**
 * @brief This function is responsible for setting the flight pilot.
 *
 * @param f Pointer to the flight.
 * @param pilot Pointer to the pilot.
 *
 * @return void.
 */
void set_flight_pilot(Flight *f, char *pilot)
{
    if (f)
    {
        f->pilot = strdup(pilot);
    }
}

/**
 * @brief This function is responsible for returning the flight copilot.
 *
 * @param f Pointer to the flight.
 *
 * @return char*.
 */
char *get_flight_copilot(Flight *f)
{
    char *copilot = strdup(f->copilot);
    return copilot;
}

/**
 * @brief This function is responsible for setting the flight copilot.
 *
 * @param f Pointer to the flight.
 * @param copilot Pointer to the copilot.
 *
 * @return void.
 */
void set_flight_copilot(Flight *f, char *copilot)
{
    if (f)
    {
        f->copilot = strdup(copilot);
    }
}

/**
 * @brief This function is responsible for returning the flight notes.
 *
 * @param f Pointer to the flight.
 *
 * @return char*.
 */
char *get_flight_notes(Flight *f)
{
    char *notes = strdup(f->notes);
    return notes;
}

/**
 * @brief This function is responsible for setting the flight notes.
 *
 * @param f Pointer to the flight.
 * @param notes Pointer to the notes.
 *
 * @return void.
 */
void set_flight_notes(Flight *f, char *notes)
{
    if (f)
    {
        f->notes = strdup(notes);
    }
}

/**
 * @brief This function is responsible for returning the flight seats taken.
 *
 * @param f Pointer to the flight.
 *
 * @return int.
 */
int get_flight_seats_taken(Flight *f)
{
    return f->seats_taken;
}

/**
 * @brief This function is responsible for setting the flight seats taken.
 *
 * @param f Pointer to the flight.
 * @param seats_taken Number of seats taken.
 *
 * @return void.
 */
void set_flight_seats_taken(Flight *f, int seats_taken)
{
    if (f)
    {
        f->seats_taken = seats_taken;
    }
}

/**
 * @brief This function is responsible for freeing the flight.
 *
 * @param f Pointer to the flight.
 *
 * @return void.
 */
void free_flight(Flight *f)
{
    free(f->id);
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

/**
 * @brief This function is responsible for printing the flight.
 *
 * @param f Pointer to the flight.
 *
 * @return void.
 */
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
    printf("seats taken: %d\n", get_flight_seats_taken(f));
}