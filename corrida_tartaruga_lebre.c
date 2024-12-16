#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct bloco {
    int posicao;
    char status;
    struct bloco *prox;
    struct bloco *ant;
} Bloco_t;

void exibirMenu(void);
void printPista(Bloco_t *pista);
void salvarPartida(const char *nome_arquivo, int rodada, Bloco_t *pista, Bloco_t *tartaruga, Bloco_t *lebre);
void moverAnimais(Bloco_t **tartaruga, Bloco_t **lebre, int sorteio);
void atualizarPista(Bloco_t *pista, Bloco_t *tartaruga, Bloco_t *lebre);
void abrirRelatorio(const char* nome_arquivo);

int main() {
    int rodada = 0;
    srand(time(NULL));

    Bloco_t *pista = malloc(sizeof(Bloco_t));
    Bloco_t *ptr1, *ptr2;
    pista->posicao = 1;
    pista->prox = NULL;
    pista->ant = pista;
    ptr1 = ptr2 = pista;

    for (int i = 2; i <= 20; i++) {
        ptr2 = ptr1;
        ptr1 = malloc(sizeof(Bloco_t));
        ptr1->posicao = i;
        ptr1->ant = ptr2;
        ptr2->prox = ptr1;
        ptr1->prox = NULL;
    }

    Bloco_t *tartaruga = pista;
    Bloco_t *lebre = pista;

    printf("Bem-vindo ao joguinho Tartaruga e Lebre! :D\n");
    int opcao;
    do {
        exibirMenu();
        scanf("%d", &opcao);

switch (opcao) {
            case 1:
                 if (tartaruga != NULL && lebre != NULL) {
                 int sorteio = rand() % 14 + 1;
                 printf("\nRodada %d:\n", rodada + 1);
                 moverAnimais(&tartaruga, &lebre, sorteio);
                 atualizarPista(pista, tartaruga, lebre);
                 printPista(pista);
                 salvarPartida("detalhes_partida.txt", rodada + 1, pista, tartaruga, lebre);

                 rodada++;

                 if (tartaruga != NULL && tartaruga->posicao >= 20) {
                 printf("A tartaruga venceu na rodada %d!\n", rodada);
                 break;
                 } else if (lebre != NULL && lebre->posicao >= 20) {
                 printf("A lebre venceu na rodada %d!\n", rodada);
                 break;
                 }
                 printf("Posicao da tartaruga: %d\n", tartaruga != NULL ? tartaruga->posicao : -1);
                 printf("Posicao da lebre: %d\n", lebre != NULL ? lebre->posicao : -1);
                 break;
            case 2:
                abrirRelatorio("detalhes_partida.txt");
                break;
            case 0:
                printf("Saindo do programa... T-T\nObrigado por jogar! :D\n");
                break;
            default:
                printf("Opção invalida. Tente novamente.\n");
        }
     }
    } while (opcao != 0);

    return 0;
}

void exibirMenu(void) {
    printf("\nMenu:\n");
    printf("1. Iniciar rodada ^-^\n");
    printf("2. Acessar relatorio dos arquivos O_o\n");
    printf("0. Sair D:\n");
    printf("Escolha uma opcao: ");
}

void printPista(Bloco_t *pista) {
    Bloco_t *atual = pista;
    while (atual != NULL) {
        printf("%c", atual->status);
        atual = atual->prox;
    }
    printf("\n");
}

void salvarPartida(const char *nome_arquivo, int rodada, Bloco_t *pista, Bloco_t *tartaruga, Bloco_t *lebre) {
    FILE *arquivo = fopen(nome_arquivo, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return;
    }
    fprintf(arquivo, "Rodada %d:\n", rodada);
    fprintf(arquivo, "Pista: ");
    Bloco_t *atual = pista;
    while (atual != NULL) {
        fprintf(arquivo, "%c", atual->status);
        atual = atual->prox;
    }
    fprintf(arquivo, "\n");
    fprintf(arquivo, "Posicao da tartaruga: %d\n", tartaruga != NULL ? tartaruga->posicao : -1);
    fprintf(arquivo, "Posicao da lebre: %d\n", lebre != NULL ? lebre->posicao : -1);
    fclose(arquivo);
}

void moverAnimais(Bloco_t **tartaruga, Bloco_t **lebre, int sorteio) {
    if (sorteio == 1) {
            printf("Numero sorteado: %d\n", sorteio);
            printf("Nenhum animal se move.\n");
    }
    if (sorteio >= 2 && sorteio <= 5 && *lebre != NULL) {
        *lebre = (*lebre)->prox;
         printf("Numero sorteado: %d\n", sorteio);
         printf("A lebre anda uma casa.\n");
    }
    if (sorteio >= 6 && sorteio <= 8 && *tartaruga != NULL) {
        *tartaruga = (*tartaruga)->prox;
        printf("Numero sorteado: %d\n", sorteio);
        printf("A tartaruga anda uma casa.\n");
    }
    if (sorteio >= 9 && sorteio <= 11) {
        if (*lebre != NULL && *tartaruga != NULL) {
            *lebre = (*lebre)->prox;
            *tartaruga = (*tartaruga)->prox;
            printf("Numero sorteado: %d\n", sorteio);
            printf("Ambos andam uma casa.\n");
        }
    }
    if (sorteio == 12 && *lebre != NULL) {
        *lebre = (*lebre)->prox->prox->prox;
        printf("Numero sorteado: %d\n", sorteio);
        printf("A lebre corre 3 casas.\n");
    }
    if (sorteio == 13 && *lebre != NULL) {
        *lebre = (*lebre)->ant;
        printf("Numero sorteado: %d\n", sorteio);
        printf("A lebre escorrega e volta uma casa!\n");
    }
    if (sorteio == 14) {
        if (*tartaruga != NULL) {
            *tartaruga = (*tartaruga)->prox->prox;
            printf("Numero sorteado: %d\n", sorteio);
            printf("A lebre dormiu! Tartaruga anda 2 casas.\n");
        }
    }
}

void atualizarPista(Bloco_t *pista, Bloco_t *tartaruga, Bloco_t *lebre) {
    Bloco_t *atual = pista;
    while (atual != NULL) {
        atual->status = '-';
        atual = atual->prox;
    }
    if (tartaruga != NULL) {
        tartaruga->status = 'T';
    }
    if (lebre != NULL) {
        lebre->status = 'L';
    }
}

void abrirRelatorio(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return;
    }
    char linha[100];
    printf("\nRelatorio das partidas:\n");
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);
    }
    fclose(arquivo);
}
