#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 20

// ======================================================
//   STRUCT PRINCIPAL DOS ITENS
//   ====================================================== 

struct Item{
    char nome[30];
    char tipo[20];
    int prioridade;
    int quantidade;
};

struct No{
    struct Item dado;
    struct No *prox;
};

// ======================================================
//   FUNCOES AUXILIARES DE INTERFACE
//   ====================================================== 

void exibirLinha(){
    printf("\n====================================================");
}

void exibirCabecalho(){
    exibirLinha();
    printf("\n     PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)");
    exibirLinha();
    printf("\n");
}

void exibirItem(struct Item item, int indice){
    printf("\n----------------------------------");
    printf("\nItem %d", indice + 1);
    printf("\n----------------------------------");
    printf("\nNome: %s", item.nome);
    printf("\nTipo: %s", item.tipo);
    printf("\nQuantidade: %d", item.quantidade);
    printf("\nPrioridade: %d\n", item.prioridade);
}

// ======================================================
//   INVENTARIO
//   ======================================================

void listarItens(struct Item mochila[], int totalItens){
    printf("\n===== INVENTARIO VETOR =====\n");

    if(totalItens == 0){
        printf("Inventario vazio.\n");
        return;
    }

    for(int i=0;i<totalItens;i++){
        exibirItem(mochila[i], i);
    }
}

int buscarItem(struct Item mochila[], int totalItens, char nome[]){
    int i;

    for(i=0;i<totalItens;i++){
        if(strcmp(mochila[i].nome,nome)==0){
            return i;
        }
    }

    return -1;
}

void cadastrarItem(struct Item mochila[], int *totalItens){
    if(*totalItens >= MAX_ITENS){
        printf("\nLimite maximo atingido.\n");
        return;
    }

    printf("\n===== CADASTRO DE COMPONENTE =====\n");

    printf("Nome: ");
    scanf(" %[^\n]", mochila[*totalItens].nome);

    printf("Tipo: ");
    scanf(" %[^\n]", mochila[*totalItens].tipo);

    printf("Quantidade: ");
    scanf("%d",&mochila[*totalItens].quantidade);

    printf("Prioridade (1-5): ");
    scanf("%d",&mochila[*totalItens].prioridade);

    (*totalItens)++;

    printf("\nComponente cadastrado com sucesso.\n");
}

void removerItem(struct Item mochila[], int *totalItens){
    char nome[30];

    printf("\nNome do componente a remover: ");
    scanf(" %[^\n]", nome);

    int pos = buscarItem(mochila,*totalItens,nome);

    if(pos == -1){
        printf("\nComponente nao encontrado.\n");
        return;
    }

    for(int i=pos;i<(*totalItens)-1;i++){
        mochila[i] = mochila[i+1];
    }

    (*totalItens)--;

    printf("\nComponente removido com sucesso.\n");
}

// ======================================================
//   ORDENACOES
//   ======================================================

long bubbleSortNome(struct Item mochila[], int total){
    long comparacoes = 0;
    struct Item aux;

    for(int i=0;i<total-1;i++){
        for(int j=0;j<total-1-i;j++){
            comparacoes++;

            if(strcmp(mochila[j].nome,mochila[j+1].nome)>0){
                aux = mochila[j];
                mochila[j] = mochila[j+1];
                mochila[j+1] = aux;
            }
        }
    }

    return comparacoes;
}

long insertionSortTipo(struct Item mochila[], int total){
    long comparacoes = 0;

    for(int i=1;i<total;i++){

        struct Item chave = mochila[i];
        int j = i - 1;

        while(j >= 0){
            comparacoes++;

            if(strcmp(mochila[j].tipo,chave.tipo)>0){
                mochila[j+1] = mochila[j];
                j--;
            }
            else{
                break;
            }
        }

        mochila[j+1] = chave;
    }

    return comparacoes;
}

long selectionSortPrioridade(struct Item mochila[], int total){
    long comparacoes = 0;
    struct Item aux;

    for(int i=0;i<total-1;i++){

        int menor = i;

        for(int j=i+1;j<total;j++){

            comparacoes++;

            if(mochila[j].prioridade < mochila[menor].prioridade){
                menor = j;
            }
        }

        aux = mochila[i];
        mochila[i] = mochila[menor];
        mochila[menor] = aux;
    }

    return comparacoes;
}

int buscaBinaria(struct Item mochila[], int total, char nome[]){
    int inicio = 0;
    int fim = total - 1;

    while(inicio <= fim){

        int meio = (inicio + fim)/2;
        int resultado = strcmp(mochila[meio].nome,nome);

        if(resultado == 0){
            return meio;
        }

        if(resultado < 0){
            inicio = meio + 1;
        }
        else{
            fim = meio - 1;
        }
    }

    return -1;
}

// ======================================================
//   LISTA ENCADEADA
//   ======================================================

void inserirLista(struct No **inicio, struct Item item){
    struct No *novo = (struct No*) malloc(sizeof(struct No));

    if(novo == NULL){
        printf("\nErro de memoria.\n");
        return;
    }

    novo->dado = item;
    novo->prox = *inicio;
    *inicio = novo;
}

void listarLista(struct No *inicio){
    printf("\n===== LISTA ENCADEADA =====\n");

    if(inicio == NULL){
        printf("Lista vazia.\n");
        return;
    }

    int contador = 1;

    while(inicio != NULL){
        exibirItem(inicio->dado, contador - 1);
        contador++;
        inicio = inicio->prox;
    }
}

// ======================================================
//   MAIN
//   ======================================================

int main(){

    struct Item mochila[MAX_ITENS];
    int totalItens = 0;

    struct No *lista = NULL;

    int opcao;
    int criterio;
    int ordenado = 0;

    long comparacoes;

    clock_t inicioTempo;
    clock_t fimTempo;

    double tempo;

    char nomeBusca[30];

    do{

        exibirCabecalho();

        printf("Itens na Mochila: %d/%d\n",totalItens,MAX_ITENS);
        printf("Status da Ordenacao por Nome: %s\n",
               ordenado ? "ORDENADO" : "NAO ORDENADO");

        printf("\n1. Adicionar Componente");
        printf("\n2. Descartar Componente");
        printf("\n3. Listar Componentes");
        printf("\n4. Organizar Mochila");
        printf("\n5. Busca Binaria");
        printf("\n6. Listar Lista Encadeada");
        printf("\n0. Sair");

        printf("\n\nEscolha: ");
        scanf("%d",&opcao);

        switch(opcao){

            case 1:

                cadastrarItem(mochila,&totalItens);

                if(totalItens > 0){
                    inserirLista(&lista, mochila[totalItens-1]);
                }

                ordenado = 0;
                break;

            case 2:

                removerItem(mochila,&totalItens);
                ordenado = 0;
                break;

            case 3:

                listarItens(mochila,totalItens);
                break;

            case 4:

                printf("\n1 - Bubble Sort (Nome)");
                printf("\n2 - Insertion Sort (Tipo)");
                printf("\n3 - Selection Sort (Prioridade)");
                printf("\nEscolha: ");
                scanf("%d",&criterio);

                inicioTempo = clock();

                if(criterio == 1){
                    comparacoes = bubbleSortNome(mochila,totalItens);
                    ordenado = 1;
                }
                else if(criterio == 2){
                    comparacoes = insertionSortTipo(mochila,totalItens);
                }
                else if(criterio == 3){
                    comparacoes = selectionSortPrioridade(mochila,totalItens);
                }
                else{
                    printf("\nOpcao invalida.\n");
                    break;
                }

                fimTempo = clock();

                tempo = ((double)(fimTempo - inicioTempo))/CLOCKS_PER_SEC;

                printf("\nComparacoes: %ld",comparacoes);
                printf("\nTempo: %.6f segundos\n",tempo);

                listarItens(mochila,totalItens);

                break;

            case 5:

                if(!ordenado){
                    printf("\nOrdene por nome primeiro.\n");
                    break;
                }

                printf("\nNome do componente: ");
                scanf(" %[^\n]",nomeBusca);

                {
                    int pos = buscaBinaria(mochila,totalItens,nomeBusca);

                    if(pos != -1){
                        exibirItem(mochila[pos],pos);
                    }
                    else{
                        printf("\nComponente nao encontrado.\n");
                    }
                }

                break;

            case 6:

                listarLista(lista);
                break;

            case 0:

                printf("\nMissao encerrada.\n");
                break;

            default:

                printf("\nOpcao invalida.\n");
        }

    }while(opcao != 0);

    return 0;
}
