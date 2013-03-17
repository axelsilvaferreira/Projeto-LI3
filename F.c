//
//  F.c
//  LI3
//
//  Created by Axel Ferreira on 3/2/13.
//  Copyright (c) 2013 Axel Ferreira. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include "F.h"
#include <limits.h>                 //  so e usado para INT_MAX
#include <string.h>
#include <ctype.h>                  // Verificas os caracteres alfanumericos
#define TRUE 1
#define FALSE 0
#define ANO_0 1936 			// GET MAX ANO DO PC 	<----------------------------------------------------------########
#define N_AUTORES 200 		// GET SOME DIMMENSION 	<----------------------------------------------------------########
//////////////////////////////////////////////////////////////////////////////////////////
#define DEBUG_MODE FALSE            //  Modo debug TRUE / FALSE                         //
#define PATH_MODE FALSE             //  Modo de caminho especificado TRUE / FALSE       //
//////////////////////////////////////////////////////////////////////////////////////////



typedef struct sAnos
{	int nArtigos;
	int nAutores[N_AUTORES];
} Anos, *pAnos;





int criaEstrutura();

int addEstrutura();

int expEstrutura();









