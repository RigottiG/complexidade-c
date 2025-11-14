#include "est.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    LIVRO livro;
    int ocupado;
} HASH;

unsigned int hashFunc(const char *titulo, int tamanho);
int inserirHash(HASH *tabela, int tamanho, LIVRO livro);
int buscarHash(HASH *tabela, int tamanho, const char *titulo);
int buscarSequencial(LIVRO *v, int n, const char *titulo);
int comparaTitulo(const void *a, const void *b);
int buscarBinaria(LIVRO *v, int n, const char *titulo);

int main(int argc, char *argv[])
{
    FILE *arqDAT;
    LIVRO *original, *ordenado;
    HASH *tabela;
    int qtd, i;

    if (argc < 2) {
        fprintf(stderr, "ERRO. Precisa passar nome arquivo txt\n");
        return (1);
    }
    if (!strstr(argv[1], ".txt")) {
        fprintf(stderr, "ERRO. Só aceito arquivos com extensão txt\n");
        return (1);
    }

    arqDAT = fopen(argv[1], "r");
    if (arqDAT == NULL) {
        fprintf(stderr, "ERRO. Não pude abrir %s para leitura\n", argv[1]);
        return (2);
    }

    if (fscanf(arqDAT, "%d", &qtd) != 1) {
        fprintf(stderr, "Não pude ler quantidade\n");
        exit(0);
    }

    original = malloc(qtd * sizeof(LIVRO));
    if (original == NULL) {
        fprintf(stderr, "Não pude alocar um vetor deste tamanho\n");
        return (1);
    }

    for (i = 0; i < qtd; i++) {
        if (feof(arqDAT)) break;
        if (lestringARQ(original[i].titulo, MAXTIT, arqDAT) < 1) break;
        if (fscanf(arqDAT, "%d", &original[i].cod) != 1) break;
        fgetc(arqDAT);
        if (lestringARQ(original[i].autor, MAXAUT, arqDAT) < 1) break;
    }
    fclose(arqDAT);

    printf("%d livros no arquivo %s\n\n", qtd, argv[1]);
    imp(original, qtd);

    int tamanhoHash = qtd * 2;
    tabela = calloc(tamanhoHash, sizeof(HASH));

    for (i = 0; i < qtd; i++) {
        inserirHash(tabela, tamanhoHash, original[i]);
    }

    ordenado = malloc(qtd * sizeof(LIVRO));
    memcpy(ordenado, original, qtd * sizeof(LIVRO));
    qsort(ordenado, qtd, sizeof(LIVRO), comparaTitulo);

    char tituloBusca[MAXTIT + 1];
    printf("\nDigite o título a buscar: ");
    lestringARQ(tituloBusca, MAXTIT, stdin);

    clock_t ini, fim;
    double tempo;

    ini = clock();
    int posSeq = buscarSequencial(original, qtd, tituloBusca);
    fim = clock();
    tempo = (double)(fim - ini) / CLOCKS_PER_SEC;
    if (posSeq >= 0)
        printf("\n[Sequencial] Encontrado: %s (%s) [%.6f s]\n",
               original[posSeq].titulo, original[posSeq].autor, tempo);
    else
        printf("\n[Sequencial] Não encontrado [%.6f s]\n", tempo);

    ini = clock();
    int posBin = buscarBinaria(ordenado, qtd, tituloBusca);
    fim = clock();
    tempo = (double)(fim - ini) / CLOCKS_PER_SEC;
    if (posBin >= 0)
        printf("[Binária]   Encontrado: %s (%s) [%.6f s]\n",
               ordenado[posBin].titulo, ordenado[posBin].autor, tempo);
    else
        printf("[Binária]   Não encontrado [%.6f s]\n", tempo);

    ini = clock();
    int posHash = buscarHash(tabela, tamanhoHash, tituloBusca);
    fim = clock();
    tempo = (double)(fim - ini) / CLOCKS_PER_SEC;
    if (posHash >= 0)
        printf("[Hash]      Encontrado: %s (%s) [%.6f s]\n",
               tabela[posHash].livro.titulo, tabela[posHash].livro.autor, tempo);
    else
        printf("[Hash]      Não encontrado [%.6f s]\n", tempo);

    free(original);
    free(ordenado);
    free(tabela);
    return 0;
}