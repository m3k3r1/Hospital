#include "apt.h"

int menu_apt()
{
    int menu_op;
    do
    {
        system(CLEAR);
        clock_date();
        printf("\n1 - Fazer marcações\n"
                "2 - Apagar marcações\n"
                "3 - Mostrar marcações\n"
                "4 - Menu anterior\n"
                "\nOpção >> ");
        scanf("\n%d", &menu_op);
        if(menu_op < 1 || menu_op > 4 || isalpha(menu_op) == 1)
        {
            printf("\n\tOpção Inválida :: Prima ENTER para tentar outra vez");
            getchar();
            getchar();
        }
    }while(menu_op < 1 || menu_op > 4);

    return menu_op;
}

void make_appointment(struct medico *head_m,  struct marcacao *head_apt)
{
  int menu_op;

  load_apt(&head_apt);
  do
  {
      menu_op  = menu_apt();
      switch(menu_op)
      {
        case 1: make_apt(&head_apt, head_m);
                      break;
        case 2: del_apt(&head_apt);
                      break;
        case 3: show_agd(head_apt);
                      break;
        case 4: sv_apt(head_apt);
                      free_apt(&head_apt);
                      return;
                      break;
        }
    } while(1);
}

void load_apt(struct marcacao **head_apt)
{
    struct marcacao tmp;

    FILE *f = fopen(APT_TXT, "r");

    if( !f )
    {
        printf("Erro a abrir o ficheiro\n" );
        return;
    }

    while ( fscanf(f, "%d %d %d %d\n", &(tmp.inicio.h), &(tmp.inicio.m), &(tmp.fim.h),
                    &(tmp.fim.m) ) == 4)
        {
            fscanf(f, "%[^\n]", tmp.nome);
            fscanf(f, "%d\n", &tmp.idade);
            fscanf(f, "%s\n", tmp.especialidade);
            fscanf(f, "%[^\n]", tmp.medico);
            fscanf(f, "%s\n", tmp.tipo);

            if (!(*head_apt = malloc(sizeof (**head_apt))))
            {
                printf("Erro a alocar o novo nó ");
                return;
            }
            tmp.next = NULL;
            **head_apt = tmp;
            head_apt = &(*head_apt)->next;
    }
    /*
        while ( fwrite(&tmp->inicio.h,sizeof(tmp->inicio.h), 1 ,f) == 1 )
        {
            fwrite(&tmp->inicio.h,sizeof(tmp->inicio.m), 1 ,f);
            fwrite(&tmp->fim.h,sizeof(tmp->fim.h), 1 ,f);
            fwrite(&tmp->fim.m,sizeof(tmp->fim.m), 1 ,f);
            fread(tmp->nome, sizeof(tmp->nome), 1, f);
            fread(&tmp->idade, sizeof(tmp->idade), 1, f);
            tmp->next = NULL;
            *head_apt = tmp;
        }
    */
    fclose(f);
}

void make_apt(struct marcacao **head_apt,struct medico *head_m)
{
    struct marcacao *aux = *head_apt;
     if(head_apt == NULL)
     {
         if ( !(*head_apt = malloc( sizeof(struct marcacao))) )
         {
             printf("Erro a alocar novo no\n" );
             return;
         }
     }
    else
    {
        while(*head_apt)
            head_apt = &(*head_apt)->next;
        *head_apt = create_apt(head_m, aux);
        printf("\n\n[MARCAÇÃO] - Prima ENTER para voltar ao menu");
        getchar();
        getchar();
    }
}

struct marcacao * create_apt(struct medico *head_m, struct marcacao *aux)
{
    struct marcacao * tmp;
    struct horas dur;
    char *tipo = "Normal";
    char t_choice;

    if ( !(tmp = malloc( sizeof(struct marcacao))) )
    {
        printf("Erro a alocar novo no\n" );
        return 0;
    }

    system(CLEAR);
    clock_date();
    memset(tmp, 0, sizeof(struct marcacao) );
    printf("\n\t\t::Marcações::\n\n");
    printf("Nome do Paciente > ");
    scanf(" %[^\n]", tmp->nome);
    if (check_name(aux, tmp->nome))
    {
        printf("O paciente já marcou uma consulta para hoje \n" );
        free(tmp);
        return NULL;
    }

    printf("Idade do Paciente > ");
    scanf("%d", &tmp->idade);

    do
    {
        printf("Especialidade > ");
        scanf(" %[^\n]", tmp->especialidade);
        check_spec(head_m, tmp->especialidade);

        if(check_spec(head_m, tmp->especialidade))
            printf("Introduza uma especialidade valida\n");
    } while(check_spec(head_m, tmp->especialidade));

    med_choice(&tmp,head_m, tmp->especialidade);
    printf("Tipo > " );
    scanf(" %[^\n]", tmp->tipo);
    dur = apt_dur(&tmp);

    //Se a consulta dor do tipo Normal
    if (!strcmp(tmp->tipo, tipo))
   {
       printf("Pretende escoher a  hora ? (s/n)");
       scanf(" %c", &t_choice);

       if( t_choice == 110)
       {
           if( assign_time(&tmp, aux, head_m, dur) )
               return 0;
       }
       else
       {
           if ( choose_time(&tmp, aux, head_m, dur) )
                return 0;
       }
   }
   else
   {
       if( assign_time(&tmp, aux, head_m, dur) )
           return 0;
   }

    tmp->next = NULL;
    return tmp;
}

int check_name(struct marcacao * head_apt, char (*nome))
{
    if (head_apt)
    {
        while (head_apt) {
            if (!strcmp(head_apt->nome, nome))
                return 1;
            head_apt = head_apt->next;
        }
    }
    return 0;
}

int check_spec(struct medico *head_m, char (*especialidade))
{
    if (head_m)
    {
        while (head_m) {
            if (!strcmp(head_m->especialidade, especialidade))
                return 0;
            head_m = head_m->next;
        }
    }
    return 1;
}

struct horas apt_dur( struct marcacao **head_apt)
{
    struct marcacao *tmp = *head_apt;
    struct horas dur;

    if(tmp->idade < 25)
    {
        dur.h = 0;
        dur.m = 30;
    }
    else
    {
        dur.h = 1;
        dur.m = 30;
    }
    return dur;
}

int choose_time(struct marcacao **head_apt, struct marcacao *old_head,
    struct medico * head_m, struct horas dur)
    {
        struct marcacao *tmp = *head_apt;
        int choice;
        //Poe o head_m a apontar para o medico da consulta
        while(head_m)
        {
            if(!strcmp(tmp->medico, head_m->nome))
                break;
            head_m = head_m->next;
        }
        printf("1 - Manhã \n" );
        printf("2 - Tarde\n" );
        printf("Qual o período que prefere ? " );
        scanf("%d", &choice );
        if (choice == 1)

        {
            tmp->inicio.h = 9;
            tmp->inicio.m = 30;

            if ( tmp->inicio.h  >= head_m->entrada.h &&  tmp->inicio.h  < head_m->saida.h)
            {
                                while (old_head)
                                {
                                    //Se houver outra consulta neste horario
                                    if ( tmp->inicio.h <= old_head->fim.h)
                                    {
                                        tmp->inicio.h = old_head->fim.h;
                                        tmp->inicio.m = old_head->fim.m + 5;

                                        if(tmp->inicio.m >= 60)
                                        {
                                            tmp->inicio.h++;
                                            tmp->inicio.m = tmp->inicio.m - 60;
                                        }
                                    }
                                    old_head = old_head->next;
                                }
                                tmp->fim.h =  tmp->inicio.h + dur.h;
                                tmp->fim.m =  tmp->inicio.m + dur.m;
                                if(tmp->fim.m >= 60)
                                {
                                    tmp->fim.h ++;
                                    tmp->fim.m = tmp->fim.m - 60;
                                }
                                *head_apt = tmp;

                                printf("%dh:%dm - %dh:%dm\n", tmp->inicio.h, tmp->inicio.m,
                                    tmp->fim.h, tmp->fim.m);
                                return 0;
            }
            else
            {
                printf("O médico já não se encontra disponivel. Tente noutra alturass \n" );
                printf("Prima ENTER para voltar ao menu\n" );
                getchar();
                getchar();
            }
        }
        else
        {
            tmp->inicio.h = 14;
            tmp->inicio.m = 0;
            if ( tmp->inicio.h  >= head_m->entrada.h &&  tmp->inicio.h  < head_m->saida.h)
            {
                                while (old_head)
                                {
                                    //Se houver outra consulta neste horario
                                    if ( tmp->inicio.h <= old_head->fim.h)
                                    {
                                        tmp->inicio.h = old_head->fim.h;
                                        tmp->inicio.m = old_head->fim.m + 5;

                                        if(tmp->inicio.m >= 60)
                                        {
                                            tmp->inicio.h++;
                                            tmp->inicio.m = tmp->inicio.m - 60;
                                        }
                                    }
                                    old_head = old_head->next;
                                }
                                tmp->fim.h =  tmp->inicio.h + dur.h;
                                tmp->fim.m =  tmp->inicio.m + dur.m;
                                if(tmp->fim.m >= 60)
                                {
                                    tmp->fim.h ++;
                                    tmp->fim.m = tmp->fim.m - 60;
                                }
                                *head_apt = tmp;

                                printf("%dh:%dm - %dh:%dm\n", tmp->inicio.h, tmp->inicio.m,
                                    tmp->fim.h, tmp->fim.m);
                                return 0;
            }
            else
            {
                printf("O médico já não se encontra disponivel. Tente noutra alturass \n" );
                printf("Prima ENTER para voltar ao menu\n" );
                getchar();
                getchar();
            }
        }
        return 1;
    }

int assign_time(struct marcacao **head_apt, struct marcacao *old_head,
    struct medico * head_m, struct horas dur)
    {
        time_t t = time(NULL);
        struct marcacao *tmp = *head_apt;
        struct tm tm = *localtime(&t);
        char *tipo = "Urgente";

        //Poe o head_m a apontar para o medico da consulta
        while(head_m)
        {
            if(!strcmp(tmp->medico, head_m->nome))
                break;
            head_m = head_m->next;
        }
        //Se a consulta for urgente
        if (!strcmp(tmp->tipo, tipo))
        {
            if ( tm.tm_hour >= head_m->entrada.h &&  tm.tm_hour < head_m->saida.h)
            {
                tmp->inicio.h = tm.tm_hour;
                tmp->inicio.m = tm.tm_min;

                while (old_head)
                {
                    //Se houver outra consulta neste horario
                    if ( tmp->inicio.h <= old_head->fim.h)
                    {
                        tmp->inicio.h = old_head->fim.h;
                        tmp->inicio.m = old_head->fim.m + 5;

                        if(tmp->inicio.m >= 60)
                        {
                            tmp->inicio.h++;
                            tmp->inicio.m = tmp->inicio.m - 60;
                        }
                    }
                    old_head = old_head->next;
                }
                tmp->fim.h =  tmp->inicio.h + dur.h;
                tmp->fim.m =  tmp->inicio.m + dur.m;
                if(tmp->fim.m >= 60)
                {
                    tmp->fim.h ++;
                    tmp->fim.m = tmp->fim.m - 60;
                }
                *head_apt = tmp;

                printf("%dh:%dm - %dh:%dm\n", tmp->inicio.h, tmp->inicio.m,
                    tmp->fim.h, tmp->fim.m);
                return 0;
            }
            else
            {
                printf("O médico já não se encontra disponivel. Tente noutra alturass \n" );
                printf("Prima ENTER para voltar ao menu\n" );
                getchar();
                getchar();
            }
        }
        else
        {
            tmp->inicio.h = tm.tm_hour + 1;
            tmp->inicio.m = tm.tm_min + 30;

            if(tmp->inicio.m >= 60)
            {
                tmp->inicio.h++;
                tmp->inicio.m = tmp->inicio.m - 60;
            }
            while (old_head)
            {
                //Se houver outra consulta neste horario
                if ( tmp->inicio.h <= old_head->fim.h)
                {
                    tmp->inicio.h = old_head->fim.h;
                    tmp->inicio.m = old_head->fim.m + 5;

                    if(tmp->inicio.m >= 60)
                    {
                        tmp->inicio.h++;
                        tmp->inicio.m = tmp->inicio.m - 60;
                    }
                }
                old_head = old_head->next;
            }
            tmp->fim.h =  tmp->inicio.h + dur.h;
            tmp->fim.m =  tmp->inicio.m + dur.m;
            if(tmp->fim.m >= 60)
            {
                tmp->fim.h ++;
                tmp->fim.m = tmp->fim.m - 60;
            }
            *head_apt = tmp;
            printf("%dh:%dm - %dh:%dm\n", tmp->inicio.h, tmp->inicio.m,
                tmp->fim.h, tmp->fim.m);
            return 0;
        }
        return 1;
    }

char * med_choice(struct marcacao **head_apt, struct medico *head_m,
    char (*especialidade) )
{
    int n = 1 ;
    int med_op;
    int x = 1;
    struct medico *current = head_m;
    struct marcacao * tmp = *head_apt;

    printf("Pode escolher os seguintes medicos \n");
    while(current)
    {
        if(!strcmp(current->especialidade, especialidade))
            printf("\n %d -> [Médico] - %s", n++, current->nome);
        current = current->next;
    }

    printf("\n\nQual deseja escolher ? ");
    scanf("%d", &med_op );

    while(head_m)
    {
        if(!strcmp(head_m->especialidade, especialidade))
        {
            if(med_op == x )
            {
                    printf( "\nMédico > %s\n", head_m->nome);
                    strcpy(tmp->medico ,head_m->nome);
                    *head_apt = tmp;
            }
        x++;
        }
        head_m = head_m->next;
    }
     return 0;
}

void show_agd(struct marcacao *head_apt)
{
    system(CLEAR);
    clock_date();
    printf("\n\t\t::Agenda::\n\n");
    if (head_apt)
    {
        while(head_apt)
        {
            printf("\n[%dh:%dm - %dh:%dm]\n ", head_apt->inicio.h, head_apt->inicio.m,
             head_apt->fim.h, head_apt->fim.m);
            printf("\n\tNome > %s\n", head_apt->nome);
            printf("\tIdade > %d\n",head_apt->idade);
            printf("\tEspecialidade > %s\n",head_apt->especialidade );
            printf("\tMédico > %s\n", head_apt->medico );
            printf("\tTipo > %s\n", head_apt->tipo);
            head_apt = head_apt->next;
        }
        printf("\n\nPrima ENTER para voltar ao menu");
        getchar();
        getchar();
    }
    else
    {
        printf("\n\tNão foram efetuadas marcações\n");
        printf("\n\nPrima ENTER para voltar ao menu");
        getchar();
        getchar();
    }
}

void del_apt(struct marcacao **head_apt)
{
    struct marcacao *tmp = NULL;
    int choice = 1;

    system(CLEAR);
    clock_date();

    tmp = *head_apt;

    //Se existir consutltas
    if(tmp)
    {
        //Se só houver uma consulta
        if (!tmp->next)
        {
            free_apt(head_apt);
            printf("\n\n\n\t[Marcação Apagada] - Prima ENTER para voltar ao menu\n");
            getchar();
            getchar();
            return;
        }
        //Se houver mais de uma
        else
        {
            while (tmp)
            {
                printf("\t %d - [%s] \n", choice++, tmp->nome);
                tmp = tmp->next;
            }
            printf("\nQual marcação pretende apagar ?\n");
            scanf("%d", &choice);
            *head_apt = wipe_apt(*head_apt, choice);

            printf("\n\n\n\t[Marcação Apagada] - Prima ENTER para voltar ao menu\n");
            getchar();
            getchar();
        }
    }
    // Senão existirem consultas
    else
    {
        printf("\n\n\n\tNão foram efetuadas marcações\n");
        printf("\n\nPrima ENTER para voltar ao menu");
        getchar();
        getchar();
        return;
    }
}

struct marcacao * wipe_apt(struct marcacao *head_apt, int choice)
{
    int i;
    struct marcacao *aux = head_apt;
    struct marcacao *del;

    if (choice == 1)
    {
        free(aux);
        return head_apt->next;
    }

    for(i = 0; i < choice - 2; i++)
            aux = aux->next;
    ///aux é o del -1
    del = aux->next;
    aux->next = del->next;
    free(del);
    return aux;
}

void free_apt(struct marcacao **head_apt)
{
    struct marcacao  * curr_apt, * next_apt;

    curr_apt = * head_apt;
    *head_apt = NULL;
    while(curr_apt != NULL)
    {
        next_apt = curr_apt->next;
        free(curr_apt);
        curr_apt = next_apt;
  }
}

void sv_apt(struct marcacao *head_apt)
{
    FILE * x= fopen(APT_FILE, "wb");
    FILE *f = fopen(APT_TXT, "w");
    if( !f )
    {
        printf("Erro a abrir o ficheiro\n" );
        return;
    }
    while (head_apt)
    {
        fprintf(f, "%d %d %d %d\n", head_apt->inicio.h, head_apt->inicio.m, head_apt->fim.h,
            head_apt->fim.m);
        fprintf(f, "%s\n", head_apt->nome);
        fprintf(f, "%d\n", head_apt->idade);
        fprintf(f, "%s\n", head_apt->especialidade);
        fprintf(f, "%s\n", head_apt->medico);
        fprintf(f, "%s\n", head_apt->tipo);



        fwrite(&head_apt->inicio.h,sizeof(head_apt->inicio.h), 1 ,x);
        fwrite(&head_apt->inicio.m,sizeof(head_apt->inicio.m), 1 ,x);
        fwrite(&head_apt->fim.h,sizeof(head_apt->fim.h), 1 ,x);
        fwrite(&head_apt->fim.m,sizeof(head_apt->fim.m), 1 ,x);
        fwrite(head_apt->nome, sizeof(head_apt->nome), 1, x);
        fwrite(&head_apt->idade, sizeof(head_apt->idade), 1, x);
        fwrite(head_apt->especialidade, sizeof(head_apt->especialidade),1, x);
        fwrite(head_apt->medico, sizeof(head_apt->medico), 1, x);
        fwrite(head_apt->tipo, sizeof(head_apt->tipo), 1, x);
        head_apt = head_apt->next;
    }
    fclose(x);
    fclose(f);
}

void daily_save(struct marcacao **head_apt, struct paciente * head_p,
    struct consulta * head_c)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char choice;
    int i;
    struct marcacao *tmp;
    FILE *f_tmp = fopen( TEMP, "w");

    if( !f_tmp)
    {
        printf("Erro a abrir o ficheiro\n" );
        return;
    }
    system(CLEAR);
    load_apt(head_apt);
    tmp = *head_apt;
    clock_date();

    printf("\n\n\tDeseja sair e fazer e guardar todas as consultas de hoje ? (s/n) ");
    scanf(" %c", &choice);

    if(choice == 110)
    {
        fclose(f_tmp);
        free_apt(head_apt);
        return;
    }
    else
    {
        while (tmp)
        {
            fprintf(f_tmp, "%s\n", tmp->nome);
            fprintf(f_tmp, "%d\n", tmp->idade);
            fprintf(f_tmp, "1 consultas\n");
            fprintf(f_tmp, "%s - %d/%d/%d - %s\n", tmp->tipo, tm.tm_mday,
                tm.tm_mon + 1,tm.tm_year + 1900 , tmp->medico);
            tmp = tmp->next;
        }

        while (head_p)
        {
            fprintf(f_tmp, "%s\n", head_p->nome);
            fprintf(f_tmp, "%d\n", head_p->idade);
            fprintf(f_tmp, "%d consultas\n" ,head_p->nconsultas);
            for(i = 0; i < head_p->nconsultas; i++)
            {
                fprintf(f_tmp, "%s - %d/%d/%d - %s\n", head_c->tipo, head_c->data.dia,
                    head_c->data.mes, head_c->data.ano , head_c->medico);
                head_c = head_c->next;
            }
            head_p = head_p->next;
        }
    }
    remove(P_FILE);
    remove(APT_TXT);
    rename(TEMP, P_FILE);
    fclose(f_tmp);
    free_apt(head_apt);
}
