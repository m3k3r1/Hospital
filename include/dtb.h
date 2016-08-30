#ifndef dtb_h_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define dtb_h_
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
#define TRUE 1
#define FALSE 0
#define M_FILE "res/medico.txt"
#define P_FILE "res/paciente.txt"

struct horas
{
    int h;
    int m;
};

struct data
{
    int dia;
    int mes;
    int ano;
};

struct medico
{
    char nome[50];
    char especialidade[50];
    struct horas entrada;
    struct horas saida;
    struct medico *next;
};

struct consulta
{
    char tipo[50];
    struct data data;
    char medico[50];
    struct consulta *next;
};

struct paciente
{
    char nome[50];
    int idade;
    int nconsultas;
    struct consulta consulta;
    struct paciente *next;
};

void clock_date();
void dump_med(struct medico **head_m);
void dump_pac(struct paciente **head_p ,struct consulta **head_c);
void show_info(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c);
void med_by_spec(struct medico *head_m);
char * assign_med_by_spec(char *especialidade, struct medico *head_m);
void pac_by_spec(struct paciente *head_p ,struct consulta *head_c,
    struct medico *head_m);
int compare_dates (struct data d1, struct data d2);
void pac_by_t(struct paciente *head_p, struct consulta *head_c);
void check_schdl(struct medico *head_m);
void free_mem(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c);
#endif
