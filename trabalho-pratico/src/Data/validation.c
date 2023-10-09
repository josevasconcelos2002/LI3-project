#include "../../include/validation.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

// Verifica se a string está vazia e se o apontador é !NULL
static bool valid_string(char *found)
{
   bool result = false;
   int size;
   if (found)
   {
      size = strlen(found);
      if (size > 0)
         result = true;
   }
   return result;
}

// verifica ints
static bool valid_int(char *found)
{
   int tam = strlen(found);

   if (tam == 0)
      return 0;

   for (int i = 0; i < tam; i++)
   {
      if (!isdigit(found[i]))
         return 0;
   }
   if (atoi(found) <= 0)
      return 0;

   return 1;
}

// verifica doubles
static int valid_double(char *found)
{
   int tam = strlen(found);
   int dotCount = 0;

   if (tam == 0)
      return 0;

   for (int i = 0; i < tam; i++)
   {
      if (!isdigit(found[i]))
      {
         if (found[i] == '.' && dotCount == 0)
         {
            dotCount++;
         }
         else
         {
            return 0;
         }
      }
   }

   double num = atof(found);
   if (num <= 0.0)
      return 0;

   // Arredonda para 3 casas decimais
   double roundedNum = round(num * 1000) / 1000.0;

   // Se o número original e o número arredondado são diferentes, significa que havia mais de 3 casas decimais
   if (num != roundedNum)
      return 0;
   return 1;
}

// verifica bools
static bool valid_bool(char *found)
{
   if (strcasecmp(found, "true") == 0 || strcasecmp(found, "false") == 0)
   {
      return true;
   }
   else
   {
      return false;
   }
}

// verifica o status de uma conta

/*
static bool valid_account_status(char *found)
{
   bool result = false;
   if (strcasecmp(found, "active\n") != 0 && strcasecmp(found, "inactive\n") != 0)
   {
      result = true;
   }
   return result;
}
*/

/**
 * @brief This function is used to see if a date is valid or not.
 *
 * @param date  Pointer to a date (yyyy/mm/dd).
 *
 * @return bool
 */
bool valid_date(const char *date)
{
   int day, month, year;
   if (sscanf(date, "%d/%d/%d", &year, &month, &day) != 3)
      return false;
   if (month < 1 || month > 12)
      return false;
   if (day < 1 || day > 31)
      return false;
   if (year < 0)
      return false;
   return true;
}

// criação de "flight-valid.csv"
static void valid_flight()
{
   FILE *fp = fopen("entrada/flight.csv", "r");
   FILE *flight_valid = fopen("Resultados/flight-valid.csv", "w");
   char *line = NULL;
   size_t len = 0;
   char *string, *found, *aux;
   int c_pal;
   int checker;

   for (int i = 0; (getline(&line, &len, fp) != -1); i++)
   {

      if (i == 0)
         fprintf(flight_valid, "%s", line);

      else
      {

         string = strdup(line);
         aux = string;

         for (c_pal = 0, checker = 1; ((found = strsep(&string, ";")) != NULL && checker != 0); c_pal++)
         {

            // id
            if (c_pal == 0)
            {
               checker = valid_int(found);
            }

            // airline
            if (c_pal == 1)
            {
               checker = valid_string(found);
            }

            // plane_model
            if (c_pal == 2)
            {
               checker = valid_string(found);
            }

            // total_seats
            if (c_pal == 3)
            {
               checker = valid_int(found);
            }

            // origin
            if (c_pal == 4)
            {
               checker = valid_string(found);
            }

            // destination
            if (c_pal == 5)
            {
               checker = valid_string(found);
            }

            // schedule_departure_date
            if (c_pal == 6)
            {
               checker = valid_date(found);
            }

            // schedyle_arrival_date
            if (c_pal == 7)
            {
               checker = valid_date(found);
            }

            // real_departure_date
            if (c_pal == 8)
            {
               checker = valid_date(found);
            }

            // real_arrival_date
            if (c_pal == 9)
            {
               checker = valid_date(found);
            }

            // pilot
            if (c_pal == 10)
            {
               checker = valid_string(found);
            }

            // copilot
            if (c_pal == 11)
            {
               checker = valid_string(found);
            }

            // notes
            if (c_pal == 12)
            {
               checker = valid_string(found);
            }
         }
         free(aux);
      }

      if (checker != 0 && c_pal == 13)
         fprintf(flight_valid, "%s", line);
   }
   fclose(fp);
   fclose(flight_valid);
}

// criação de "passenger-valid.csv"
static void valid_passenger()
{
   FILE *fp = fopen("entrada/passenger.csv", "r");
   FILE *passenger_valid = fopen("Resultados/passenger-valid.csv", "w");
   char *line = NULL;
   size_t len = 0;
   char *string, *found, *aux;
   int c_pal;
   int checker;

   for (int i = 0; (getline(&line, &len, fp) != -1); i++)
   {

      if (i == 0)
         fprintf(passenger_valid, "%s", line);

      else
      {

         string = strdup(line);
         aux = string;

         for (c_pal = 0, checker = 1; ((found = strsep(&string, ";")) != NULL && checker != 0); c_pal++)
         {

            // flight_id
            if (c_pal == 0)
            {
               checker = valid_int(found);
            }

            // user_id
            if (c_pal == 1)
            {
               checker = valid_int(found);
            }
         }
         free(aux);
      }

      if (checker != 0 && c_pal == 2)
         fprintf(passenger_valid, "%s", line);
   }
   fclose(fp);
   fclose(passenger_valid);
}

// criação de "reservation-valid.csv"
static void valid_reservation()
{
   FILE *fp = fopen("entrada/reservation.csv", "r");
   FILE *reservation_valid = fopen("Resultados/reservation-valid.csv", "w");
   char *line = NULL;
   size_t len = 0;
   char *string, *found, *aux;
   int c_pal;
   int checker;

   for (int i = 0; (getline(&line, &len, fp) != -1); i++)
   {

      if (i == 0)
         fprintf(reservation_valid, "%s", line);

      else
      {

         string = strdup(line);
         aux = string;

         for (c_pal = 0, checker = 1; ((found = strsep(&string, ";")) != NULL && checker != 0); c_pal++)
         {

            // id
            if (c_pal == 0)
            {
               checker = valid_int(found);
            }

            // user_id
            if (c_pal == 1)
            {
               checker = valid_int(found);
            }

            // hotel_id
            if (c_pal == 2)
            {
               checker = valid_int(found);
            }

            // hotel_name
            if (c_pal == 3)
            {
               checker = valid_string(found);
            }

            // hotel_stars
            if (c_pal == 4)
            {
               checker = valid_int(found);
            }

            // city_tax
            if (c_pal == 5)
            {
               checker = valid_double(found);
            }

            // adress
            if (c_pal == 6)
            {
               checker = valid_string(found);
            }

            // begin_date
            if (c_pal == 7)
            {
               checker = valid_date(found);
            }

            // end_date
            if (c_pal == 8)
            {
               checker = valid_date(found);
            }

            // price_per_night
            if (c_pal == 9)
            {
               checker = valid_double(found);
            }

            // includes_breakfast
            if (c_pal == 10)
            {
               checker = valid_bool(found);
            }

            // room_details
            if (c_pal == 11)
            {
               checker = valid_string(found);
            }

            // rating
            if (c_pal == 12)
            {
               checker = valid_double(found);
            }

            // comment
            if (c_pal == 13)
            {
               checker = valid_string(found);
            }
         }
         free(aux);
      }

      if (checker != 0 && c_pal == 14)
         fprintf(reservation_valid, "%s", line);
   }
   fclose(fp);
   fclose(reservation_valid);
}

// criação de "user-valid.csv"
static void valid_user()
{
   FILE *fp = fopen("entrada/user.csv", "r");
   FILE *user_valid = fopen("Resultados/user-valid.csv", "w");
   char *line = NULL;
   size_t len = 0;
   char *string, *found, *aux;
   int c_pal;
   int checker;

   for (int i = 0; (getline(&line, &len, fp) != -1); i++)
   {

      if (i == 0)
         fprintf(user_valid, "%s", line);

      else
      {

         string = strdup(line);
         aux = string;

         for (c_pal = 0, checker = 1; ((found = strsep(&string, ";")) != NULL && checker != 0); c_pal++)
         {

            // id
            if (c_pal == 0)
            {
               checker = valid_int(found);
            }

            // name
            if (c_pal == 1)
            {
               checker = valid_string(found);
            }

            // email
            if (c_pal == 2)
            {
               checker = valid_string(found);
            }

            // phone_number
            if (c_pal == 3)
            {
               checker = valid_int(found);
            }

            // birth_date
            if (c_pal == 4)
            {
               checker = valid_date(found);
            }

            // sex
            if (c_pal == 5)
            {
               checker = valid_string(found);
            }

            // passport
            if (c_pal == 6)
            {
               checker = valid_int(found);
            }

            // country_code
            if (c_pal == 7)
            {
               checker = valid_string(found);
            }

            // adress
            if (c_pal == 8)
            {
               checker = valid_string(found);
            }

            // account_creation
            if (c_pal == 9)
            {
               checker = valid_date(found);
            }

            // pay_method
            if (c_pal == 10)
            {
               checker = valid_string(found);
            }

            // account_status
            if (c_pal == 11)
            {
               checker = valid_string(found);
            }
         }
         free(aux);
      }

      if (checker != 0 && c_pal == 12)
         fprintf(user_valid, "%s", line);
   }
   fclose(fp);
   fclose(user_valid);
}

// Função principal
int limpar_dados_invalidos()
{
   valid_flight();
   valid_passenger();
   valid_reservation();
   valid_user();
   return 0;
}

/* For Testing
int main(){
   limpar_dados_invalidos();
}
*/
