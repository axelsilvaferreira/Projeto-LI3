#ifndef _TABELAHASH
#define _TABELAHASH

#include <stdlib.h>
#include <stddef.h>
#include "ArrayDinamico.h"

typedef struct tabelahash *TabelaHash;

/*Funcao que cria uma nova tabela de hash*/
TabelaHash novaTabelaHash (int tamanho, int tamanhoElemento);

/*Funcao que realoca uma dada tabela de hash com um novo tamanho*/
void realocarTabelaHash (TabelaHash tabela, int novoTamanho, int (*funcaohash)(void*,int));

/*Funcao que adiciona um elemento a tebela de hash*/
void addElementoTabelaHash(TabelaHash tabela, void* elem, int (*funcaohash)(void*,int));

/*Funcao que elimina um elemento da tabela de hash*/
void removeElementoTabelaHash(TabelaHash tabela, void* elem, int (*funcaohash)(void*,int), int (*compare)(void*,void*));

/*Funcao que diz qual a posicao de um elemento na tabela de hash*/
int procuraElementoTabelaHash(TabelaHash tabela, void* elem, int (*funcaohash)(void*,int), int (*compare)(void*,void*));

/*Funcao que devolve um apontador para um elemento da tabela de hash*/
void* getApontadorElementoTabelaHash(TabelaHash tabela, void* elem, int (*funcaohash)(void*,int), int (*compare)(void*,void*));

/*Funcao que devolve uma copia de um elemento da tabela de hash*/
int getElementoTabelaHash(TabelaHash tabela, void* destino, void* elem, int (*funcaohash)( void *, int ), int (*compare)( void *, void * ));

/*Funcao que devolve uma lista de apontadores para elementos da tabela que possuam determinado atributo*/
void getListaApontadorElemTabelaHash(TabelaHash tabela, ArrayDinamico destino, void* elem, int (*funcaoHash)(void*, int), int (*compare)(void*,void*));

/*Funcao que devolve o factor de carga da tabela de hash*/
float getFactorCargaTabelaHash (TabelaHash tabela);

/*Funcao que devolve o numero de elementos guardados na tabela de hash*/
int getOcupadosTabelaHash (TabelaHash tabela);

/*Funcao que devolve o tamanho de uma tabela de hash*/
int getTamanhoTabelaHash (TabelaHash tabela);

/*Funcao que devolve o tamanho de um elemento da tabela de hash*/
int getTamanhoElemTabelaHash (TabelaHash tabela);

/*Funcao que liberta uma tabela de hash*/
void freeTabelaHash (TabelaHash tabela);

/*Funcao que guarda uma tabela de hash em ficheiro*/
void serializarTabelaHash (TabelaHash tabela, FILE *ficheiro);

/*Funcao que carrega uma tabela de hash de um ficheiro*/
TabelaHash carregarTabelaHash (FILE *ficheiro);

#endif
