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
#include <math.h>

#define TRUE 1
#define FALSE 0
#define ANO_I 1936 			// GET MAX ANO DO PC 	<----------------------------------------------------------########
#define N_AUTOR 100			// GET MAX ANO DO PC 	<----------------------------------------------------------########
#define MAXDIM 77           // GET MAX ANO DO PC 	<----------------------------------------------------------########
#define N_AUTORES 200 		// GET SOME DIMMENSION 	<----------------------------------------------------------########
//////////////////////////////////////////////////////////////////////////////////////////
#define DEBUG_MODE FALSE            //  Modo debug TRUE / FALSE                         //
#define PATH_MODE TRUE              //  Modo de caminho especificado TRUE / FALSE       //
//////////////////////////////////////////////////////////////////////////////////////////

static char * G_PATH    = "/Users/axelferreira/Desktop/dir/G.csv";          // Nome do ficheiro E.txt            //
static char * G_NAME    = "G.csv";                                                                               //


typedef struct sAno
{   int nArtigos;           // Serve para saber quantos artigos existem para este ano, e se existe algum artigo.
    int nodo[N_AUTOR];              // Estrutura que guarda o nº de autores
}Ano;

typedef struct sAnos
{   int maxDimAno;             // Dimensao maxima do array dos anos
    int maxDimNodo;             // Dimensao maxima do array dos nodos
    Ano ano[MAXDIM];        // Array de celulas ano
} Anos;

// Declaracao da estrutura de dados
static Anos estrutura;


int initEstrutura()
{int i=0,j=0;
    estrutura.maxDimAno=MAXDIM;
    for(i=0;i<(MAXDIM);i++)
    {   estrutura.ano[i].nArtigos=0;
        estrutura.maxDimNodo=N_AUTOR;
        for (j=0;j<(N_AUTOR);j++)
        {   estrutura.ano[i].nodo[j]=0;
        }
    }
    
    return 0;
}

int addnArt(int ano, int nAutor)
{   int a = (ano - ANO_I);
    int b = (nAutor - 1);
    
    if ((a < estrutura.maxDimAno) && (b < N_AUTOR))
    { estrutura.ano[a].nodo[b] ++; }
    
    return 0;
}

int printEstrutura()
{int i,j,k=0,kk=0,f=0;
   // char * buffer = malloc(100*sizeof(sizeof(int)));
    FILE * g;
    if (PATH_MODE==TRUE)
    { g = fopen(G_PATH, "w");}
    else { g = fopen(G_NAME, "w");}
    
    /*
    for (i=0;i<estrutura.maxDimNodo;i++)
    {   k=0;
        for (j=0;j<estrutura.maxDimAno;j++)
        { k+= estrutura.ano[j].nodo[i];
            if (k>0)
            {fprintf("Ano:%d,#Autores:%d,#artigos:%d\n",(j+ANO_I),(i+1),k);}
        }
    }
    */
     
    if (g)
    {   /////////////       Imprime "ano","#autores","#artigos"         ///////////////////
        fprintf(g, "\"ano\",\"#autores\",\"#artigos\"\n");
        
        for (j=0;j<(estrutura.maxDimNodo);j++)
        {   k=0;
            for (i=0;i<(estrutura.maxDimAno);i++)
            {   k += estrutura.ano[i].nodo[j];
                if (k>0) {  fprintf(g,"\"%d\",\"%d\",\"%d\"\n", (i+ANO_I), (j+1), k);
                            if (DEBUG_MODE==TRUE) {printf("\"%d\",\"%d\",\"%d\"\n",(i+ANO_I), (j+1), k);}
                         }
            }
        }
    /*
        for (i=0;i<(estrutura.maxDimNodo);i++)
        {
            for (j=0; j<(estrutura.maxDimAno); j++)
            {   k = estrutura.ano[j].nodo[i]; }
            if (k>0) {fprintf(g,"\"%d\",\"%d\",\"%d\"\n", (i+ANO_I), (j+1), k);
                if (DEBUG_MODE==TRUE) {printf("\"%d\",\"%d\",\"%d\"\n",(i+ANO_I), (j+1), k);}}
        }
    */
        /////////////       Imprime "#autores","#artigos"               ///////////////////
        fprintf(g, "\"#autores\",\"#artigos\"\n");
        k=0;
        for(i=0;i<(estrutura.maxDimAno); i++)
        { for (j=0;j<(estrutura.maxDimNodo);j++)
            {   k = estrutura.ano[i].nodo[j];
                if (k>0) {fprintf(g, "\"%d\",\"%d\"\n",(j+1), k);}
                if (DEBUG_MODE==TRUE) {printf("\"%d\",\"%d\"\n",(j+1), k);}
            }
        }
        /////////////       Imprime "intervalo","#artigos"              ///////////////////    <-------------  VERIFICAR
        fprintf(g, "\"intervalo\",\"#artigos\"\n");
        k=0;
        for(i=0;i<(estrutura.maxDimAno); i++)
        { for (j=0;j<(estrutura.maxDimNodo);j++)
            {   k = estrutura.ano[i].nodo[j];
                if (k>0) {fprintf(g, "\"%d\",\"%d\"\n",(j+1), k);}
                if (DEBUG_MODE==TRUE) {printf("\"%d\",\"%d\"\n",(j+1), k);}
            }
        }
        /////////////       Imprime "ano","#autores","percentagem"      ///////////////////
        fprintf(g, "\"ano\",\"#autores\",\"percentagem\"\n");
        k=0;
        for(i=0;i<(estrutura.maxDimAno); i++)
        { for (j=0;j<(estrutura.maxDimNodo);j++)
            {   k = estrutura.ano[i].nodo[j];
                kk = estrutura.ano[i].nArtigos;
               if (kk>0)
               {    f = (k / kk);
                    k = k%kk;
                    if (k>0) {fprintf(g,"\"%d\",\"%d\",\"%d.%d\"\n", (i+ANO_I), (j+1), f,k);
                    if (DEBUG_MODE==TRUE) {printf("\"%d\",\"%d\",\"%d.%d\"\n",(i+ANO_I), (j+1), f,k);}}
               }
            }
        }
        
    }
    return 0;
}









