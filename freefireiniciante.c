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