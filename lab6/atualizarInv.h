#ifndef ATUALIZAR_INV
#define ATUALIZAR_INV

#include "getDados.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

extern float taxasInvestimentos[];

int diasNumMes(int mes, int ano);
int dateToDays(Data d);
int diferencaMeses(Data d1, Data d2);
float calcTaxaImposto(int diasPassados);

// void calcInvIPCA(Financeiro *financa, int numMeses);
void calcInvMensal(Financeiro *financa, int numMeses);
void atualizarDataAtual();

void atualizarInvestimento(Financeiro *financa);
void imprimirValorBrutoTotal(Financeiro *financa);
void imprimirValorLiquidoTotal(Financeiro *financa);

#endif
