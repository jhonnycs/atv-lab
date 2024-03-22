#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int *array, int tamanhoArray);
int gerarNumeroAleatorio(int min, int max);

void gerarSenhas();
void consumirSenha();
void mostrarSenhas();

#define SAIR 0
#define GERAR_SENHAS 1
#define CONSUMIR 2
#define MOSTRAR_SENHAS 3


#define NUMERO_SENHAS 10

#define VALOR_MINIMO 0
#define VALOR_MAXIMO 99

int ultimaSenhaNormal = 0;
int ultimaSenhaPrioridade = 1000;

int senhasNormais[NUMERO_SENHAS];
int senhasPrioridade[NUMERO_SENHAS];
int vetorTipoSenha[NUMERO_SENHAS];
int senhasTotais[NUMERO_SENHAS];

int ponteiroSenhasNormais = 0;
int ponteiroSenhasPrioridades = 0;
int quantSenhasTotais = 0;

int main() {
    srand(time(NULL));

    int opc;

    while (1) {
    
        printf("Digite a opção que deseja:\n");
        printf("0- Sair do programa\n");
        printf("1- Gerar senhas:\n");
        printf("2- Consumir:\n");
        printf("3- Mostrar as senhas:\n> ");
            
        scanf("%d", &opc);

        while (opc < 0 || opc > 3) {
            printf("Por favor, digite uma opção válida\n> ");
            scanf("%d", &opc);
        }

        switch (opc) {
        case SAIR:
            return 0;
        case GERAR_SENHAS:
            gerarSenhas();
            break;

        case CONSUMIR:
            consumirSenha();
            break;
            
        case MOSTRAR_SENHAS:
            mostrarSenhas();
            break;
        }
    }

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

void gerarSenhas() {
    for (int i = 0; i < NUMERO_SENHAS; i++) {
        quantSenhasTotais++;
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
}

int ultimaSenha = 0;
int quantSenhasNormais = ponteiroSenhasNormais;
int quantSenhasPrioridade = ponteiroSenhasPrioridades;

void consumirSenha() {

    if (ultimaSenha == 0) {
        ultimaSenha = 1;
        ponteiroSenhasNormais--;

    } else {
        ultimaSenha = 0;

    }
    
}

void mostrarSenhas() {
    printf("Senhas normais:\n ");
    printArray(senhasNormais, ponteiroSenhasNormais);
    printf("\n\n");

    printf("\nSenhas de prioridade\n");
    printArray(senhasPrioridade, ponteiroSenhasPrioridades);
    printf("\n\n");
}
