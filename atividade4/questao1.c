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
    printf("Digite a opção que deseja:\n");
    printf("Sair do programa - 0\n");
    printf("Soma: 1:\n");
    printf("Subtração: 2:\n");
    printf("Multiplicação: 3:\n");
    printf("Divisão: 4:\n");
    printf("Resto: 5:\n> ");
    
    scanf("%d", &opc);

    while (opc < 0 || opc > 5) {
        limparTerminal();
        printf("Por favor, digite uma opção válida\n> ");
        scanf("%d", &opc);
    }

    switch (opc) {
    case SAIR:
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

    printf("%d + %d = %d\n\n", valor1, valor2, valor1 + valor2);

}

void subtracao() {
    int valor1, valor2;
    printf("Digite o valor 1:\n> ");
    scanf("%d", &valor1);

    printf("Digite o valor 2:\n> ");
    scanf("%d", &valor2);

    printf("%d - %d = %d\n\n", valor1, valor2, valor1 - valor2);
}

void multiplicacao() {
    int valor1, valor2;
    printf("Digite o valor 1:\n> ");
    scanf("%d", &valor1);

    printf("Digite o valor 2:\n> ");
    scanf("%d", &valor2);

    printf("%d x %d = %d\n\n", valor1, valor2, valor1 * valor2);
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
        printf("%d / %d = %.2f\n\n", valor1, valor2, (float)valor1 / (float)valor2);
    }
}

void resto() {
    int valor1, valor2;
    printf("Digite o valor 1:\n> ");
    scanf("%d", &valor1);

    printf("Digite o valor 2:\n> ");
    scanf("%d", &valor2);

    printf("%d %% %d = %d\n\n", valor1, valor2, valor1 % valor2);
}
