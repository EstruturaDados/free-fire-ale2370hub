#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

// ===========================================
// ==========      STRUCTS BÁSICAS   =========
// ===========================================

// Item armazenado na mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó para lista encadeada
typedef struct No {
    Item dados;
    struct No *proximo;
} No;


// ===========================================
// ========== CONTADORES DE COMPARAÇÃO =======
// ===========================================
int compSequencialVetor = 0;
int compBinariaVetor = 0;
int compSequencialLista = 0;


// ===========================================
// ==========       FUNÇÕES - VETOR  =========
// ===========================================

// Inserir item no vetor
void inserirItemVetor(Item vetor[], int *n) {
    if (*n >= MAX) {
        printf("Mochila (vetor) cheia!\n");
        return;
    }

    Item novo;

    printf("Nome: ");
    scanf("%s", novo.nome);

    printf("Tipo: ");
    scanf("%s", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    vetor[*n] = novo;
    (*n)++;

    printf("Item inserido no vetor!\n");
}

// Remover item do vetor
void removerItemVetor(Item vetor[], int *n) {
    if (*n == 0) {
        printf("Vetor vazio!\n");
        return;
    }

    char nome[30];
    printf("Nome do item para remover: ");
    scanf("%s", nome);

    for (int i = 0; i < *n; i++) {
        if (strcmp(vetor[i].nome, nome) == 0) {
            for (int j = i; j < *n - 1; j++)
                vetor[j] = vetor[j + 1];

            (*n)--;
            printf("Item removido!\n");
            return;
        }
    }

    printf("Item nao encontrado!\n");
}

// Listar itens do vetor
void listarItensVetor(Item vetor[], int n) {
    if (n == 0) {
        printf("Vetor vazio!\n");
        return;
    }

    printf("\n=== ITENS NO VETOR ===\n");
    for (int i = 0; i < n; i++)
        printf("%d) Nome: %s | Tipo: %s | Qtd: %d\n",
               i+1, vetor[i].nome, vetor[i].tipo, vetor[i].quantidade);
}

// Busca sequencial no vetor
int buscarSequencialVetor(Item vetor[], int n, char nome[]) {
    compSequencialVetor = 0;

    for (int i = 0; i < n; i++) {
        compSequencialVetor++;
        if (strcmp(vetor[i].nome, nome) == 0)
            return i;
    }

    return -1;
}

// Ordenação (Bubble Sort)
void ordenarVetor(Item vetor[], int n) {
    Item temp;
    int trocou;

    for (int i = 0; i < n - 1; i++) {
        trocou = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(vetor[j].nome, vetor[j+1].nome) > 0) {
                temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = temp;
                trocou = 1;
            }
        }
        if (!trocou) break;
    }

    printf("Vetor ordenado por nome!\n");
}

// Busca binária no vetor (após ordenar)
int buscarBinariaVetor(Item vetor[], int n, char nome[]) {
    compBinariaVetor = 0;
    int ini = 0, fim = n - 1, meio;

    while (ini <= fim) {
        meio = (ini + fim) / 2;
        compBinariaVetor++;

        int cmp = strcmp(nome, vetor[meio].nome);

        if (cmp == 0) return meio;
        if (cmp > 0) ini = meio + 1;
        else fim = meio - 1;
    }

    return -1;
}



// ===========================================
// ========    FUNÇÕES - LISTA ENCADEADA =====
// ===========================================

void inserirItemLista(No **lista) {
    No *novo = (No*) malloc(sizeof(No));

    printf("Nome: ");
    scanf("%s", novo->dados.nome);

    printf("Tipo: ");
    scanf("%s", novo->dados.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = *lista;
    *lista = novo;

    printf("Item inserido na lista!\n");
}

void removerItemLista(No **lista) {
    if (*lista == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    char nome[30];
    printf("Nome para remover: ");
    scanf("%s", nome);

    No *ant = NULL, *atual = *lista;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (ant == NULL)
                *lista = atual->proximo;
            else
                ant->proximo = atual->proximo;

            free(atual);
            printf("Item removido da lista!\n");
            return;
        }
        ant = atual;
        atual = atual->proximo;
    }

    printf("Item nao encontrado!\n");
}

void listarItensLista(No *lista) {
    if (lista == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    printf("\n=== ITENS NA LISTA ===\n");

    while (lista != NULL) {
        printf("Nome: %s | Tipo: %s | Qtd: %d\n",
               lista->dados.nome,
               lista->dados.tipo,
               lista->dados.quantidade);
        lista = lista->proximo;
    }
}

int buscarSequencialLista(No *lista, char nome[]) {
    compSequencialLista = 0;

    while (lista != NULL) {
        compSequencialLista++;
        if (strcmp(lista->dados.nome, nome) == 0)
            return 1;
        lista = lista->proximo;
    }

    return 0;
}


// ===========================================
// ================    MENU    ===============
// ===========================================
void menu() {
    printf("\n=== SISTEMA DE MOCHILA ===\n");
    printf("1 - Inserir Item (Vetor)\n");
    printf("2 - Remover Item (Vetor)\n");
    printf("3 - Listar Itens (Vetor)\n");
    printf("4 - Buscar Sequencial (Vetor)\n");
    printf("5 - Ordenar Vetor\n");
    printf("6 - Buscar Binaria (Vetor)\n");
    printf("7 - Inserir Item (Lista)\n");
    printf("8 - Remover Item (Lista)\n");
    printf("9 - Listar Itens (Lista)\n");
    printf("10 - Buscar Sequencial (Lista)\n");
    printf("0 - Sair\n");
}


// ===========================================
// ================= MAIN ====================
// ===========================================
int main() {
    Item vetor[MAX];
    int n = 0;

    No *lista = NULL;

    int opc;
    char nome[30];

    do {
        menu();
        printf("Escolha: ");
        scanf("%d", &opc);

        switch (opc) {

        case 1:
            inserirItemVetor(vetor, &n);
            break;

        case 2:
            removerItemVetor(vetor, &n);
            break;

        case 3:
            listarItensVetor(vetor, n);
            break;

        case 4:
            printf("Nome para buscar sequencial: ");
            scanf("%s", nome);
            if (buscarSequencialVetor(vetor, n, nome) != -1)
                printf("Item encontrado!\n");
            else
                printf("Nao encontrado.\n");

            printf("Comparacoes: %d\n", compSequencialVetor);
            break;

        case 5:
            ordenarVetor(vetor, n);
            break;

        case 6:
            printf("Nome para busca binaria: ");
            scanf("%s", nome);
            if (buscarBinariaVetor(vetor, n, nome) != -1)
                printf("Item encontrado!\n");
            else
                printf("Nao encontrado.\n");

            printf("Comparacoes: %d\n", compBinariaVetor);
            break;

        case 7:
            inserirItemLista(&lista);
            break;

        case 8:
            removerItemLista(&lista);
            break;

        case 9:
            listarItensLista(lista);
            break;

        case 10:
            printf("Nome para busca na lista: ");
            scanf("%s", nome);
            if (buscarSequencialLista(lista, nome))
                printf("Item encontrado!\n");
            else
                printf("Nao encontrado.\n");
            printf("Comparacoes: %d\n", compSequencialLista);
            break;

        }

    } while (opc != 0);

    return 0;
}
