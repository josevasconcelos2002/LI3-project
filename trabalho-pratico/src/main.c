#include "../include/validation.h"
#include "../include/interface.h"
#include "../include/batch.h"
#include <stdio.h>

/**
 * @brief This function is responsible for running the main program.
 *
 * @param argc
 * @param argv
 *
 * @return int
 */
int main(int argc, char **argv)
{
    // limpar_dados_invalidos();

    if (argc == 3)
    {
        // modo batch
        batch(argc, argv);
    }
    else
        // modo interativo
        logo(argc, argv);
    return 0;
}