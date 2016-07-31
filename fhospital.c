#include "hospital.h"

int menu()
{
    int menu_op;
    system(CLEAR);
    clock_date();
    printf("\n1 - Listagem Completa de Medicos e Pacientes\n"
           "2 - Pesquisar médicos por especialidade\n"
           "3 - Listagem de paciente por especialidade\n"
           "4 - Listagem de paciente por período de tempo\n"
           "5 - Médicos disponiveis\n"
           "6 - Marcações\n"
           "7 - Sair\n"
           "\nOpção >> ");
    scanf("\n%d", &menu_op);
    return menu_op;
}

void clock_date()
{
    time_t mytime;
    mytime = time(NULL);
    

    printf("\n\t\t\t%s\n", ctime(&mytime));  
}

void show_all(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c)
{
    dump_database(&head_m, &head_p, &head_c);
    show_info(head_m, head_p, head_c);
}

void search_med(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c)
{
    dump_database(&head_m, &head_p, &head_c);
    med_by_spec(head_m);
}

void pac_by_speciality(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c)
{
    dump_database(&head_m, &head_p, &head_c);
    pac_by_spec(head_p, head_c);
}

void pac_by_time(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c)
{
}

void med_now(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c)
{
}

int menu_apt()
{
    int menu_op;
    system(CLEAR);
    clock_date();
    printf("\n1 - Fazer marcações\n"
           "2 - Apagar marcações\n"
           "3 - Mostrar marcações\n"
           "4 - Menu anterior\n"
           "\nOpção >> ");
    scanf("\n%d", &menu_op);
    return menu_op;
}

void make_appointment()
{
    int menu_op = 0;

    do
    {
        menu_op = menu_apt();
        switch(menu_op)
        {
            case 1: make_apt();
                    break;
            case 2: del_apt();
                    break;
            case 3: show_agd();
                    break;
            case 4: return;
                    break;
        }
    }while(1);
}

void dump_database(struct medico **head_m, struct paciente **head_p ,
    struct consulta **head_c)
{

    dump_med(head_m);
    dump_pac(head_p, head_c);
}

void dump_med(struct medico **head_m)
{
    struct medico tmp;
   
    FILE *f = fopen(M_FILE, "r");
    if(f == NULL)
    {
        printf("Erro a abrir o ficheiro\n");
        return;
    }

    while (fscanf(f, "%[^\n]", tmp.nome) == 1 &&
           fscanf(f, "%s %d.%d--%d.%d\n",tmp.especialidade, 
           &(tmp.entrada.h), &(tmp.entrada.m), &(tmp.saida.h), 
           &(tmp.saida.m)) == 5)
    {
        if (!(*head_m = malloc(sizeof (**head_m))))
        {
            printf("Failed to allocate new list node: ");
            return;
        }
        tmp.next = NULL;
        **head_m = tmp;
        head_m = &(*head_m)->next;
    }
    fclose(f);
}

void dump_pac(struct paciente **head_p ,struct consulta **head_c)
{
    struct paciente tmp;
    //struct consulta tmp_c;

    FILE *f = fopen(P_FILE, "r");
        if(f == NULL)
    {
        printf("Erro a abrir o ficheiro\n");
        return;
    }

    while(fscanf(f, "%[^\n]", tmp.nome) == 1 &&
          fscanf(f, "%d", &tmp.idade) == 1 &&
          fscanf(f, "%d consultas", &tmp.nconsultas) == 1)
    {
        /**if(tmp.nconsultas > 0)
        {
            while(fscanf(f, "%s--%d/%d/%d--%[^\n]", tmp_c.tipo, 
                    &tmp_c.data.dia, &tmp_c.data.mes, &tmp_c.data.ano, tmp_c.medico ) == 5)
            {
                printf("%d/%d/%d\n", tmp_c.data.dia, tmp_c.data.mes, tmp_c.data.ano);
                 if (!(*head_c = malloc(sizeof (**head_c))))
                {
                printf("Failed to allocate new list node: ");
                return;
                }
                tmp_c.next = NULL;
                **head_c = tmp_c;
                head_c = &(*head_c)->next;
            }
        }**/
        printf("%s\n", tmp.nome);
        printf("%d\n", tmp.idade);
        printf("%d\n", tmp.nconsultas);
        if (!(*head_p = malloc(sizeof (**head_p))))
        {
            printf("Failed to allocate new list node: ");
            return;
        }
        tmp.next = NULL;
        **head_p = tmp;
        head_p = &(*head_p)->next;
    }
    fclose(f);
}

void show_info(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c)
{   
    //int n = 0;
    system(CLEAR);
    clock_date();
    printf("\n\t\t::Medicos::\n\n");
    while(head_m != NULL)
    {   
        printf( "\nMédico > %s [%s]\n", head_m->nome, head_m->especialidade );
        head_m = head_m->next;
    }

    printf("\n\nPrima ENTER para ver a lista de pacientes");
    getchar();
    getchar();

    system(CLEAR);
    clock_date();
    printf("\n\t\t::Pacientes::\n\n");
    while(head_p != NULL)
    {   
        printf( "Paciente > %s\n", head_p->nome);
        printf( "Idade > %d\n", head_p->idade);
        printf( "Consultas > %d\n", head_p->nconsultas);
        /**while( n < head_p->nconsultas )
        {
            printf("\tData: %d/%d/%d\n", head_c->data.dia, head_c->data.mes, 
                head_c->data.ano);
            printf("\tMedico da Consulta: %s\n", head_c->medico);
            head_c = head_c->next;
            n++;
        }
        n=0;**/
        head_p = head_p->next;
    }
    printf("\n\nPrima ENTER para voltar ao menu");
    getchar();
}

void med_by_spec(struct medico *head_m)
{
    char str[50];
    int found = FALSE;

    system(CLEAR);
    clock_date();
    printf("\n\t\t::Pesquisa de Medico::\n\n");
    printf("[MEDICO]Especialidade pretendida > ");
    scanf("%s", str);

    while(head_m != NULL)
    {   
        if(!strcmp(str, head_m->especialidade)){
            printf( "\nMédico > %s\n", head_m->nome);
            found = TRUE;
        }
        head_m = head_m->next;
    }
    if(found == FALSE)
        printf("Não existe médico para essa especialidade\n");

    printf("\n\nPrima ENTER para voltar ao menu");
    getchar();
    getchar();
}

void pac_by_spec(struct paciente *head_p ,struct consulta *head_c)
{
    char str[50];

    printf("[PACIENTE]Especialidade pretendida > ");
    scanf("%s", str);

}

void make_apt()
{
}

void del_apt()
{
}

void show_agd()
{
}