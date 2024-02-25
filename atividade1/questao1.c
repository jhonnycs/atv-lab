#include <stdio.h>

/*
    Solicitar um número inteiro ao usuário e mostrar
    esse número com 4 bits deslocados para a direita
*/

int main() {

    int num;

    printf("Digite um número inteiro:\n> ");
    scanf("%d", &num);

    num = num >> 4;

    printf("O número com 4 bits deslocados para a direita é: %d\n\n", num);

    return 0;
}
