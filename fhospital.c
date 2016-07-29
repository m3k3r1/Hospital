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
    struct consulta tmp_c;

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
        while(fscanf(f, "%s--%d/%d/%d--%[^\n]", tmp_c.tipo, 
            &tmp_c.data.dia, &tmp_c.data.mes, &tmp_c.data.ano, tmp_c.medico ) == 4 )
        {
            printf("\tTipo de Consulta: %s\n", tmp_c.tipo);
            if (!(*head_c = malloc(sizeof (**head_c))))
            {
                printf("Failed to allocate new list node: ");
                return;
            }
            tmp_c.next = NULL;
            **head_c = tmp_c;
            head_c = &(*head_c)->next;
        }
        
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
    system(CLEAR);
    printf("\n\n\n\t\t::Medicos::\n\n");
    while(head_m->next != NULL)
    {   
        printf( "\nMédico > %s [%s]\n", head_m->nome, head_m->especialidade );
        printf( "Horário > %dh%dm - %dh%dm\n", head_m->entrada.h, head_m->entrada.m,
            head_m->saida.h, head_m->saida.m);
        head_m = head_m->next;
    }
    printf("\n\nPrima ENTER para ver a lista de pacientes");
    getchar();
    getchar();

    system(CLEAR);
    printf("\n\n\n\t\t::Pacientes::\n");
    while(head_p != NULL)
    {   
        printf( "Paciente > %s\n", head_p->nome);
        printf( "Idade > %d\n", head_p->idade);
        printf( "Consultas > %d\n", head_p->nconsultas);
        /*while(  )
        {
            
            printf("\tData: %d/%d/%d\n", head_c->data.dia, head_c->data.mes, 
                head_c->data.ano);
            printf("\tMedico da Consulta: %s\n", head_c->medico);
            head_c = head_c->next;
        }*/
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
    printf("\n\n\n\t\t::Pesquisa de Medico::\n\n");
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
