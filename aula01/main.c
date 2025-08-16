#include <stdio.h>
#include <stdlib.h>

int busca_sequencial(int *vet, int tam, int valor, int *contador) {
    int i;
    for (i = 0; i < tam; i++) {
        (*contador)++;
        if (vet[i] == valor) {
            return i;
        }
    }
    return -1;
}

// fonte: https://www.geeksforgeeks.org/dsa/insertion-sort-algorithm/
void insertion_sort(int *vet, int tam) {
    for (int i = 1; i < tam; i++) {
        int chave = vet[i];
        int j = i - 1;

        while (j >= 0) {
            if (vet[j] > chave) {
                vet[j + 1] = vet[j];
                j--;
            } else {
                break;
            }
        }
        vet[j + 1] = chave;
    }
}

// fonte: https://github.com/MatheusGODZILLA/bubble-sort-e-busca-binaria-C
int busca_binaria(int *vet, int tam, int valor, int *contador) {
    int ini = 0, fim = tam - 1;
    while (ini <= fim) {
        int meio = ini + (fim - ini) / 2;
        (*contador)++;
        if (vet[meio] == valor) return meio;
        if (valor < vet[meio]) {
            fim = meio - 1;
        } else {
            ini = meio + 1;
        }
    }
    return -1;
}

int main() {
    int *vet;
    int tam = 0, i, valor;

    printf("Quantos elementos?\n");
    scanf("%d", &tam);
    if (tam <= 0) {
        printf("ERRO: tam tem que ser positivo\n");
        return 1;
    }

    vet = (int *) malloc(tam * sizeof(int));
    if (vet == NULL) {
        printf("ERRO na alocação de %d elementos\n", tam);
        return 2;
    }

    for (i = 0; i < tam; i++) {
        vet[i] = (tam - i) * 2;
    }

    printf("Digite um valor para buscar: ");
    scanf("%d", &valor);

    /* BUSCA SEQUENCIAL SEM ORDENACAO */
    int comp_seq = 0;
    int pos_seq = busca_sequencial(vet, tam, valor, &comp_seq);

    if (pos_seq != -1) {
        printf("[A] Valor encontrado (sequencial) na posicao %d\n", pos_seq);
    } else {
        printf("[A] Valor NAO encontrado (sequencial)\n");
    }
    printf("[A] Comparacoes realizadas: %d\n\n", comp_seq);

    /* ORDENACAO + BUSCA BINARIA */
    insertion_sort(vet, tam);

    int comp_bin = 0;
    int pos_bin = busca_binaria(vet, tam, valor, &comp_bin);

    if (pos_bin != -1) {
        printf("[B] Valor encontrado (binaria) na posicao %d\n", pos_bin);
    } else {
        printf("[B] Valor NAO encontrado (binaria)\n");
    }
    printf("[B] Comparacoes na BUSCA BINARIA: %d\n\n", comp_bin);

    free(vet);
    return 0;
}

/*
1) Quantos testes serão feitos para descobrir que um valor não existe no caso da versão A?
   - Na busca sequencial, no pior caso sera N comparações (onde N é o tamanho do vetor).
   - No caso médio, aproximadamente N/2.

2) E no caso da versão B? Mudou alguma coisa?
   - Na busca binária (vetor ordenado), no pior caso (valor ausente), serão feitas aproximadamente log2(N) comparações.
   A busca sequencial é O(N) e a binária é O(log N).

3) Percebe alguma lentidão no algoritmo à medida que o tamanho do vetor aumenta?
   - Sim. A ordenação com Insertion Sort tem custo O(N²), e como o vetor começa em ordem decrescente (pior caso),
   a ordenação se torna o gargalo quando N é grande. A busca binária em si continua muito rápida, mesmo para valores grandes.
*/