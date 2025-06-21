/*/*Objetivo:
 Desenvolver um sistema de registro de estudantes em C, utilizando TADs, Listas, Pilhas, Filas e
 Deques para gerenciar informações dos estudantes.
 Funcionalidades:
 1. Definição do TAD Estudante:
 Criar um TAD para representar as informações de um estudante, como nome, número
 de matrícula, notas, etc.
 2. Listas:
 Utilizar listas encadeadas para armazenar informações dos estudantes.
 Permitir adição, remoção e busca de estudantes na lista.
 3. Pilhas:
 Implementar uma pilha para armazenar históricos de notas de um estudante.
 Ao atualizar as notas, empilhar o histórico anterior.
 4. Filas:
 Utilizar uma fila para simular uma fila de espera de estudantes para matrícula em
 disciplinas.
 Adicionar estudantes à fila e remover quando matriculados.
 5. Deques:
 Utilizar um deque para gerenciar uma lista de espera para atendimento.
 Adicionar estudantes no início ou final da fila de espera.
 6. Funções adicionais:
 Implementar funções para calcular médias de notas de um estudante ou percorrer
 estruturas de dados.
 Exemplo de Estrutura do TAD:
 typedef struct { 
char nome[50]; 
int matricula; 
float notas[3];  // Supondo 3 notas por estudante 
} Estudante;
 Fluxo Geral do Programa:
 1. Inicialização:
Criar uma lista de estudantes vazia, uma pilha para históricos de notas, uma fila para
 matrículas e um deque para atendimentos.
 2. Adição de Estudantes:
 Permitir ao usuário adicionar novos estudantes à lista.
 3. Atualização de Notas:
 Ao atualizar as notas de um estudante, empilhar o histórico anterior, por disciplina.
 4. Matrícula em Disciplinas:
 Adicionar estudantes a uma fila de espera para matrícula em disciplinas.
 Remover estudantes da fila quando matriculados.
 5. Atendimento:
 Utilizar um deque para gerenciar uma lista de espera para atendimento.
 Adicionar estudantes no início ou final da fila de espera.
 6. Funções:
 Implementar funções para calcular médias de notas ou realizar operações específicas
 nos dados dos estudantes.
 Observações:
 Este projeto oferece uma abordagem prática para manipulação de dados de estudantes
 usando várias estruturas de dados.
 Explorem a eficiência das operações de inserção, remoção e busca em listas e deques,
 considerando os contextos específicos.
 Caso seja interessante, acrescentem uma opção para salvar os dados dos alunos, disciplinas
 e notas em arquivos.
 Experimentem as diferentes estruturas de dados e a implementem suas próprias funções
 recursivas ou não para aprofundar a compreensão dos conceitos.*/
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