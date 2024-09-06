#include <stdio.h>

/*
    Solicitar número inteiro e guardar em uma variável
    signed int, transformar o número com o modificador
    unsigned e imprimir.
*/

int main() {

    int num;

    printf("Digite um número inteiro:\n> ");
    scanf("%d", &num);

    unsigned numU = num;

    printf("\n%u\n\n", numU);

    /*
        Se tentarmos imprimir o numU e o valor for originalmente negativo,
        o número que aparece é esquisito. Isso ocorre porque ao atribuir
        um número negativo à variável, o valor da variável será na verdade
        o maior valor positivo possível menos o módulo do valor negativo
        atribuído +1 (já que o -1 seria exatamente o maior valor).
        Por exemplo (à esquerda o valor signed, à direita, unsigned):
        -1 = 4294967295
        -5 = 4294967291
        Basicamente ocorre um overflow, onde os números passam a voltar de 1
        em 1 começando do maior valor até chegar em 0.
    */
    
    return 0;
}
