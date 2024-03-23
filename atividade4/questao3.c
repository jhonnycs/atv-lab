#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mostrarArray(int *array, int tamanhoArray, int ponteiroArray);
int gerarNumeroAleatorio(int min, int max);

void gerarSenhas();
void consumirSenha();
void mostrarSenhas();
void limparTerminal();

#define SAIR 0
#define GERAR_SENHAS 1
#define CONSUMIR 2
#define MOSTRAR_SENHAS 3

#define NUMERO_SENHAS 10
#define NUMERO_SENHAS_GLOBAIS 1000

#define VALOR_MINIMO 0
#define VALOR_MAXIMO 99

int ultimaSenhaNormal = 0;
int ultimaSenhaPrioridade = 1000;

int senhasNormais[NUMERO_SENHAS_GLOBAIS];
int senhasPrioridade[NUMERO_SENHAS_GLOBAIS];

int posUltimaSenhaNormal = 0;
int posUltimaSenhaPrioridade = 0;
int quantSenhasTotais = 0;

int ponteiroSenhasNormais = 0;
int ponteiroSenhasPrioridade = 0;

#define SENHA_NORMAL 0
#define SENHA_PRIORIDADE 1

int tipoSenha = 0; // armazenar qual será a próxima senha a ser retirada

int main() {
    srand(time(NULL));

    int opc;

    while (1) {
        limparTerminal();
        printf("Digite a opção que deseja:\n");
        printf("0- Sair do programa\n");
        printf("1- Gerar senhas:\n");
        printf("2- Consumir senha:\n");
        printf("3- Mostrar as senhas:\n> ");
            
        scanf("%d", &opc);

        while (opc < 0 || opc > 3) {
            printf("Por favor, digite uma opção válida\n> ");
            scanf("%d", &opc);
        }

        switch (opc) {
        case SAIR:
            limparTerminal();
            printf("Saindo...");
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

        printf("Pressione enter para continuar ");
        getchar();
        getchar();
    }

    return 0;
}

void mostrarArray(int *array, int tamanhoArray, int ponteiroArray) {
    for (int i = ponteiroArray; i < tamanhoArray; i++) {
        printf("%d  %s", array[i], i > 0 && ((i + 1) % 20 == 0) ? "\n" : "");
    }
}

int gerarNumeroAleatorio(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

void gerarSenhas() {
    for (int i = 0; i < NUMERO_SENHAS; i++) {

        int tipoSenha = gerarNumeroAleatorio(VALOR_MINIMO, VALOR_MAXIMO);

        if (tipoSenha <= 66) {
            if (posUltimaSenhaNormal <= NUMERO_SENHAS_GLOBAIS) {
                senhasNormais[posUltimaSenhaNormal] = ++ultimaSenhaNormal;
                posUltimaSenhaNormal++;
            }
        } else {
            if (posUltimaSenhaPrioridade <= NUMERO_SENHAS_GLOBAIS) {
                senhasPrioridade[posUltimaSenhaPrioridade] = ++ultimaSenhaPrioridade;
                posUltimaSenhaPrioridade++;
            }
        }
    }
    printf("\nSenhas geradas\n\n");
}

void consumirSenha() {
    if (tipoSenha == SENHA_NORMAL && ponteiroSenhasNormais < posUltimaSenhaNormal) {
        // consumir senha normal
        tipoSenha = SENHA_PRIORIDADE;
        ponteiroSenhasNormais++;
        printf("\n\nSenha normal consumida.\n\n");
        return;
    } 
    if (tipoSenha == SENHA_PRIORIDADE && ponteiroSenhasPrioridade < posUltimaSenhaPrioridade) {
        // consumir senha prioridade
        tipoSenha = SENHA_NORMAL;
        ponteiroSenhasPrioridade++;
        printf("\n\nSenha de prioridade consumida.\n\n");
        return;
    }
    if (
        tipoSenha == SENHA_NORMAL &&
        ponteiroSenhasNormais >= posUltimaSenhaNormal &&
        ponteiroSenhasPrioridade < posUltimaSenhaPrioridade
    ) {
        // consumir senha prioridade
        ponteiroSenhasPrioridade++;
        printf("\n\nSenha de prioridade consumida.\n\n");
        return;
    }
    if (
        tipoSenha == SENHA_PRIORIDADE &&
        ponteiroSenhasPrioridade >= posUltimaSenhaPrioridade  &&
        ponteiroSenhasNormais < posUltimaSenhaNormal
    ) {
        // comsumir senha normal
        ponteiroSenhasNormais++;
        printf("\n\nSenha normal consumida.\n\n");
        return;
    }

    printf("\n\nNão há senhas para serem consumidas.\n\n");
}

void mostrarSenhas() {
    if (posUltimaSenhaNormal > 0 && ponteiroSenhasNormais < posUltimaSenhaNormal) {
        printf("Senhas normais:\n ");
        mostrarArray(senhasNormais, posUltimaSenhaNormal, ponteiroSenhasNormais);
    } else {
        printf("\n\nNão há senhas normais\n\n");
    }
    
    if (posUltimaSenhaPrioridade > 0 && ponteiroSenhasPrioridade < posUltimaSenhaPrioridade) {
        printf("\n\nSenhas de prioridade:\n");
        mostrarArray(senhasPrioridade, posUltimaSenhaPrioridade, ponteiroSenhasPrioridade);
    } else {
        printf("\n\nNão há senhas de prioridade\n\n");
    }
    printf("\n\n");
}

void limparTerminal() {
    printf("\033[H\033[J");
}