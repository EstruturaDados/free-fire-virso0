#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// Struct que representa um item da mochila
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};
// Função para listar todos os itens cadastrados
void listarItens(struct Item mochila[], int totalItens) {
    printf("\n========== MOCHILA ==========\n");

    if (totalItens == 0) {
        printf("A mochila esta vazia.\n");
    } else {
        for (int i = 0; i < totalItens; i++) {
            printf("\nItem %d\n", i + 1);
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
        }
    }

    printf("=============================\n");
}
// Função para cadastrar um novo item
void cadastrarItem(struct Item mochila[], int *totalItens) {

    if (*totalItens >= MAX_ITENS) {
        printf("\nA mochila esta cheia!\n");
        return;
    }

    printf("\n=== CADASTRO DE ITEM ===\n");

    printf("Nome do item: ");
    scanf(" %[^\n]", mochila[*totalItens].nome);

    printf("Tipo do item (arma, cura, municao...): ");
    scanf(" %[^\n]", mochila[*totalItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[*totalItens].quantidade);

    (*totalItens)++;

    printf("\nItem cadastrado com sucesso!\n");

    listarItens(mochila, *totalItens);
}