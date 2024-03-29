//
//  F.h
//  LI3
//
//  Created by Axel Ferreira on 2/27/13.
//  Copyright (c) 2013 Axel Ferreira. All rights reserved.
//

#ifndef LI3_F_h
#define LI3_F_h


#define MAXDIM 1301   // Numero máximo de anos

struct sList
{   //int ano;                    // ano de publicacao.
    int nAut;                   // numero de Autores.
    int nArt;                   // numero de Artigos.
    struct sList * seg;         // Nodo seguinte
};




int initEstrutura();

int addnArt();

struct sList * addListit();


/**
 * Adds data to the structure.
 * @return returns a pointer to a structure with the linked list
 */
struct sList * addList();

/**
 * Retruns a Linked List 
 *
 *
 *
 */
int getList();

void printaStruct();


/**
 * This function creates the file "G.csv" and it's content. If the file alreaddy exists it is rewritten.
 * @param bool if it's first time opens in "w" mode else in "a".
 */
int imprimeG();

/**
 * Frees the structure.
 * @return returns 1 if success 0 otherwise.
 */
int freeEstrutura();















#endif