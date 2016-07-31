#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define M_FILE "medico.txt"
#define P_FILE "paciente.txt"
#define TRUE 1
#define FALSE 0

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

int menu();
void clock_date();
void show_all(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c);
void search_med(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c);
void pac_by_speciality(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c);
void pac_by_time(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c);
void med_now(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c);
void make_appointment();
void dump_database(struct medico **head_m, struct paciente **head_p ,
    struct consulta **head_c);
void dump_med(struct medico **head_m);
void dump_pac(struct paciente **head_p ,struct consulta **head_c);
void show_info(struct medico *head_m, struct paciente *head_p ,
    struct consulta *head_c);
void med_by_spec(struct medico *head_m);
void pac_by_spec(struct paciente *head_p ,struct consulta *head_c);
