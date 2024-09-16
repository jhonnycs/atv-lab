#ifndef GERENCIAR_INV
#define GERENCIAR_INV

#include <stdio.h>
#include <stdlib.h>
#include "getDados.h"

void mostrarFinancasPessoas(Pessoa pessoa);
void adicionarFinanca(int idPessoa);
void modificarFinanca(int idPessoa, int indexFinanca);

void deletarFinanca(Pessoa *pessoa, int indexFinanca);

int compararPorData(const void *a, const void *b);
int compararPorTipo(const void *a, const void *b);
int compararPorValor(const void *a, const void *b);
int compararPorNome(const void *a, const void *b);

void ordenarFinancasPorData(Pessoa *pessoa);
void ordenarFinancasPorTipo(Pessoa *pessoa);
void ordenarFinancasPorValor(Pessoa *pessoa);

void agruparEOrdenarFinancasData(Pessoa *pessoa);
void agruparEOrdenarFinancasValor(Pessoa *pessoa);

#endif
