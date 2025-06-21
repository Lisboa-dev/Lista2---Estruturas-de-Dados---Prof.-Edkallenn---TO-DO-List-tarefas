 /* 
**  Função :    to-do list tarefas
**  Autor : Matheus Lira Lisboa
**  Data  : 14/06/2025
**  Observações:  
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DESC 100

// -------------------- TAD ---------------------
typedef struct {
    char descricao[MAX_DESC];
    int prioridade;         // 1 = baixa, 2 = média, 3 = alta
    int dataVencimento;     // formato DDMMYYYY
} Tarefa;

// ----------------- Lista Encadeada -----------------
typedef struct NoLista {
    Tarefa tarefa;
    struct NoLista *prox;
} NoLista;

NoLista *listaToDo = NULL;

void adicionarTarefaInicio(Tarefa t) {
    NoLista *novo = malloc(sizeof(NoLista));
    novo->tarefa = t;
    novo->prox = listaToDo;
    listaToDo = novo;
}

void adicionarTarefaFim(Tarefa t) {
    NoLista *novo = malloc(sizeof(NoLista));
    novo->tarefa = t;
    novo->prox = NULL;
    if (listaToDo == NULL) {
        listaToDo = novo;
    } else {
        NoLista *aux = listaToDo;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
}

void imprimirLista(NoLista *l) {
    while (l != NULL) {
        printf("Tarefa: %s | Prioridade: %d | Vencimento: %d\n", l->tarefa.descricao, l->tarefa.prioridade, l->tarefa.dataVencimento);
        l = l->prox;
    }
}

// ----------------- Pilha ------------------
typedef struct NoPilha {
    Tarefa tarefa;
    struct NoPilha *ant;
} NoPilha;

NoPilha *pilhaConcluidas = NULL;

void empilharConclusao(Tarefa t) {
    NoPilha *novo = malloc(sizeof(NoPilha));
    novo->tarefa = t;
    novo->ant = pilhaConcluidas;
    pilhaConcluidas = novo;
}

// ----------------- Fila ------------------
typedef struct NoFila {
    Tarefa tarefa;
    struct NoFila *prox;
} NoFila;

typedef struct {
    NoFila *inicio, *fim;
} Fila;

Fila filaAgendada = {NULL, NULL};

void enfileirar(Fila *f, Tarefa t) {
    NoFila *novo = malloc(sizeof(NoFila));
    novo->tarefa = t;
    novo->prox = NULL;
    if (f->fim == NULL) {
        f->inicio = f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

Tarefa desenfileirar(Fila *f) {
    Tarefa invalida = {"", -1, -1};
    if (f->inicio == NULL) return invalida;
    NoFila *tmp = f->inicio;
    Tarefa t = tmp->tarefa;
    f->inicio = tmp->prox;
    if (f->inicio == NULL) f->fim = NULL;
    free(tmp);
    return t;
}

// ----------------- Deque ------------------
typedef struct NoDeque {
    Tarefa tarefa;
    struct NoDeque *ant, *prox;
} NoDeque;

typedef struct {
    NoDeque *inicio, *fim;
} Deque;

void inserirInicio(Deque *d, Tarefa t) {
    NoDeque *novo = malloc(sizeof(NoDeque));
    novo->tarefa = t;
    novo->ant = NULL;
    novo->prox = d->inicio;
    if (d->inicio != NULL) d->inicio->ant = novo;
    d->inicio = novo;
    if (d->fim == NULL) d->fim = novo;
}

void inserirFim(Deque *d, Tarefa t) {
    NoDeque *novo = malloc(sizeof(NoDeque));
    novo->tarefa = t;
    novo->prox = NULL;
    novo->ant = d->fim;
    if (d->fim != NULL) d->fim->prox = novo;
    d->fim = novo;
    if (d->inicio == NULL) d->inicio = novo;
}

void removerInicio(Deque *d) {
    if (d->inicio == NULL) return;
    NoDeque *tmp = d->inicio;
    d->inicio = tmp->prox;
    if (d->inicio != NULL) d->inicio->ant = NULL;
    else d->fim = NULL;
    free(tmp);
}

void removerFim(Deque *d) {
    if (d->fim == NULL) return;
    NoDeque *tmp = d->fim;
    d->fim = tmp->ant;
    if (d->fim != NULL) d->fim->prox = NULL;
    else d->inicio = NULL;
    free(tmp);
}

// ----------------- Recursivo ------------------
int contarTarefas(NoLista *l) {
    if (l == NULL) return 0;
    return 1 + contarTarefas(l->prox);
}
