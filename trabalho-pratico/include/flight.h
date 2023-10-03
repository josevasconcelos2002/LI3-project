#ifndef FLIGHT_H
#define FLIGHT_H

typedef struct flight Flight;

int get_flight_id(Flight *f);
char *get_flight_airline(Flight *f);
char *get_flight_plane_model(Flight *f);
int get_flight_total_seats(Flight *f);
char *get_flight_origin(Flight *f);
char *get_flight_destination(Flight *f);
char *get_flight_schedule_departure_date(Flight *f);
char *get_flight_schedule_arrival_date(Flight *f);
char *get_flight_real_departure_date(Flight *f);
char *get_flight_real_arrival_date(Flight *f);
char *get_flight_pilot(Flight *f);
char *get_flight_copilot(Flight *f);
char *get_flight_notes(Flight *f);

#endif