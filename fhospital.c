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
    int i = 1, x = 1, w = 1, n;

    FILE *f = fopen("medico.txt", "r");
    FILE *y = fopen("paciente.txt", "r");

    medico *med_current = med;
    paciente *pac_current = pac;
    consulta *con_current = con;
    
    med_current = malloc(sizeof(medico));
    pac_current = malloc(sizeof(paciente));
    con_current = malloc(sizeof(consulta));

    med = med_current;
    pac = pac_current;
    con = con_current;

    if(f == NULL || y == NULL)
    {
        printf("Erro a abrir o ficheiro\n");
        return;
    }
    if(med_current == NULL || pac_current == NULL || con_current == NULL)
    {
        printf("Erro a alocar a memória\n");
        return;
    }

    while(!feof(f))
    {   
        
        fscanf(f, "%[^\n]", med_current->nome);
        fscanf(f, "%s", med_current->especialidade);
        fscanf(f, "%d.%d--%d.%d", &(med_current->entrada.h), &(med_current->entrada.m), 
            &(med_current->saida.h), &(med_current->saida.m));
        med_current = med_current->next;
        i++;
        med_current = realloc(med_current, sizeof(medico)* i);
    }
    while(!feof(y))
    {
        fscanf(y, "%[^\n]", pac_current->nome);
        fscanf(y, "%d", &(pac_current->idade));
        fscanf(y, "%d consultas", &n);
        for(i = 0; i < n; i++)
        {
            fscanf(y, "%s--%d/%d/%d--%s", con_current->tipo, &(con_current->data.dia), 
                &(con_current->data.mes), &(con_current->data.ano), con_current->medico);
            w++;
            con_current =realloc(con_current, sizeof(consulta)* w);
        }
        pac_current = realloc(pac_current, sizeof(paciente)* x);
        x++;
    }

    fclose(f);
    fclose(y);   
}

void show_info()
{
    while( med != NULL)
    {
        printf( "\n\nMédico > %s\n", med->nome);
        printf( "Especialidade > %s\n", med->especialidade);
        printf( "Horário > %dh%dm - %dh%dm\n", med->entrada.h, med->entrada.m, 
            med->saida.h, med->saida.m);
        med = med->next;
    }
}
