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
      struct marcacao *next;
};

int menu_apt();
void make_appointment(struct medico *head_m,  struct marcacao *head_apt);
void make_apt( struct marcacao **head_apt );
struct marcacao  * create_apt();
void del_apt(struct marcacao **head_apt);
void show_agd(struct marcacao *head_apt);
void free_apt(struct marcacao **head_apt);
void sv_apt(struct marcacao *head_apt);
void load_apt(struct marcacao **head_apt);
#endif
