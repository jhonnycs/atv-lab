#include <stdio.h>
#include <stdlib.h>

#define SAIR 0
#define SOMA 1
#define SUBTRACAO 2
#define MULTIPLICACAO 3
#define DIVISAO 4
#define RESTO 5

void limparTerminal();
void soma();
void subtracao();
void multiplicacao();
void divisao();
void resto();

int main() {

    int opc;

    while (1) {
        limparTerminal();
        printf("Digite a opção que deseja:\n");
        printf("0- Sair do programa\n");
        printf("1- Soma:\n");
        printf("2- Subtração:\n");
        printf("3- Multiplicação:\n");
        printf("4- Divisão:\n");
        printf("5- Resto:\n> ");
    
        scanf("%d", &opc);

        while (opc < 0 || opc > 5) {
            printf("Por favor, digite uma opção válida\n> ");
            scanf("%d", &opc);
        }

        switch (opc) {
        case SAIR:
            limparTerminal();
            printf("Saindo...");
            return 0;
        case SOMA:
            soma();
            break;

        case SUBTRACAO:
            multiplicacao();
            break;
            
        case MULTIPLICACAO:
            multiplicacao();
            break;
        
        case DIVISAO:
            divisao();
            break;
        
        case RESTO:
            resto();
            break;
        }
        // esperar um input do usuário para que o terminal não seja limpo
        // antes que a resposta seja visualizada
        printf("Pressione enter para continuar ");
        getchar();
        getchar();
        // um dos getchar vai limpar o \n e o outro vai ser para esperar o usuário
        // presionar enter

    }
    return 0;
}

void limparTerminal() {
    printf("\033[H\033[J");
}

void soma() {
    int valor1, valor2;
    printf("Digite o valor 1:\n> ");
    scanf("%d", &valor1);

    printf("Digite o valor 2:\n> ");
    scanf("%d", &valor2);

    printf("\n%d + %d = %d\n\n", valor1, valor2, valor1 + valor2);
}

void subtracao() {
    int valor1, valor2;
    printf("Digite o valor 1:\n> ");
    scanf("%d", &valor1);

    printf("Digite o valor 2:\n> ");
    scanf("%d", &valor2);

    printf("\n%d - %d = %d\n\n", valor1, valor2, valor1 - valor2);
}

void multiplicacao() {
    int valor1, valor2;
    printf("Digite o valor 1:\n> ");
    scanf("%d", &valor1);

    printf("Digite o valor 2:\n> ");
    scanf("%d", &valor2);

    printf("\n%d x %d = %d\n\n", valor1, valor2, valor1 * valor2);
}

void divisao() {
    int valor1, valor2;
    printf("Digite o valor 1:\n> ");
    scanf("%d", &valor1);

    printf("Digite o valor 2:\n> ");
    scanf("%d", &valor2);

    if (valor2 == 0) {
        printf("Não é possível dividir por 0\n\n");
    } else {
        printf("\n%d / %d = %f\n\n", valor1, valor2, (float)valor1 / (float)valor2);
    }
}

void resto() {
    int valor1, valor2;
    printf("Digite o valor 1:\n> ");
    scanf("%d", &valor1);

    printf("Digite o valor 2:\n> ");
    scanf("%d", &valor2);

    printf("\n%d %% %d = %d\n\n", valor1, valor2, valor1 % valor2);
}
