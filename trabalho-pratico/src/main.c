#include "../include/validation.h"
#include "../include/interface.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    // limpar_dados_invalidos();

    if (argc == 3)
    {
        // modo batch;
    }
    else
        // modo interativo
        logo(argc, argv);
    return 0;
}