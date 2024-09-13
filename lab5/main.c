#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "getDados.h"
#include "gerenciarInv.h"
#include "calcInv.h"

Pessoa pessoas[MAX_PESSOAS];
Data dataAtual;
int quantPessoas = 0;
char tipoInvestimentoString[4][TAM_NOME] = {
    "Prefixado",
    "IPCA+",
    "Selic",
    "CDI"
};

float taxasInvestimentos[] = {
    
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
    printf("11. Exibir valor bruto total\n");
    printf("12. Exibir valor líquido total\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
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
