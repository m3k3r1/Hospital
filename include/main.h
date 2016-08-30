#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "dtb.h"

int menu()
{
    int menu_op;

    do
    {
        system(CLEAR);
        clock_date();
        printf("\n1 - Listagem Completa de Medicos e Pacientes\n"
                "2 - Pesquisar médicos por especialidade\n"
                "3 - Listagem de paciente por especialidade\n"
                "4 - Listagem de paciente por período de tempo\n"
                "5 - Médicos disponiveis neste momento\n"
                "6 - Marcações\n"
                "7 - Sair\n"
                "\nOpção >> ");
    scanf("\n%d", &menu_op);
    if(menu_op < 1 || menu_op > 7)
    {
        printf("\n\tOpção Inválida :: Prima ENTER para tentar outra vez");
        getchar();
        getchar();
    }
    }while( menu_op < 1 || menu_op > 7);

    return menu_op;
}
