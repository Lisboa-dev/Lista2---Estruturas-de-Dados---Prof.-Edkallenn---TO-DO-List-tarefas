
#include <stdlib.h>
#include <stdio.h>
#include "registroEstudantes.h"

int main() {
    int opcao;
    Tarefa t;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Adicionar tarefa (início)\n");
        printf("2. Adicionar tarefa (fim)\n");
        printf("3. Exibir tarefas To-Do\n");
        printf("4. Concluir tarefa (mover para pilha)\n");
        printf("5. Agendar tarefa\n");
        printf("6. Contar tarefas (recursivo)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch (opcao) {
            case 1:
            case 2:
                printf("Descricao: ");
                fgets(t.descricao, MAX_DESC, stdin);
                t.descricao[strcspn(t.descricao, "\n")] = 0;
                printf("Prioridade (1-3): ");
                scanf("%d", &t.prioridade);
                printf("Data de vencimento (DDMMYYYY): ");
                scanf("%d", &t.dataVencimento);
                if (opcao == 1)
                    adicionarTarefaInicio(t);
                else
                    adicionarTarefaFim(t);
                break;
            case 3:
                imprimirLista(listaToDo);
                break;
            case 4:
                if (listaToDo) {
                    NoLista *tmp = listaToDo;
                    listaToDo = tmp->prox;
                    empilharConclusao(tmp->tarefa);
                    free(tmp);
                    printf("Tarefa concluída e movida para a pilha.\n");
                } else {
                    printf("Nenhuma tarefa para concluir.\n");
                }
                break;
            case 5:
                printf("Descricao: ");
                fgets(t.descricao, MAX_DESC, stdin);
                t.descricao[strcspn(t.descricao, "\n")] = 0;
                printf("Prioridade (1-3): ");
                scanf("%d", &t.prioridade);
                printf("Data de vencimento (DDMMYYYY): ");
                scanf("%d", &t.dataVencimento);
                enfileirar(&filaAgendada, t);
                printf("Tarefa agendada.\n");
                break;
            case 6:
                printf("Total de tarefas na To-Do List: %d\n", contarTarefas(listaToDo));
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
