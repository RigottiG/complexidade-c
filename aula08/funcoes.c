#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTIT 100
#define MAXAUT 50

typedef struct {
    char titulo[MAXTIT + 1];
    int cod;
    char autor[MAXAUT + 1];
} LIVRO;

typedef struct {
    LIVRO livro;
    int ocupado; // 0 = livre, 1 = ocupado
} HASH;

unsigned int hashFunc(const char *titulo, int tamanho) {
    unsigned int soma = 0;
    for (int i = 0; titulo[i] != '\0'; i++) {
        soma += tolower((unsigned char)titulo[i]);
    }
    return soma % tamanho;
}

int inserirHash(HASH *tabela, int tamanho, LIVRO livro) {
    unsigned int pos = hashFunc(livro.titulo, tamanho);
    unsigned int original = pos;

    while (tabela[pos].ocupado) {
        pos = (pos + 1) % tamanho;
        if (pos == original) return 0;
    }

    tabela[pos].livro = livro;
    tabela[pos].ocupado = 1;
    return 1;
}

int buscarHash(HASH *tabela, int tamanho, const char *titulo) {
    unsigned int pos = hashFunc(titulo, tamanho);
    unsigned int original = pos;

    while (tabela[pos].ocupado) {
        if (strcmp(tabela[pos].livro.titulo, titulo) == 0)
            return pos;
        pos = (pos + 1) % tamanho;
        if (pos == original)
            break;
    }
    return -1;
}

int buscarSequencial(LIVRO *v, int n, const char *titulo) {
    for (int i = 0; i < n; i++) {
        if (strcmp(v[i].titulo, titulo) == 0)
            return i;
    }
    return -1;
}

int comparaTitulo(const void *a, const void *b) {
    const LIVRO *x = (const LIVRO *)a;
    const LIVRO *y = (const LIVRO *)b;
    return strcmp(x->titulo, y->titulo);
}

int buscarBinaria(LIVRO *v, int n, const char *titulo) {
    int ini = 0, fim = n - 1, meio, cmp;
    while (ini <= fim) {
        meio = (ini + fim) / 2;
        cmp = strcmp(v[meio].titulo, titulo);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}
