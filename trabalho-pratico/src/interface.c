#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <glib-2.0/glib.h>
#include "../include/validation.h"

#include "../include/gestor.h"
#include "../include/batch.h"




void sair(catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users)
{
    int continuar = 1;
    do
    {
        printf("\n1. Menu Queries\n");
        printf("2. Sair\n\n");

        int scan = scanf("%d", &continuar);
        int sys = system("clear");
        if (scan && sys == 0)
        {
            switch (continuar)
            {
            case 1:
                menu_queries(cat_flights, cat_passengers, cat_reservations, cat_users);
                break;

            case 2:
                free_catalogo_flights(cat_flights);
                free_catalogo_reservations(cat_reservations);
                free_catalogo_passengers(cat_passengers);
                free_catalogo_users(cat_users);
                exit(0);
                break;

            default:
                printf("\nDigite uma opcao valida\n");
            }
        }
    } while (continuar != 2);
}

void query_1(catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users)

{
    int sys = system("clear");
    if (sys == 0)
    {
        printf("\nListar o resumo de um utilizador, voo, ou reserva, consoante o identificador recebido por argumento <ID>.\n");
        printf("Note que o identificador poderá corresponder a um voo, reserva ou a um utilizador.\n");
        printf("\nIntroduza o <ID> do utilizador: ");
        char id[50];
        int scan = scanf("%s", id);
        printf("\nDeseja obter o output com a flag 'F'? (S ou N) ");
        char s2[20];
        int scan2 = scanf("%s", s2);
        if (scan && scan2)
        {
            if (strcasecmp(s2, "S") != 0 && strcasecmp(s2, "N") != 0)
            {
                printf("\033[31m\nOpção inválida... A voltar ao menu.\033[0m\n");
                menu_queries(cat_flights, cat_passengers, cat_reservations, cat_users);
            }
            if (strcasecmp(s2, "S") == 0)
            {
                char *real_account_status2 = NULL;
                if (is_valid_user_id(id) == 1)
                {
                    User *user = g_hash_table_lookup(get_table_users(cat_users), id);
                    if (user == NULL)
                    {
                        printf("\033[31m\nError: user_id %s does not exist\n", id);
                        menu_queries(cat_flights, cat_passengers, cat_reservations, cat_users);
                    }
                    real_account_status2 = get_user_account_status(user);
                    real_account_status2[strcspn(real_account_status2, "\n")] = '\0';
                    if (strcasecmp(real_account_status2, "inactive") == 0)
                    {
                        printf("\033[31m\nUtilizador %s está inativo\033[0m\n", id);
                        menu_queries(cat_flights, cat_passengers, cat_reservations, cat_users);
                    }

                    char *user_name = get_user_name(user);
                    char *user_sex = get_user_sex(user);
                    char *user_age = get_user_birth_date(user);
                    char *user_country_code = get_user_country_code(user);
                    char *user_passport = get_user_passport(user);
                    double user_number_of_flights = get_user_number_of_flights(user);
                    double user_number_of_reservations = get_user_number_of_reservations(user);
                    double user_total_spent = get_user_total_spent(user);

                    printf("\n--- 1 ---\n");
                    printf("name: \033[32m%s\033[0m\n", user_name);
                    printf("sex: \033[32m%s\033[0m\n", user_sex);
                    printf("age: \033[32m%d\033[0m\n", calculate_age(user_age));
                    printf("country_code: \033[32m%s\033[0m\n", user_country_code);
                    printf("passport: \033[32m%s\033[0m\n", user_passport);
                    printf("number_of_flights: \033[32m%.0f\033[0m\n", user_number_of_flights);
                    printf("number_of_reservations: \033[32m%.0f\033[0m\n", user_number_of_reservations);
                    printf("total_spent: \033[32m%.3f\033[0m\n", user_total_spent);

                    free(user_name);
                    free(user_sex);
                    free(user_age);
                    free(user_country_code);
                    free(user_passport);
                    free(real_account_status2);
                }
                else if (is_valid_user_id(id) == 2)
                {
                    Flight *flight = g_hash_table_lookup(get_table_flights(cat_flights), id);
                    if (flight == NULL)
                    {
                        printf("\033[31m\nError: flight_id %s does not exist\033[0m\n", id);
                        menu_queries(cat_flights, cat_passengers, cat_reservations, cat_users);
                    }

                    char *flight_airline = get_flight_airline(flight);
                    char *flight_plane_model = get_flight_plane_model(flight);
                    char *flight_origin = get_flight_origin(flight);
                    char *flight_destination = get_flight_destination(flight);
                    char *flight_schedule_departure_date = get_flight_schedule_departure_date(flight);
                    char *flight_schedule_arrival_date = get_flight_schedule_arrival_date(flight);

                    printf("\n--- 1 ---\n");
                    printf("airline: \033[32m%s\033[0m\n", flight_airline);
                    printf("plane_model: \033[32m%s\033[0m\n", flight_plane_model);
                    printf("origin: \033[32m%s\033[0m\n", flight_origin);
                    printf("destination: \033[32m%s\033[0m\n", flight_destination);
                    printf("schedule_departure_date: \033[32m%s\033[0m\n", flight_schedule_departure_date);
                    printf("schedule_arrival_date: \033[32m%s\033[0m\n", flight_schedule_arrival_date);
                    printf("passengers: \033[32m%d\033[0m\n", get_flight_seats_taken(flight));
                    printf("delay: \033[32m%d\033[0m\n", calculate_delay(flight));

                    free(flight_airline);
                    free(flight_plane_model);
                    free(flight_origin);
                    free(flight_destination);
                    free(flight_schedule_departure_date);
                    free(flight_schedule_arrival_date);
                }
                else if (is_valid_user_id(id) == 3)
                {
                    Reservation *reservation = g_hash_table_lookup(get_table_reservations(cat_reservations), id);
                    if (reservation == NULL)
                    {
                        printf("\033[31m\nError: reservation user_id %s does not exist\033[0m\n", id);
                        menu_queries(cat_flights, cat_passengers, cat_reservations, cat_users);
                    }

                    char *reservation_hotel_id = get_reservation_hotel_id(reservation);
                    char *reservation_hotel_name = get_reservation_hotel_name(reservation);
                    int reservation_hotel_stars = get_reservation_hotel_stars(reservation);
                    char *reservation_begin_date = get_reservation_begin_date(reservation);
                    char *reservation_end_date = get_reservation_end_date(reservation);
                    bool reservation_includes_breakfast = get_reservation_includes_breakfast(reservation);
                    double reservation_total_price = get_reservation_total_price(reservation);

                    printf("\n--- 1 ---\n");
                    printf("hotel_id: \033[32m%s\033[0m\n", reservation_hotel_id);
                    printf("hotel_name: \033[32m%s\033[0m\n", reservation_hotel_name);
                    printf("hotel_stars: \033[32m%d\033[0m\n", reservation_hotel_stars);
                    printf("begin_date: \033[32m%s\033[0m\n", reservation_begin_date);
                    printf("end_date: \033[32m%s\033[0m\n", reservation_end_date);
                    printf("includes_breakfast: \033[32m%s\033[0m\n", reservation_includes_breakfast ? "True" : "False");
                    printf("nights: \033[32m%.0f\033[0m\n", calculate_nights2(reservation_begin_date, reservation_end_date));
                    printf("total_price: \033[32m%.3f\033[0m\n", reservation_total_price);

                    free(reservation_hotel_id);
                    free(reservation_hotel_name);
                    free(reservation_begin_date);
                    free(reservation_end_date);
                    free(real_account_status2);
                }
                else
                {
                    printf("\033[31m\nError: this id %s does not exist\033[0m\n", id);
                    menu_queries(cat_flights, cat_passengers, cat_reservations, cat_users);
                }
                sair(cat_flights, cat_passengers, cat_reservations, cat_users);
            }
            else if (strcasecmp(s2, "N") == 0)
            {
                char *real_account_status = NULL;
                if (is_valid_user_id(id) == 1)
                {
                    User *user = g_hash_table_lookup(get_table_users(cat_users), id);
                    if (user == NULL)
                    {
                        printf("\033[31m\nError: user_id %s does not exist\033[0m\n", id);
                        menu_queries(cat_flights, cat_passengers, cat_reservations, cat_users);
                    }
                    real_account_status = get_user_account_status(user);
                    real_account_status[strcspn(real_account_status, "\n")] = '\0';
                    if (strcasecmp(real_account_status, "inactive") == 0)
                    {
                        printf("\033[31m\nUtilizador %s está inativo\033[0m\n", id);
                        menu_queries(cat_flights, cat_passengers, cat_reservations, cat_users);
                    }

                    char *user_name = get_user_name(user);
                    char *user_sex = get_user_sex(user);
                    char *user_age = get_user_birth_date(user);
                    char *user_country_code = get_user_country_code(user);
                    char *user_passport = get_user_passport(user);
                    double user_number_of_flights = get_user_number_of_flights(user);
                    double user_number_of_reservations = get_user_number_of_reservations(user);
                    double user_total_spent = get_user_total_spent(user);

                    printf("\033[32m\n%s;", user_name);
                    printf("%s;", user_sex);
                    printf("%d;", calculate_age(user_age));
                    printf("%s;", user_country_code);
                    printf("%s;", user_passport);
                    printf("%.0f;", user_number_of_flights);
                    printf("%.0f;", user_number_of_reservations);
                    printf("%.3f\033[0m\n", user_total_spent);

                    free(user_name);
                    free(user_sex);
                    free(user_age);
                    free(user_country_code);
                    free(user_passport);
                    free(real_account_status);
                }
                else if (is_valid_user_id(id) == 2)
                {
                    Flight *flight = g_hash_table_lookup(get_table_flights(cat_flights), id);
                    if (flight == NULL)
                    {
                        printf("\033[31m\nError: flight_id %s does not exist\033[0m\n", id);
                        menu_queries(cat_flights, cat_passengers, cat_reservations, cat_users);
                    }

                    char *flight_airline = get_flight_airline(flight);
                    char *flight_plane_model = get_flight_plane_model(flight);
                    char *flight_origin = get_flight_origin(flight);
                    char *flight_destination = get_flight_destination(flight);
                    char *flight_schedule_departure_date = get_flight_schedule_departure_date(flight);
                    char *flight_schedule_arrival_date = get_flight_schedule_arrival_date(flight);

                    printf("\033[32m\n%s;", flight_airline);
                    printf("%s;", flight_plane_model);
                    printf("%s;", flight_origin);
                    printf("%s;", flight_destination);
                    printf("%s;", flight_schedule_departure_date);
                    printf("%s;", flight_schedule_arrival_date);
                    printf("%d;", get_flight_seats_taken(flight));
                    printf("%d\033[0m\n", calculate_delay(flight));

                    free(flight_airline);
                    free(flight_plane_model);
                    free(flight_origin);
                    free(flight_destination);
                    free(flight_schedule_departure_date);
                    free(flight_schedule_arrival_date);
                }
                else if (is_valid_user_id(id) == 3)
                {
                    Reservation *reservation = g_hash_table_lookup(get_table_reservations(cat_reservations), id);
                    if (reservation == NULL)
                    {
                        printf("\033[31m\nError: reservation user_id %s does not exist\033[0m\n", id);
                        menu_queries(cat_flights, cat_passengers, cat_reservations, cat_users);
                    }
                    User *user_reservation = g_hash_table_lookup(get_table_users(cat_users), get_reservation_real_user_id(reservation));
                    real_account_status = get_user_account_status(user_reservation);
                    if (strcasecmp(real_account_status, "inactive") == 0)
                    {
                        printf("\033[31mUser %s Inactive\033[0m", get_reservation_user_id(reservation));
                        free(real_account_status);
                        menu_queries(cat_flights, cat_passengers, cat_reservations, cat_users);
                    }

                    char *reservation_hotel_id = get_reservation_hotel_id(reservation);
                    char *reservation_hotel_name = get_reservation_hotel_name(reservation);
                    int reservation_hotel_stars = get_reservation_hotel_stars(reservation);
                    char *reservation_begin_date = get_reservation_begin_date(reservation);
                    char *reservation_end_date = get_reservation_end_date(reservation);
                    bool reservation_includes_breakfast = get_reservation_includes_breakfast(reservation);
                    double reservation_total_price = get_reservation_total_price(reservation);

                    printf("\033[32m\n%s;", reservation_hotel_id);
                    printf("%s;", reservation_hotel_name);
                    printf("%d;", reservation_hotel_stars);
                    printf("%s;", reservation_begin_date);
                    printf("%s;", reservation_end_date);
                    printf("%s;", reservation_includes_breakfast ? "True" : "False");
                    printf("%.0f;", calculate_nights2(reservation_begin_date, reservation_end_date));
                    printf("%.3f\033[0m\n", reservation_total_price);

                    free(reservation_hotel_id);
                    free(reservation_hotel_name);
                    free(reservation_begin_date);
                    free(reservation_end_date);
                    free(real_account_status);
                }
                else
                {
                    printf("\033[31m\nError: this id %s does not exist\033[0m\n", id);
                    menu_queries(cat_flights, cat_passengers, cat_reservations, cat_users);
                }
                sair(cat_flights, cat_passengers, cat_reservations, cat_users);
            }
        }
    }
}

void query_2(catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users)
{
    int sys = system("clear");
    if (sys == 0)
    {
        printf("\n Listar os voos ou reservas de um utilizador, se o segundo argumento for flights ou reservations, respetivamente, ordenados por data (da mais recente para a mais antiga).\n");
        printf("\nCaso não seja fornecido um segundo argumento, apresentar voos e reservas, juntamente com o tipo (flight ou reservation).\n");
        printf("\nIntroduza o <ID>: ");
        char id[30];
        int scan = scanf("%s", id);
        char *type = NULL;
        printf("\nDeseja introduzir o <Tipo> ? (S ou N): ");
        char r[20];
        int scan2 = scanf("%s", r);
        int scan3 = 0;
        if (strcasecmp(r, "S") != 0 && strcasecmp(r, "N") != 0)
        {
            printf("\033[31m\nOpção inválida... A voltar ao menu.\033[0m\n");
            menu_queries(cat_flights, cat_passengers, cat_reservations, cat_users);
        }
        else if (strcasecmp(r, "S") == 0)
        {
            printf("\nIntroduza o <Tipo>: ");
            char type1[20];
            scan3 = scanf("%s", type1);
            if (scan3)
            {
                type = strdup(type1);
            }
        }
        int scan4 = scanf("%s", type);
        printf("\nDeseja obter o output com a flag 'F'? (S ou N) ");
        char flag[20];
        int scan5 = scanf("%s", flag);
        if (scan && scan2 && scan3 && scan4 && scan5)
        {
            if (strcasecmp(flag, "S") != 0 && strcasecmp(flag, "N") != 0)
            {
                printf("\033[31m\nOpção inválida... A voltar ao menu.\033[0m\n");
                menu_queries(cat_flights, cat_passengers, cat_reservations, cat_users);
            }
            sair(cat_flights, cat_passengers, cat_reservations, cat_users);
        }
    }
}

void query_3(catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users)
{
    int sys = system("clear");
    if (sys == 0)
    {
        printf("\nApresentar a classificação média de um hotel, a partir do seu identificador <ID>.\n");
        printf("\nIntroduza o <ID> : \n");
        char id[50];
        int scan = scanf("%s", id);
        printf("\nDeseja obter o output com a flag 'F'? (S ou N): ");
        char s2[20];
        int scan2 = scanf("%s", s2);
        if (scan && scan2)
        {
            if (strcasecmp(s2, "S") != 0 && strcasecmp(s2, "N") != 0)
            {
                printf("\033[31m\nOpção inválida... A voltar ao menu.\033[0m\n");
                menu_queries(cat_flights, cat_passengers, cat_reservations, cat_users);
            }
            else
            {
                double sum = 0.0;
                int count = 0;
                double average = 0.0;
                GHashTableIter iter;
                gpointer key, value;
                g_hash_table_iter_init(&iter, get_table_reservations(cat_reservations));
                while (g_hash_table_iter_next(&iter, &key, &value))
                {
                    Reservation *r = (Reservation *)value;
                    char *reservation_hotel_id = get_reservation_hotel_id(r);
                    if (strcmp(reservation_hotel_id, id) == 0)
                    {
                        sum += get_reservation_rating(r);
                        count++;
                    }
                    free(reservation_hotel_id);
                }
                if (count > 0)
                {
                    average = sum / count;
                }
                if (strcasecmp(s2, "S") == 0)
                {
                    printf("\n--- 1 ---\n");
                    printf("rating: \033[32m%.3f\033[0m\n", average);
                }
                else if (strcasecmp(s2, "N") == 0)
                {
                    printf("\n\033[32m%.3f\033[0m\n", average);
                }
            }
        }
        sair(cat_flights, cat_passengers, cat_reservations, cat_users);
    }
}

void query_4(catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users)
{
    int sys = system("clear");
    if (sys == 0)
    {
        printf("\nListar as reservas de um hotel, ordenadas por data de início (da mais recente para a mais antiga).\n ");
        printf("\nCaso duas reservas tenham a mesma data, deve ser usado o identificador da reserva como critério de desempate (de forma crescente).\n");
        printf("\nIntroduza o <ID> do hotel: ");
        char ID[30];
        int scan = scanf("%s", ID);
        printf("\nDeseja obter o output com a flag 'F'? (S ou N) ");
        char flag[20];
        int scan2 = scanf("%s", flag);
        if (scan && scan2)
        {
            if (strcasecmp(flag, "S") != 0 && strcasecmp(flag, "N") != 0)
            {
                printf("\033[31m\nOpção inválida... A voltar ao menu.\033[0m\n");
                menu_queries(cat_flights, cat_passengers, cat_reservations, cat_users);
            }
            else if (strcasecmp(flag, "S") == 0)
            {
                GList *reservations = get_reservations_by_hotel_id(get_table_reservations(cat_reservations), ID);
                reservations = g_list_sort(reservations, compare_reservations_by_begin_date_desc);

                GList *iter;
                int i;
                for (iter = reservations, i = 1; iter != NULL; iter = iter->next, i++)
                {
                    Reservation *reservation = (Reservation *)iter->data;
                    char *reservation_id = get_reservation_id(reservation);
                    char *begin_date = get_reservation_begin_date(reservation);
                    char *end_date = get_reservation_end_date(reservation);
                    char *user_id = get_reservation_user_id(reservation);
                    double rating = get_reservation_rating(reservation);
                    double total_price = get_reservation_total_price(reservation);

                    if (i == 1)
                    {
                        printf("--- %d ---\n", i);
                        printf("id: \033[32m%s\033[0m\n", reservation_id);
                        printf("begin_date: \033[32m%s\033[0m\n", begin_date);
                        printf("end_date: \033[32m%s\033[0m\n", end_date);
                        printf("user_id: \033[32m%s\033[0m\n", user_id);
                        printf("rating: \033[32m%.0f\033[0m\n", rating);
                        printf("total_price: \033[32m%.3f\033[0m\n", total_price);
                    }
                    else
                    {
                        printf("\n--- %d ---\n", i);
                        printf("id: \033[32m%s\033[0m\n", reservation_id);
                        printf("begin_date: \033[32m%s\033[0m\n", begin_date);
                        printf("end_date: \033[32m%s\033[0m\n", end_date);
                        printf("user_id: \033[32m%s\033[0m\n", user_id);
                        printf("rating: \033[32m%.0f\033[0m\n", rating);
                        printf("total_price: \033[32m%.3f\033[0m\n", total_price);
                    }

                    free(reservation_id);
                    free(begin_date);
                    free(end_date);
                    free(user_id);
                }

                g_list_free(reservations);
            }
            else if (strcasecmp(flag, "N") == 0)
            {
                GList *reservations = get_reservations_by_hotel_id(get_table_reservations(cat_reservations), ID);
                reservations = g_list_sort(reservations, compare_reservations_by_begin_date_desc);

                GList *iter;
                for (iter = reservations; iter != NULL; iter = iter->next)
                {
                    Reservation *reservation = (Reservation *)iter->data;
                    char *reservation_id = get_reservation_id(reservation);
                    char *begin_date = get_reservation_begin_date(reservation);
                    char *end_date = get_reservation_end_date(reservation);
                    char *user_id = get_reservation_user_id(reservation);
                    double rating = get_reservation_rating(reservation);
                    double total_price = get_reservation_total_price(reservation);

                    printf("%s\033[32m;\033[0m%s\033[32m;\033[0m%s\033[32m;\033[0m%s\033[32m;\033[0m%.0f\033[32m;\033[0m%.3f\n", reservation_id, begin_date, end_date, user_id, rating, total_price);
                    free(reservation_id);
                    free(begin_date);
                    free(end_date);
                    free(user_id);
                }

                g_list_free(reservations);
            }
            sair(cat_flights, cat_passengers, cat_reservations, cat_users);
        }
    }
}

void query_5(catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users)
{
    int sys = system("clear");
    if (sys == 0)
    {

        sair(cat_flights, cat_passengers, cat_reservations, cat_users);
    }
}

void query_6(catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users)
{
    int sys = system("clear");
    if (sys == 0)
    {
        printf("Listar o top <N> aeroportos com mais passageiros, para um dado ano <YEAR>.");
        printf("\nDeverão ser contabilizados os voos com a data estimada de partida nesse ano.\n");
        printf("Introduza <N> : ");
        char n[20];
        int scan1 = scanf("%s", n);
        printf("\nIntroduza o <YEAR> : ");
        char year[20];
        int scan2 = scanf("%s", year);
        printf("\nDeseja obter o output com a flag 'F'? (S ou N) ");
        char s2[20];
        int scan3 = scanf("%s", s2);
        if (scan1 && scan2 && scan3)
        {
            if (strcasecmp(s2, "S") != 0 && strcasecmp(s2, "N") != 0)
            {
                printf("\033[31m\nOpção inválida... A voltar ao menu.\033[0m\n");
                menu_queries(cat_flights, cat_passengers, cat_reservations, cat_users);
            }
            else
            {
                // quando a query 6 estiver pronta, continuar
            }
        }
        sair(cat_flights, cat_passengers, cat_reservations, cat_users);
    }
}

void query_7(catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users)
{
    /*
    int sys = system("clear");
    if (sys == 0)
    {
        printf("\nListar o top <N> aeroportos com a maior mediana de atrasos.\n");
        printf("\nAtrasos num aeroporto são calculados a partir da diferença entre a data estimada e a data real de partida, para voos com origem nesse aeroporto.\n");
        printf("\nO valor do atraso deverá ser apresentado em segundos.\n");
        printf("\nCaso dois aeroportos tenham a mesma mediana, o nome do aeroporto deverá ser usado como critério de desempate (de forma crescente).\n");
        char n[20];
        printf("\nIntroduza <N> : ");
        int scan1 = scanf("%s", n);
        printf("\nDeseja obter o output com a flag 'F'? (S ou N) ");
        char flag[20];
        int scan2 = scanf("%s", flag);
        if (scan1 && scan2)
        {
            if (strcasecmp(flag, "S") != 0 && strcasecmp(flag, "N") != 0)
            {
                printf("\033[31m\nOpção inválida... A voltar ao menu.\033[0m\n");
                menu_queries(cat_flights, cat_passengers, cat_reservations, cat_users);
            }
            else
            {
                if (strcasecmp(flag, "S") == 0)
                {
                    int N = atoi(n);
                    GHashTable *flights = get_table_flights(cat_flights);
                    GHashTable *airportDelays = g_hash_table_new(g_str_hash, g_str_equal);
                    GHashTableIter iter;
                    gpointer key, value;
                    g_hash_table_iter_init(&iter, flights);
                    while (g_hash_table_iter_next(&iter, &key, &value))
                    {
                        Flight *flight = (Flight *)value;
                        char *origin = get_flight_origin(flight);
                        char *uppercaseOrigin = g_ascii_strup(origin, -1);
                        int delay = calculate_delay(flight);

                        GList *delaysList = g_hash_table_lookup(airportDelays, uppercaseOrigin);
                        if (delaysList == NULL)
                        {
                            delaysList = g_list_append(NULL, GINT_TO_POINTER(delay));
                            g_hash_table_insert(airportDelays, strdup(uppercaseOrigin), delaysList);
                        }
                        else
                        {
                            delaysList = g_list_append(delaysList, GINT_TO_POINTER(delay));
                        }
                        g_free(uppercaseOrigin);
                    }

                    GList *airportMedianList = NULL;
                    GHashTableIter iter2;
                    g_hash_table_iter_init(&iter2, airportDelays);
                    while (g_hash_table_iter_next(&iter2, &key, &value))
                    {
                        char *airport = (char *)key;
                        GList *delaysList = (GList *)value;
                        delaysList = g_list_sort(delaysList, compareByDelaysAscending);

                        int listLength = g_list_length(delaysList);
                        double median;
                        if (listLength % 2 == 0)
                        {
                            GList *middle1 = g_list_nth(delaysList, listLength / 2 - 1);
                            GList *middle2 = g_list_nth(delaysList, listLength / 2);
                            int delay1 = GPOINTER_TO_INT(middle1->data);
                            int delay2 = GPOINTER_TO_INT(middle2->data);
                            median = (delay1 + delay2) / 2.0;
                        }
                        else
                        {
                            GList *middle = g_list_nth(delaysList, listLength / 2);
                            median = GPOINTER_TO_INT(middle->data);
                        }

                        AirportMedian *airportMedian = g_new(AirportMedian, 1);
                        airportMedian->airport = strdup(airport);
                        airportMedian->median = median;
                        airportMedianList = g_list_append(airportMedianList, airportMedian);
                        g_free(airport);
                        g_list_free(delaysList);
                    }
                    g_hash_table_destroy(airportDelays);
                    airportMedianList = g_list_sort(airportMedianList, compareByMedianDescending);
                    GList *iter3;
                    int i;
                    for (iter3 = airportMedianList, i = 1; iter3 != NULL && i <= N; iter3 = iter3->next)
                    {
                        AirportMedian *airportMedian = (AirportMedian *)iter3->data;
                        if (strlen(airportMedian->airport) == 3)
                        {
                            printf("--- %d ---\n", i);
                            printf("name: \033[32m%s\033[0m\n", airportMedian->airport);
                            printf("median: \033[32m%.0f\033[0m\n", airportMedian->median);
                            if (i == N || g_list_next(iter3) == NULL)
                            {
                                break;
                            }
                            i++;
                            printf("\n");
                        }
                    }
                    g_list_free_full(airportMedianList, freeAirportMedian);
                }
                else if (strcasecmp(flag, "N") == 0)
                {
                    int N = atoi(n);
                    GHashTable *flights = get_table_flights(cat_flights);
                    GHashTable *airportDelays = g_hash_table_new(g_str_hash, g_str_equal);
                    GHashTableIter iter;
                    gpointer key, value;
                    g_hash_table_iter_init(&iter, flights);
                    while (g_hash_table_iter_next(&iter, &key, &value))
                    {
                        Flight *flight = (Flight *)value;
                        char *origin = flight->origin;
                        char *uppercaseOrigin = g_ascii_strup(origin, -1);
                        int delay = calculate_delay(flight);

                        GList *delaysList = g_hash_table_lookup(airportDelays, uppercaseOrigin);
                        if (delaysList == NULL)
                        {
                            delaysList = g_list_append(NULL, GINT_TO_POINTER(delay));
                            g_hash_table_insert(airportDelays, strdup(uppercaseOrigin), delaysList);
                        }
                        else
                        {
                            delaysList = g_list_append(delaysList, GINT_TO_POINTER(delay));
                        }
                        g_free(uppercaseOrigin);
                    }
                    GList *airportMedianList = NULL;
                    GHashTableIter iter2;
                    g_hash_table_iter_init(&iter2, airportDelays);
                    while (g_hash_table_iter_next(&iter2, &key, &value))
                    {
                        char *airport = (char *)key;
                        GList *delaysList = (GList *)value;
                        delaysList = g_list_sort(delaysList, compareByDelaysAscending);

                        int listLength = g_list_length(delaysList);
                        double median;
                        if (listLength % 2 == 0)
                        {
                            GList *middle1 = g_list_nth(delaysList, listLength / 2 - 1);
                            GList *middle2 = g_list_nth(delaysList, listLength / 2);
                            int delay1 = GPOINTER_TO_INT(middle1->data);
                            int delay2 = GPOINTER_TO_INT(middle2->data);
                            median = (delay1 + delay2) / 2.0;
                        }
                        else
                        {
                            GList *middle = g_list_nth(delaysList, listLength / 2);
                            median = GPOINTER_TO_INT(middle->data);
                        }

                        AirportMedian *airportMedian = g_new(AirportMedian, 1);
                        airportMedian->airport = strdup(airport);
                        airportMedian->median = median;
                        airportMedianList = g_list_append(airportMedianList, airportMedian);
                        g_free(airport);
                        g_list_free(delaysList);
                    }

                    airportMedianList = g_list_sort(airportMedianList, compareByMedianDescending);
                    GList *iter3;
                    int i = 0;
                    for (iter3 = airportMedianList; iter3 != NULL && i < N; iter3 = iter3->next)
                    {
                        AirportMedian *airportMedian = (AirportMedian *)iter3->data;
                        if (strlen(airportMedian->airport) == 3)
                        {
                            printf("\n%s\033[32m;\033[0m%.0f\n", airportMedian->airport, airportMedian->median);
                        }
                        i++;
                    }
                    g_hash_table_destroy(airportDelays);
                    g_list_free_full(airportMedianList, freeAirportMedian);
                }
            }
        }
        sair(cat_flights, cat_passengers, cat_reservations, cat_users);
    }
    */
}

void query_8(catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users)
{
    int sys = system("clear");
    if (sys == 0)
    {
        printf("Apresentar a receita total de um hotel entre duas datas (inclusive), a partir do seu identificador <ID>. \n");
        printf("As receitas de um hotel devem considerar apenas o preço por noite (price_per_night) de todas as reservas com noites entre as duas datas.\n");
        printf("Introduza <ID> : ");
        char hotel_id[20];
        int scan1 = scanf("%s", hotel_id);
        printf("\nIntroduza a data inicial : ");
        char start_date[20];
        int scan2 = scanf("%s", start_date);
        printf("\nIntroduza a data final : ");
        char end_date[20];
        int scan3 = scanf("%s", end_date);
        printf("\nDeseja obter o output com a flag 'F'? (S ou N) ");
        char s4[20];
        int scan4 = scanf("%s", s4);
        if (scan1 && scan2 && scan3 && scan4)
        {
            if (strcasecmp(s4, "S") != 0 && strcasecmp(s4, "N") != 0)
            {
                printf("\033[31m\nOpção inválida... A voltar ao menu.\033[0m\n");
                menu_queries(cat_flights, cat_passengers, cat_reservations, cat_users);
            }
            else
            {
                if (strcasecmp(s4, "S") == 0)
                {

                    int j = 0;
                    double total_revenue = 0.0;
                    double nights = 0.0;
                    GPtrArray *reservations = get_reservations_by_hotel_id2(get_table_reservations(cat_reservations), hotel_id);

                    if (strcmp(start_date, end_date) == 0)
                    {
                        increment_date(end_date);
                        j = 1;
                    }

                    for (int i = 0; i < reservations->len; i++)
                    {
                        Reservation *reservation = g_ptr_array_index(reservations, i);
                        char *begin_date = get_reservation_begin_date(reservation);
                        char *end_date2 = get_reservation_end_date(reservation);

                        if (is_date_between(begin_date, start_date, end_date) && is_date_between(end_date2, start_date, end_date))
                        {

                            if (j == 1)
                            {
                                nights = 1;
                            }
                            else
                            {
                                nights = calculate_nights2(begin_date, end_date2);
                            }
                            if (nights > 0)
                            {
                                total_revenue += nights * get_reservation_price_per_night(reservation);
                            }
                        }
                        free(begin_date);
                        free(end_date2);
                    }

                    g_ptr_array_free(reservations, TRUE);
                    printf("\n--- 1 ---\n");
                    printf("revenue: \033[32m%.0f\033[0m\n", total_revenue);
                }
                else if (strcasecmp(s4, "N") == 0)
                {
                    double total_revenue = 0.0;
                    int j = 0;
                    double nights = 0.0;
                    GPtrArray *reservations = get_reservations_by_hotel_id2(get_table_reservations(cat_reservations), hotel_id);

                    if (strcmp(start_date, end_date) == 0)
                    {
                        increment_date(end_date);
                        j = 1;
                    }

                    for (int i = 0; i < reservations->len; i++)
                    {
                        Reservation *reservation = g_ptr_array_index(reservations, i);
                        char *begin_date = get_reservation_begin_date(reservation);
                        char *end_date2 = get_reservation_end_date(reservation);

                        if (is_date_between(begin_date, start_date, end_date) && is_date_between(end_date2, start_date, end_date))
                        {

                            if (j == 1)
                            {
                                nights = 1;
                            }
                            else
                            {
                                nights = calculate_nights2(begin_date, end_date2);
                            }

                            if (nights > 0)
                            {
                                total_revenue += nights * get_reservation_price_per_night(reservation);
                            }
                        }
                        free(begin_date);
                        free(end_date2);
                    }

                    g_ptr_array_free(reservations, TRUE);
                    printf("\n\033[32m%.0f\033[0m\n", total_revenue);
                }
            }
        }
        sair(cat_flights, cat_passengers, cat_reservations, cat_users);
    }
}

void query_9(catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users)
{
    int sys = system("clear");
    if (sys == 0)
    {
        printf("\n Listar todos os utilizadores cujo nome começa com o prefixo passado por argumento, ordenados por nome (de forma crescente).\n");
        printf("\nCaso dois utilizadores tenham o mesmo nome, deverá ser usado o seu identificador como critério de desempate (de forma crescente).\n");
        printf("\nUtilizadores inativos não deverão ser considerados pela pesquisa\n");
        printf("\nIntroduza o <prefixo> : ");
        char prefix[30];
        int scan1 = scanf("%s", prefix);
        printf("\nDeseja obter o output com a flag 'F'? (S ou N) ");
        char flag[10];
        int scan2 = scanf("%s", flag);
        if (scan1 && scan2)
        {
            if (strcasecmp(flag, "S") != 0 && strcasecmp(flag, "N") != 0)
            {
                printf("\033[31m\nOpção inválida... A voltar ao menu.\033[0m\n");
                menu_queries(cat_flights, cat_passengers, cat_reservations, cat_users);
            }
            else
            {
                if (strcasecmp(flag, "S") == 0)
                {
                    GPtrArray *users = get_users_by_name_prefix2(get_table_users(cat_users), prefix);

                    g_ptr_array_sort(users, compare_users_by_name2);
                    guint i;
                    for (i = 0; i < users->len; i++)
                    {
                        User *user = g_ptr_array_index(users, i);
                        char *user_id = get_user_id(user);
                        char *user_name = get_user_name(user);

                        if (i == 0)
                        {
                            printf("--- %d ---\n", i + 1);
                            printf("id: \033[32m%s\033[0m\n", user_id);
                            printf("name: \033[32m%s\033[0m\n", user_name);
                        }
                        else
                        {
                            printf("\n--- %d ---\n", i + 1);
                            printf("id: \033[32m%s\033[0m\n", user_id);
                            printf("name: \033[32m%s\033[0m\n", user_name);
                        }
                        // Free the memory allocated by get_user_id()
                        free(user_id);
                        // Free the memory allocated by get_user_name()
                        free(user_name);
                        free(user);
                    }
                    g_ptr_array_free(users, TRUE);
                }
                else if (strcasecmp(flag, "N") == 0)
                {
                    GPtrArray *users = get_users_by_name_prefix2(get_table_users(cat_users), prefix);
                    g_ptr_array_sort(users, compare_users_by_name2);

                    guint i;
                    for (i = 0; i < users->len; i++)
                    {
                        User *user = g_ptr_array_index(users, i);
                        char *user_id = get_user_id(user);
                        char *user_name = get_user_name(user);

                        printf("\n%s\033[32m;\033[0m%s\n", user_id, user_name);

                        free(user_id);
                        free(user_name);
                        free(user);
                    }
                    g_ptr_array_free(users, TRUE);
                }
            }
            sair(cat_flights, cat_passengers, cat_reservations, cat_users);
        }
    }
}

void query_10(catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users)
{
    int sys = system("clear");
    if (sys == 0)
    {
        printf("\nListar as viagens nas quais o passageiro deu gorjeta, no intervalo de tempo (data A, data B), sendo esse intervalo representado pelos parâmetros <data A> e <data B>, ordenadas por ordem de distância percorrida (em ordem decrescente).\n");
        printf("Em caso de empate, as viagens mais recentes deverão aparecer primeiro.\n");
        printf("Se persistirem empates, ordenar pelo id da viagem (em ordem decrescente).\n");
        sair(cat_flights, cat_passengers, cat_reservations, cat_users);
    }
}

void menu_queries(catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users)
{
    int continuar = 1;
    do
    {
        printf("\nEscolha a query que deseja realizar.\n\n");
        printf("1.  Query 1\n");
        printf("2.  Query 2\n");
        printf("3.  Query 3\n");
        printf("4.  Query 4\n");
        printf("5.  Query 5\n");
        printf("6.  Query 6\n");
        printf("7.  Query 7\n");
        printf("8.  Query 8\n");
        printf("9.  Query 9\n");
        printf("10. Query 10\n");
        printf("11. Voltar\n\n");

        int scan = scanf("%d", &continuar);
        if (scan)
        {
            switch (continuar)
            {
            case 1:
                query_1(cat_flights, cat_passengers, cat_reservations, cat_users);
                break;

            case 2:
                query_2(cat_flights, cat_passengers, cat_reservations, cat_users);
                break;

            case 3:
                query_3(cat_flights, cat_passengers, cat_reservations, cat_users);
                break;

            case 4:
                query_4(cat_flights, cat_passengers, cat_reservations, cat_users);
                break;

            case 5:
                query_5(cat_flights, cat_passengers, cat_reservations, cat_users);
                break;

            case 6:
                query_6(cat_flights, cat_passengers, cat_reservations, cat_users);
                break;

            case 7:
                //query_7(cat_flights, cat_passengers, cat_reservations, cat_users);
                break;

            case 8:
                query_8(cat_flights, cat_passengers, cat_reservations, cat_users);
                break;

            case 9:
                query_9(cat_flights, cat_passengers, cat_reservations, cat_users);
                break;

            case 10:
                query_10(cat_flights, cat_passengers, cat_reservations, cat_users);
                break;

            case 11:
                int sys = system("clear");
                if (sys != 0)
                    break;
                sair(cat_flights, cat_passengers, cat_reservations, cat_users);
                break;

            default:
                printf("\nDigite uma opcao valida\n");
            }
        }
    } while ((continuar != 11 || continuar != 4));
}

void menu_interativo(int argc, char **argv)
{
    int continuar = 1;
    char *path = NULL;
    path = malloc(100 * sizeof(char));
    int sys = system("clear");
    if (sys == 0)
    {
        do
        {
            printf("\nSeja bem-vindo ao modo interativo.\n\n");
            if (argc <= 1)
            {

                printf("Introduza o caminho para a pasta com o dataset a ser utilizado: ");
                if (scanf("%s", path) != 1)
                {
                    printf("\nInput error!");
                    menu_interativo(argc, argv);
                }
            }
            else
            {
                path = strdup(argv[1]);
            }
            sys = system("clear");

            printf("\nO caminho escolhido é: %s\n\n", path);
            printf("1. Continuar\n");
            printf("2. Sair\n\n");

            int scan = scanf("%d", &continuar);
            sys = system("clear");
            if (scan && sys == 0)
            {
                switch (continuar)
                {
                case 1:

                    bool flight_csv = find_csv(path, "flights.csv");
                    bool passengers_csv = find_csv(path, "passengers.csv");
                    bool reservations_csv = find_csv(path, "reservations.csv");
                    bool users_csv = find_csv(path, "users.csv");

                    if (path[strlen(path) - 1] != '/')
                    {
                        strcat(path, "/");
                    }

                    if (flight_csv && passengers_csv && reservations_csv && users_csv)
                    {

                        printf("\033[1;32m");
                        printf("\n\nTodos os ficheiros foram encontrados!\n\n");
                        printf("\033[0m");
                        catalogo_Flights *cat_flights = init_catalogo_flights();
                        catalogo_Passengers *cat_passengers = init_catalogo_passengers();
                        catalogo_Reservations *cat_reservations = init_catalogo_reservations();
                        catalogo_Users *cat_users = init_catalogo_users();
                        limpar_dados_validos(path, cat_flights, cat_passengers, cat_reservations, cat_users);

                        sair(cat_flights, cat_passengers, cat_reservations, cat_users);
                    }
                    else
                    {
                        printf("\033[1;31m");
                        printf("\n\nErro! Não foi possível encontrar todos os ficheiros no diretório %s!\n\n", path);
                        printf("\033[0m");
                    }
                    free(path);
                    sys = system("clear");
                    break;

                case 2:
                    exit(0);
                    break;

                default:
                    printf("\nDigite uma opcao valida\n");
                }
            }
        } while (continuar != 2);
    }
}

void logo(int argc, char **argv)
{
    int sys = system("clear");
    if (sys == 0)
    {
        printf("\033[1;34m"); // Configura cor vermelha e negrito
        printf("\n\n\n\n\n");
        printf("                         ___________      ___________      ______      _______        ___________        _______         ________        \n");
        printf("                        |._________.|    |_____._____|    |.. _ .|     |. __ .|       |.........|       |.. _ ..|       |........|\n");
        printf("                        |.|       |.|         |.|         |..|_|.|     |.|__|.|       |...__....|       |..|_|..|       |___ . __|\n");
        printf("                        |.|_______|.|         |.|         |. ____|     |______|       |..|__|...|       | ._____|           |.|   \n");
        printf("                        |. _______ .|         |.|         |.| \\        |.|            |.........|       |.| \\               |.|    \n");
        printf("                        |.|       |.|     ____|.|____     |.|  \\       |.|            |.........|       |.|  \\              |.|    \n");
        printf("                        |_|       |_|    |___________|    |_|   \\      |_|            |_________|       |_|   \\             |_|    \n");
        printf("                   \n");
        printf("\n");
        printf("\n");
        // completar :   Escrever de forma semelhante, por baixo do Airport, "Manager"
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\033[0m");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t Prima qualquer tecla para continuar...\n\n\n\n\n");
        getchar();
        menu_interativo(argc, argv);
    }
}
