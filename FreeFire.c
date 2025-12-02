#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    return 0;
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.


/*
    DESAFIO MESTRE – Torre de Fuga
    Executor: Zimmerman Santos

    Funcionalidades:
    - Cadastro de até 20 componentes
    - Ordenação por:
        (1) Nome          → Bubble Sort   (string)
        (2) Tipo          → Insertion Sort (string)
        (3) Prioridade    → Selection Sort (int)
    - Busca Binária por Nome (somente após ordenação por nome)
    - Medição de comparações e tempo com clock()
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

// ----------------------------------------------------------------------
// STRUCT DO COMPONENTE
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ----------------------------------------------------------------------
// FUNÇÃO PARA LIMPAR BUFFER DO TECLADO
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ----------------------------------------------------------------------
// CADASTRO DOS COMPONENTES
int cadastrarComponentes(Componente v[]) {
    int n;

    printf("Quantos componentes deseja cadastrar? (1 a 20): ");
    scanf("%d", &n);
    limparBuffer();

    if (n < 1 || n > MAX) {
        printf("Valor inválido.\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        printf("\n--- Componente %d ---\n", i + 1);

        printf("Nome: ");
        fgets(v[i].nome, 30, stdin);
        v[i].nome[strcspn(v[i].nome, "\n")] = '\0';

        printf("Tipo: ");
        fgets(v[i].tipo, 20, stdin);
        v[i].tipo[strcspn(v[i].tipo, "\n")] = '\0';

        printf("Prioridade (1 a 10): ");
        scanf("%d", &v[i].prioridade);
        limparBuffer();
    }
    return n;
}

// ----------------------------------------------------------------------
// EXIBIR COMPONENTES
void mostrarComponentes(Componente v[], int n) {
    printf("\n===== COMPONENTES =====\n");
    for (int i = 0; i < n; i++) {
        printf("%2d) Nome: %-20s Tipo: %-12s Prioridade: %d\n",
               i + 1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
    printf("=========================\n");
}

// ----------------------------------------------------------------------
// BUBBLE SORT – ORDENAR POR NOME
long bubbleSortNome(Componente v[], int n) {
    long comparacoes = 0;
    Componente aux;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
    return comparacoes;
}

// ----------------------------------------------------------------------
// INSERTION SORT – ORDENAR POR TIPO
long insertionSortTipo(Componente v[], int n) {
    long comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;

        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            v[j + 1] = v[j];
            j--;
        }
        if (j >= 0) comparacoes++;

        v[j + 1] = chave;
    }
    return comparacoes;
}

// ----------------------------------------------------------------------
// SELECTION SORT – ORDENAR POR PRIORIDADE
long selectionSortPrioridade(Componente v[], int n) {
    long comparacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        int menor = i;

        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade < v[menor].prioridade) {
                menor = j;
            }
        }

        if (menor != i) {
            Componente tmp = v[i];
            v[i] = v[menor];
            v[menor] = tmp;
        }
    }
    return comparacoes;
}

// ----------------------------------------------------------------------
// BUSCA BINÁRIA POR NOME (só funciona se estiver ordenado por nome)
int buscaBinariaPorNome(Componente v[], int n, char chave[]) {
    int ini = 0, fim = n - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;

        int cmp = strcmp(v[meio].nome, chave);

        if (cmp == 0) return meio;
        else if (cmp < 0) ini = meio + 1;
        else fim = meio - 1;
    }

    return -1;
}

// ----------------------------------------------------------------------
// MEDIR TEMPO DE UM ALGORITMO DE ORDENAÇÃO
void medirTempo(long (*algoritmo)(Componente[], int), Componente v[], int n, char nomeAlg[]) {
    Componente copia[MAX];
    memcpy(copia, v, sizeof(Componente) * n);

    clock_t inicio = clock();
    long comparacoes = algoritmo(copia, n);
    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n--- %s ---\n", nomeAlg);
    mostrarComponentes(copia, n);
    printf("Comparações: %ld\n", comparacoes);
    printf("Tempo: %.6f segundos\n", tempo);
}

// ----------------------------------------------------------------------
// MENU PRINCIPAL
int main() {
    Componente vetor[MAX];
    int n = 0;
    int ordenadoPorNome = 0;

    int opc;

    do {
        printf("\n===== TORRE DE FUGA – MENU =====\n");
        printf("1 - Cadastrar componentes\n");
        printf("2 - Ordenar por NOME (Bubble Sort)\n");
        printf("3 - Ordenar por TIPO (Insertion Sort)\n");
        printf("4 - Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("5 - Buscar componente por NOME (busca binária)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);
        limparBuffer();

        if (opc == 1) {
            n = cadastrarComponentes(vetor);

        } else if (opc == 2) {
            long comp = bubbleSortNome(vetor, n);
            ordenadoPorNome = 1;
            printf("\nOrdenado por NOME!\nComparações: %ld\n", comp);
            mostrarComponentes(vetor, n);

        } else if (opc == 3) {
            long comp = insertionSortTipo(vetor, n);
            ordenadoPorNome = 0;
            printf("\nOrdenado por TIPO!\nComparações: %ld\n", comp);
            mostrarComponentes(vetor, n);

        } else if (opc == 4) {
            long comp = selectionSortPrioridade(vetor, n);
            ordenadoPorNome = 0;
            printf("\nOrdenado por PRIORIDADE!\nComparações: %ld\n", comp);
            mostrarComponentes(vetor, n);

        } else if (opc == 5) {
            if (!ordenadoPorNome) {
                printf("\nERRO: a lista deve estar ordenada por NOME!\n");
            } else {
                char chave[30];
                printf("Digite o nome a buscar: ");
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = '\0';

                int pos = buscaBinariaPorNome(vetor, n, chave);

                if (pos == -1)
                    printf("\nComponente não encontrado!\n");
                else {
                    printf("\nComponente encontrado:\n");
                    printf("Nome: %s\nTipo: %s\nPrioridade: %d\n",
                           vetor[pos].nome, vetor[pos].tipo, vetor[pos].prioridade);
                }
            }
        }

    } while (opc != 0);

    printf("\nSistema finalizado.\n");
    return 0;
}
