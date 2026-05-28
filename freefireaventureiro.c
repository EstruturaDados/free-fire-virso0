#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// ===============================
// STRUCT PRINCIPAL DOS ITENS
// ===============================
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// ===============================
// LISTA ENCADEADA
// ===============================
struct No {
    struct Item dado;
    struct No *prox;
};

// ===============================
// FUNÇÕES DO VETOR (MOCHILA ORIGINAL)
// ===============================

// Listar itens do vetor
void listarItens(struct Item mochila[], int totalItens) {

    printf("\n===== MOCHILA VETOR =====\n");

    if(totalItens == 0) {
        printf("Mochila vazia\n");
        return;
    }

    for(int i=0;i<totalItens;i++) {

        printf("\nItem %d\n", i+1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }
}
