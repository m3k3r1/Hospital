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
        case 1: make_apt(&head_apt);
                      break;
        case 2: del_apt(&head_apt);
                      break;
        case 3: show_agd(head_apt);
                      break;
        case 4: free_apt(&head_apt);
                      return;
                      break;
        }
    } while(1);
}

void load_apt(struct marcacao **head_apt)
{
    struct marcacao *tmp;
    tmp = malloc(sizeof(struct marcacao));
    FILE *f = fopen(APT_FILE, "ab");
    if( !f )
    {
        printf("Erro a abrir o ficheiro\n" );
        return;
    }
    while(*head_apt)
        head_apt = &(*head_apt)->next;

    while ( fread(tmp->nome, sizeof(tmp->nome), 1, f) == 1 ) {
        fread(&tmp->idade, sizeof(tmp->idade), 1, f);
        tmp->next = NULL;
        *head_apt = tmp;
    }
    free(tmp);
    fclose(f);
}

void make_apt(struct marcacao **head_apt)
{
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
        *head_apt = create_apt();
        printf("\n\n[MARCAÇÃO EFETUADA] - Prima ENTER para confirmar");
        getchar();
        getchar();
    }
}

struct marcacao * create_apt()
{
    struct marcacao * tmp;
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
    printf("Idade do Paciente > ");
    scanf("%d", &tmp->idade);
    tmp->next = NULL;

    sv_apt(tmp);
    return tmp;
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
            printf("\n\tNome > %s\n", head_apt->nome);
            printf("\tIdade > %d\n",head_apt->idade);
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
    char nome[50];
    struct marcacao  * curr_apt, * next_apt ,*prev_apt, *aux;

    system(CLEAR);
    clock_date();

    aux = * head_apt;
    curr_apt = * head_apt;
    head_apt = NULL;

    if(aux)
    {
        while(aux)
        {
            printf("\n\t Nome > %s\n", aux->nome);
            aux = aux->next;
        }
        printf("\nQual marcação pretende apagar ? ");
        scanf("%s", nome);

        while(curr_apt)
        {
            if ( !strcmp(nome, curr_apt->nome) )
            {
                next_apt = curr_apt->next;
                free(curr_apt);
                prev_apt->next = next_apt;
            }
            prev_apt = curr_apt;
            curr_apt = curr_apt->next;
        }
        printf("\n\n\n\t\n");
        printf("\n\n[MARCAÇÃO APAGADA] - Prima ENTER para confirmar");
        getchar();
        getchar();
    }
    else
    {
        printf("\n\n\n\tNão foram efetuadas marcações\n");
        printf("\n\nPrima ENTER para voltar ao menu");
        getchar();
        getchar();
        return;
    }
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
    FILE *f = fopen(APT_FILE, "ab");
    if( !f )
    {
        printf("Erro a abrir o ficheiro\n" );
        return;
    }
    fwrite(head_apt->nome, sizeof(head_apt->nome), 1, f);
    fwrite(&head_apt->idade, sizeof(head_apt->idade), 1, f);
    fclose(f);
}
