#ifndef appt_h_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "dtb.h"
#define appt_h_

#define APT_FILE "res/marcacao.bin"

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
struct marcacao  * create_apt(struct medico *head_m);
int check_spec(struct medico *head_m, char (*especialidade));
void apt_dur( struct marcacao **head_apt);
char * med_choice(struct marcacao **head_apt, struct medico *head_m, char (*especialidade));
void assign_time_by_user( struct marcacao **head_apt);
void del_apt(struct marcacao **head_apt);
struct marcacao * wipe_apt(struct marcacao *head_apt, int choice);
void show_agd(struct marcacao *head_apt);
void free_apt(struct marcacao **head_apt);
void sv_apt(struct marcacao *head_apt);
void load_apt(struct marcacao **head_apt);
#endif
