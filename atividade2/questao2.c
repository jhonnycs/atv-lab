#include <stdio.h>

/*
    Implementar uma função que recebe dois números inteiros positivos
    e imprime o primeiro elevado ao segundo
*/

int pot(int num1, int num2);

int main() {

    int num1, num2;

    printf("Digite o número 1:\n> ");
    scanf("%d", &num1);

    while (num1 < 1) {
        printf("Digite um número positivo:\n> ");
        scanf("%d", &num1);
    }
    
    printf("Digite o número 2:\n> ");
    scanf("%d", &num2);

    while (num2 < 1) {
        printf("Digite um número positivo:\n> ");
        scanf("%d", &num2);
    }

    int resultPot = pot(num1, num2);

    printf("\n%d ^ %d = %d\n\n", num1, num2, resultPot);
    
    return 0;
}

int pot(int num1, int num2) {
    int multiplicador = num1;
    while (num2 > 1) {
        num1 = num1 * multiplicador;
        num2--;
    }
    return num1;
}