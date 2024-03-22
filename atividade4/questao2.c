#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int *array, int tamanhoArray);
int gerarNumeroAleatorio(int min, int max);

#define NUMERO_SENHAS 10

#define VALOR_MINIMO 0
#define VALOR_MAXIMO 99

int main() {
    srand(time(NULL));

    int ultimaSenhaNormal = 0;
    int ultimaSenhaPrioridade = 1000;

    int senhasNormais[NUMERO_SENHAS];
    int senhasPrioridade[NUMERO_SENHAS];

    int ponteiroSenhasNormais = 0;
    int ponteiroSenhasPrioridades = 0;


    for (int i = 0; i < NUMERO_SENHAS; i++) {
        int tipoSenha = gerarNumeroAleatorio(VALOR_MINIMO, VALOR_MAXIMO);
        printf("%d\n\n", tipoSenha);

        if (tipoSenha <= 66) {
            senhasNormais[ponteiroSenhasNormais] = ++ultimaSenhaNormal;
            ponteiroSenhasNormais++;
            
        } else {
            senhasPrioridade[ponteiroSenhasPrioridades] = ++ultimaSenhaPrioridade;
            ponteiroSenhasPrioridades++;
        }
    }

    printf("Senhas normais:\n ");
    printArray(senhasNormais, ponteiroSenhasNormais);

    printf("\nSenhas de prioridade\n");
    printArray(senhasPrioridade, ponteiroSenhasPrioridades);

    printf("\n\n");

    return 0;
}


void printArray(int *array, int tamanhoArray) {
    for (int i = 0; i < tamanhoArray; i++) {
        printf("%d  %s", array[i], i > 0 && ((i + 1) % 20 == 0) ? "\n" : "");
    }
}

int gerarNumeroAleatorio(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}
