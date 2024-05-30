#include "../../include/user.h"
#include "../../include/gestorUsers.h"
#include "../../include/gestor.h"
#include <glib-2.0/glib.h>
#include <stdio.h>

struct catalogo_users
{
    GHashTable *table_users;
};
typedef struct catalogo_users catalogo_Users;

/**
 * @brief This function is responsible for initializing the users catalog.
 *
 * @return catalogo_Users*.
 */
catalogo_Users *init_catalogo_users()
{
    catalogo_Users *new_cat_users = malloc(sizeof(catalogo_Users));
    new_cat_users->table_users = new_hashtable();
    return new_cat_users;
}

/**
 * @brief This function is responsible for printing a user pair key.
 *
 * @param key The key of the user.
 * @param value The value of the user.
 *
 * @return void.
 */
void print_user_pair_key(gpointer key, gpointer value)
{
    printf("Key: %s\n", (char *)key);
    print_user((User *)value);
    printf("\n");
}

/**
 * @brief This function is responsible for freeing a user.
 *
 * @param key The key of the user.
 * @param value The value of the user.
 *
 * @return void.
 */
void free_users_value(gpointer key, gpointer value)
{
    User *user = (User *)value;

    free_user(user);
}

/**
 * @brief This function is responsible for freeing the users catalog.
 *
 * @param cat_users Pointer to the users catalog.
 *
 * @return void.
 */
void free_catalogo_users(catalogo_Users *cat_users)
{
    if (cat_users->table_users)
    {
        g_hash_table_foreach(cat_users->table_users, (GHFunc)free_users_value, NULL);
        g_hash_table_destroy(cat_users->table_users);
    }
    free(cat_users);
}

/**
 * @brief This function is responsible for returning the users table.
 *
 * @param cat_users Pointer to the users catalog.
 *
 * @return GHashTable*.
 */
GHashTable *get_table_users(catalogo_Users *cat_users)
{
    return cat_users->table_users;
}

/**
 * @brief This function is responsible for setting the users table.
 *
 * @param cat_users Pointer to the users catalog.
 * @param table_users Pointer to the new users table.
 *
 * @return void.
 */
void set_table_users(catalogo_Users *cat_users, GHashTable *table_users)
{
    cat_users->table_users = table_users;
}

/**
 * @brief This function is responsible for inserting a new user into the catalog.
 *
 * @param cat_users Pointer to the users catalog.
 *
 * @return void.
 */
void print_catalogo_users(catalogo_Users *cat_users)
{
    g_hash_table_foreach(cat_users->table_users, (GHFunc)print_user_pair_key, NULL);
}
