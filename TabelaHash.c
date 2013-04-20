#include "TabelaHash.h"

struct tabelahash {
	int tamanho;
	int tamanhoElemento;
	int ocupados;
	float factorCarga;
	ArrayDinamico tabela;
};

TabelaHash novaTabelaHash (int tamanho, int tamanhoElemento){
	TabelaHash novatabela = (TabelaHash) malloc (sizeof(struct tabelahash));
	ArrayDinamico linha;
	int i;
	novatabela->tamanho = tamanho;
	novatabela->tamanhoElemento = tamanhoElemento;
	novatabela->ocupados = 0;
	novatabela->factorCarga = 0.0;
	novatabela->tabela = novoArrayDinamico(tamanho, sizeof(ArrayDinamico));
	for(i = 0; i < tamanho; i++){
		linha = novoArrayDinamico(2,tamanhoElemento);
		addElementoArray(novatabela->tabela, &linha);
	}
	return novatabela;
}

void realocarTabelaHash (TabelaHash tabela, int novoTamanho, int (*funcaohash)(void*,int)){
	ArrayDinamico novatabela;
	ArrayDinamico novalinha;
	ArrayDinamico *linha;
	int i,j,ocupados,k,novaposicao;
	void* elem; 
	ArrayDinamico *linhaColocar;
	/*Cria nova tabela*/
	novatabela = novoArrayDinamico(novoTamanho, sizeof(ArrayDinamico));
	for(i = 0; i < novoTamanho; i++){
		novalinha = novoArrayDinamico(tabela->tamanho, tabela->tamanhoElemento);
		addElementoArray(novatabela, &novalinha);
	}
	/*Move elementos para nova tabela*/
	for(j = 0; j < tabela->tamanho; j++){
		linha = getApontadorElementoArray(tabela->tabela,j);
		ocupados = getOcupadosArray(*linha);
		for(k = 0; k < ocupados; k++){
			elem = getApontadorElementoArray(*linha,k);
			novaposicao = funcaohash(elem,novoTamanho);
			linhaColocar = getApontadorElementoArray(novatabela,novaposicao);
			addElementoArray(*(ArrayDinamico*) linhaColocar, elem);
		}
		freeArrayDinamico(*linha);
	}
	/*Substitui antiga tabela por nova*/
	freeArrayDinamico(tabela->tabela);
	tabela->tabela = novatabela;
	tabela->tamanho = novoTamanho;
	tabela->factorCarga = (float) tabela->ocupados / (float) tabela->tamanho;
}

void addElementoTabelaHash(TabelaHash tabela, void* elem, int (*funcaohash)(void*,int)){
	ArrayDinamico *linha;
	int posicaoColocar;
	int ocupadosAntes, ocupadosDepois;
	if(tabela->factorCarga > 0.8){
		realocarTabelaHash(tabela,tabela->tamanho * 2, funcaohash);
	}
	posicaoColocar = funcaohash(elem,tabela->tamanho);
	linha = getApontadorElementoArray(tabela->tabela, posicaoColocar);
	ocupadosAntes = getOcupadosArray(*linha);
	addElementoArray(*linha, elem);
	ocupadosDepois = getOcupadosArray(*linha);
	if(ocupadosAntes < ocupadosDepois){
		tabela->ocupados++;
		tabela->factorCarga = (float) tabela->ocupados / (float) tabela->tamanho;
	}
}

void removeElementoTabelaHash(TabelaHash tabela, void* elem, int (*funcaohash)(void*,int), int (*compare)(void*,void*)){
	ArrayDinamico *linha;
	int posicaoEliminar;
	int removeu;
	posicaoEliminar = funcaohash(elem, tabela->tamanho);
	linha = getApontadorElementoArray(tabela->tabela, posicaoEliminar);
	removeu = removeElemArray(*linha, elem, compare);
	if(removeu){
		tabela->ocupados--;
		tabela->factorCarga = (float) tabela->ocupados / (float) tabela->tamanho;
		if(tabela->factorCarga < 0.2){
			realocarTabelaHash(tabela,tabela->tamanho * 0.5, funcaohash);
		}
	}
}

int procuraElementoTabelaHash(TabelaHash tabela, void* elem, int (*funcaohash)(void*,int), int (*compare)(void*,void*)){
	int posicaoProcurar;
	ArrayDinamico *linha;
	int posicaoElemento;
	posicaoProcurar = funcaohash(elem, tabela->tamanho);
	linha = getApontadorElementoArray(tabela->tabela, posicaoProcurar);
	posicaoElemento = posicaoElementoArray(*linha, elem, compare);
	return posicaoElemento;
}

void* getApontadorElementoTabelaHash(TabelaHash tabela, void* elem, int (*funcaohash)(void*,int), int (*compare)(void*,void*)){
	void* elemento;
	int posicaoProcurar;
	int posicaoElemento;
	ArrayDinamico *linha;
	posicaoElemento = procuraElementoTabelaHash(tabela,elem,funcaohash,compare);
	if(posicaoElemento == -1){
		return NULL;
	}
	else {
		posicaoProcurar = funcaohash(elem,tabela->tamanho);
		linha = getApontadorElementoArray(tabela->tabela,posicaoProcurar);
		elemento = getApontadorElementoArray(*linha,posicaoElemento);
		return elemento;
	}
}

int getElementoTabelaHash(TabelaHash tabela, void* destino, void* elem, int (*funcaohash)( void *, int ), int (*compare)( void *, void * )){
	int posicaoElemento; 
	int posicaoProcurar;
	ArrayDinamico *linha;
	posicaoElemento = procuraElementoTabelaHash(tabela, elem, funcaohash, compare);
	posicaoProcurar = funcaohash(elem, tabela->tamanho);
	if ( posicaoElemento != -1 ){
		linha = getApontadorElementoArray(tabela->tabela, posicaoProcurar);
		getElementoArray(*linha, posicaoElemento, destino);
		return 1;
	}
	else
		return 0;
}

void getListaApontadorElemTabelaHash(TabelaHash tabela, ArrayDinamico destino, void* elem, int (*funcaoHash)(void*, int), int (*compare)(void*,void*)){
	ArrayDinamico *linha;
	int i = funcaoHash(elem, tabela->tamanho);
	linha = getApontadorElementoArray(tabela->tabela, i);
	getListaElementosArray(*linha,destino,elem,compare);	
}

float getFactorCargaTabelaHash (TabelaHash tabela){
	return tabela->factorCarga;
}

int getOcupadosTabelaHash (TabelaHash tabela){
	return tabela->ocupados;
}

int getTamanhoTabelaHash (TabelaHash tabela){
	return tabela->tamanho;
}

int getTamanhoElemTabelaHash (TabelaHash tabela){
	return tabela->tamanhoElemento;
}

void freeTabelaHash (TabelaHash tabela){
	int i;
	ArrayDinamico *linha;
	for(i = 0; i < tabela->tamanho; i++){
		linha = getApontadorElementoArray(tabela->tabela, i);
		freeArrayDinamico(*linha);
	}
	freeArrayDinamico(tabela->tabela);
	free(tabela);
}

void serializarTabelaHash (TabelaHash tabela, FILE *ficheiro){
	int i;
	ArrayDinamico *linha;
	fwrite(tabela, offsetof(struct tabelahash, tabela), 1, ficheiro );
	for(i = 0; i < tabela->tamanho; i++){
		linha = getApontadorElementoArray(tabela->tabela, i);
		serializarArrayDinamico(*linha, ficheiro);
	}
}

TabelaHash carregarTabelaHash (FILE *ficheiro){
	int i;
	ArrayDinamico *auxTabela;
	ArrayDinamico linha;
	TabelaHash novaTabela; 
	novaTabela = novaTabelaHash(1, 1);
	fread(novaTabela, offsetof( struct tabelahash, tabela ), 1, ficheiro);
	auxTabela = getApontadorElementoArray(novaTabela->tabela, 0);
	freeArrayDinamico(*auxTabela);
	freeArrayDinamico(novaTabela->tabela);
	novaTabela->tabela = novoArrayDinamico(novaTabela->tamanho, sizeof(ArrayDinamico));
	for (i = 0; i < novaTabela->tamanho; i++) {
		linha = carregarArrayDinamico(ficheiro);
		addElementoArray(novaTabela->tabela, &linha);
	}
	return novaTabela;
}
