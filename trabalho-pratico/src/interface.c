#include "../include/interface.h"
#include <stdlib.h>
#include <stdio.h>

void menu_interativo(int argc, char **argv)
{
    int sys = system("clear");
    if (sys == 0)
        printf("Hello, World!\n");
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