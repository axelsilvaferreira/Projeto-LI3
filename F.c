//
//  F.c
//  LI3
//
//  Created by Axel Ferreira on 3/2/13.
//  Copyright (c) 2013 Axel Ferreira. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>                 //  so e usado para INT_MAX
#include <string.h>
#include <ctype.h>                  // Verificas os caracteres alfanumericos
#include <math.h>
#include "F.h"
//#include "Estruturas.h"

#define TRUE 1
#define FALSE 0
#define ANO_I 1936 			// GET MAX ANO DO PC 	<----------------------------------------------------------########
#define N_AUTOR 100			// GET MAX ANO DO PC 	<----------------------------------------------------------########
#define MAXDIM 80           // GET MAX ANO DO PC 	<----------------------------------------------------------########
#define N_AUTORES 200 		// GET SOME DIMMENSION 	<----------------------------------------------------------########
#define MAX_DATAS 40
//////////////////////////////////////////////////////////////////////////////////////////
#define DEBUG_MODE FALSE            //  Modo debug TRUE / FALSE                         //
#define PATH_MODE TRUE              //  Modo de caminho especificado TRUE / FALSE       //
//////////////////////////////////////////////////////////////////////////////////////////

static char * G_PATH    = "/Users/axelferreira/Desktop/dir/G.txt";          // Nome do ficheiro E.txt            //
static char * G_NAME    = "G.csv";                                                                               //
static char * DATA3_P   = "/Users/axelferreira/Desktop/dir/datas3.txt";
static char * DATA4_P   = "/Users/axelferreira/Desktop/dir/datas4.txt";
static char * DATA3     = "datas3.txt";
static char * DATA4    = "datas4.txt";

typedef struct sList
{   int nAut;               // numero de Autores.
    int nArt;               // numero de Artigos.
    struct sList * seg;     // Nodo seguinte
}List, * Nodo;


typedef struct sAno
{   int totArtigos;           // Serve para saber quantos artigos existem para este ano, e se existe algum artigo.
    Nodo list;              // Estrutura que guarda o nº de autores
}Ano;

typedef struct sAnos
{   int maxDimAno;             // Dimensao maxima do array dos anos
    Ano ano[MAXDIM];        // Array de celulas ano
} Anos;

// Declaracao da estrutura de dados
static Anos estrutura;


int initEstrutura()
{int i=0;
    estrutura.maxDimAno=MAXDIM;
    for(i=0;i<(MAXDIM);i++)
    {   estrutura.ano[i].totArtigos =0;
        estrutura.ano[i].list = NULL;
    }
    
    return 0;
}


int addnArt(int ano, int nAutor)
{   // Calcula o ano no array
    ano = (ano-ANO_I+1);
 
    // Adiciona ao numero total
    addList(estrutura.ano[0].list, nAutor, 1);
    estrutura.ano[0].totArtigos++;

    // Adiciona ao ano em questao
    addList(estrutura.ano[ano].list, nAutor, 1);
    estrutura.ano[ano].totArtigos++;
    
    return 0;
}


int imprimeG()
{ int ret=FALSE, i=0, anoI=-1, anoF=-1, p1=0, p2=0;
    char * buffer = malloc(MAX_DATAS*sizeof(char));
    char * token=NULL, *tofree = buffer;
    List * l = NULL;
    FILE * g=NULL, * d3=NULL, * d4=NULL;
    // escolhe o modo Path
    if (PATH_MODE==TRUE) {  g = fopen(G_PATH, "w");
                            d3=fopen(DATA3_P, "r");
                            d4=fopen(DATA4_P, "r");
                         }
    else {  g = fopen(G_NAME, "w");
            d3=fopen(DATA3, "r");
            d4=fopen(DATA4, "r");
         }
    
    
    

    if (g && d3 && d4)
    {   
        // imprime ANO, #AUTORES, #ARTIGOS
            fprintf(g, "\"ano\",\"#autores\",\"#artigos\"\n");
            for (i=1;i<estrutura.maxDimAno;i++)     // i=1 pq o array[0] tem os totais
            {   l = estrutura.ano[i].list;
                if (l)
                {   while (l)
                    {   fprintf(g,"\"%d\",\"%d\",\"%d\"\n",(i+ANO_I-1), (l->nAut), (l->nArt));
                        l=l->seg;
                    }
                }
            }
        // imprime #AUTORES, #ARTIGOS
            fprintf(g, "\"#autores\",\"#artigos\"\n");
            l = estrutura.ano[0].list;
            if (l)
            {   while (l)
                {   fprintf(g, "\"%d\",\"%d\"\n", (l->nAut), (l->nArt));
                    l=l->seg;
                }
            }
        // imprime Intervalo-ANO, #ARTIGOS
            fprintf(g, "\"intervalo\",\"#artigos\"\n");
            while (fgets(buffer, MAX_DATAS, d3))
            {   token = strsep(&buffer, "-");
                anoI = atoi(token);
                anoF = atoi(buffer);
printf("anoI:%d#\nanoF:%d#\n", anoI, anoF);
                for (i=anoI;i<=anoF;i++)
                {   l = estrutura.ano[i].list;
                    if (l)
                    {   while(l)
                        {   fprintf(g, "\"%d-%d\",\"%d\"\n", anoI, anoF,(l->nArt));
                            l=l->seg;
                        }
                    }
                }
            }
        // imprime ANO, #AUTORES, Precentagem
            fprintf(g, "\"ano\",\"#autores\",\"percentagem\"\n");
            while (fgets(buffer, 20, d4))
            {   anoI = atoi(buffer);
                l = estrutura.ano[anoI].list;
                if (l)
                {   while (l)
                    {   p1 = (l->nArt)/(estrutura.ano[i].totArtigos);
                        p2 = (l->nArt)%(estrutura.ano[i].totArtigos);
                        fprintf(g, "\"%d\",\"%d\",\"%d.%d\"\n", (i+ANO_I-1), (l->nAut), p1, p2);
                        l=l->seg;
                    }
                }
            }
        
        
        ret = TRUE;
        fclose(d3);
        fclose(d4);
        fclose(g);
    }
    
    free(tofree);
    return ret;
}




/*
 
int printEstrutura()
{int i,j,k=0,kk=0,f=0;
   // char * buffer = malloc(100*sizeof(sizeof(int)));
    FILE * g;
    if (PATH_MODE==TRUE)
    { g = fopen(G_PATH, "w");}
    else { g = fopen(G_NAME, "w");}
    
    / *
    for (i=0;i<estrutura.maxDimNodo;i++)
    {   k=0;
        for (j=0;j<estrutura.maxDimAno;j++)
        { k+= estrutura.ano[j].nodo[i];
            if (k>0)
            {fprintf("Ano:%d,#Autores:%d,#artigos:%d\n",(j+ANO_I),(i+1),k);}
        }
    }
    * /
     
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
    / *
        for (i=0;i<(estrutura.maxDimNodo);i++)
        {
            for (j=0; j<(estrutura.maxDimAno); j++)
            {   k = estrutura.ano[j].nodo[i]; }
            if (k>0) {fprintf(g,"\"%d\",\"%d\",\"%d\"\n", (i+ANO_I), (j+1), k);
                if (DEBUG_MODE==TRUE) {printf("\"%d\",\"%d\",\"%d\"\n",(i+ANO_I), (j+1), k);}}
        }
    * /
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


*/


int addList(List * l, int aut, int art)
{ int ret = TRUE;
    
    if (l)
    {   // Avanca ate a posicao de insercao
        while (l->seg && l->nAut < aut)
        { l = l->seg; }
        
        // verifica se ja existe a posicao e insere
        if(l->nAut == aut)
        { l->nArt+=aut;}
        else // nao existe cria e insere
        { Nodo n = (Nodo) malloc(sizeof(List));
            n->nAut = aut;
            n->nArt = art;
            n->seg  = NULL;
            if (l->seg)
            {   n->seg = l->seg;
                l->seg = n;
            }
        }
    }
    
    return ret;
}

int getList(List * l, int aut)
{int art=-1;
    
    if (l)
    {
        while (l && l->nAut<aut)
        {l=l->seg;}
        if (l->nAut == aut)
        {art = l->nArt;}
    }
    
    
    return art;
}







