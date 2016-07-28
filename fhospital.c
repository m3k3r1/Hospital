#include "hospital.h"

int menu()
{
    int menu_op;
    system(CLEAR);
    printf("1 - Listagem Completa de Medicos e Pacientes\n"
           "2 - Pesquisar médicos por especialidade\n"
           "3 - Listagem de paciente por especialidade\n"
           "4 - Stuff\n"
           "\nOpção >> ");
    scanf("%d", &menu_op);
    return menu_op;
}