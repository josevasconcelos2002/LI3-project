#ifndef FLIGHT_H
#define FLIGHT_H



typedef struct Flight Flight;

struct Flight* create_flight();

char *get_flight_id(Flight *f);
char *get_real_flight_id(Flight *f);
void set_flight_id(Flight *f, char *id);
char *get_flight_airline(Flight *f);
void set_flight_airline(Flight *f, char *airline);
char *get_flight_plane_model(Flight *f);
void set_flight_plane_model(Flight *f, char *plane_model);
int get_flight_total_seats(Flight *f);
void set_flight_total_seats(Flight *f, int total_seats);
char *get_flight_origin(Flight *f);
void set_flight_origin(Flight *f, char *origin);
char *get_flight_destination(Flight *f);
void set_flight_destination(Flight *f, char *destination);
char *get_flight_schedule_departure_date(Flight *f);
void set_flight_schedule_departure_date(Flight *f, char *schedule_departure_date);
char *get_flight_schedule_arrival_date(Flight *f);
void set_flight_schedule_arrival_date(Flight *f, char *schedule_arrival_date);
char *get_flight_real_departure_date(Flight *f);
void set_flight_real_departure_date(Flight *f, char *real_departure_date);
char *get_flight_real_arrival_date(Flight *f);
void set_flight_real_arrival_date(Flight *f, char *real_arrival_date);
char *get_flight_pilot(Flight *f);
void set_flight_pilot(Flight *f, char *pilot);
char *get_flight_copilot(Flight *f);
void set_flight_copilot(Flight *f, char *copilot);
char *get_flight_notes(Flight *f);
void set_flight_notes(Flight *f, char *notes);
int get_flight_seats_taken(Flight *f);
void set_flight_seats_taken(Flight *f, int seats_taken);
void free_flight(Flight *f);
void print_flight(Flight *f);

#endif