#ifndef GET_DADOS
#define GET_DADOS

#include <stdio.h>
#include <string.h>

#define TAM_NOME 250
#define MAX_INVEST 300
#define MAX_PESSOAS 100

typedef struct data {
    int dia: 6;
    int mes: 5;
    int ano;
} Data;

typedef enum {
    PREFIXADO,
    IPCA_PLUS,
    SELIC,
    CDI
} TipoInvestimento;

typedef struct financeiro {
    TipoInvestimento tipo;
    char nome[TAM_NOME];
    Data dataAplicacao;
    float valorBruto;
    
    Data dataVencimento;
    float valorAplicado;
    float taxaJuros;    // em %
    float imposto;      // valor a ser segurado
    int isUpToDate;
} Financeiro;

typedef struct pessoa {
    int id;
    char nome[TAM_NOME];
    int quantFinancas;
    Financeiro financas[MAX_INVEST];
} Pessoa;

extern Pessoa pessoas[MAX_PESSOAS];
extern int quantPessoas;
extern Data dataAtual;

extern char tipoInvestimentoString[4][TAM_NOME];

int isBissexto(int ano);
int diasNoMes(int mes, int ano);
Data getData();
void removeNewline(char *str);
Pessoa criarFinanca();

#endif