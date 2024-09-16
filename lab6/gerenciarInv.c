#include "gerenciarInv.h"

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
    pessoas->financas[indexFinanca].isUpToDate = 0;
    strcpy(pessoa->financas[indexFinanca].nome, nomeInv);
}

void deletarFinanca(Pessoa *pessoa, int indexFinanca) {

    for (int i = indexFinanca; i < pessoa->quantFinancas - 1; i++) {
        pessoa->financas[i] = pessoa->financas[i + 1];
    }

    pessoa->quantFinancas--;

    printf("Finança no índice %d removida.\n", indexFinanca);
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

