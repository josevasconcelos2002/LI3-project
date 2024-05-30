#include "../../include/user.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


struct User {
    char *id;
    char *name;
    char *email;
    char *phone_number;
    char *birth_date;
    char *sex;
    char *passport;
    char *country_code;
    char *adress;
    char *account_creation;
    char *pay_method;
    char *account_status;
    double total_spent;
    double number_of_flights;
    double number_of_reservations;
};

struct User* create_user() {
    struct User* user = malloc(sizeof(struct User));
    if (user) {
        // Initialize the members of the User struct
        user->id = NULL;
        user->name = NULL;
        user->email = NULL;
        user->phone_number = NULL;
        user->birth_date = NULL;
        user->sex = NULL;
        user->passport = NULL;
        user->country_code = NULL;
        user->adress = NULL;
        user->account_creation = NULL;
        user->pay_method = NULL;
        user->account_status = NULL;
        user->total_spent = 0.0;
        user->number_of_flights = 0;
        user->number_of_reservations = 0;
        // Initialize other members as needed
    }
    return user;
}



/**
 * @brief This function is responsible for returning the user id.
 *
 * @param u Pointer to the user.
 *
 * @return char*.
 */
char *get_user_id(User *u)
{
    char *id = strdup(u->id);
    return id;
}

char *get_real_user_id(User *u){
    return u->id;
}

/**
 * @brief This function is responsible for setting the user id.
 *
 * @param u Pointer to the user.
 * @param id Pointer to the new id.
 *
 * @return void.
 */
void set_user_id(User *u, char *id)
{
    if (u)
    {
        u->id = strdup(id);
    }
}

/**
 * @brief This function is responsible for returning the user name.
 *
 * @param u Pointer to the user.
 *
 * @return char*.
 */
char *get_user_name(User *u)
{
    char *name = strdup(u->name);
    return name;
}

/**
 * @brief This function is responsible for setting the user name.
 *
 * @param u Pointer to the user.
 * @param name Pointer to the new name.
 *
 * @return void.
 */
void set_user_name(User *u, char *name)
{
    if (u)
    {
        u->name = strdup(name);
    }
}

/**
 * @brief This function is responsible for returning the user email.
 *
 * @param u Pointer to the user.
 *
 * @return char*.
 */
char *get_user_email(User *u)
{
    char *email = strdup(u->email);
    return email;
}

/**
 * @brief This function is responsible for setting the user email.
 *
 * @param u Pointer to the user.
 * @param email Pointer to the new email.
 *
 * @return void.
 */
void set_user_email(User *u, char *email)
{
    if (u)
    {
        u->email = strdup(email);
    }
}

/**
 * @brief This function is responsible for returning the user phone number.
 *
 * @param u Pointer to the user.
 *
 * @return char*.
 */
char *get_user_phone_number(User *u)
{
    char *phone_number = strdup(u->phone_number);
    return phone_number;
}

/**
 * @brief This function is responsible for setting the user phone number.
 *
 * @param u Pointer to the user.
 * @param phone_number Pointer to the new phone number.
 *
 * @return void.
 */
void set_user_phone_number(User *u, char *phone_number)
{
    if (u)
    {
        u->phone_number = strdup(phone_number);
    }
}

/**
 * @brief This function is responsible for returning the user birth date.
 *
 * @param u Pointer to the user.
 *
 * @return char*.
 */
char *get_user_birth_date(User *u)
{
    char *birth_date = strdup(u->birth_date);
    return birth_date;
}

/**
 * @brief This function is responsible for setting the user birth date.
 *
 * @param u Pointer to the user.
 * @param birth_date Pointer to the new birth date.
 *
 * @return void.
 */
void set_user_birth_date(User *u, char *birth_date)
{
    if (u)
    {
        u->birth_date = strdup(birth_date);
    }
}

/**
 * @brief This function is responsible for returning the user sex.
 *
 * @param u Pointer to the user.
 *
 * @return char*.
 */
char *get_user_sex(User *u)
{
    char *sex = strdup(u->sex);
    return sex;
}

/**
 * @brief This function is responsible for setting the user sex.
 *
 * @param u Pointer to the user.
 * @param sex Pointer to the new sex.
 *
 * @return void.
 */
void set_user_sex(User *u, char *sex)
{
    if (u)
    {
        u->sex = strdup(sex);
    }
}

/**
 * @brief This function is responsible for returning the user passport.
 *
 * @param u Pointer to the user.
 *
 * @return char*.
 */
char *get_user_passport(User *u)
{
    char *passport = strdup(u->passport);
    return passport;
}

/**
 * @brief This function is responsible for setting the user passport.
 *
 * @param u Pointer to the user.
 * @param passport Pointer to the new passport.
 *
 * @return void.
 */
void set_user_passport(User *u, char *passport)
{
    if (u)
    {
        u->passport = strdup(passport);
    }
}

/**
 * @brief This function is responsible for returning the user country code.
 *
 * @param u Pointer to the user.
 *
 * @return char*.
 */
char *get_user_country_code(User *u)
{
    char *country_code = strdup(u->country_code);
    return country_code;
}

/**
 * @brief This function is responsible for setting the user country code.
 *
 * @param u Pointer to the user.
 * @param country_code Pointer to the new country code.
 *
 * @return void.
 */
void set_user_country_code(User *u, char *country_code)
{
    if (u)
    {
        u->country_code = strdup(country_code);
    }
}

/**
 * @brief This function is responsible for returning the user adress.
 *
 * @param u Pointer to the user.
 *
 * @return char*.
 */
char *get_user_adress(User *u)
{
    char *adress = strdup(u->adress);
    return adress;
}

/**
 * @brief This function is responsible for setting the user adress.
 *
 * @param u Pointer to the user.
 * @param adress Pointer to the new adress.
 *
 * @return void.
 */
void set_user_adress(User *u, char *adress)
{
    if (u)
    {
        u->adress = strdup(adress);
    }
}

/**
 * @brief This function is responsible for returning the user account creation.
 *
 * @param u Pointer to the user.
 *
 * @return char*.
 */
char *get_user_account_creation(User *u)
{
    char *account_creation = strdup(u->account_creation);
    return account_creation;
}

/**
 * @brief This function is responsible for setting the user account creation.
 *
 * @param u Pointer to the user.
 * @param account_creation Pointer to the new account creation.
 *
 * @return void.
 */
void set_user_account_creation(User *u, char *account_creation)
{
    if (u)
    {
        u->account_creation = strdup(account_creation);
    }
}

/**
 * @brief This function is responsible for returning the user pay method.
 *
 * @param u Pointer to the user.
 *
 * @return char*.
 */
char *get_user_pay_method(User *u)
{
    char *pay_method = strdup(u->pay_method);
    return pay_method;
}

/**
 * @brief This function is responsible for setting the user pay method.
 *
 * @param u Pointer to the user.
 * @param pay_method Pointer to the new pay method.
 *
 * @return void.
 */
void set_user_pay_method(User *u, char *pay_method)
{
    if (u)
    {
        u->pay_method = strdup(pay_method);
    }
}

/**
 * @brief This function is responsible for returning the user account status.
 *
 * @param u Pointer to the user.
 *
 * @return char*.
 */
char *get_user_account_status(User *u)
{
    char *account_status = strdup(u->account_status);
    return account_status;
}

/**
 * @brief This function is responsible for setting the user account status.
 *
 * @param u Pointer to the user.
 * @param account_status Pointer to the new account status.
 *
 * @return void.
 */
void set_user_account_status(User *u, char *account_status)
{
    if (u)
    {
        u->account_status = strdup(account_status);
    }
}

/**
 * @brief This function is responsible for returning the user total spent.
 *
 * @param u Pointer to the user.
 *
 * @return double
 */
double get_user_total_spent(User *u)
{
    return u->total_spent;
}

/**
 * @brief This function is responsible for setting the user total spend.
 *
 * @param u Pointer to the user.
 * @param total_spent New total spent.
 *
 * @return void
 */
void set_user_total_spent(User *u, double total_spent)
{
    if (u)
    {
        u->total_spent = total_spent;
    }
}

/**
 * @brief This function is responsible for returning the user number of flights.
 *
 * @param u Pointer to the user.
 *
 * @return double
 */
double get_user_number_of_flights(User *u)
{
    return u->number_of_flights;
}

/**
 * @brief This function is responsible for setting the user number of flights.
 *
 * @param u Pointer to the user.
 * @param number_of_flights New number of flights.
 *
 * @return void
 */
void set_user_number_of_flights(User *u, double number_of_flights)
{
    if (u)
    {
        u->number_of_flights = number_of_flights;
    }
}

/**
 * @brief This function is responsible for setting the user number of flights.
 *
 * @param u Pointer to the user.
 *
 * @return void
 */
double get_user_number_of_reservations(User *u)
{
    return u->number_of_reservations;
}

/**
 * @brief This function is responsible for setting the user number of reservations.
 *
 * @param u Pointer to the user.
 * @param number_of_reservations New number of reservations.
 *
 * @return void
 */
void set_user_number_of_reservations(User *u, double number_of_reservations)
{
    if (u)
    {
        u->number_of_reservations = number_of_reservations;
    }
}

/*

GList *get_user_flights_list(User *u)
{
    return u->flights_list;
}

*/

/**
 * @brief This function is responsible for freeing the user.
 *
 * @param u Pointer to the user.
 *
 * @return void
 */
void free_user(User *u)
{
    if (u)
    {
        free(u->id);
        free(u->name);
        free(u->email);
        free(u->phone_number);
        free(u->birth_date);
        free(u->sex);
        free(u->country_code);
        free(u->adress);
        free(u->account_creation);
        free(u->passport);
        free(u->pay_method);
        free(u->account_status);
        free(u);
    }
}

/**
 * @brief This function is responsible for printing the user.
 *
 * @param u Pointer to the user.
 *
 * @return void
 */
void print_user(User *u)
{
    printf("ID: %s\n", get_user_id(u));
    printf("Name: %s\n", get_user_name(u));
    printf("Email: %s\n", get_user_email(u));
    printf("Phone number: %s\n", get_user_phone_number(u));
    printf("Birth date: %s\n", get_user_birth_date(u));
    printf("Sex: %s\n", get_user_sex(u));
    printf("Passport: %s\n", get_user_passport(u));
    printf("Country code: %s\n", get_user_country_code(u));
    printf("Adress: %s\n", get_user_adress(u));
    printf("Account creation: %s\n", get_user_account_creation(u));
    printf("Pay method: %s\n", get_user_pay_method(u));
    printf("Account status: %s\n", get_user_account_status(u));
    printf("Total spent: %f\n", get_user_total_spent(u));
    printf("Number of flights: %f\n", get_user_number_of_flights(u));
    printf("Number of reservations: %f\n", get_user_number_of_reservations(u));
}