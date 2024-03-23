#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    O código é um guichê de senhas.
    
    Funcionamento:

    Quando o programa iniciar, será mostrado um menu com 4 opções (uma extra):
    0- sair do programa
    1- gerar 10 senhas
    2- consumir uma senha
    3- mostrar as senhas atuais

    Ao selecionar 1, o switch vai chamar a função de gerar senhas. Essa função irá
    usar um RNG para determinar a chance de que a senha gerada seja uma senha normal
    ou uma senha de prioridade. Há 67% de chance de ser gerada uma senha normal e 33%
    de chance de sair uma senha de prioridade. As senhas irão começar ambas em 1.

    Ao selecionar 2, o switch vai chamar a função de consumir uma senha.
    O código começa sempre consumindo uma senha normal. Ao consumir uma senha normal,
    o tipo de senha a ser consumido será trocado. Esse tipo será armazenado na variável
    tipoSenha.
    Para consumir uma senha, é verificado o tipo de senha e se esse tipo de
    senha está disponível (ou seja, se há a senha), o que é feito comparando o ponteiro
    das senhas e a última posição das senhas. Caso uma se esgote, apenas o outro tipo será
    consumido.
    O consumo de senhas é feito fazendo o ponteiro de senhas apontar para a senha seguinte,
    ou seja, a senha anterior não é retirada da memória, apenas não aparece quando a função
    mostrar senhas é chamada.

    Ao selecionar 3, a função de mostrar senhas irá percorrer cada um dos arrays de senhas
    individualmente. Será usado o ponteiro de senhas para começar a percorrer, assim não
    serão mostradas as senhas já consumidas. O for vai percorrer as senhas de i=ponteiro até
    i < posUltimaSenha.
*/

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

// quantidade de senhas geradas a cada chamada de gerarSenhas()
#define NUMERO_SENHAS 10

// quantidade de senhas de cada tipo que podem ser armazenadas
#define NUMERO_SENHAS_GLOBAIS 1000

// porcentagem de senhas que serão rotuladas como normal
#define PORCENTAGEM_SENHA_NORMAL 67

// armazenam qual foi a última senha atribuída a cada um dos tipos de senha
int ultimaSenhaNormal = 0;
int ultimaSenhaPrioridade = 0;

// arrays para armazenar as senhas geradas
int senhasNormais[NUMERO_SENHAS_GLOBAIS];
int senhasPrioridade[NUMERO_SENHAS_GLOBAIS];

// armazenam a última posição de cada senha armazenada + 1
// + 1 porque só depois de armazenar ela é incrementada, sendo assim ficará com 1 a mais
int posUltimaSenhaNormal = 0;
int posUltimaSenhaPrioridade = 0;

// apontam paraa próxima senha a ser consumida
int ponteiroSenhasNormais = 0;
int ponteiroSenhasPrioridade = 0;

// uma maneira mais fácil de visualizar o tipo de senha
// será usado em consumirSenha()
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
        printf("1- Gerar 10 senhas:\n");
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

        int numeroAleatorio = gerarNumeroAleatorio(0, 99);
        
        if (numeroAleatorio < PORCENTAGEM_SENHA_NORMAL) {
            // se o vetor ainda tem espaço pra armazenar senhas
            if (posUltimaSenhaNormal < NUMERO_SENHAS_GLOBAIS) {
                senhasNormais[posUltimaSenhaNormal] = ++ultimaSenhaNormal;
                posUltimaSenhaNormal++;
            }
        } else {
            if (posUltimaSenhaPrioridade < NUMERO_SENHAS_GLOBAIS) {
                senhasPrioridade[posUltimaSenhaPrioridade] = ++ultimaSenhaPrioridade;
                posUltimaSenhaPrioridade++;
            }
        }
    }
    printf("\nSenhas geradas\n\n");
}

void consumirSenha() {
    // se a senha for do tipo normal e houver senhas do tipo normal
    if (tipoSenha == SENHA_NORMAL && ponteiroSenhasNormais < posUltimaSenhaNormal) {
        // consumir senha normal
        tipoSenha = SENHA_PRIORIDADE;
        ponteiroSenhasNormais++;
        printf("\n\nSenha normal %d consumida.\n\n", senhasNormais[ponteiroSenhasNormais-1]);
        return;
    }
    // se a senha for do tipo prioridade e houver senhas prioridade
    if (tipoSenha == SENHA_PRIORIDADE && ponteiroSenhasPrioridade < posUltimaSenhaPrioridade) {
        // consumir senha prioridade
        tipoSenha = SENHA_NORMAL;
        ponteiroSenhasPrioridade++;
        printf("\n\nSenha de prioridade %d consumida.\n\n", senhasPrioridade[ponteiroSenhasPrioridade-1]);
        return;
    }
    // se a senha for normal, não houver senhas normais mas houver senhas prioridade
    if (
        tipoSenha == SENHA_NORMAL &&
        ponteiroSenhasNormais >= posUltimaSenhaNormal &&
        ponteiroSenhasPrioridade < posUltimaSenhaPrioridade
    ) {
        // consumir senha prioridade
        ponteiroSenhasPrioridade++;
        printf("\n\nSenha de prioridade %d consumida.\n\n", senhasPrioridade[ponteiroSenhasPrioridade-1]);
        return;
    }
    // se a senha for prioridade, não houver prioridade mas houver senhas normais
    if (
        tipoSenha == SENHA_PRIORIDADE &&
        ponteiroSenhasPrioridade >= posUltimaSenhaPrioridade  &&
        ponteiroSenhasNormais < posUltimaSenhaNormal
    ) {
        // comsumir senha normal
        ponteiroSenhasNormais++;
        printf("\n\nSenha normal %d consumida.\n\n", senhasNormais[ponteiroSenhasNormais-1]);
        return;
    }

    printf("\n\nNão há senhas para serem consumidas.\n\n");
}

void mostrarSenhas() {
    if (posUltimaSenhaNormal > 0 && ponteiroSenhasNormais < posUltimaSenhaNormal) {
        printf("Senhas normais:\n");
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