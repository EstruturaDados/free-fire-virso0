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
// Busca sequencial
int buscarItem(struct Item mochila[], int totalItens, char nome[]) {

    for(int i=0;i<totalItens;i++) {

        if(strcmp(mochila[i].nome,nome)==0)
            return i;
    }

    return -1;
}

// Cadastro
void cadastrarItem(struct Item mochila[], int *totalItens) {

    if(*totalItens >= MAX_ITENS) {

        printf("\nLimite atingido!\n");
        return;
    }

    printf("\nNome: ");
    scanf(" %[^\n]", mochila[*totalItens].nome);

    printf("Tipo: ");
    scanf(" %[^\n]", mochila[*totalItens].tipo);

    printf("Quantidade: ");
    scanf("%d",&mochila[*totalItens].quantidade);

    (*totalItens)++;

    listarItens(mochila,*totalItens);
}

// Remover vetor
void removerItem(struct Item mochila[], int *totalItens) {

    char nome[30];

    printf("\nItem para remover: ");
    scanf(" %[^\n]",nome);

    int pos=
    buscarItem(
    mochila,
    *totalItens,
    nome
    );

    if(pos==-1) {

        printf("\nNao encontrado\n");
        return;
    }

    for(
    int i=pos;
    i<*totalItens-1;
    i++
    ) {

        mochila[i]=
        mochila[i+1];
    }

    (*totalItens)--;

    listarItens(
    mochila,
    *totalItens
    );
}