#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>


// Verifica se a string está vazia
static int validstring (char *found) {
   if(strlen(found) == 0)
      return 0;
   return 1;
}

//verifica ints
static int valid_int (char *found){
   int tam = strlen(found);

   if (tam == 0) return 0;

   for (int i = 0; i < tam; i++) {
      if (!isdigit(found[i])) return 0;
   }
   if(atoi(found) <= 0) return 0;

   return 1;
}

//verifica doubles
static int valid_double(char *found) {
    int tam = strlen(found);
    int dotCount = 0;

    if (tam == 0) return 0;

    for (int i = 0; i < tam; i++) {
        if (!isdigit(found[i])) {
            if (found[i] == '.' && dotCount == 0) {
                dotCount++;
            } else {
                return 0;
            }
        }
    }

    double num = atof(found);
    if (num <= 0.0) return 0;

    // Arredonda para 3 casas decimais
    double roundedNum = round(num * 1000) / 1000.0;

    // Se o número original e o número arredondado são diferentes, significa que havia mais de 3 casas decimais
    if (num != roundedNum) return 0;
    return 1;
}

//verifica bools
static int valid_bool(char *found) {
    if (strcasecmp(found, "true") == 0 || strcasecmp(found, "false") == 0) {
        return 1;
    } else {
        return 0;
    }
}

//verifica o status de uma conta
static int valid_account_status (char *found){
    if (strcasecmp(found, "active\n") != 0 && strcasecmp(found, "inactive\n") != 0) {
        return 0;
    }
    return 1;
}

//Verificar se uma data é valida
static int validdata (char *found) {

   int ano, mes, dia, r, e, i;
   char *data;

   time_t t = time(NULL);
 
   struct tm tm = *localtime(&t);

   e=1;
   if (strlen(found) != 10) e=0;
   if (found[2] != '/' || found[5] != '/') e=0;

   for (i = 0; (data = strsep(&found, "/")); i++) {
      if (i == 0){
         if(strlen(data) != 2 || !isdigit(data[0]) || !isdigit(data[1])) e=0;
         dia = atoi(data);
      }
      if (i == 1){
         if(strlen(data) != 2 || !isdigit(data[0]) || !isdigit(data[1])) e=0;
         mes = atoi(data);
      }
      if (i == 2){
         if(strlen(data) != 4 || !isdigit(data[0]) || !isdigit(data[1]) || !isdigit(data[2]) || !isdigit(data[3])) e=0;
         ano = atoi(data);
      }
   }

   r = 1;

   if (i != 3) r = 0;
   else if ( mes <= 0 || mes > 12 || dia <= 0 || dia > 31) r = 0;
   else if (ano == tm.tm_year + 1900 && mes > tm.tm_mon + 1) r = 0; //
   else if (ano == tm.tm_year + 1900 && mes == tm.tm_mon + 1 && dia > tm.tm_mday) r = 0; //
   else if (mes <= 7 && (mes % 2) == 0 && dia > 30) r = 0;
   else if (mes > 7 && (mes % 2) == 1 && dia > 30) r = 0;
   else if (mes == 2 && dia > 29) r = 0;
   else if ( (!( ( ano % 4 == 0 && ano % 100 != 0 ) || ano % 400 == 0 ) ) && mes == 2 && dia > 28) r = 0; // trata dos anos bissextos

   if(e == 0) r=0;
   return r;
}


// criação de "flight-valid.csv"
static void valid_flight(){
    FILE *fp = fopen ("entrada/flight.csv", "r");
    FILE *flight_valid = fopen ("Resultados/flight-valid.csv","w");
    char*line = NULL;
     size_t len = 0;
    char *string,*found,*aux;
    int c_pal;
    int checker;
    
          for (int i=0; (getline(&line, &len, fp) != -1); i++) {

         if (i==0) fprintf(flight_valid,"%s", line);

         else {

      string = strdup(line);
      aux = string;

      for (c_pal = 0, checker = 1 ; ((found = strsep(&string,";")) != NULL && checker != 0); c_pal++) {
      
      //id
      if (c_pal == 0) {checker = valid_int (found);}

      //airline
      if (c_pal == 1) {checker = validstring (found);}

      //plane_model
      if (c_pal == 2) {checker = validstring (found);}

      //total_seats
      if (c_pal == 3) {checker = valid_int (found);}

      //origin
      if (c_pal == 4) {checker = validstring (found);}

      //destination
      if (c_pal == 5) {checker = validstring (found);} 

      //schedule_departure_date
      if (c_pal == 6) {checker = validdata (found);}

      //schedyle_arrival_date
      if (c_pal == 7) {checker = validdata (found);}

      //real_departure_date
      if (c_pal == 8) {checker = validdata (found);}

      //real_arrival_date
      if (c_pal == 9) {checker = validdata (found);}

      //pilot
      if (c_pal == 10) {checker = validstring (found);}

      //copilot
      if (c_pal == 11) {checker = validstring (found);}

      //notes
      if (c_pal == 12) {checker = validstring (found);}

      }
      free (aux);
    }

    if (checker != 0 && c_pal == 13) fprintf(flight_valid,"%s", line);
 }
    fclose (fp);
    fclose (flight_valid);

}


// criação de "passenger-valid.csv"
static void valid_passenger(){
    FILE *fp = fopen ("entrada/passenger.csv", "r");
    FILE *passenger_valid = fopen ("Resultados/passenger-valid.csv","w");
    char*line = NULL;
     size_t len = 0;
    char *string,*found,*aux;
    int c_pal;
    int checker;
    
          for (int i=0; (getline(&line, &len, fp) != -1); i++) {

         if (i==0) fprintf(passenger_valid,"%s", line);

         else {

      string = strdup(line);
      aux = string;

      for (c_pal = 0, checker = 1 ; ((found = strsep(&string,";")) != NULL && checker != 0); c_pal++) {
      
      //flight_id
      if (c_pal == 0) {checker = valid_int (found);}

      //user_id
      if (c_pal == 1) {checker = valid_int (found);}

      }
      free (aux);
    }

    if (checker != 0 && c_pal == 2) fprintf(passenger_valid,"%s", line);
 }
    fclose (fp);
    fclose (passenger_valid);

}


// criação de "reservation-valid.csv"
static void valid_passenger(){
    FILE *fp = fopen ("entrada/reservation.csv", "r");
    FILE *reservation_valid = fopen ("Resultados/reservation-valid.csv","w");
    char*line = NULL;
     size_t len = 0;
    char *string,*found,*aux;
    int c_pal;
    int checker;
    
          for (int i=0; (getline(&line, &len, fp) != -1); i++) {

         if (i==0) fprintf(reservation_valid,"%s", line);

         else {

      string = strdup(line);
      aux = string;

      for (c_pal = 0, checker = 1 ; ((found = strsep(&string,";")) != NULL && checker != 0); c_pal++) {
      
     //id
      if (c_pal == 0) {checker = valid_int (found);}

      //user_id
      if (c_pal == 1) {checker = valid_int (found);}

      //hotel_id
      if (c_pal == 2) {checker = valid_int (found);}

      //hotel_name
      if (c_pal == 3) {checker = validstring (found);}

      //hotel_stars
      if (c_pal == 4) {checker = valid_int (found);}

      //city_tax
      if (c_pal == 5) {checker = valid_double (found);} 

      //adress
      if (c_pal == 6) {checker = validstring (found);}

      //begin_date
      if (c_pal == 7) {checker = validdata (found);}

      //end_date
      if (c_pal == 8) {checker = validdata (found);}

      //price_per_night
      if (c_pal == 9) {checker = valid_double (found);}

      //includes_breakfast
      if (c_pal == 10) {checker = valid_bool (found);}

      //room_details
      if (c_pal == 11) {checker = validstring (found);}

      //rating
      if (c_pal == 12) {checker = valid_double (found);}

      //comment
      if (c_pal == 13) {checker = validstring (found);}

      }
      free (aux);
    }

    if (checker != 0 && c_pal == 14) fprintf(reservation_valid,"%s", line);
 }
    fclose (fp);
    fclose (reservation_valid);

}


// criação de "user-valid.csv"
static void valid_passenger(){
    FILE *fp = fopen ("entrada/user.csv", "r");
    FILE *user_valid = fopen ("Resultados/user-valid.csv","w");
    char*line = NULL;
     size_t len = 0;
    char *string,*found,*aux;
    int c_pal;
    int checker;
    
          for (int i=0; (getline(&line, &len, fp) != -1); i++) {

         if (i==0) fprintf(user_valid,"%s", line);

         else {

      string = strdup(line);
      aux = string;

      for (c_pal = 0, checker = 1 ; ((found = strsep(&string,";")) != NULL && checker != 0); c_pal++) {
      
     //id
      if (c_pal == 0) {checker = valid_int (found);}

      //name
      if (c_pal == 1) {checker = validstring (found);}

      //email
      if (c_pal == 2) {checker = validstring (found);}

      //phone_number
      if (c_pal == 3) {checker = valid_int (found);}

      //birth_date
      if (c_pal == 4) {checker = validdata (found);}

      //sex
      if (c_pal == 5) {checker = validstring (found);} 

      //passport
      if (c_pal == 6) {checker = valid_int (found);}

      //country_code
      if (c_pal == 7) {checker = validstring (found);}

      //adress
      if (c_pal == 8) {checker = validstring (found);}

      //account_creation
      if (c_pal == 9) {checker = validdata (found);}

      //pay_method
      if (c_pal == 10) {checker = validstring (found);}

      //account_status
      if (c_pal == 11) {checker = validstring (found);}

      }
      free (aux);
    }

    if (checker != 0 && c_pal == 12) fprintf(user_valid,"%s", line);
 }
    fclose (fp);
    fclose (user_valid);

}

// Função principal
int limpar_dados_invalidos () {
   valid_flight();
   valid_passenger();
   valid_reservation();
   valid_user();
   return 0;
}