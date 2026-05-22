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

    // Função para buscar um item pelo nome
    int buscarItem(struct Item mochila[], int totalItens, const char *nomeBuscar) {
        for (int i = 0; i < totalItens; i++) {
            if (strcmp(mochila[i].nome, nomeBuscar) == 0) {
                return i;
            }
        }
        return -1;
}
}
// Função para remover um item da mochila
void removerItem(struct Item mochila[], int *totalItens) {
    char nomeRemover[30];

    if (*totalItens == 0) {
        printf("\nNao ha itens para remover.\n");
        return;
    }

    printf("\nDigite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nomeRemover);

    int posicao = buscarItem(mochila, *totalItens, nomeRemover);

    if (posicao == -1) {
        printf("\nItem nao encontrado.\n");
    } else {

        // Move os itens para preencher o espaço vazio
        for (int i = posicao; i < *totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }

        (*totalItens)--;

        printf("\nItem removido com sucesso!\n");
    }

    listarItens(mochila, *totalItens);
}
//função main principal contendo o menu da mochila 
int main() {

    struct Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao;

    do {

        printf("\n========= MOCHILA DE SOBREVIVENCIA =========\n");

        // Contador de itens na mochila
        printf("Itens armazenados: %d/%d\n", totalItens, MAX_ITENS);

        printf("1 - Cadastrar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("0 - Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

                switch (opcao) {

            case 1:
                cadastrarItem(mochila, &totalItens);
                break;

            case 2:
                removerItem(mochila, &totalItens);
                break;

            case 3:
                listarItens(mochila, totalItens);
                break;

            case 0:
                printf("\nEncerrando sistema...\n");
                break;

            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}