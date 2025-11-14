#include "est.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Programa inicial do trabalho.
 * 
 * */

int main(int argc, char *argv[])
{
    FILE *arqDAT;
    LIVRO *original;
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
    // primeira linha do arquivo deve ter a quantidade
    if (fscanf(arqDAT, "%d", &qtd) != 1) {
        fprintf(stderr, "Não pude ler quantidade\n");
        exit(0);
    }
    // Alocando o vetor de tamanho PRECISO para colocar todos os livros
    // CUIDADO: o vetor para pesquisa HASH deverá ter outro tamanho
    original = malloc(qtd * sizeof(LIVRO));
    if (original == NULL) {
        fprintf(stderr, "Não pude alocar um vetor deste tamanho\n");
        return (1);
    }
    // parte para ler os dados do arquivo. Sim, a construção do vetor
    // original já foi feita por mim. 
    for (i = 0; i < qtd; i++) {
        if (feof(arqDAT)) {
            fprintf(stderr, "Arquivo chegou ao fim sem ter todos os livros. Arquivo bugado?");
            qtd = i;
            break;
        }
        // arquivo tem, na ordem, titulo, cod e autor
        if (lestringARQ(original[i].titulo, MAXTIT, arqDAT) < 1) {
            fprintf(stderr, "Nao tem titulo. Arquivo bugado?");
            qtd = i;
            break;
        }
        if (fscanf(arqDAT, "%d", &original[i].cod) != 1) {
            fprintf(stderr, "Nao tem codigo. Arquivo bugado?");
            return (2);         // encerra
        }
        if (lestringARQ(original[i].autor, MAXAUT, arqDAT) < 1) {
            fprintf(stderr, "Nao tem autor. Arquivo bugado?");
            return (2);
        }
    }
    printf("%d livros no arquivo %s\n", qtd, argv[1]);

    /* Todos os livros do arquivo agora estão no vetor original na ordem em que foram
     * lidos do arquivo. 
     * */
    // debug: impressao so para ver
    imp(original, qtd);         // função imp está em est.h

    /* O que você precisa implementar agora?
     * 1) Criar um vetor para hashes:
     *         - a estrutura deve mudar, pois para hash deve ter campos a mais, como:
     *       - pelo menos um flag para livre ou ocupado
     *    
     * 2) Inserir cada livro no vetor de hashes na sua posição devida
     *         - definir o tamanho deste vetor
     *     - definir a função de hash
     * 3) testar o tempo para busca sequencial, binária e por hash
     * 
     * Você pode já fazer essa inserção no mesmo for onde é criado o vetor
     * original. O uso deste vetor (original) é apenas para dispensar a leitura
     * de arquivo e para ter a consulta sequencial como comparação
     * */
}
