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

void dump_database()
{
    dump_med();
    //dump_pac();
    show_info();
}

void dump_med()
{
    int i = 1;
    FILE *f;
    struct medico *new_med;
    struct medico *temp_m;

    f = fopen(M_FILE, "r");
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
        fscanf(f, "%s", new_med->especialidade);
        fscanf(f, "%d.%d--%d.%d\n", &(new_med->entrada.h), &(new_med->entrada.m),
            &(new_med->saida.h), &(new_med->saida.m));
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
    int i = 1, n;
    struct paciente *new_pac;
    struct paciente *temp_p;
    struct consulta *new_con;
    struct consulta *temp_c;
    FILE *f;
    head_c = NULL;
    head_p = NULL;

    f = fopen(P_FILE, "r");
    new_pac = malloc(sizeof(struct paciente));
    temp_p = malloc(sizeof(struct paciente));
    new_con = malloc(sizeof(struct consulta));
    temp_c = malloc(sizeof(struct consulta));

    if(f == NULL)
    {
        printf("Erro a abrir o ficheiro\n");
        return;
    }
    while(!feof(f))
    {
        new_pac = realloc(new_pac, sizeof(struct paciente) * i);
        fscanf(f, "%[^\n]", new_pac->nome);
        fscanf(f, "%d", &(new_pac->idade));
        fscanf(f, "%d consultas", &(new_pac->nconsultas));
        for(n = 0; n < new_pac->nconsultas; n++)
        {
            new_con =realloc(new_con, sizeof(struct consulta)* (n+1));
            fscanf(f, "%s--%d/%d/%d--%[^\n]", new_con->tipo, &(new_con->data.dia), 
                &(new_con->data.mes), &(new_con->data.ano), new_con->medico);
            temp_c = new_con;
            temp_c = head_c;
            head_c = temp_c;
            new_con = new_con->next;
        }
        temp_p = new_pac;
        temp_p->next = head_p;
        head_p = temp_p;
        new_pac = new_pac->next;
        i++;
    }
    free(new_pac);
    free(new_con);
    free(temp_p);
    free(temp_c);
    fclose(f);
}

void show_info()
{
    while(head_m != NULL)
    {
        printf( "\n\nMédico > %s\n", head_m->nome);
        printf( "Especialidade > %s\n", head_m->especialidade);
        printf( "Horário > %dh%dm - %dh%dm\n", head_m->entrada.h, head_m->entrada.m,
            head_m->saida.h, head_m->saida.m);
        head_m = head_m->next;
    }
   while (head_p != NULL)
    {
        int i;

        printf ( "\n\nPaciente > %s\n", head_p->nome);
        printf ("Idade > %d\n", head_p->idade);
        printf ("%d Consultas:\n", head_p->nconsultas);
         for(i = 0; i < head_p->nconsultas; i++)
        {
            printf("\tTipo > %s", head_c->tipo);
            printf("\tData > %d/%d/%d", (head_c->data.dia), 
                (head_c->data.mes), (head_c->data.ano));
            printf("\tMédico > %s", head_c->medico);
            head_c = head_c->next;
            i++;
        }
        head_p = head_p->next;
    }
}
