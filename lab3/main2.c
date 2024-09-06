#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TAM_NOME 250
#define MAX_INVEST 300
#define MAX_PESSOAS 100

typedef struct data {
    int dia: 5;
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
} Financeiro;

typedef struct pessoa {
    int id;
    char nome[TAM_NOME];
    int quantFinancas;
    Financeiro financas[MAX_INVEST];
} Pessoa;

Pessoa pessoas[MAX_PESSOAS];
int quantPessoas = 0;
Data dataAtual;

char tipoInvestimentoString[4][TAM_NOME] = {
    "Prefixado",
    "IPCA+",
    "Selic",
    "CDI"
};

int isBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int diasNoMes(int mes, int ano) {
    switch (mes) {
        case 1: return 31; // Janeiro
        case 2: return isBissexto(ano) ? 29 : 28; // Fevereiro
        case 3: return 31; // Março
        case 4: return 30; // Abril
        case 5: return 31; // Maio
        case 6: return 30; // Junho
        case 7: return 31; // Julho
        case 8: return 31; // Agosto
        case 9: return 30; // Setembro
        case 10: return 31; // Outubro
        case 11: return 30; // Novembro
        case 12: return 31; // Dezembro
        default: return 0; // Mês inválido
    }
}

Data getData() {
    int ano, mes, dia;
    
    printf("Digite o ano:\n> ");
    scanf("%d", &ano);
    while (ano <= 0) {
        printf("Ano inválido. Por favor, insira um ano positivo.\n");
        scanf("%d", &ano);
        while (getchar() != '\n');
    }
    
    printf("Digite o mês (1-12):\n> ");
    scanf("%d", &mes);
    while (mes < 1 || mes > 12) {
        printf("Mês inválido. Por favor, insira um valor entre 1 e 12.\n");
        scanf("%d", &mes);
        while (getchar() != '\n');
    }

    printf("Digite o dia:\n> ");
    scanf("%d", &dia);
    int diasNoMesAtual = diasNoMes(mes, ano);
    while (dia < 1 || dia > diasNoMesAtual) {
        printf("Dia inválido. Por favor, digite um dia válido, entre 1 e %d.\n", diasNoMesAtual);
        scanf("%d", &dia);
        while (getchar() != '\n');
    }

    Data data = {dia, mes, ano};
    return data;
}

void removeNewline(char *str) {
    size_t length = strlen(str);

    // Verifica se a string não está vazia e se o último caractere é '\n'
    if (length > 0 && str[length - 1] == '\n') {
        str[length - 1] = '\0'; // Substitui '\n' por '\0'
    }
}

Pessoa criarFinanca() {
    Pessoa pessoa;
    float valor;
    int tipo;
    char nomeInv[TAM_NOME];
    char nomePessoa[TAM_NOME];
    printf("Digite a data de investimento\n");
    Data data = getData();
    printf("\nDigite o valor\n> ");
    scanf("%f", &valor);


    while (getchar() != '\n');    // Limpar o buffer de entrada
    
    printf("Digite o tipo de investimento (0 a 3)\n");
    printf("0- Prefixado\n");
    printf("1- IPCA+\n");
    printf("2- Selic\n");
    printf("3- CDI\n> ");
    scanf("%d", &tipo);
    while (tipo < 0 || tipo > 3) {
        printf("Inválido. Digite o tipo de investimento (0 a 3)\n> ");
        scanf("%d", &tipo);
    }
    
    printf("Digite o nome do investimento:\n> ");
    fgets(nomeInv, TAM_NOME, stdin);
    while (getchar() != '\n');    // Limpar o buffer de entrada

    printf("Digite o seu nome:\n> ");
    fgets(nomePessoa, TAM_NOME, stdin);

    removeNewline(nomeInv);
    removeNewline(nomePessoa);

    pessoa.quantFinancas = 0;
    pessoa.id = quantPessoas++;
    strcpy(pessoa.nome, nomePessoa);

    if (pessoa.quantFinancas < MAX_INVEST) {
        pessoa.financas[pessoa.quantFinancas].dataAplicacao = data;
        pessoa.financas[pessoa.quantFinancas].valorAplicado = valor;
        pessoa.financas[pessoa.quantFinancas].taxaJuros = 0.12;
        pessoa.financas[pessoa.quantFinancas].tipo = (TipoInvestimento)tipo;
        strcpy(pessoa.financas[pessoa.quantFinancas].nome, nomeInv);
        pessoa.quantFinancas++;
    } else {
        printf("Número máximo de finanças atingido.\n");
    }
    pessoas[pessoa.id] = pessoa;

    return pessoa;
}

void mostrarFinancasPessoas(Pessoa pessoa) {
    printf("Finanças de %s\n", pessoa.nome);

    for (int i = 0; i < pessoa.quantFinancas; i++) {
        printf("Nome da finança: %s\n", pessoa.financas[i].nome);
        printf("Tipo da finança: %s\n", tipoInvestimentoString[pessoa.financas[i].tipo]);
        printf("Valor aplicado na finança: %.2f\n", pessoa.financas[i].valorAplicado);
        printf("Data: %d/%d/%d\n\n", pessoa.financas[i].dataAplicacao.dia, pessoa.financas[i].dataAplicacao.mes, pessoa.financas[i].dataAplicacao.ano);
    }
}

void adicionarFinanca(int idPessoa) {
    if (idPessoa < 0 || idPessoa >= quantPessoas) {
        printf("ID de pessoa inválido.\n");
        return;
    }

    Pessoa *pessoa = &pessoas[idPessoa];

    if (pessoa->quantFinancas >= MAX_INVEST) {
        printf("Número máximo de finanças atingido.\n");
        return;
    }

    float valor;
    int tipo;
    char nomeInv[TAM_NOME];
    Data data;

    printf("Digite a data de investimento\n> ");
    data = getData();
    
    printf("\nDigite o valor\n> ");
    scanf("%f", &valor);
    
    while (getchar() != '\n');    // Limpar o buffer de entrada
    
    printf("Digite o tipo de investimento (0 a 3)\n");
    printf("0- Prefixado\n");
    printf("1- IPCA+\n");
    printf("2- Selic\n");
    printf("3- CDI\n> ");
    scanf("%d", &tipo);
    while (tipo < 0 || tipo > 3) {
        printf("Inválido. Digite o tipo de investimento (0 a 3)\n> ");
        scanf("%d", &tipo);
    }
    
    printf("Digite o nome do investimento:\n> ");
    fgets(nomeInv, TAM_NOME, stdin);
    removeNewline(nomeInv);
    
    // Adicionar a nova finança
    pessoa->financas[pessoa->quantFinancas].dataAplicacao = data;
    pessoa->financas[pessoa->quantFinancas].valorAplicado = valor;
    pessoa->financas[pessoa->quantFinancas].tipo = tipo;
    strcpy(pessoa->financas[pessoa->quantFinancas].nome, nomeInv);
    pessoa->quantFinancas++;
}

void modificarFinanca(int idPessoa, int indexFinanca) {
    if (idPessoa < 0 || idPessoa >= quantPessoas) {
        printf("ID de pessoa inválido.\n");
        return;
    }

    Pessoa *pessoa = &pessoas[idPessoa];

    if (indexFinanca < 0 || indexFinanca >= pessoa->quantFinancas) {
        printf("Índice de finança inválido.\n");
        return;
    }

    float valor;
    int tipo;
    char nomeInv[TAM_NOME];
    Data data;

    printf("Digite a nova data de investimento\n> ");
    data = getData();
    
    printf("\nDigite o novo valor\n> ");
    scanf("%f", &valor);
    
    // Limpar o buffer de entrada
    while (getchar() != '\n');
    
    printf("Digite o tipo de investimento (0 a 3)\n");
    printf("0- Prefixado\n");
    printf("1- IPCA+\n");
    printf("2- Selic\n");
    printf("3- CDI\n> ");
    scanf("%d", &tipo);
    while (tipo < 0 || tipo > 3) {
        printf("Inválido. Digite o tipo de investimento (0 a 3)\n> ");
        scanf("%d", &tipo);
    }
    
    printf("Digite o novo nome do investimento:\n> ");
    fgets(nomeInv, TAM_NOME, stdin);
    removeNewline(nomeInv);
    
    // Modificar a finança
    pessoa->financas[indexFinanca].dataAplicacao = data;
    pessoa->financas[indexFinanca].valorAplicado = valor;
    pessoa->financas[indexFinanca].tipo = tipo;
    strcpy(pessoa->financas[indexFinanca].nome, nomeInv);
}

// Funções de comparação para qsort
int compararPorData(const void *a, const void *b) {
    const Financeiro *fin1 = (const Financeiro *)a;
    const Financeiro *fin2 = (const Financeiro *)b;
    
    if (fin1->dataAplicacao.ano != fin2->dataAplicacao.ano) {
        return fin1->dataAplicacao.ano - fin2->dataAplicacao.ano;
    } else if (fin1->dataAplicacao.mes != fin2->dataAplicacao.mes) {
        return fin1->dataAplicacao.mes - fin2->dataAplicacao.mes;
    } else {
        return fin1->dataAplicacao.dia - fin2->dataAplicacao.dia;
    }
}

int compararPorTipo(const void *a, const void *b) {
    const Financeiro *fin1 = (const Financeiro *)a;
    const Financeiro *fin2 = (const Financeiro *)b;
    if (fin1->tipo < fin2->tipo) return -1;
    if (fin1->tipo > fin2->tipo) return 1;
    return 0;
}

int compararPorValor(const void *a, const void *b) {
    const Financeiro *fin1 = (const Financeiro *)a;
    const Financeiro *fin2 = (const Financeiro *)b;
    
    if (fin1->valorAplicado < fin2->valorAplicado) return -1;
    if (fin1->valorAplicado > fin2->valorAplicado) return 1;
    return 0;
}

int compararPorNome(const void *a, const void *b) {
    const Financeiro *fin1 = (const Financeiro *)a;
    const Financeiro *fin2 = (const Financeiro *)b;
    return strcmp(fin1->nome, fin2->nome);
}

// Funções de ordenação
void ordenarFinancasPorData(Pessoa *pessoa) {
    qsort(pessoa->financas, pessoa->quantFinancas, sizeof(Financeiro), compararPorData);
}

void ordenarFinancasPorTipo(Pessoa *pessoa) {
    qsort(pessoa->financas, pessoa->quantFinancas, sizeof(Financeiro), compararPorTipo);
}

void ordenarFinancasPorValor(Pessoa *pessoa) {
    qsort(pessoa->financas, pessoa->quantFinancas, sizeof(Financeiro), compararPorValor);
}

// Função de agrupamento e ordenação
void agruparEOrdenarFinancasData(Pessoa *pessoa) {
    // Ordenar por tipo primeiro
    qsort(pessoa->financas, pessoa->quantFinancas, sizeof(Financeiro), compararPorTipo);
    
    // Encontrar o início de cada grupo de tipo
    int i = 0;
    while (i < pessoa->quantFinancas) {
        int j = i;
        
        // Encontrar o fim do grupo de tipo
        while (j < pessoa->quantFinancas && pessoa->financas[i].tipo == pessoa->financas[j].tipo) {
            j++;
        }
        
        // Ordenar o grupo atual por data
        qsort(pessoa->financas + i, j - i, sizeof(Financeiro), compararPorData);
        
        // Mover para o próximo grupo
        i = j;
    }
}

void agruparEOrdenarFinancasValor(Pessoa *pessoa) {
    // Ordenar por tipo primeiro
    qsort(pessoa->financas, pessoa->quantFinancas, sizeof(Financeiro), compararPorTipo);
    
    // Encontrar o início de cada grupo de tipo
    int i = 0;
    while (i < pessoa->quantFinancas) {
        int j = i;
        
        // Encontrar o fim do grupo de tipo
        while (j < pessoa->quantFinancas && pessoa->financas[i].tipo == pessoa->financas[j].tipo) {
            j++;
        }
        
        // Ordenar o grupo atual por valor
        qsort(pessoa->financas + i, j - i, sizeof(Financeiro), compararPorValor);
        
        // Mover para o próximo grupo
        i = j;
    }
}


void exibirMenu() {
    printf("\nMenu:\n");
    printf("01. Criar nova pessoa e finança\n");
    printf("02. Adicionar finança a uma pessoa\n");
    printf("03. Modificar finança de uma pessoa\n");
    printf("04. Mostrar finanças de uma pessoa\n");
    printf("05. Ordenar finanças por data\n");
    printf("06. Ordenar finanças por tipo\n");
    printf("07. Ordenar finanças por valor\n");
    printf("08. Agrupar por tipo e ordenar por data\n");
    printf("09. Agrupar por tipo e ordenar por valor\n");
    printf("10. Atualizar investimento\n");
    printf("10. Exibir valor bruto total\n");
    printf("11. Exibir valor líquido total\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

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

    printf("%d\n", dataAtual.ano);
    printf("%d\n", dataAtual.mes);
    printf("%d\n", dataAtual.dia);
}

void atualizarInvestimento(Financeiro *financa) {

    atualizarDataAtual();
    
    financa->valorBruto = financa->valorAplicado;

    int dataAplicacaoEmDias = dateToDays(financa->dataAplicacao);
    int dataAtualEmDias = dateToDays(dataAtual);

    int diferencaDias = dataAtualEmDias - dataAplicacaoEmDias;

    double taxaDiaria = pow(financa->taxaJuros + 1, (double)1 / (double)365);
    financa->valorBruto = financa->valorBruto * pow(taxaDiaria, diferencaDias);

    float lucro = financa->valorBruto - financa->valorAplicado;
    financa->imposto = lucro * calcTaxaImposto(diferencaDias);

    printf("imposto: %.2f\n", financa->imposto);
    printf("Valor aplicado: %.2f\n", financa->valorAplicado);
    printf("valor bruto: %.2f\n", financa->valorBruto);
}

void imprimirValorBrutoTotal(Financeiro *financa) {
    printf("Valor bruto total: %.2f\n", financa->valorBruto);
}

void imprimirValorLiquidoTotal(Financeiro *financa) {
    printf("Valor líquido total: %.2f\n", financa->valorBruto-financa->imposto);
}

int main() {
    int opcao, idPessoa, indexFinanca;
    
    while (1) {
        exibirMenu();
        scanf("%d", &opcao);
        
        while (getchar() != '\n'); // Limpar o buffer de entrada

        switch (opcao) {
            case 0: {                // Sair
                printf("Saindo...\n");
                exit(0);
            }
            case 1: {                // Criar nova pessoa e finança
                criarFinanca();
                break;
            }
            case 2: {                // Adicionar finança a uma pessoa
                printf("Digite o ID da pessoa:\n> ");
                scanf("%d", &idPessoa);
                adicionarFinanca(idPessoa);
                break;
            }
            case 3: {                // Modificar finança de uma pessoa
                printf("Digite o ID da pessoa:\n> ");
                scanf("%d", &idPessoa);
                printf("Digite o índice da finança:\n> ");
                scanf("%d", &indexFinanca);
                modificarFinanca(idPessoa, indexFinanca);
                break;
            }
            case 4: {                // Mostrar finanças de uma pessoa
                printf("Digite o ID da pessoa:\n> ");
                scanf("%d", &idPessoa);
                if (idPessoa < 0 || idPessoa >= quantPessoas) {
                    printf("ID de pessoa inválido.\n");
                } else {
                    mostrarFinancasPessoas(pessoas[idPessoa]);
                }
                break;
            }
            case 5: {               // Ordenar finanças por data
                printf("Digite o ID da pessoa:\n> ");
                scanf("%d", &idPessoa);
                if (idPessoa < 0 || idPessoa >= quantPessoas) {
                    printf("ID de pessoa inválido.\n");
                } else {
                    ordenarFinancasPorData(&pessoas[idPessoa]);
                    mostrarFinancasPessoas(pessoas[idPessoa]);
                }
                break;
            }
            case 6: {                // Ordenar finanças por tipo
                printf("Digite o ID da pessoa:\n> ");
                scanf("%d", &idPessoa);
                if (idPessoa < 0 || idPessoa >= quantPessoas) {
                    printf("ID de pessoa inválido.\n");
                } else {
                    ordenarFinancasPorTipo(&pessoas[idPessoa]);
                    mostrarFinancasPessoas(pessoas[idPessoa]);
                }
                break;
            }
            case 7: {                // Ordenar finanças por valor
                printf("Digite o ID da pessoa:\n> ");
                scanf("%d", &idPessoa);
                if (idPessoa < 0 || idPessoa >= quantPessoas) {
                    printf("ID de pessoa inválido.\n");
                } else {
                    ordenarFinancasPorValor(&pessoas[idPessoa]);
                    mostrarFinancasPessoas(pessoas[idPessoa]);
                }
                break;
            }
            case 8: {                // Agrupar por tipo e ordenar por data
                printf("Digite o ID da pessoa:\n> ");
                scanf("%d", &idPessoa);
                if (idPessoa < 0 || idPessoa >= quantPessoas) {
                    printf("ID de pessoa inválido.\n");
                } else {
                    agruparEOrdenarFinancasData(&pessoas[idPessoa]);
                    mostrarFinancasPessoas(pessoas[idPessoa]);
                }
                break;
            }
            case 9: {                // Agrupar por tipo e ordenar por valor
                printf("Digite o ID da pessoa:\n> ");
                scanf("%d", &idPessoa);
                if (idPessoa < 0 || idPessoa >= quantPessoas) {
                    printf("ID de pessoa inválido.\n");
                } else {
                    agruparEOrdenarFinancasValor(&pessoas[idPessoa]);
                    mostrarFinancasPessoas(pessoas[idPessoa]);
                }
                break;
            }
            case 10: {              // atualizar investimento
                printf("Digite o ID da pessoa:\n> ");
                scanf("%d", &idPessoa);
                printf("Digite o índice da finança:\n> ");
                scanf("%d", &indexFinanca);
                atualizarInvestimento(&pessoas[idPessoa].financas[indexFinanca]);
                break;
            }
            case 11: {              // valor bruto total
                printf("Digite o ID da pessoa:\n> ");
                scanf("%d", &idPessoa);
                printf("Digite o índice da finança:\n> ");
                scanf("%d", &indexFinanca);
                imprimirValorBrutoTotal(&pessoas[idPessoa].financas[indexFinanca]);
                break;
            }
            case 12: {              // valor bruto total
                printf("Digite o ID da pessoa:\n> ");
                scanf("%d", &idPessoa);
                printf("Digite o índice da finança:\n> ");
                scanf("%d", &indexFinanca);
                imprimirValorLiquidoTotal(&pessoas[idPessoa].financas[indexFinanca]);
                break;
            }
            default: {
                printf("Opção inválida. Tente novamente.\n");
                break;
            }
        }
    }

    return 0;
}