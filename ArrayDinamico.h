#ifndef _ARRAYDINAMICO
#define _ARRAYDINAMICO

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

typedef struct arraydinamico *ArrayDinamico;

/*Funcao que cria um novo array dinamico*/
ArrayDinamico novoArrayDinamico (int tamanho, int tamanhoElem);

/*Funcao que realoca espaço para o array dinamico quando necessario. Tanto aumenta como diminui o tamanho do array*/
int realocarArrayDinamico (ArrayDinamico array, int novoTamanho);

/*Funcao que verifica se um dado elemento esta no array*/
int temElementoArray(ArrayDinamico array, void* elem, int (*compare)(void*, void*));

/*Funcao que procura um dado elemento e devolve a sua posição no array*/
int posicaoElementoArray(ArrayDinamico array, void* elem, int (*compare)(void*, void*));

/*Funcao que adiciona um elemento na proxima posicao disponivel ao array*/
int addElementoArray(ArrayDinamico array, void* elem);

/*Funcao que adiciona um elemento na proxima posicao disponivel mas apenas que ele ainda nao existir no array*/
int addNaoRepetidoArray(ArrayDinamico array, void* elem, int (*compare)(void*, void*));

/*Funcao que troca a posicao de dois elemento no array*/
void swapPosicoesArray(ArrayDinamico array, int p1, int p2);

/*Funcao que ordena o array de acordo com uma dada funcao de comparacao*/
void ordenaArrayDinamico(ArrayDinamico array, int (*compare)(const void*,const void*));

/*Funcao que remove um elemento do array trocando o elemento a remover pelo ultimo fornecendo a posicao do elemento no array*/
int removeElemSwapPosicaoArray(ArrayDinamico array, int pos);

/*Funcao que remove um elemento do array sem alterar a ordem fornecendo a posicao do elemento no array*/
int removeElemPosicaoArray(ArrayDinamico array, int pos);

/*Funcao que remove um dado elemento do array sem alterar a ordem*/ 
int removeElemArray(ArrayDinamico array, void* elem, int (*compare)(void*, void*));

/*Funcao que remove um dado elemento do array trocando o elemento a remover pelo ultimo*/ 
int removeElemSwapArray(ArrayDinamico array, void* elem, int (*compare)(void*, void*));

/*Funcao que guarda na variavel elem o elemento de uma dada posicao*/
void getElementoArray(ArrayDinamico array, int pos, void* elem);

/*Funcao que devolve o apontador para o elemento na posicao dada*/
void* getApontadorElementoArray(ArrayDinamico array, int pos);

/*Funcao que devolve uma lista de apontadores para elementos que fazem match com um dado elemento ou atributo*/ 
void getListaElementosArray(ArrayDinamico array, ArrayDinamico lista, void * elem, int (*compare)(void*, void*));

/*Funcao que devolve um elemento que tem um atributo passado por parametro*/
void* getElementoDeAtributo(ArrayDinamico array, void* atributo, int (*compare)(void*, void*));

/*Funcao que devolve a posicao de um elemento para o qual foi dado o apontador para o mesmo*/
int getPosicaoApontadorArray(ArrayDinamico array, void * apontador);

/*Funcao que devolve o tamanho de um elemento do array*/
int getTamanhoElementoArray (ArrayDinamico array);

/*Funcao que devolve o tamanho do array*/ 
int getTamanhoArray (ArrayDinamico array);

/*Funcao que devolve o numero posicoes ocupadas no array*/
int getOcupadosArray (ArrayDinamico array);

/*Funcao que copia para a posicao dada do array o elemento dado*/
void setElementoArray(ArrayDinamico array, int pos, void* elem);

/*Funcao que estabelece o numero de posicoes ocupadas no array dinamico*/
void setOcupadosArray(ArrayDinamico array, int val);

/*Funcao que liberta um dado array dinamico*/
void freeArrayDinamico(ArrayDinamico array);

/*Funcao que guarda num ficheiro o array dinamico dado*/
void serializarArrayDinamico(ArrayDinamico array, FILE* file);

/*Funcao que carrega de um ficheiro o array dinamico dado*/
ArrayDinamico carregarArrayDinamico(FILE* file);

/*Funcao que guarda num ficheiro o array dinamico dado com a ajuda de uma funcao que guarda o elemento*/
void serializarArrayDinamicoComElem(ArrayDinamico array, FILE* file, void (*serializarElem)(void*, FILE*));

/*Funcao que carrega de um ficheiro o array dinamico dado com a ajuda de uma funcao que carrega o elemento o elemento*/
ArrayDinamico carregarArrayDinamicoComElem(FILE* file, void* (*carregaElem)(FILE*));

#endif
