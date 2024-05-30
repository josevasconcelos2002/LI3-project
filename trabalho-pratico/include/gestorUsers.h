#ifndef GESTORUSERS_H
#define GESTORUSERS_H
#include <glib-2.0/glib.h>
#include "user.h"
#include <stdio.h>

// Forward declaration of struct catalogo_Users
typedef struct catalogo_users catalogo_Users;

// Function declarations
catalogo_Users *init_catalogo_users();
GHashTable *get_table_users(catalogo_Users *cat_users);
void set_table_users(catalogo_Users *cat_users, GHashTable *table_users);
void print_user_pair_key(gpointer key, gpointer value);
void free_users_value(gpointer key, gpointer value);
void free_catalogo_users(catalogo_Users *cat_users);
GHashTable *get_table_users(catalogo_Users *cat_users);
// GHashTable *new_hash_table();

#endif // GESTORUSERS_H
