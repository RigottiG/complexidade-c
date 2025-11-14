/*
Um trabalho de programação feito em C:
O trabalho é uma implementação que envolva vetor com busca sequencial, binária e hash.
Envolve ler e escrever em arquivos.
Considere um programa de pesquisa de livros de uma biblioteca. Cada livro tem os seguintes dados:
titulo com até 100 caracteres
codigo um valor inteiro
autor com até 50 caractares

Aqui está a estrutura em C para armazenar um único livro:
#define MAXTIT 100 
#define MAXAUT 50
typedef struct {
   char titulo[MAXTIT + 1];
   int cod;
   char autor[MAXAUT + 1];
} LIVRO;
Seu programa irá ler muitos livros de um arquivo texto e cadastrar eles em estruturas vetor (já pense no tamanho do vetor):

vetor original com os dados sequenciais, como entraram, lidos do arquivo
outro vetor para pesquisa hash cuja chave é o título
Use uma função de hash adequada.
Implemente busca por titulo. Leia um titulo e procure no vetor usando busca sequencial e hash. Faça comparações de desempenho.
Não esqueça de realizar tratamento de colisões.
Exemplo de um arquivo TXT com os livros:

A primeira informação que tem no arquivo é a quantidade de livros (no caso 5)
Depois vem, na sequencia:
titulo
cod
autor
Um para cada um dos 5.
As quebras de linha adicionais podem não existir:
Mas sempre será um dado por linha.
A leitura de livros por um arquivo TXT é para testes. Porque tenho já arquivos com centenas de milhares de livros e seria IMPRATICÁVEL digitar todos eles. A leitura dos dados por arquivo substitui o cadastro do teclado.
*/