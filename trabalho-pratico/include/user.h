#ifndef USER_H
#define USER_H

typedef struct user User;

int get_user_id(User *u);
char *get_user_name(User *u);
char *get_user_email(User *u);
int get_user_phone_number(User *u);
char *get_user_birth_date(User *u);
char *get_user_sex(User *u);
int get_user_passport(User *u);
char *get_user_country_code(User *u);
char *get_user_adress(User *u);
char *get_user_account_creation(User *u);
char *get_user_account_status(User *u);

#endif