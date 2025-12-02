#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// -----------------------------------------------------
// STRUCT ITEM
// Armazena os dados essenciais de cada objeto do inventário
// -----------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// -----------------------------------------------------
// Protótipos das funções
// -----------------------------------------------------
void inserirItem(Item inventario[], int *qtd);
void removerItem(Item inventario[], int *qtd);
void listarItens(Item inventario[], int qtd);
void buscarItem(Item inventario[], int qtd);

int main() {
    Item inventario[MAX_ITENS];
    int qtdItens = 0;
    int opcao;

    do {
        printf("\n=== SISTEMA DE INVENTÁRIO ===\n");
        printf("1 - Inserir Item\n");
        printf("2 - Remover Item\n");
        printf("3 - Buscar Item\n");
        printf("4 - Listar Itens\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer

        switch (opcao) {
            case 1:
                inserirItem(inventario, &qtdItens);
                break;
            case 2:
                removerItem(inventario, &qtdItens);
                break;
            case 3:
                buscarItem(inventario, qtdItens);
                break;
            case 4:
                listarItens(inventario, qtdItens);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// -----------------------------------------------------
// INSERIR ITEM
// Adiciona um novo item ao inventário (máx. 10 itens)
// -----------------------------------------------------
void inserirItem(Item inventario[], int *qtd) {

    if (*qtd >= MAX_ITENS) {
        printf("Inventario cheio! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novo;

    printf("Digite o nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Digite o tipo (arma, municao, cura, etc.): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar(); // limpar buffer

    inventario[*qtd] = novo;
    (*qtd)++;

    printf("Item inserido com sucesso!\n");
    listarItens(inventario, *qtd);
}

// -----------------------------------------------------
// REMOVER ITEM
// Procura o item pelo nome e remove deslocando o vetor
// -----------------------------------------------------
void removerItem(Item inventario[], int *qtd) {
    char nomeBusca[30];
    int encontrado = -1;

    if (*qtd == 0) {
        printf("Inventario vazio! Nada para remover.\n");
        return;
    }

    printf("Digite o nome do item a remover: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < *qtd; i++) {
        if (strcmp(inventario[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Item nao encontrado!\n");
        return;
    }

    // Desloca os itens
    for (int i = encontrado; i < *qtd - 1; i++) {
        inventario[i] = inventario[i + 1];
    }

    (*qtd)--;

    printf("Item removido com sucesso!\n");
    listarItens(inventario, *qtd);
}

// -----------------------------------------------------
// LISTAR ITENS
// Exibe todos os itens cadastrados no inventário
// -----------------------------------------------------
void listarItens(Item inventario[], int qtd) {

    printf("\n=== LISTA DE ITENS ===\n");

    if (qtd == 0) {
        printf("Inventario vazio!\n");
        return;
    }

    for (int i = 0; i < qtd; i++) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, inventario[i].nome, inventario[i].tipo, inventario[i].quantidade);
    }
}

// -----------------------------------------------------
// BUSCAR ITEM
// Busca sequencial por nome
// -----------------------------------------------------
void buscarItem(Item inventario[], int qtd) {
    char nomeBusca[30];

    printf("Digite o nome do item para buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < qtd; i++) {
        if (strcmp(inventario[i].nome, nomeBusca) == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n",
                   inventario[i].nome,
                   inventario[i].tipo,
                   inventario[i].quantidade);
            return;
        }
    }

    printf("Item nao encontrado!\n");
}
