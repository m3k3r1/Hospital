#include "hospital.h"

/**######################################## MENU 1 ###########################################**/

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

/**######################################## OPÇÃO 1 ###########################################**/

void show_all(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c)
{
    dump_database(&head_m, &head_p, &head_c);
    show_info(head_m, head_p, head_c);
    free_mem(head_m, head_p, head_c);
}

/**######################################## OPÇÃO 2 ###########################################**/

void search_med(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c)
{
    dump_database(&head_m, &head_p, &head_c);
    med_by_spec(head_m);
    free_mem(head_m, head_p, head_c);
}

/**######################################## OPÇÃO 3 ###########################################**/

void pac_by_speciality(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c)
{
    dump_database(&head_m, &head_p, &head_c);
    pac_by_spec(head_p, head_c, head_m);
    free_mem(head_m, head_p, head_c);
}

/**######################################## OPÇÃO 4 ###########################################**/

void pac_by_time(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c)
{
    free_mem(head_m, head_p, head_c);
}

/**######################################## OPÇÃO 5 ###########################################**/

void med_now(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c)
{
    dump_database(&head_m, &head_p, &head_c);
    check_schdl(head_m);
    free_mem(head_m, head_p, head_c);
}

/**######################################## OPÇÃO 6 ###########################################**/

void make_appointment(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c, struct marcacao *head_apt)
{
    int menu_op = 0;

    do
    {
        menu_op = menu_apt();
        switch(menu_op)
        {
            case 1: dump_database(&head_m, &head_p, &head_c);
                          make_apt(head_m, &head_apt);
                          free_mem(head_m, head_p, head_c);
                          break;
            case 2: dump_database(&head_m, &head_p, &head_c);
                          del_apt(head_apt);
                          free_mem(head_m, head_p, head_c);
                          break;
            case 3: dump_database(&head_m, &head_p, &head_c);
                          show_agd(head_apt);
                          free_mem(head_m, head_p, head_c);
                          break;
            case 4: free_apt(head_apt);
                          return;
                          break;
        }
    } while(1);
}

/**######################################## OPÇÃO 7 ###########################################**/

void sv_chg(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c, struct marcacao *head_apt)
{
    sv_apt(head_apt);
    upt_pac(head_apt);
}

/**##################################### [REQUESITOS GERAIS] ###################################**/

void clock_date()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("%d/%d/%d",tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900);
    printf("\t\t\t\t  %dh%dm\n", tm.tm_hour, tm.tm_min);
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

    while(fscanf(f,"%[^\n]", tmp.nome) == 1 &&
              fscanf(f, " %d", &tmp.idade) == 1 &&
              fscanf(f, "%d consultas", &tmp.nconsultas) == 1)
    {
        printf("!!!!NOME > %s\n", tmp.nome);
        while(fscanf(f, "%s - %d/%d/%d - %[^\n]", tmp_c.tipo, 
                    &tmp_c.data.dia, &tmp_c.data.mes, &tmp_c.data.ano, tmp_c.medico ) == 5)
        {
             if ( !(*head_c = malloc(sizeof (**head_c))) )
            {
                printf("Erro a alocar o novo nó \n");
                return;
            }
            tmp_c.next = NULL;
            **head_c = tmp_c;
            head_c = &(*head_c)->next;
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

void free_apt(struct marcacao *head_apt)
{
    struct marcacao *tmp_apt = NULL; 

    while (head_apt)
    { 
        tmp_apt = head_apt->next;
        free(head_apt);
        head_apt = tmp_apt;
    }
}
/**##################################### 1 [REQUESITOS] ######################################**/

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
            printf("\t[Tipo]: %s\n", head_c->tipo);
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

/**##################################### 2 [REQUESITOS] ######################################**/

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

/**##################################### 3 [REQUESITOS] ######################################**/
//FIX A REPETIÇÃO DO NOME DO PACIENTE
void pac_by_spec(struct paciente *head_p ,struct consulta *head_c,
    struct medico *head_m)
{
    int n;
    char str[50];
    char *med;

    system(CLEAR);
    clock_date();
    printf("\n\n\n[PACIENTE]Especialidade pretendida > ");
    scanf("%s", str);
    med =  assign_med_by_spec(str, head_m);

    while(head_p != NULL)
    {   
        while( n < head_p->nconsultas )
        {
            if(!strcmp(med, head_c->medico))
                printf("\nPaciente > %s", head_p->nome);

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

/**##################################### 4 [REQUESITOS] ######################################**/



/**##################################### 5 [REQUESITOS] ######################################**/

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

/**##################################### 6 [REQUESITOS] ######################################**/

/**---------------------------------------- MENU 2 -------------------------------------------**/

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

/**--------------------------------------  OPÇÃO 1 -----------------------------------------**/

void make_apt(struct medico *head_m, struct marcacao **head_apt)
{  
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    struct marcacao tmp;
    char especialidade[50];
    char choice;

    while( *head_apt != NULL)
    {
        //printf("I'm deleting the previous info\n");
        head_apt = &(*head_apt)->next;  
    }

    system(CLEAR);
    clock_date();
    printf("\n\t\t::Marcações::\n\n");
    printf("Nome do Paciente > ");
    scanf(" %[^\n]", tmp.nome);
    printf("Idade do Paciente > ");
    scanf("%d", &tmp.idade);
    tmp.data.dia = tm.tm_mday;
    tmp.data.mes = tm.tm_mon + 1;
    tmp.data.ano = tm.tm_year + 1900;
    printf("Tipo de Consulta [Normal/Urgente] > ");
    scanf(" %[^\n]", tmp.tipo);
    printf("Especialidade > ");
    scanf(" %[^\n]", especialidade);

    printf("Deseja escolher médico ? (s/n)");
    scanf(" %c", &choice);
    if( choice == 115)
        tmp.medico = med_choice(head_m, especialidade);
    else
        tmp.medico = assign_med_by_spec(especialidade, head_m);
    
    tmp.next = NULL;
    
    if ( !(*head_apt = malloc( sizeof (**head_apt) ) ) )
    {
        printf("Failed to allocate new list node: ");
        return;
    }

    **head_apt = tmp;

    printf("\n\n[MARCAÇÃO] - Prima ENTER para confirmar consulta");
    getchar();
    getchar();

}
        
/**-------------------------------------  OPÇÃO 2 ------------------------------------------**/

void del_apt(struct marcacao *head_apt)
{
    struct marcacao *aux = head_apt;
    struct marcacao **nxt = NULL;
    int p_choice = 0;
    int i = 1;
    int x = 1;
    system(CLEAR);
    clock_date();

    if(!head_apt)
    {
        printf("\n\n\n\tNão foram efetuadas marcações\n");
        printf("\n\nPrima ENTER para voltar ao menu");
        getchar();
        getchar();
        return;
    }
    
    else
        while(aux)
        {
            printf("\n\n\n\t %d -> %s \n", i, aux->nome);
            i++;
            aux = aux->next;
        }

         printf("\nQual marcação pretende apagar ? ");
         scanf(" %d", &p_choice);
         
         while(head_apt)
         {
             if( p_choice == x )
             {
                 *nxt = head_apt->next;
                 free(head_apt);
                 head_apt = *nxt;  
             }
             x++;
             head_apt = head_apt->next;
         }
}

/**-------------------------------------  OPÇÃO 3 ------------------------------------------**/

void show_agd(struct marcacao *head_apt)
{
    system(CLEAR);
    clock_date();
    printf("\n\t\t::Marcações::\n\n");
    
    if(head_apt == NULL)
    {
        printf("\n\tNão foram efetuadas marcações\n");
        printf("\n\nPrima ENTER para voltar ao menu");
        getchar();
        getchar();
        return;
    }
    while(head_apt != NULL)
    {
        printf("\nNome > %s\n", head_apt->nome);
        printf("Idade > %d\n",head_apt->idade);
        printf("Tipo > %s\n", head_apt->tipo);
        printf("Medico > %s\n", head_apt->medico);
        head_apt = head_apt->next;
    }
    printf("\n\nPrima ENTER para voltar ao menu");
    getchar();
    getchar();
}

/**-------------------------------------- 1 [REQUESITOS] #----------------------------------**/

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

char * med_choice(struct medico *head_m, char * especialidade)
{
    int n = 1 ;
    int med_op;
    int x = 1;
    struct medico *current = head_m;

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
                    return head_m->nome;
            }
        x++;
        }
        head_m = head_m->next;
    }
     return 0;
}
/**##################################### 7 [REQUESITOS] ######################################**/

void sv_apt(struct marcacao *head_apt)
{

}

void upt_pac(struct marcacao *head_apt)
{

}