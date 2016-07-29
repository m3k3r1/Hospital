#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define M_FILE "medico.txt"
#define P_FILE "paciente.txt"

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
}*head_m;


struct consulta
{
    char tipo[50];
    struct data data;
    char medico[50];
    struct consulta *next;
}*head_c;

struct paciente
{
    char nome[50];
    int idade;
    int nconsultas;
    struct consulta consulta;
    struct paciente *next;
}*head_p;

int menu();
void dump_database();
void dump_med();
void dump_pac();
void add_Node(struct medico *current);
void show_info();