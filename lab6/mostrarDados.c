#include "mostrarDados.h"

void mostrarFinancasPessoas(Pessoa pessoa) {
    printf("Finanças de %s (%d)-----------------------\n", pessoa.nome, pessoa.quantFinancas);

    for (int i = 0; i < pessoa.quantFinancas; i++) {
        printf("Índice da finança: %d\n", i);
        printf("Nome da finança: %s\n", pessoa.financas[i].nome);
        printf("Tipo da finança: %s\n", tipoInvestimentoString[pessoa.financas[i].tipo]);
        printf("Valor aplicado na finança: %.2f\n", pessoa.financas[i].valorAplicado);
        printf("Data de aplicação: %d/%d/%d\n", pessoa.financas[i].dataAplicacao.dia, pessoa.financas[i].dataAplicacao.mes, pessoa.financas[i].dataAplicacao.ano);
        if (pessoa.financas[i].isUpToDate) {
            printf("Imposto: %.2f\n", pessoa.financas[i].imposto);
            printf("Valor bruto: %.2f\n\n", pessoa.financas[i].valorBruto);
        } else {
            printf("Atualize o investimento para mais informações\n\n");
        }
    }
}

void mostrarUmaFinancaDeUmaPessoa(Financeiro financa) {
    printf("Nome da finança: %s\n", financa.nome);
    printf("Tipo da finança: %s\n", tipoInvestimentoString[financa.tipo]);
    printf("Valor aplicado na finança: %.2f\n", financa.valorAplicado);
    printf("Data de aplicação: %d/%d/%d\n", financa.dataAplicacao.dia, financa.dataAplicacao.mes, financa.dataAplicacao.ano);
    if (financa.isUpToDate) {
        printf("Imposto: %.2f\n", financa.imposto);
        printf("Valor bruto: %.2f\n\n", financa.valorBruto);
    } else {
        printf("Atualize o investimento para mais informações\n\n");
    }
}

void imprimirValorBrutoTotal(Financeiro *financa) {
    if (!financa->isUpToDate) {
        printf("Atualize o investimento para ver o valor bruto total.\n");
        return;
    }
    printf("Valor bruto total: %.2f\n", financa->valorBruto);
}

void imprimirValorLiquidoTotal(Financeiro *financa) {
    if (!financa->isUpToDate) {
        printf("Atualize o investimento para ver o valor líquido total.\n");
        return;
    }
    printf("Valor líquido total: %.2f\n", financa->valorBruto-financa->imposto);
}
