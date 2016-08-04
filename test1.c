#include <stdio.h>
#include <stdlib.h>
#define P_FILE "paciente.txt"

struct data
{
    int dia;
    int mes;
    int ano;
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

int main()
{   
    struct paciente **head_p;
    struct paciente tmp;
    struct consulta tmp_c;
    struct consulta **head_c;

    FILE *f = fopen(P_FILE, "r");
        if(f == NULL)
    {
        printf("Erro a abrir o ficheiro\n");
        return 0;
    }

    fscanf(f, "%[^\n]", tmp.nome); 
    fscanf(f, "%d", &tmp.idade); 
    fscanf(f, "%d consultas", &tmp.nconsultas);
    fscanf(f, "%c-%d/%d/%d-%[^\n]", tmp_c.tipo, &tmp_c.data.dia, &tmp_c.data.mes, &tmp_c.data.ano, tmp_c.medico);
    printf("%s %d/%d/%d\n", tmp_c.tipo ,tmp_c.data.dia, tmp_c.data.mes, tmp_c.data.ano);

    fclose(f);
}
