/**
Considere uma árvore AVL com matricula e nome, cuja estrutura pode ser essa:

typedef struct ARV{
    int mat;
    char nome[STRMAX+1];
    int bal;
    struct ARV *e;
    struct ARV *d;
} AVL;

A chave é a matricula.

Faça um programa em C com as seguintes funções:

percurso em ordem, pos ordem e pre-ordem
busca por uma determinada matricula
busca por um nome
inserção na árvore
calculo do balanceamento após a inserção
remoção de todos os nós


Não se preocupe em balancear a AVL. Ainda não vimos isso. Apenas manter o fb atualizado.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRMAX 50

typedef struct ARV{
    int mat;
    char nome[STRMAX+1];
    int bal;
    struct ARV *e;
    struct ARV *d;
} AVL;


int altura(AVL* no) {
    if (no == NULL) return 0;
    int alt_e = altura(no->e);
    int alt_d = altura(no->d);
    return 1 + (alt_e > alt_d ? alt_e : alt_d);
}

void atualizar_bal(AVL* no) {
    if (no != NULL) {
        no->bal = altura(no->d) - altura(no->e);
    }
}

AVL* inserir(AVL* raiz, int mat, char* nome) {
    if (raiz == NULL) {
        AVL* novo = (AVL*)malloc(sizeof(AVL));
        novo->mat = mat;
        strcpy(novo->nome, nome);
        novo->bal = 0;
        novo->e = NULL;
        novo->d = NULL;
        return novo;
    }
    if (mat < raiz->mat) {
        raiz->e = inserir(raiz->e, mat, nome);
    } else if (mat > raiz->mat) {
        raiz->d = inserir(raiz->d, mat, nome);
    } else {
        return raiz;
    }

    atualizar_bal(raiz);
    return raiz;
}

void em_ordem(AVL* raiz) {
    if (raiz != NULL) {
        em_ordem(raiz->e);
        printf("Mat: %d, Nome: %s, Bal: %d\n", raiz->mat, raiz->nome, raiz->bal);
        em_ordem(raiz->d);
    }
}

void pre_ordem(AVL* raiz) {
    if (raiz != NULL) {
        printf("Mat: %d, Nome: %s, Bal: %d\n", raiz->mat, raiz->nome, raiz->bal);
        pre_ordem(raiz->e);
        pre_ordem(raiz->d);
    }
}

void pos_ordem(AVL* raiz) {
    if (raiz != NULL) {
        pos_ordem(raiz->e);
        pos_ordem(raiz->d);
        printf("Mat: %d, Nome: %s, Bal: %d\n", raiz->mat, raiz->nome, raiz->bal);
    }
}

AVL* busca_mat(AVL* raiz, int mat) {
    if (raiz == NULL || raiz->mat == mat) {
        return raiz;
    }
    if (mat < raiz->mat) {
        return busca_mat(raiz->e, mat);
    } else {
        return busca_mat(raiz->d, mat);
    }
}

AVL* busca_nome(AVL* raiz, char* nome) {
    if (raiz == NULL) return NULL;
    if (strcmp(raiz->nome, nome) == 0) return raiz;
    AVL* res = busca_nome(raiz->e, nome);
    if (res != NULL) return res;
    return busca_nome(raiz->d, nome);
}

void liberar_arvore(AVL* raiz) {
    if (raiz != NULL) {
        liberar_arvore(raiz->e);
        liberar_arvore(raiz->d);
        free(raiz);
    }
}

int main() {
    AVL* raiz = NULL;

    raiz = inserir(raiz, 10, "Joao");
    raiz = inserir(raiz, 5, "Maria");
    raiz = inserir(raiz, 15, "Antonio");
    raiz = inserir(raiz, 3, "Carlos");
    raiz = inserir(raiz, 7, "Jose");

    printf("Percurso em ordem:\n");
    em_ordem(raiz);

    printf("\nPercurso pré-ordem:\n");
    pre_ordem(raiz);

    printf("\nPercurso pós-ordem:\n");
    pos_ordem(raiz);

    AVL* encontrado = busca_mat(raiz, 7);
    if (encontrado) {
        printf("\nEncontrado por mat 7: %s\n", encontrado->nome);
    }

    encontrado = busca_nome(raiz, "Carlos");
    if (encontrado) {
        printf("Encontrado por nome Carlos: mat %d\n", encontrado->mat);
    }

    liberar_arvore(raiz);

    return 0;
}
