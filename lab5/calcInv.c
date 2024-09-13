#include "calcInv.h"

int diasNumMes(int mes, int ano) {
    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isBissexto(ano) ? 29 : 28;
        default:
            return 0; // Mês inválido
    }
}

int dateToDays(Data d) {
    int diasTotais = 0;

    // Adiciona os dias dos anos anteriores
    for (int ano = 1; ano < d.ano; ++ano) {
        diasTotais += isBissexto(ano) ? 366 : 365;
    }

    // Adiciona os dias dos meses do ano atual
    for (int mes = 1; mes < d.mes; ++mes) {
        diasTotais += diasNumMes(mes, d.ano);
    }

    // Adiciona os dias do mês atual
    diasTotais += d.dia;

    return diasTotais;
}

int diferencaMeses(Data d1, Data d2) {
    int totalMeses1 = d1.ano * 12 + d1.mes;

    int totalMeses2 = d2.ano * 12 + d2.mes;

    return abs(totalMeses1-totalMeses2);
}

float calcTaxaImposto(int diasPassados) {
    float taxaImposto;

    if (diasPassados <= 180) {
        taxaImposto = 0.225;
    } else if (diasPassados <= 360) {
        taxaImposto = 0.200;
    } else if (diasPassados <= 720) {
        taxaImposto = 0.175;
    } else {
        taxaImposto = 0.15;
    }

    return taxaImposto;
}

void atualizarDataAtual() {
    time_t tempoAtual = time(NULL);
    struct tm *tm = localtime(&tempoAtual);

    dataAtual.ano = tm->tm_year + 1900;
    dataAtual.mes = tm->tm_mon + 1;
    dataAtual.dia = tm->tm_mday;
}

void atualizarInvestimento(Financeiro *financa) {

    atualizarDataAtual();
    
    financa->valorBruto = financa->valorAplicado;

    int dataAplicacaoEmDias = dateToDays(financa->dataAplicacao);
    int dataAtualEmDias = dateToDays(dataAtual);

    int diferencaDias = dataAtualEmDias - dataAplicacaoEmDias;

    // double taxaDiaria = pow(financa->taxaJuros + 1, (double)1 / (double)365);
    // financa->valorBruto = financa->valorBruto * pow(taxaDiaria, diferencaDias);

    calcInvIPCA(financa, diferencaMeses(dataAtual, financa->dataAplicacao));

    float lucro = financa->valorBruto - financa->valorAplicado;
    financa->imposto = lucro * calcTaxaImposto(diferencaDias);

    financa->isUpToDate = 1;

    printf("imposto: %.2f\n", financa->imposto);
    printf("Valor aplicado: %.2f\n", financa->valorAplicado);
    printf("valor bruto: %.2f\n", financa->valorBruto);
}

void calcInvIPCA(Financeiro *financa, int numMeses) {
    float *ipca = (float*) malloc(numMeses * sizeof(float));

    if (ipca == NULL) {
        printf("Erro na alocação de memória!\n");
        return;
    }

    for (int i = 0; i < numMeses; i++) {
        ipca[i] = ((float)rand() / RAND_MAX) * 0.10;
        financa->valorBruto = financa->valorBruto + financa->valorBruto * ipca[i];
    }

    free(ipca);
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
