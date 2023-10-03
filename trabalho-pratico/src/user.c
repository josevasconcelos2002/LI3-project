#include "user.h"
#include <string.h>

struct user
{
    int id;
    char *name;
    char *email;
    int phone_number;
    char *birth_date;
    char *sex; // ou apenas char (?)
    int passport;
    char *country_code;
    char *adress;
    char *account_creation;
    char *pay_method;
    char *account_status;
};

int get_user_id(User *u)
{
    return u->id;
}

char *get_user_name(User *u)
{
    char *name = strdup(u->name);
    return name;
}

char *get_user_email(User *u)
{
    char *email = strdup(u->email);
    return email;
}

int get_user_phone_number(User *u)
{
    return u->phone_number;
}

char *get_user_birth_date(User *u)
{
    char *birth_date = strdupt(u->birth_date);
    return birth_date;
}

char *get_user_sex(User *u)
{
    char *sex = strdup(u->sex);
    return sex;
}

int get_user_passport(User *u)
{
    return u->passport;
}

char *get_user_country_code(User *u)
{
    char *country_code = strdup(u->country_code);
    return country_code;
}

char *get_user_adress(User *u)
{
    char *adress = strdup(u->adress);
    return adress;
}

char *get_user_account_creation(User *u)
{
    char *account_creation = strdup(u->account_creation);
    return account_creation;
}

char *get_user_account_status(User *u)
{
    char *account_status = strdup(u->account_status);
    return account_status;
}