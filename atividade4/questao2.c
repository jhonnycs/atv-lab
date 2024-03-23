#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    Código que gera dois tipos de senhas: senhas normais e senhas de prioridade.
    As senhas geradas serão armazenadas em vetores distintos, um para senhas normais,
    outro para senhas de prioridade.
    As senhas normais possuem 67% de chance de serem geradas, restando 33% de
    chance de ser gerada uma senha de prioridade.
    Para determinar qual o tipo de senha gerada, foi usado um RNG, onde a chance
    de sair um determinado número varia de acordo com a faixa de valores escolhida
    pra ele. Por exemplo: se o RNG gera números de 0 a 99, há 67% de chance de que
    um número gerado seja menor que 67, pois de 0 a 66, há 67 números, de um total
    de 100 números.
*/

void mostrarArray(int *array, int tamanhoArray);
int gerarNumeroAleatorio(int min, int max);
void gerarSenhas();
void mostrarSenhas();

#define NUMERO_SENHAS 10
#define NUMERO_SENHAS_GLOBAIS 1000

#define PORCENTAGEM_SENHA_NORMAL 67

int senhasNormais[NUMERO_SENHAS_GLOBAIS];
int senhasPrioridade[NUMERO_SENHAS_GLOBAIS];

int ultimaSenhaNormal = 0;
int ultimaSenhaPrioridade = 0;

int quantSenhasNormais = 0;
int quantSenhasPrioridade = 0;

int main() {
    srand(time(NULL));

    gerarSenhas();
    mostrarSenhas();

    return 0;
}

int gerarNumeroAleatorio(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

void mostrarArray(int *array, int tamanhoArray) {
    for (int i = 0; i < tamanhoArray; i++) {
        printf("%d  %s", array[i], i > 0 && ((i + 1) % 20 == 0) ? "\n" : "");
    }
}

void gerarSenhas() {
    for (int i = 0; i < NUMERO_SENHAS; i++) {
        int tipoSenha = gerarNumeroAleatorio(0, 99);

        if (tipoSenha < PORCENTAGEM_SENHA_NORMAL) {
            senhasNormais[quantSenhasNormais] = ++ultimaSenhaNormal;
            quantSenhasNormais++;
            
        } else {
            senhasPrioridade[quantSenhasPrioridade] = ++ultimaSenhaPrioridade;
            quantSenhasPrioridade++;
        }
    }
}

void mostrarSenhas() {
    printf("Senhas normais:\n");
    mostrarArray(senhasNormais, quantSenhasNormais);

    printf("\n\nSenhas de prioridade:\n");
    mostrarArray(senhasPrioridade, quantSenhasPrioridade);
    printf("\n\n");
}