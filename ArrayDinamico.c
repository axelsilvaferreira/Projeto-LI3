#include "ArrayDinamico.h"

struct arraydinamico {
	int tamanho;
	int tamanhoElemento;
	int ocupados;
	void* array;
};

ArrayDinamico novoArrayDinamico (int tamanho, int tamanhoElem) {
	ArrayDinamico array = (ArrayDinamico) malloc (sizeof(struct arraydinamico));
	array->tamanho = tamanho;
	array->tamanhoElemento = tamanhoElem;
	array->ocupados = 0;
	if (tamanho > 0 && tamanhoElem > 0){
		array -> array = malloc(tamanho * tamanhoElem); 
		if (array -> array == NULL){
			array->tamanho = 0;
		}
	}
	else {
		array->array = NULL;
	}
	return array;
}

int realocarArrayDinamico (ArrayDinamico array, int novoTamanho) {
	void* novoArray;
	int nBytes;
	if (novoTamanho != array->tamanho){
		novoArray = malloc(novoTamanho * array->tamanhoElemento);
		if (novoArray == NULL){
			return 0;
		}
		if (novoTamanho > array->ocupados) {
			nBytes = array->ocupados * array->tamanhoElemento;
		}
		else nBytes = novoTamanho * array-> tamanhoElemento;
		memmove(novoArray, array->array, nBytes);
		free(array->array);
		array->tamanho = novoTamanho;
		array->array = novoArray;
	}
	return 1;
}

int temElementoArray(ArrayDinamico array, void* elem, int (*compare)(void*, void*)){
	int i = 0;
	int tem = 0;
	int j;
	while (i < array->ocupados && !tem){
		j = compare(elem, array->array + i * array->tamanhoElemento);
		if (j == 0) tem = 1;
		i++;
	}
	return tem;
}

int posicaoElementoArray(ArrayDinamico array, void* elem, int (*compare)(void*, void*)){
	int i = 0;
	int encontrado = 0;
	int j;
	while (i < array->ocupados && !encontrado){
		j = compare(elem, array->array + i * array->tamanhoElemento);
		if (j == 0) encontrado = 1;
		i++;
	}
	i--;
	if (encontrado) return i;
	else return -1;
}

int addElementoArray(ArrayDinamico array, void* elem){
	if (array->tamanho == array->ocupados){
		realocarArrayDinamico(array, array->tamanho * 2);
	}
	if(memcpy(array->array + array->ocupados * array->tamanhoElemento, elem, array->tamanhoElemento)){
		array->ocupados++;
		return array->ocupados-1;
	}
	else return -1;
}

int addNaoRepetidoArray(ArrayDinamico array, void* elem, int (*compare)(void*, void*)){
	int i,j;
	i = temElementoArray(array,elem, compare);
	if (!i) {
		j = addElementoArray(array, elem);
		return j;
	}
	else return -1;
}

void swapPosicoesArray(ArrayDinamico array, int p1, int p2){
	void* elem = malloc(array->tamanhoElemento);
	if (p1 >= 0 && p1 < array->ocupados && p2 >= 0 && p2 < array->ocupados) {
		memmove(elem, array->array + p1 * array->tamanhoElemento, array->tamanhoElemento);
		memmove(array->array + p1 * array->tamanhoElemento, array->array + p2 * array->tamanhoElemento, array->tamanhoElemento);
		memmove(array->array + p2 * array->tamanhoElemento, elem, array->tamanhoElemento);
	}
	free(elem);
}

void ordenaArrayDinamico(ArrayDinamico array, int (*compare)(const void*,const void*)){
	qsort(array->array, array->ocupados, array->tamanhoElemento, compare);
}

int removeElemSwapPosicaoArray(ArrayDinamico array, int pos){
	int ultimo = array->ocupados-1;
	int i;
	if(pos >= 0 && pos <= array->ocupados-1 && array->ocupados > 0){
		if(ultimo > 0 && ultimo != pos){
			swapPosicoesArray(array, pos, ultimo);
			array->ocupados--;
		}
		if(array->ocupados == 0 || array->tamanho / array->ocupados >= 2){
			i = realocarArrayDinamico(array, (array->tamanho + array->ocupados)/2 + 1);
		}
		if (i == 0) return 0;
		return 1;
	}
	else return 0;			
}

int removeElemPosicaoArray(ArrayDinamico array, int pos){
	int nBytes = (array->ocupados - pos - 1) * array->tamanhoElemento;
	int i; 
	if(pos >= 0 && pos <= array->ocupados-1 && array->ocupados > 0){
		array->ocupados--;
		memmove(array->array + pos * array->tamanhoElemento, array->array + (pos+1) * array->tamanhoElemento, nBytes);
		if(array->ocupados == 0 || array->tamanho / array->ocupados >=2){
			i = realocarArrayDinamico(array, (array->tamanho + array->ocupados)/2 + 1);
		}
		if (i == 0) return 0;
		return 1;
	}
	else return 0;			
}

int removeElemArray(ArrayDinamico array, void* elem, int (*compare)(void*, void*)) {
	int pos,i; 
	pos = posicaoElementoArray(array, elem, compare);
	if (pos == -1) return 0;
	i = removeElemPosicaoArray(array,pos);
	return i;
}

int removeElemSwapArray(ArrayDinamico array, void* elem, int (*compare)(void*, void*)) {
	int pos,i; 
	pos = posicaoElementoArray(array, elem, compare);
	if (pos == -1) return 0;
	i = removeElemSwapPosicaoArray(array,pos);
	return i;
}

void getElementoArray(ArrayDinamico array, int pos, void* elem){
	if(pos >= 0 && pos < array->ocupados){
		memcpy(elem, array->array + pos * array->tamanhoElemento, array->tamanhoElemento);
	}
}

void* getApontadorElementoArray(ArrayDinamico array, int pos){
	return array->array + pos * array->tamanhoElemento;
}

void getListaElementosArray(ArrayDinamico array, ArrayDinamico lista, void * elem, int (*compare)(void*, void*)){
	int i;
	for ( i = 0; i < array->ocupados; i++ ){
		if (compare(elem, array->array + i * array->tamanhoElemento) == 0)
			addElementoArray(lista, (void*)(array->array + i * array->tamanhoElemento));
	}
}

void* getElementoDeAtributo(ArrayDinamico array, void* atributo, int (*compare)(void*, void*)){
	int i;
	for ( i = 0; i < array->ocupados; i++ ){
		if (compare(atributo, array->array + i * array->tamanhoElemento) == 0)
			return (array->array + i * array->tamanhoElemento);
	}
	return NULL;
}

int getPosicaoApontadorArray(ArrayDinamico array, void * apontador){

	return (int) ((int)(apontador - array->array) / array->tamanhoElemento);
}

int getTamanhoElementoArray (ArrayDinamico array){
	return array->tamanhoElemento;
}

int getTamanhoArray (ArrayDinamico array){
	return array->tamanho;
}

int getOcupadosArray (ArrayDinamico array){
	return array->ocupados;
}

void setElementoArray(ArrayDinamico array, int pos, void* elem){
	memcpy(array->array + pos * array->tamanhoElemento, elem, array->tamanhoElemento);
}

void setOcupadosArray(ArrayDinamico array, int val){
	array->ocupados = val;
}

void freeArrayDinamico(ArrayDinamico array){
	free(array->array);
	free(array);
}

void serializarArrayDinamico(ArrayDinamico array, FILE* file){
	fwrite(array, offsetof(struct arraydinamico, array), 1, file);
	fwrite(array->array, array->tamanhoElemento, array->ocupados, file);
}

ArrayDinamico carregarArrayDinamico(FILE* file){
	ArrayDinamico array;
	void* dados;
	array = novoArrayDinamico(1,1);
	fread(array, offsetof(struct arraydinamico, array), 1, file);
	dados = malloc(array->tamanho * array->tamanhoElemento);
	fread(dados, array->tamanhoElemento, array->ocupados, file);
	free(array->array);
	array->array = dados;
	return array;
}

void serializarArrayDinamicoComElem(ArrayDinamico array, FILE* file, void (*serializarElem)(void*, FILE*)){
	int i;
	void* elemento;
	int tamanhoArray = getTamanhoArray(array);
	int tamanhoElemento = getTamanhoElementoArray(array);
	fwrite(&tamanhoArray, sizeof(int), 1, file);
	fwrite(&tamanhoElemento, sizeof(int), 1, file);
	fwrite(array, offsetof(struct arraydinamico, array), 1, file);
	for (i = 0; i < array->ocupados; i++){
		elemento = getApontadorElementoArray(array, i);
		serializarElem(elemento,file);
	}
}

ArrayDinamico carregarArrayDinamicoComElem(FILE* file, void* (*carregaElem)(FILE*)){
	ArrayDinamico array;
	int i, tamanhoArray, ocupados, tamanhoElemento;
	void* dados;
	void* elemento;
	fread(&tamanhoArray, sizeof(int), 1, file);
	fread(&tamanhoElemento, sizeof(int), 1, file);
	array = novoArrayDinamico(tamanhoArray,tamanhoElemento);
	fread(array, offsetof(struct arraydinamico, array), 1, file);
	for(i = 0; i < array->ocupados; i++){
		elemento = carregaElem(file);
		memcpy(array->array + i * array->tamanhoElemento, elemento, array->tamanhoElemento);
		free(elemento);
	}
	return array;
}
