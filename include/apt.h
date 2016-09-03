#ifndef appt_h_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "dtb.h"
#define appt_h_

#define APT_FILE "res/marcacao.bin"
#define APT_TXT "res/marcacao.txt"
#define TEMP "res/tmp.txt"

struct marcacao
{
      char nome[50];
      int idade;
      char tipo[50];
      char especialidade[50];
      char medico[50];
      struct horas inicio;
      struct horas fim;
      struct marcacao *next;
};

int menu_apt();
void make_appointment(struct medico *head_m,  struct marcacao *head_apt);
void make_apt( struct marcacao **head_apt, struct medico *head_m);
struct marcacao  * create_apt(struct medico *head_m, struct marcacao *aux);
int check_name(struct marcacao * head_apt, char (*nome));
int check_spec(struct medico *head_m, char (*especialidade));
struct horas apt_dur( struct marcacao **head_apt);
int choose_time(struct marcacao **head_apt, struct marcacao *old_head,
    struct medico * head_m, struct horas dur);
int assign_time(struct marcacao **head_apt, struct marcacao *old_head,
    struct medico * head_m, struct horas dur);
char * med_choice(struct marcacao **head_apt, struct medico *head_m,
    char (*especialidade));
void del_apt(struct marcacao **head_apt);
struct marcacao * wipe_apt(struct marcacao *head_apt, int choice);
void show_agd(struct marcacao *head_apt);
void free_apt(struct marcacao **head_apt);
void sv_apt(struct marcacao *head_apt);
void load_apt(struct marcacao **head_apt);
void daily_save( struct marcacao **head_apt, struct paciente * head_p,
    struct consulta * head_c);

#endif
