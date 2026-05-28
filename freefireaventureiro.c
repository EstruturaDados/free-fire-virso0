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

// ===============================
// ORDENAÇÃO + BUSCA BINÁRIA
// ===============================

void ordenarItens(
struct Item mochila[],
int total
) {

    struct Item aux;

    for(
    int i=0;
    i<total-1;
    i++
    ) {

        for(
        int j=0;
        j<total-1-i;
        j++
        ) {

            if(
            strcmp(
            mochila[j].nome,
            mochila[j+1].nome
            ) > 0
            ) {

                aux=
                mochila[j];

                mochila[j]=
                mochila[j+1];

                mochila[j+1]=
                aux;
            }
        }
    }
}

int buscaBinaria(
struct Item mochila[],
int total,
char nome[]
) {

    int inicio=0;
    int fim=total-1;

    while(inicio<=fim) {

        int meio=
        (inicio+fim)/2;

        int comp=
        strcmp(
        mochila[meio].nome,
        nome
        );

        if(comp==0)
            return meio;

        if(comp<0)
            inicio=meio+1;

        else
            fim=meio-1;
    }

    return -1;
}

// ===============================
// FUNÇÕES DA LISTA ENCADEADA
// ===============================

// Inserção
void inserirLista(
struct No **inicio,
struct Item item
) {

    struct No *novo=
    malloc(sizeof(struct No));

    novo->dado=item;

    novo->prox=
    *inicio;

    *inicio=novo;
}

// Listagem
void listarLista(
struct No *inicio
) {

    printf(
    "\n===== LISTA ENCADEADA =====\n"
    );

    while(
    inicio!=NULL
    ) {

        printf(
        "\nNome: %s",
        inicio->dado.nome
        );

        printf(
        "\nTipo: %s",
        inicio->dado.tipo
        );

        printf(
        "\nQuantidade: %d\n",
        inicio->dado.quantidade
        );

        inicio=
        inicio->prox;
    }
}

// Busca
void buscarLista(
struct No *inicio,
char nome[]
) {

    while(
    inicio!=NULL
    ) {

        if(
        strcmp(
        inicio->dado.nome,
        nome
        )==0
        ) {

            printf(
            "\nEncontrado na lista!\n"
            );

            return;
        }

        inicio=
        inicio->prox;
    }

    printf(
    "\nNao encontrado\n"
    );
}
