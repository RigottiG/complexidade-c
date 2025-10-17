#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct AVL {
    int m;
    int bal;
    char n[80];
    struct AVL *esq;
    struct AVL *dir;
};

typedef struct AVL AVL;

AVL* busca_por_m(AVL *r, int m) {
    if (r == NULL) return NULL;
    if (r->m == m) return r;
    
    AVL *res = busca_por_m(r->esq, m);
    if (res) return res;
    return busca_por_m(r->dir, m);
}

AVL* busca_por_n(AVL *r, char *n) {
    if (r == NULL) return NULL;
    
    int cmp = strcmp(n, r->n);
    if (cmp == 0) return r;
    if (cmp < 0) return busca_por_n(r->esq, n);
    return busca_por_n(r->dir, n);
}

AVL* rotacao_direita(AVL *p) {
    AVL *u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    return u;
}

AVL* rotacao_esquerda(AVL *p) {
    AVL *v = p->dir;
    p->dir = v->esq;
    v->esq = p;
    return v;
}

AVL* rotacao_dupla_direita(AVL *p) {
    p->esq = rotacao_esquerda(p->esq);
    return rotacao_direita(p);
}

AVL* rotacao_dupla_esquerda(AVL *p) {
    p->dir = rotacao_direita(p->dir);
    return rotacao_esquerda(p);
}

int main() {
    AVL n1 = {10, 0, "maria", NULL, NULL};
    AVL n2 = {5, 0, "joao", NULL, NULL};
    AVL n3 = {15, 0, "pedro", NULL, NULL};
    AVL n4 = {3, 0, "ana", NULL, NULL};
    AVL n5 = {7, 0, "carlos", NULL, NULL};
    AVL n6 = {12, 0, "beatriz", NULL, NULL};
    AVL n7 = {18, 0, "daniel", NULL, NULL};
    AVL n8 = {1, 0, "elisa", NULL, NULL};
    AVL n9 = {20, 0, "fernanda", NULL, NULL};
    
    // Construindo a árvore como BST por n (ordem alfabética)
    // Raiz: joao
    // Esq: ana
    //   Dir: beatriz
    //     Dir: carlos
    //       Dir: daniel
    //         Dir: elisa
    //           Dir: fernanda
    // Dir: maria
    //   Dir: pedro
    
    n2.esq = &n4;  // joao.esq = ana
    n2.dir = &n1;  // joao.dir = maria
    n4.dir = &n6;  // ana.dir = beatriz
    n6.dir = &n5;  // beatriz.dir = carlos
    n5.dir = &n7;  // carlos.dir = daniel
    n7.dir = &n8;  // daniel.dir = elisa
    n8.dir = &n9;  // elisa.dir = fernanda
    n1.dir = &n3;  // maria.dir = pedro
    
    printf("=== BUSCA POR M ===\n");
    AVL *res = busca_por_m(&n2, 5);
    printf("  m=5: %s", res ? "encontrado" : "nao encontrado");
    if (res) printf(" (n=%s)", res->n);
    printf("\n");
    
    res = busca_por_m(&n2, 3);
    printf("  m=3: %s", res ? "encontrado" : "nao encontrado");
    if (res) printf(" (n=%s)", res->n);
    printf("\n");
    
    res = busca_por_m(&n2, 8);
    printf("  m=8: %s", res ? "encontrado" : "nao encontrado");
    if (res) printf(" (n=%s)", res->n);
    printf("\n");
    
    res = busca_por_m(&n2, 15);
    printf("  m=15: %s", res ? "encontrado" : "nao encontrado");
    if (res) printf(" (n=%s)", res->n);
    printf("\n");
    
    res = busca_por_m(&n2, 7);
    printf("  m=7: %s", res ? "encontrado" : "nao encontrado");
    if (res) printf(" (n=%s)", res->n);
    printf("\n");
    
    res = busca_por_m(&n2, 99);
    printf("  m=99: %s\n", res ? "encontrado" : "nao encontrado");
    
    printf("\n=== BUSCA POR N ===\n");
    
    res = busca_por_n(&n2, "joao");
    printf("  n=joao: %s", res ? "encontrado" : "nao encontrado");
    if (res) printf(" (m=%d)", res->m);
    printf("\n");
    
    res = busca_por_n(&n2, "maria");
    printf("  n=maria: %s", res ? "encontrado" : "nao encontrado");
    if (res) printf(" (m=%d)", res->m);
    printf("\n");
    
    res = busca_por_n(&n2, "ana");
    printf("  n=ana: %s", res ? "encontrado" : "nao encontrado");
    if (res) printf(" (m=%d)", res->m);
    printf("\n");
    
    res = busca_por_n(&n2, "carlos");
    printf("  n=carlos: %s", res ? "encontrado" : "nao encontrado");
    if (res) printf(" (m=%d)", res->m);
    printf("\n");
    
    res = busca_por_n(&n2, "pedro");
    printf("  n=pedro: %s", res ? "encontrado" : "nao encontrado");
    if (res) printf(" (m=%d)", res->m);
    printf("\n");
    
    res = busca_por_n(&n2, "beatriz");
    printf("  n=beatriz: %s", res ? "encontrado" : "nao encontrado");
    if (res) printf(" (m=%d)", res->m);
    printf("\n");
    
    res = busca_por_n(&n2, "daniel");
    printf("  n=daniel: %s", res ? "encontrado" : "nao encontrado");
    if (res) printf(" (m=%d)", res->m);
    printf("\n");
    
    res = busca_por_n(&n2, "elisa");
    printf("  n=elisa: %s", res ? "encontrado" : "nao encontrado");
    if (res) printf(" (m=%d)", res->m);
    printf("\n");
    
    res = busca_por_n(&n2, "fernanda");
    printf("  n=fernanda: %s", res ? "encontrado" : "nao encontrado");
    if (res) printf(" (m=%d)", res->m);
    printf("\n");
    
    res = busca_por_n(&n2, "gabriel");
    printf("  n=gabriel: %s\n", res ? "encontrado" : "nao encontrado");
    
    return 0;
}
