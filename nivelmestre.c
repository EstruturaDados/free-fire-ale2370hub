#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

// ==========================================================
// ======================= STRUCT ===========================
// ==========================================================

// Componente necessário para montar a torre de fuga
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;


// ==========================================================
// ============ VARIÁVEIS PARA CONTAR OPERAÇÕES =============
// ==========================================================

long comparacoes = 0;


// ==========================================================
// ======================= FUNÇÕES ==========================
// ==========================================================

// ----------------------------------------------------------
// Exibir todos os componentes
// ----------------------------------------------------------
void mostrarComponentes(Componente v[], int n) {
    printf("\n=== LISTA DE COMPONENTES ===\n");
    for (int i = 0; i < n; i++) {
        printf("%2d) Nome: %-20s  Tipo: %-15s  Prioridade: %d\n",
            i+1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
}



// ----------------------------------------------------------
// BUBBLE SORT – Ordenar por nome (string)
// ----------------------------------------------------------
void bubbleSortNome(Componente v[], int n) {
    comparacoes = 0;
    Componente temp;

    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}



// ----------------------------------------------------------
// INSERTION SORT – Ordenar por tipo (string)
// ----------------------------------------------------------
