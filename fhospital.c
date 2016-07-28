#include "hospital.h"

int menu()
{
    int menu_op;
    system(CLEAR);
    printf("1 - Listagem Completa de Medicos e Pacientes\n"
           "2 - Pesquisar médicos por especialidade\n"
           "3 - Listagem de paciente por especialidade\n"
           "4 - Stuff\n"
           "5 - Sair\n"
           "\nOpção >> ");
    scanf("%d", &menu_op);
    return menu_op;
}

void save_file_info()
{
    int i = 1, x = 1;
    medico *med;
    paciente *pac;
    FILE *f = fopen("medico.txt", "r");
    FILE *y = fopen("paciente.txt", "r");

    if(f == NULL || y == NULL)
    {
        printf("Erro a abrir o ficheiro\n");
        return;
    }

    while( feof(f) != 0)
    {   
        med = realloc(med, sizeof(medico)* i);
        fscanf(f, "%c\n", med->nome);
        fscanf(f, "%c", med->especialidade);
        fscanf(f, "%d.%d--%d.%d", &(med->entrada.h), &(med->entrada.h), 
            &(med->saida.h), &(med->saida.m));
        med = med->next;
        i++;
    }
     while( feof(y) != 0)
    {
        pac = realloc(med, sizeof(paciente)* x);
        fscanf(y, "%c\n", pac->nome);
        fscanf(y, "%d", pac->idade);
        

    }   

}


void show_info()
{

}
