#ifndef CALC_INV
#define CALC_INV

#include "getDados.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int diasNumMes(int mes, int ano);
int dateToDays(Data d);
int diferencaMeses(Data d1, Data d2);
float calcTaxaImposto(int diasPassados);

float calcInvIPCA(int numMeses);

void atualizarDataAtual();

void atualizarInvestimento(Financeiro *financa);
void imprimirValorBrutoTotal(Financeiro *financa);
void imprimirValorLiquidoTotal(Financeiro *financa);

#endif