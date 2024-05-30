#include "../../include/validation.h"
#include "../../include/parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <sys/stat.h>

/**
 * @brief This function is responsible for checking if a string is valid.
 *
 * @param found Pointer to the string.
 *
 * @return bool.
 */
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

void free_id(gpointer key, gpointer value)
{
    free(key);
}

/**
 * @brief This function is responsible for checking if an airport string is valid.
 *
 * @param airport Pointer to the airport name.
 *
 * @return bool.
 */
bool valid_origin_dest(const char *airport)
{
   if (airport != NULL && strlen(airport) == 3)
   {
      for (int i = 0; i < 3; ++i)
      {
         if (!isalpha(airport[i]))
         {
            return false;
         }
      }
      return true;
   }
   return false;
}

/**
 * @brief This function is responsible for checking if a includes_breakfast string is valid.
 *
 * @param str Pointer to the string.
 *
 * @return int.
 */
int valid_includes_breakfast(char *str)
{
   // Check for empty string
   if (strlen(str) == 0)
      return 1;

   // Check for "false" values
   if (strcasecmp(str, "f") == 0 || strcasecmp(str, "false") == 0 || strcmp(str, "0") == 0)
      return 1;

   // Check for "true" values
   if (strcasecmp(str, "t") == 0 || strcasecmp(str, "true") == 0 || strcmp(str, "1") == 0)
      return 1;

   // Invalid string
   return 0;
}

/**
 * @brief This function is responsible for checking if a sex string is valid.
 *
 * @param found Pointer to the string.
 *
 * @return bool.
 */
static bool valid_sex(char *found)
{
   if (found == NULL || strlen(found) != 1)
      return false;

   char gender = toupper(found[0]);

   return (gender == 'M' || gender == 'F');
}

/**
 * @brief This function is responsible for checking if a hotel_stars string is valid.
 *
 * @param hotel_stars Pointer to the string.
 *
 * @return bool.
 */
bool valid_hotel_stars(const char *hotel_stars)
{
   // Check if the hotel_stars is not NULL
   if (hotel_stars == NULL)
   {
      return false;
   }

   // Check if the hotel_stars contains only digits and has a length of 1
   for (int i = 0; hotel_stars[i] != '\0'; i++)
   {
      if (!isdigit(hotel_stars[i]))
      {
         return false;
      }
   }
   if (strlen(hotel_stars) != 1)
   {
      return false;
   }

   // Convert the string to an integer
   int stars = atoi(hotel_stars);

   // Check if the number of stars is between 1 and 5 (inclusive)
   return (stars >= 1 && stars <= 5);
}

/**
 * @brief This function is responsible for checking if a rating string is valid.
 *
 * @param rating Pointer to the string.
 *
 * @return bool.
 */
bool valid_rating(const char *rating)
{
   // Check if the rating is not NULL and has a length of 1
   if (rating == NULL || strlen(rating) != 1)
   {
      return false;
   }

   // Check if the rating contains only digits
   for (int i = 0; rating[i] != '\0'; i++)
   {
      if (!isdigit(rating[i]))
      {
         return false;
      }
   }

   // Convert the string to an integer
   int ratingValue = atoi(rating);

   // Check if the number of stars is between 1 and 5 (inclusive)
   return (ratingValue >= 1 && ratingValue <= 5);
}

/**
 * @brief This function is responsible for checking if a phone_number string is valid.
 *
 * @param found Pointer to the string.
 *
 * @return bool.
 */
static bool valid_phone_number(char *found)
{
   int size = strlen(found);

   // Check if the size is above 18
   if (size > 18)
      return false;

   // Check for the format "xxx xxx xxx" (with or without spaces)
   int digit_count = 0;
   for (int i = 0; i < size; i++)
   {
      if (found[i] == ' ' || found[i] == '\0' || found[i] == '+' || found[i] == '(' || found[i] == ')')
         continue; // Skip spaces and parentheses

      if (!isdigit(found[i]))
         return false; // Non-digit character

      digit_count++;
   }

   return digit_count == 9 || digit_count == 12;
}

/**
 *  @brief This function is responsible for checking if a custom_int string (e.g: Book00000001) is valid.
 *
 * @param found Pointer to the string.
 *
 * @return bool.
 */
static bool valid_custom_int(char *found)
{
   int tam = strlen(found);

   if (tam == 0)
      return 0;

   if (strncmp(found, "Book", 4) == 0)
   {
      for (int i = 4; i < tam; i++)
      {
         if (!isdigit(found[i]))
            return 0;
      }

      if (atoi(found + 4) <= 0)
         return 0;

      return 1;
   }

   for (int i = 0; i < tam; i++)
   {
      if (!isdigit(found[i]))
         return 0;
   }

   if (atoi(found) <= 0)
      return 0;

   return 1;
}

/**
 * @brief This function is responsible for checking if a email string is valid.
 *
 * @param email Pointer to the string.
 *
 * @return bool.
 */
bool valid_email(const char *email)
{
   // Check if the email is not NULL
   if (email == NULL)
   {
      return false;
   }

   // Find the position of '@' in the email
   const char *atSymbol = strchr(email, '@');

   if (atSymbol == NULL || atSymbol == email || atSymbol == email + strlen(email) - 1)
   {
      return false;
   }

   char username[atSymbol - email + 1];
   strncpy(username, email, atSymbol - email);
   username[atSymbol - email] = '\0';

   const char *domainAndTLD = atSymbol + 1;
   const char *dotSymbol = strchr(domainAndTLD, '.');
   if (dotSymbol == NULL || dotSymbol == domainAndTLD || dotSymbol == domainAndTLD + strlen(domainAndTLD) - 1)
   {
      return false;
   }

   char domain[dotSymbol - domainAndTLD + 1];
   strncpy(domain, domainAndTLD, dotSymbol - domainAndTLD);
   domain[dotSymbol - domainAndTLD] = '\0';

   const char *tld = dotSymbol + 1;

   if (strlen(username) < 1 || strlen(domain) < 1 || strlen(tld) < 2)
   {
      return false;
   }

   return true;
}

/**
 * @brief This function is responsible for checking if a city_tax string is valid.
 *
 * @param city_tax Pointer to the string.
 *
 * @return bool.
 */
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

bool valid_city_tax(const char *city_tax)
{
   // Check if the city_tax is not NULL
   if (city_tax == NULL)
   {
      return false;
   }

   // Check if the string is empty
   if (city_tax[0] == '\0')
   {
      return false;
   }

   // Iterate through each character of the string
   for (int i = 0; city_tax[i] != '\0'; i++)
   {
      // Check if the character is not a digit
      if (!isdigit(city_tax[i]))
      {
         return false;
      }
   }

   // Convert the string to an integer
   int tax = atoi(city_tax);

   // Check if the number is non-negative
   return (tax >= 0);
}

/**
 * @brief This function is responsible for checking if a country_code string is valid.
 *
 * @param country_code Pointer to the string.
 *
 * @return bool.
 */
bool valid_country_code(const char *countryCode)
{
   if (countryCode == NULL)
   {
      return false;
   }

   if (strlen(countryCode) != 2)
   {
      return false;
   }

   for (int i = 0; i < 2; i++)
   {
      if (!isalpha(countryCode[i]))
      {
         return false;
      }
   }

   return true;
}

/**
 * @brief This function is responsible for checking if a price_per_night string is valid.
 *
 * @param price Pointer to the string.
 *
 * @return bool.
 */
bool valid_price_per_night(const char *price)
{
   // Check if the price is not NULL
   if (price == NULL)
   {
      return false;
   }

   // Check if the price contains only digits
   for (int i = 0; price[i] != '\0'; i++)
   {
      if (price[i] < '0' || price[i] > '9')
      {
         return false;
      }
   }

   // Convert the string to an integer
   int priceValue = atoi(price);

   // Check if the price is higher than 0
   return (priceValue > 0);
}

/**
 * @brief This function is responsible for checking if a integer string is valid.
 *
 * @param found Pointer to the string.
 *
 * @return bool.
 */
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

/**
 * @brief This function is responsible for checking if a account_status string is valid.
 *
 * @param accountStatus Pointer to the string.
 *
 * @return bool.
 */
bool valid_account_status(const char *accountStatus)
{
   if (accountStatus == NULL)
   {
      return false;
   }
   if (strcasecmp(accountStatus, "active") == 0 || strcasecmp(accountStatus, "inactive") == 0 || strcasecmp(accountStatus, "active\n") == 0 || strcasecmp(accountStatus, "inactive\n") == 0)
   {
      return true;
   }

   return false;
}

/**
 * @brief This function is responsible for checking if a hour string is valid.
 *
 * @param hours Pointer to the string.
 *
 * @return bool.
 */
static bool valid_hour(char *hours)
{
   int hour, minute, second;
   if (sscanf(hours, "%d:%d:%d", &hour, &minute, &second) != 3)
      return false;
   if (hour < 0 || hour > 23)
      return false;
   if (minute < 0 || minute > 59)
      return false;
   if (second < 0 || second > 59)
      return false;
   return true;
}

/**
 * @brief This function is responsible for checking if a date string is valid.
 *
 * @param date Pointer to the string.
 *
 * @return bool.
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

/**
 * @brief This function is responsible for comparing two date.
 *
 * @param date1 Pointer to the first date.
 * @param date2 Pointer to the second date.
 *
 * @return bool.
 */
bool compare_dates_users(char *date1, char *date2)
{
   int year1, month1, day1;
   int year2, month2, day2, hour2, minute2, second2;

   sscanf(date1, "%d/%d/%d", &year1, &month1, &day1);
   sscanf(date2, "%d/%d/%d %d:%d:%d", &year2, &month2, &day2, &hour2, &minute2, &second2);

   if (year1 > year2)
      return false;
   else if (year1 < year2)
      return true;

   // If the years are equal, compare months
   if (month1 > month2)
      return false;
   else if (month1 < month2)
      return true;

   // If the months are equal, compare days
   if (day1 > day2)
      return false;
   else if (day1 < day2)
      return true;

   return false;
}

/**
 * @brief This function is responsible for comparing two dates.
 *
 * @param date1 Pointer to the first date.
 * @param date2 Pointer to the second date.
 *
 * @return bool.
 */
bool compare_dates(const char *date1, const char *date2)
{

   int year1, month1, day1;
   int year2, month2, day2;

   sscanf(date1, "%d/%d/%d", &year1, &month1, &day1);
   sscanf(date2, "%d/%d/%d", &year2, &month2, &day2);

   if (year1 > year2)
      return true;
   else if (year1 < year2)
      return false;

   // If the years are equal, compare months
   if (month1 > month2)
      return true;
   else if (month1 < month2)
      return false;

   // If the months are equal, compare days
   if (day1 > day2)
      return true;
   else if (day1 < day2)
      return false;

   return true;
}

/**
 * @brief This function is responsible for comparing two dates.
 *
 * @param date1 Pointer to the first date.
 * @param date2 Pointer to the second date.
 *
 * @return bool.
 */
bool compare_dates_flights(char *date1, char *date2)
{

   int year1, month1, day1, hour1, minute1, second1;
   int year2, month2, day2, hour2, minute2, second2;

   char *data1 = strtok(date1, " ");
   char *tim1 = strtok(NULL, " ");
   char *data2 = strtok(date2, " ");
   char *tim2 = strtok(NULL, " ");

   sscanf(data1, "%d/%d/%d", &year1, &month1, &day1);
   sscanf(tim1, "%d:%d:%d", &hour1, &minute1, &second1);
   sscanf(data2, "%d/%d/%d", &year2, &month2, &day2);
   sscanf(tim2, "%d:%d:%d", &hour2, &minute2, &second2);

   if (year1 > year2)
      return true;
   else if (year1 < year2)
      return false;

   // If the years are equal, compare months
   if (month1 > month2)
      return true;
   else if (month1 < month2)
      return false;

   // If the months are equal, compare days
   if (day1 > day2)
      return true;
   else if (day1 < day2)
      return false;

   if (hour1 > hour2)
      return true;
   else if (hour1 < hour2)
      return false;

   if (minute1 > minute2)
      return true;
   else if (minute1 < minute2)
      return false;

   if (second1 > second2)
      return true;
   else if (second1 < second2)
      return false;

   return false;
}

/**
 * @brief This function is responsible for eliminating the invalid flights, writing them on the errors file and inserting them in an array.
 *
 * @param dataset_path Path to the dataset.
 * @param cat_flights Pointer to the catalog of flights.
 * @param invalid_fuds Pointer to the array of invalid flights.
 * @param num_invalid_fuds Pointer to the number of invalid flights.
 *
 * @return void.
 */
static void invalid_flights(char *dataset_path, catalogo_Flights *cat_flights, GHashTable** id_table_flight)
{
   char file_path[256];
   snprintf(file_path, sizeof(file_path), "%sflights.csv", dataset_path);
   FILE *fp = fopen(file_path, "r");
   FILE *flights_errors = fopen("Resultados/flights_errors.csv", "w");
   char *line = NULL;
   size_t len = 0;
   char *string, *found, *aux;
   int c_pal = 0;
   int checker = 1;
   static char schedule_departure_date[20]; // Assuming "yyyy/mm/dd hh:mm:ss" format
   static char schedule_arrival_date[20];
   static char real_departure_date[20];
   static char real_arrival_date[20];
   static char origin[20];
   static char dest[20];
   char *id = NULL;

   for (int i = 0; (getline(&line, &len, fp) != -1); i++)
   {

      if (i == 0)
         fprintf(flights_errors, "%s", line);

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
               id = strdup(found);
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
               strcpy(origin, found);
               checker = valid_origin_dest(found);
            }

            // destination
            if (c_pal == 5)
            {
               strcpy(dest, found);
               checker = valid_origin_dest(found);
               if (strcasecmp(origin, dest) == 0)
                  checker = 0;
            }

            // schedule_departure_date
            if (c_pal == 6)
            {
               strcpy(schedule_departure_date, found);
               if (found)
               {
                  char *date = strtok(found, " ");
                  char *time = strtok(NULL, " ");

                  if (date && time)
                  {
                     checker = valid_date(date) && valid_hour(time);
                  }
                  else
                  {
                     checker = false;
                  }
               }
               else
                  checker = false;
            }

            // schedule_arrival_date
            if (c_pal == 7)
            {
               strcpy(schedule_arrival_date, found);
               if (found)
               {
                  char *date = strtok(found, " ");
                  char *time = strtok(NULL, " ");
                  if (date && time)
                  {
                     checker = valid_date(date) && valid_hour(time);
                  }
                  else
                  {
                     checker = false;
                  }
               }
               else
                  checker = false;
               if (checker != 0)
               {
                  checker = compare_dates_flights(schedule_arrival_date, schedule_departure_date);
               }
            }

            // real_departure_date
            if (c_pal == 8)
            {
               strcpy(real_departure_date, found);
               if (found)
               {
                  char *date = strtok(found, " ");
                  char *time = strtok(NULL, " ");
                  if (date && time)
                  {
                     checker = valid_date(date) && valid_hour(time);
                  }
                  else
                  {
                     checker = false;
                  }
               }
               else
                  checker = false;
            }

            // real_arrival_date
            if (c_pal == 9)
            {
               strcpy(real_arrival_date, found);
               if (found)
               {
                  char *date = strtok(found, " ");
                  char *time = strtok(NULL, " ");
                  if (date && time)
                  {
                     checker = valid_date(date) && valid_hour(time);
                  }
                  else
                  {
                     checker = false;
                  }
               }
               else
                  checker = false;
               if (checker != 0)
               {
                  checker = compare_dates_flights(real_arrival_date, real_departure_date);
               }
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

      if (checker == 0 || c_pal != 13)
      {
         if (id != NULL && strcmp(id, "") != 0)
         {
            char* id_copy = strdup(id);
            g_hash_table_insert(*id_table_flight, id_copy, id_copy);

         }
         fprintf(flights_errors, "%s", line);
      }
      if (checker != 0 || c_pal == 13)
      {
         parse_flight_line2(line, cat_flights);
      }
      free(id);
   }
   if (line)
      free(line);
   fclose(fp);
   fclose(flights_errors);
}

/**
 * @brief This function is responsible for eliminating the invalid reservations, writing them on the errors file and inserting them in an array.
 *
 * @param dataset_path Path to the dataset.
 * @param cat_reservations Pointer to the catalog of reservations.
 * @param invalid_uids Pointer to the array of invalid reservations.
 * @param num_invalid_uids Pointer to the number of invalid reservations.
 *
 * @return void
 */
static void invalid_reservations(char *dataset_path, catalogo_Reservations *cat_reservations,catalogo_Users *cat_users,GHashTable* id_table_user)
{
   char file_path[256];
   snprintf(file_path, sizeof(file_path), "%sreservations.csv", dataset_path);
   FILE *fp = fopen(file_path, "r");
   FILE *reservations_errors = fopen("Resultados/reservations_errors.csv", "w");
   char *line = NULL;
   size_t len = 0;
   char *string, *found, *aux;
   int c_pal = 0;
   int checker = 1;
   static char begin_date[11]; // Assuming "yyyy/mm/dd" format
   static char end_date[11];
   for (int i = 0; (getline(&line, &len, fp) != -1); i++)
   {

      if (i == 0)
         fprintf(reservations_errors, "%s", line);

      else
      {

         string = strdup(line);
         aux = string;

         for (c_pal = 0, checker = 1; ((found = strsep(&string, ";")) != NULL && checker != 0); c_pal++)
         {

            // id
            if (c_pal == 0)
            {
               checker = valid_custom_int(found);
            }

            // user_id
            if (c_pal == 1)
            {
               checker = valid_string(found);
               if(g_hash_table_lookup(id_table_user, found) != NULL)
               {
                  checker = 0;
                  break;
               }
            }

            // hotel_id
            if (c_pal == 2)
            {
               checker = valid_string(found);
            }

            // hotel_name
            if (c_pal == 3)
            {
               checker = valid_string(found);
            }

            // hotel_stars
            if (c_pal == 4)
            {
               checker = valid_hotel_stars(found);
            }

            // city_tax
            if (c_pal == 5)
            {
               checker = valid_city_tax(found);
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
               if (checker != 0)
               {
                  strcpy(begin_date, found);
               }
            }

            // end_date
            if (c_pal == 8)
            {
               checker = valid_date(found);
               if (checker != 0)
               {
                  strcpy(end_date, found);
                  checker = compare_dates(end_date, begin_date);
               }
            }

            // price_per_night
            if (c_pal == 9)
            {
               checker = valid_price_per_night(found);
            }

            // includes_breakfast
            if (c_pal == 10)
            {
               checker = valid_includes_breakfast(found);
            }

            // room_details
            if (c_pal == 11)
            {
               checker = valid_string(found);
            }

            // rating
            if (c_pal == 12)
            {
               checker = valid_rating(found);
            }

            // comment
            if (c_pal == 13)
            {
               checker = valid_string(found);
            }
         }
         free(aux);
      }

      if (checker == 0 || c_pal != 14)
         fprintf(reservations_errors, "%s", line);
      if (checker != 0 && c_pal == 14)
      {
         parse_reservation_line2(line, cat_reservations, cat_users);
      }
   }
   if (line)
      free(line);
   fclose(fp);
   fclose(reservations_errors);
}

/**
 * @brief This function is responsible for eliminating the invalid passengers, writing them on the errors file and inserting them in an array.
 *
 * @param dataset_path Path to the dataset.
 * @param cat_passengers Pointer to the catalog of passengers.
 * @param invalid_fids Pointer to the array of invalid passengers.
 * @param num_invalid_fids Pointer to the number of invalid passengers.
 * @param invalid_uids Pointer to the array of invalid passengers.
 * @param num_invalid_uids Pointer to the number of invalid passengers.
 *
 * @return void
 */
static void invalid_passengers(char *dataset_path, catalogo_Passengers *cat_passengers,catalogo_Flights *cat_flights,catalogo_Users *cat_users,GHashTable* id_table_user, GHashTable* id_table_flight)
{
   char file_path[256];
   snprintf(file_path, sizeof(file_path), "%spassengers.csv", dataset_path);
   FILE *fp = fopen(file_path, "r");
   FILE *passengers_errors = fopen("Resultados/passengers_errors.csv", "w");
   char *line = NULL;
   size_t len = 0;
   char *string, *found, *aux;
   int c_pal = 0;
   int checker;

   for (int i = 0; (getline(&line, &len, fp) != -1); i++)
   {
      checker = 1; // Reset checker for each line

      if (i == 0)
         fprintf(passengers_errors, "%s", line);
      else
      {
         string = strdup(line);
         aux = string;

         for (c_pal = 0; ((found = strsep(&string, ";")) != NULL && checker != 0); c_pal++)
         {
            // flight_id
            if (c_pal == 0)
            {
               checker = valid_string(found);
               if(g_hash_table_lookup(id_table_flight, found) != NULL)
               {
                  checker = 0;
                  break;
               }
            }

            // user_id
            if (c_pal == 1)
            {
               checker = valid_string(found);
               found[strcspn(found, "\n")] = '\0';
               if(g_hash_table_lookup(id_table_user, found) != NULL)
               {
                  checker = 0;
                  break;
               }
            }
         }
         free(aux);
      }

      if (checker == 0 || c_pal != 2)
      {
         fprintf(passengers_errors, "%s", line);
      }
      if (checker != 0 && c_pal == 2)
      {
         parse_passenger_line2(line, cat_passengers,cat_flights,cat_users);
      }
   }
   if (line)
      free(line);
   fclose(fp);
   fclose(passengers_errors);
}

/**
 * @brief This function is responsible for eliminating the invalid users, writing them on the errors file and inserting them in an array.
 *
 * @param dataset_path Path to the dataset.
 * @param cat_users Pointer to the catalog of users.
 * @param invalid_uds Pointer to the array of invalid users.
 * @param num_invalid_uds Pointer to the number of invalid users.
 *
 * @return void
 */
static void invalid_users(char *dataset_path, catalogo_Users *cat_users,GHashTable** id_table_user)
{
   char file_path[256];
   snprintf(file_path, sizeof(file_path), "%susers.csv", dataset_path);
   FILE *fp = fopen(file_path, "r");
   FILE *users_errors = fopen("Resultados/users_errors.csv", "w");
   char *line = NULL;
   size_t len = 0;
   char *string, *found, *aux;
   int c_pal = 0;
   int checker = 1;
   static char birth_date[11]; // Assuming "yyyy/mm/dd" format
   static char account_creation[100];
   char *id = NULL;

   for (int i = 0; (getline(&line, &len, fp) != -1); i++)
   {

      if (i == 0)
         fprintf(users_errors, "%s", line);

      else
      {

         string = strdup(line);
         aux = string;

         for (c_pal = 0, checker = 1; ((found = strsep(&string, ";")) != NULL && checker != 0); c_pal++)
         {

            // id
            if (c_pal == 0)
            {
               checker = valid_string(found);
               id = strdup(found);
            }
            // name
            if (c_pal == 1)
            {
               checker = valid_string(found);
            }

            // email
            if (c_pal == 2)
            {
               checker = valid_email(found);
            }

            // phone_number
            if (c_pal == 3)
            {
               checker = valid_phone_number(found);
            }

            // birth_date
            if (c_pal == 4)
            {
               checker = valid_date(found);
               if (checker != 0)
               {
                  strcpy(birth_date, found);
               }
            }

            // sex
            if (c_pal == 5)
            {
               checker = valid_sex(found);
            }

            // passport
            if (c_pal == 6)
            {
               checker = valid_string(found);
            }

            // country_code
            if (c_pal == 7)
            {
               checker = valid_country_code(found);
            }

            // adress
            if (c_pal == 8)
            {
               checker = valid_string(found);
            }

            // account_creation
            if (c_pal == 9)
            {
               strcpy(account_creation, found);
               if (found)
               {
                  char *date = strtok(found, " ");
                  char *time = strtok(NULL, " ");

                  if (date && time)
                  {
                     checker = valid_date(date) && valid_hour(time);
                  }
                  else
                  {
                     checker = false;
                  }
               }
               if (checker != 0)
               {
                  checker = (compare_dates_users(birth_date, account_creation));
               }
            }

            // pay_method
            if (c_pal == 10)
            {
               checker = valid_string(found);
            }

            // account_status
            if (c_pal == 11)
            {
               checker = valid_account_status(found);
            }
         }
         free(aux);
      }

      if (checker == 0 || c_pal != 12)
      {
         if (id != NULL && strcmp(id, "") != 0)
         {
            char* id_copy = strdup(id);
            g_hash_table_insert(*id_table_user, id_copy, id_copy);

         }
         fprintf(users_errors, "%s", line);
      }
      if (checker != 0 && c_pal == 12)
      {
         parse_user_line2(line, cat_users);
      }
      free(id);
   }
   if (line)
      free(line);
   fclose(fp);
   fclose(users_errors);
}

/**
 * @brief This function is responsible for filtering the data from the dataset.
 *
 * @param dataset_path Path to the dataset.
 * @param cat_flights Pointer to the catalog of flights.
 * @param invalid_fids Pointer to the array of invalid flights.
 * @param num_invalid_fids Pointer to the number of invalid flights.
 * @param cat_users Pointer to the catalog of users.
 * @param invalid_uids Pointer to the array of invalid users.
 * @param num_invalid_uids Pointer to the number of invalid users.
 * @param cat_passengers Pointer to the catalog of passengers.
 *
 */
void limpar_dados_validos(char *dataset_path, catalogo_Flights *cat_flights, catalogo_Passengers *cat_passengers, catalogo_Reservations *cat_reservations, catalogo_Users *cat_users)
{
   GHashTable* id_table_user = g_hash_table_new(g_str_hash, g_str_equal);
   GHashTable* id_table_flight = g_hash_table_new(g_str_hash, g_str_equal);
   size_t length = 0;

   invalid_flights(dataset_path, cat_flights, &id_table_flight);
   length = g_hash_table_size(get_table_flights(cat_flights));
   printf("\033[1;32mLength of the hash table flights:\033[0m %zu\n\n", length);
   invalid_users(dataset_path, cat_users, &id_table_user);
   length = g_hash_table_size(get_table_users(cat_users));
   printf("\033[1;32mLength of users:\033[0m %zu\n\n", length);
   invalid_passengers(dataset_path, cat_passengers,cat_flights,cat_users,id_table_user, id_table_flight);
   length = g_hash_table_size(get_table_passengers(cat_passengers));
   printf("\033[1;32mLength of passengers:\033[0m %zu\n\n", length);
   invalid_reservations(dataset_path, cat_reservations, cat_users, id_table_user);
   length = g_hash_table_size(get_table_reservations(cat_reservations));
   printf("\033[1;32mLength of reservations:\033[0m %zu\n\n", length);

   g_hash_table_foreach(id_table_user,(GHFunc) free_id, NULL);
   g_hash_table_foreach(id_table_flight,(GHFunc) free_id, NULL);
   g_hash_table_destroy(id_table_user);
   g_hash_table_destroy(id_table_flight);

}
