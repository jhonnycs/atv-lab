#include "getDados.h"

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

    printf("%s\n", nomeInv); 

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
        pessoa.financas[pessoa.quantFinancas].isUpToDate = 0;
        pessoa.quantFinancas++;
    } else {
        printf("Número máximo de finanças atingido.\n");
    }
    pessoas[pessoa.id] = pessoa;

    return pessoa;
}
