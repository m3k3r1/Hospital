#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

struct horas 
{
    int h;
    int m;
};
typedef struct horas horas;

typedef struct medico medico;
struct medico
{
    char nome[50];
    char especialidade[50];
    horas entrada;
    horas saida;
    medico *next;    
};


struct data
{
    int dia;
    int mes;
    int ano;
};
typedef struct data data;

struct consulta
{
    char tipo[50];
    data x;
    char medico[50];
};
typedef struct consulta consulta;

typedef struct paciente paciente; 
struct paciente
{
    char nome[50];
    int idade;
    consulta x;
    paciente *next;
};
 


int menu();
void save_file_info();