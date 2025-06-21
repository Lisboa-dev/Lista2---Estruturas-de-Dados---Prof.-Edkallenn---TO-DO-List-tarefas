#ifndef TODO_H
#define TODO_H

#define MAX_DESC 100

// --------- TAD ---------
typedef struct {
    char descricao[MAX_DESC];
    int prioridade;
    int dataVencimento;
} Tarefa;

// --------- Lista Encadeada ---------
typedef struct NoLista {
    Tarefa tarefa;
    struct NoLista *prox;
} NoLista;

void adicionarTarefaInicio(Tarefa t);
void adicionarTarefaFim(Tarefa t);
void imprimirLista(NoLista *l);
int contarTarefas(NoLista *l);

// --------- Pilha ---------
typedef struct NoPilha {
    Tarefa tarefa;
    struct NoPilha *ant;
} NoPilha;

void empilharConclusao(Tarefa t);

// --------- Fila ---------
typedef struct NoFila {
    Tarefa tarefa;
    struct NoFila *prox;
} NoFila;

typedef struct {
    NoFila *inicio, *fim;
} Fila;

void enfileirar(Fila *f, Tarefa t);
Tarefa desenfileirar(Fila *f);

// --------- Deque ---------


typedef struct NoDeque {
    Tarefa tarefa;
    struct NoDeque *ant, *prox;
} NoDeque;

typedef struct{
       NoDeque *inicio, *fim;
} Deque;

void inserirInicio(Deque *d, Tarefa t);
void inserirFim(Deque *d, Tarefa t);
void removerInicio(Deque *d);
void removerFim(Deque *d);

#endif
