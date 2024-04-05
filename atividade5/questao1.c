#include <stdio.h>


// Nomes: Jhonny Cunha Simões
//        Vinicius Celestino Rodrigues

int returnIndexFinalChar(char *str);

int main() {

    int quantPalavras;
    printf("Digite a quantidade de palavras:\n> ");
    scanf("%d", &quantPalavras);

    while (quantPalavras < 1) {
        printf("Digite um número válido de palavras:\n> ");
        scanf("%d", &quantPalavras);
    }
    getchar();
    char texto[1000];
    char palavras[quantPalavras][300];

    
    for (int i = 0; i < quantPalavras; i++) {
        printf("Digite a palavra %d\n> ", i+1);
        fgets(palavras[i], sizeof(palavras[i]), stdin);
    }

    printf("Digite um texto aí:\n> ");
    fgets(texto, sizeof(texto), stdin);

    printf("%s", texto);

    int tamanhoTexto = returnIndexFinalChar(texto);
    
    for (int i = 0; i < tamanhoTexto; i++) {

        for (int j = 0; j < quantPalavras; j++) {

            int tamanhoPalavra = returnIndexFinalChar(palavras[j]);
            
            if (texto[i] == palavras[j][0]) {
                
                int palavrasSaoIguais = 1;

                for (int k = 0; k < tamanhoPalavra; k++) {

                    if (texto[i + k] != palavras[j][k]) {
                        palavrasSaoIguais = 0;
                    }
                }

                if (palavrasSaoIguais &&
                    (
                        texto[i + tamanhoPalavra] == ' ' ||
                        texto[i + tamanhoPalavra] == ',' ||
                        texto[i + tamanhoPalavra] == '.' ||
                        texto[i + tamanhoPalavra] == '\n' ||
                        texto[i + tamanhoPalavra] == '\0'
                        ) &&
                        (
                            texto[i-1] == ' ' ||
                            texto[i-1] == ',' ||
                            texto[i-1] == '.' ||
                            texto[i-1] == '\n' ||
                            texto[i-1] == '\0'
                        )
                    ) {
                        for (int k = 0; k < tamanhoPalavra; k++) {
                            texto[i + k] = '*';
                        }
                }
            }
        }
    }

    printf("\n%s\n", texto);
    
    return 0;
}

int returnIndexFinalChar(char *str) {
    char c = 'a';
    int index = -1;
    while (c != '\0') {
        index++;
        c = str[index];
    }
    return index-1;
}
