#include <stdio.h>

/*
    Solicitar um número inteiro positivo e imprimir
    1 caso ele seja ímpar, e 0 caso ele seja par
*/

int main() {

    int num;

    printf("Digite um número inteiro positivo:\n> ");
    scanf("%d", &num);

    while (num <= 0) {
        printf("Por favor, digite um número inteiro positivo:\n> ");
        scanf("%d", &num);
    }

    printf("\n%d\n\n", num % 2);

    return 0;
}