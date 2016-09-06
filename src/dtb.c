#include "dtb.h"

void clock_date()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("%d/%d/%d",tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900);
    printf("\t\t\t\t  %dh%dm\n", tm.tm_hour, tm.tm_min);
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
            printf("Erro a alocar o novo nó ");
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
    int i;

    FILE *f = fopen(P_FILE, "r");
    if(f == NULL)
    {
        printf("Erro a abrir o ficheiro\n");
        return;
    }

    while(fscanf(f,"%[^\n]", tmp.nome) == 1 )
    {
        fscanf(f, " %d", &tmp.idade);
        fscanf(f, "%d consultas", &tmp.nconsultas);

        if(tmp.nconsultas > 0)
        {
            for(i = 0; i < tmp.nconsultas; i++)
            {
                fscanf(f, "%s - %d/%d/%d - %[^\n]\n", tmp_c.tipo, &tmp_c.data.dia,
                      &tmp_c.data.mes, &tmp_c.data.ano, tmp_c.medico );

                 if ( !(*head_c = malloc(sizeof (**head_c))) )
                {
                    printf("Erro a alocar o novo nó \n");
                    return;
                }

                tmp_c.next = NULL;
                **head_c = tmp_c;
                head_c = &(*head_c)->next;
            }
        }

        if ( !(*head_p = malloc(sizeof (**head_p))) )
        {
            printf("Erro a alocar o novo nó \n");
            return;
        }

        tmp.next = NULL;
        **head_p = tmp;
        head_p = &(*head_p)->next;
    }
    fclose(f);
}

void free_mem(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c)
{
    struct medico *tmp_m = NULL;
    struct paciente *tmp_p = NULL;
    struct consulta *tmp_c = NULL;

    while (head_m)
    {
        tmp_m = head_m->next;
        free(head_m);
        head_m = tmp_m;
    }
   while (head_p)
    {
        tmp_p = head_p->next;
        free(head_p);
        head_p = tmp_p;
    }
    while (head_c)
    {
        tmp_c = head_c->next;
        free(head_c);
        head_c = tmp_c;
    }
}

void show_info(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c)
{
    int n = 0;
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
        printf( "\nPaciente > %s\n", head_p->nome);
        printf( "Idade > %d\n", head_p->idade);
        printf( "Consultas > %d\n", head_p->nconsultas);
        while( n < head_p->nconsultas )
        {
            printf("\n\t[Tipo]: %s\n", head_c->tipo);
            printf("\t[Data]: %d/%d/%d\n", head_c->data.dia, head_c->data.mes,
                head_c->data.ano);
            printf("\t[Medico] : %s\n", head_c->medico);
            head_c = head_c->next;
            n++;
        }
        n=0;
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

char * assign_med_by_spec(char *especialidade, struct medico *head_m)
{
    while(head_m != NULL)
    {
        if(!strcmp(especialidade, head_m->especialidade)){
            printf( "\nMédico > %s\n", head_m->nome);
            return head_m->nome;
        }
        head_m = head_m->next;
    }
    return 0;
}

void pac_by_spec(struct paciente *head_p ,struct consulta *head_c,
    struct medico *head_m)
{
    int n = 0;
    char str[50];
    char *med = NULL;
    //char *nome_old = NULL;

    do {
      system(CLEAR);
      clock_date();
      printf("\n\n\n[PACIENTE]Especialidade pretendida > ");
      scanf("%s", str);
      med =  assign_med_by_spec(str, head_m);

      if(!med)
      {
        printf("\n\tEspecialidade Inexistente :: Prima ENTER para tentar outra vez");
        getchar();
        getchar();
      }
    } while(!med);


    while(head_p != NULL)
    {
        while( n < head_p->nconsultas )
        {
            if(!strcmp(med, head_c->medico))
            {
                    printf("\nPaciente > %s", head_p->nome);
                    break;
            }
            head_c = head_c->next;
            n++;
        }
        n=0;
        head_p = head_p->next;
    }

    printf("\n\nPrima ENTER para voltar ao menu");
    getchar();
    getchar();
}

void pac_by_t(struct paciente *head_p, struct consulta *head_c)
{
    int  n = 0;
    struct data de;
    struct data a;
    int found = FALSE;

    system(CLEAR);
    clock_date();
    printf("\n\n\n[PACIENTE] Periodo pretendido  > \n");
    printf("\t De (d/m/a) :");
    scanf("%d/%d/%d", &(de.dia), &(de.mes), &(de.ano));
    do
    {
        printf("\t A (d/m/a) :");
        scanf("%d/%d/%d", &(a.dia), &(a.mes), &(a.ano));
        if( compare_dates(de, a) == 1 )
        {
            printf("Tem que inserir uma data posterior a %d/%d/%d\n", (de.dia), (de.mes), 
                (de.ano) );
        }
    } while(compare_dates(de, a) == 1);


    while(head_p != NULL)
    {
        while( n < head_p->nconsultas )
        {
            if(compare_dates(de, head_c->data) ==  -1 &&
                compare_dates(a, head_c->data) == 1)
            {
                printf( "\nPaciente > %s\n", head_p->nome);
                printf("\t[Data]: %d/%d/%d\n", head_c->data.dia, head_c->data.mes,
                    head_c->data.ano);
                printf("\t[Medico] : %s\n", head_c->medico);
                found=TRUE;
            }
            head_c = head_c->next;
            n++;
        }
        n=0;
        head_p = head_p->next;
    }
    if(found == FALSE)
      printf("\nNão existem consultas nesse período\n" );

    printf("\n\nPrima ENTER para voltar ao menu");
    getchar();
    getchar();
}

int compare_dates (struct data d1, struct data d2)
{
     if (d1.ano < d2.ano)
    return -1;

    else if (d1.ano > d2.ano)
       return 1;

    if (d1.ano == d2.ano)
    {
         if (d1.mes<d2.mes)
              return -1;
         else if (d1.mes>d2.mes)
              return 1;
         else if (d1.dia<d2.dia)
              return -1;
         else if(d1.dia>d2.dia)
              return 1;
         else
              return 0;
    }
    return 2;
}

void check_schdl(struct medico *head_m)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int found = FALSE;

    system(CLEAR);
    clock_date();
    printf("\n\t\t::Medicos disponiveis::\n\n");

    while(head_m != NULL)
    {
        if( (head_m->entrada.h < tm.tm_hour && head_m->saida.h > tm.tm_hour)
            || (head_m->entrada.h == tm.tm_hour && head_m->entrada.m <= tm.tm_min)
            || (head_m->saida.h == tm.tm_hour && head_m->saida.m >= tm.tm_min) )
        {
            printf( "\nMédico > %s [%s]\n", head_m->nome, head_m->especialidade );
            found = TRUE;
        }
        head_m = head_m->next;
    }
    if(found == FALSE)
        printf("Não existe médico disponiveis neste momento\n");

    printf("\n\nPrima ENTER para voltar ao menu");
    getchar();
    getchar();
}
