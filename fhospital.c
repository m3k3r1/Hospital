#include "hospital.h"

int menu()
{
    int menu_op;
    system(CLEAR);
    printf("\n\n\n1 - Listagem Completa de Medicos e Pacientes\n"
           "2 - Pesquisar médicos por especialidade\n"
           "3 - Listagem de paciente por especialidade\n"
           "4 - Stuff\n"
           "5 - Sair\n"
           "\nOpção >> ");
    scanf("\n%d", &menu_op);
    return menu_op;
}

void dump_database()
{
    dump_med();
    dump_pac();
}

void dump_med()
{
    int i = 1;
    struct medico *new_med;
    struct medico *temp_m;
    head_m = NULL;
    FILE *f = fopen(M_FILE, "r");

    new_med = malloc(sizeof(struct medico));
    temp_m = malloc(sizeof(struct medico));

    if(f == NULL)
    {
        printf("Erro a abrir o ficheiro\n");
        return;
    }

    if( new_med == NULL || temp_m == NULL)
    {
        printf("Erro a alocar a memória\n");
        return;
    }
    while(!feof(f))
    {   
        new_med = realloc(new_med, sizeof(struct medico) * i);
        if( new_med == NULL)
        {
            printf("Erro a realocar a memória\n");
            return;
        }
        fscanf(f, "%[^\n]", new_med->nome);
        fscanf(f, "%s %d.%d--%d.%d\n", new_med->especialidade, &(new_med->entrada.h), 
            &(new_med->entrada.m), &(new_med->saida.h), &(new_med->saida.m));
        temp_m = new_med;
        temp_m->next = head_m;
        head_m = temp_m;
        new_med = new_med->next;
        i++;
    }
    free(new_med);
    free(temp_m);
    fclose(f);
}

void dump_pac()
{
    int i = 1;
    struct paciente *new_pac;
    struct paciente *temp_p;
    head_p = NULL;
    head_c = NULL;
    FILE *f = fopen(P_FILE, "r");

    new_pac = malloc(sizeof(struct paciente));
    temp_p = malloc(sizeof(struct paciente));

    if(f == NULL)
    {
        printf("Erro a abrir o ficheiro\n");
        return;
    }

    if( new_pac == NULL || temp_p == NULL)
    {
        printf("Erro a alocar a memória\n");
        return;
    }
    while(!feof(f))
    {
        new_pac = realloc(new_pac, sizeof(struct paciente) * i);
        if( new_pac == NULL)
        {
            printf("Erro a realocar a memória\n");
            return;
        }
        fscanf(f, "%[^\n]", new_pac->nome);
        fscanf(f, "%d", &(new_pac->idade));
        temp_p = new_pac;
        temp_p->next = head_p;
        head_p = temp_p;
        new_pac = new_pac->next;
        i++;
    }
    free(new_pac);
    free(temp_p);
    fclose(f);
}

void show_info()
{   
    //FIX
    system(CLEAR);
    printf("\n\n\n\t\t::Medicos::\n\n");
    while(head_m != NULL)
    {   
        printf( "Médico > %s\n", head_m->nome);
        printf( "Especialidade > %s\n", head_m->especialidade);
        printf( "Horário > %dh%dm - %dh%dm\n", head_m->entrada.h, head_m->entrada.m,
            head_m->saida.h, head_m->saida.m);
        head_m = head_m->next;
    }
    printf("\n\nPrima ENTER para ver os pacientes");
    getchar();
    getchar();

    system(CLEAR);
    printf("\n\n\n\t\t::Pacientes::\n");
    while(head_p != NULL)
    {   
        printf( "Paciente > %s\n", head_p->nome);
        printf( "Idade > %d\n", head_p->idade);
        head_p = head_p->next;
    }
    printf("\n\nPrima ENTER para sair");
    getchar();
    getchar();
}

void med_by_spec()
{
    char str[50];

    printf("[MEDICO]Especialidade pretendida > ");
    scanf("%s", str);

    while(head_m != NULL)
    {   
        if(!strcmp(str, head_m->especialidade))
            printf( "\nMédico > %s\n", head_m->nome);
        head_m = head_m->next;
    }
}
void pac_by_spec()
{
    char str[50];

    printf("[PACIENTE]Especialidade pretendida > ");
    scanf("%s", str);

}
