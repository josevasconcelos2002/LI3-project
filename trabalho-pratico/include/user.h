#ifndef USER_H
#define USER_H

#include <stdbool.h>


typedef struct User User;


struct User* create_user();

char *get_user_id(User *u);
char *get_real_user_id(User *u);
void set_user_id(User *u, char *id);
char *get_user_name(User *u);
void set_user_name(User *u, char *name);
char *get_user_email(User *u);
void set_user_email(User *u, char *email);
char *get_user_phone_number(User *u);
void set_user_phone_number(User *u, char *phone_number);
char *get_user_birth_date(User *u);
void set_user_birth_date(User *u, char *birth_date);
char *get_user_sex(User *u);
void set_user_sex(User *u, char *sex);
char *get_user_passport(User *u);
void set_user_passport(User *u, char *passport);
char *get_user_country_code(User *u);
void set_user_country_code(User *u, char *country_code);
char *get_user_adress(User *u);
void set_user_adress(User *u, char *adress);
char *get_user_account_creation(User *u);
void set_user_account_creation(User *u, char *account_creation);
char *get_user_pay_method(User *u);
void set_user_pay_method(User *u, char *pay_method);
char *get_user_account_status(User *u);
void set_user_account_status(User *u, char *account_status);
double get_user_total_spent(User *u);
void set_user_total_spent(User *u, double total_spent);
double get_user_number_of_flights(User *u);
void set_user_number_of_flights(User *u, double number_of_flights);
double get_user_number_of_reservations(User *u);
void set_user_number_of_reservations(User *u, double number_of_reservations);
void free_user(User *u);
void print_user(User *u);

#endif