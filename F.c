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
//#define N_AUTOR 100			// GET MAX ANO DO PC 	<----------------------------------------------------------########
//#define N_AUTORES 200 		// GET SOME DIMMENSION 	<----------------------------------------------------------########
#define MAX_DATAS 40        // Get MAX CHAR DATAS3/4
//////////////////////////////////////////////////////////////////////////////////////////
#define DEBUG_MODE FALSE            //  Modo debug TRUE / FALSE                         //
#define PATH_MODE TRUE              //  Modo de caminho especificado TRUE / FALSE       //
//////////////////////////////////////////////////////////////////////////////////////////


typedef struct sList
{   int nAut;                   // numero de Autores.
    int nArt;                   // numero de Artigos.
    struct sList * seg;         // Nodo seguinte
}List, * Nodo;


typedef struct sAno
{   int totArtigos;             // Serve para saber quantos artigos existem para este ano, e se existe algum artigo.
    List * list;                // Estrutura que guarda o nº de autores
}Ano;

typedef struct sAnos
{   int maxDimAno;              // Dimensao maxima do array dos anos
    Ano ano[MAXDIM];            // Array de celulas ano
} Anos;

// Declaracao da estrutura de dados
static Anos estrutura;


int initEstrutura()
{int i=0;
    estrutura.maxDimAno=MAXDIM;
    for(i=0;i<(MAXDIM);i++)
    {   estrutura.ano[i].totArtigos = 0;
        estrutura.ano[i].list = NULL;
    }
    return 0;
}


int addnArt(int ano, int nAutor)
{ List * l0 = estrutura.ano[0].list, * l = estrutura.ano[ano].list;
    
    // Calcula o ano no array
    ano = (ano-ANO_I+1); //'+1' pq 0 está rezervado

    // Verifica se o ano cabe no array
    if (ano <= MAXDIM)
    {   // Adiciona ao numero total
        if (DEBUG_MODE){printf("tot:%d\n", estrutura.ano[ano].totArtigos);}
        l0 = addList(l0, nAutor, 1);
        estrutura.ano[0].totArtigos++;
        if (DEBUG_MODE){printf("adicionou:\nano:%d nAutor:%d\n",(ano+1936-1),nAutor);}
        // Adiciona ao ano em questao
        l = addList(l, nAutor, 1);
        estrutura.ano[ano].totArtigos++;
        if (DEBUG_MODE){printf("entrou:\ntot:%d\n\n", estrutura.ano[ano].totArtigos);}
    }
    
    return 0;
}

List * addList(List ** l, int aut, int art)
{ int ret = TRUE;
  
    Nodo n = (Nodo) malloc(sizeof(List));
    if (!n) {return FALSE;}
    n->nAut = aut;
    n->nArt = art;
    n->seg  = NULL;
        
    if (*l)
    {   // Avanca ate a posicao de insercao
        while ((*l)!=NULL && (*l)->nAut < aut)
        { (*l) = (*l)->seg; }
        
        // verifica se ja existe a posicao e insere
        if(!(*l))
        { (*l)->nArt+=art;
        }
        else if ((*l)->nAut==aut)
            {   (*l)->nArt += art; }
        else
        {   (*l)->seg = n; }
    }
    else    // Se não tem lista cria um nodo e adiciona
    { (*l) = n; }
    
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
    
    
    return n;
}



int imprimeG(int bool, char * G_PATH, char * DATA3_P, char * DATA4_P)
{ int ret=FALSE, i=0, anoI=-1, anoF=-1, p1=0, p2=0;
    char * buffer = malloc(MAX_DATAS*sizeof(char));
    char * token=NULL, *tofree = buffer;
    List * l = NULL;
    FILE * g=NULL, * d3=NULL, * d4=NULL;
    // Open files data3 data4 and G.csv
    if (bool) {g  = fopen(G_PATH, "w");}
    else {g  = fopen(G_PATH, "a");}
    d3 = fopen(DATA3_P, "r");
    d4 = fopen(DATA4_P, "r");
    
    printf("Chegou a imprimeG()\n");
    //////////////////////////////////////////////////////////////////////
    ////// IMPRIME ANO[0]   //////////////////////////////////////////////
                                                                        //
    l = estrutura.ano[0].list;                                          //
    if (l)                                                              //
    {   while (l)                                                       //
        {   printf("#Autores:%d\n#Artigos:%d\n",l->nAut, l->nArt);      //
            l=l->seg;                                                   //
        }                                                               //
    }                                                                   //
    //////////////////////////////////////////////////////////////////////
    if (g && d3 && d4)
    {
        // imprime ANO, #AUTORES, #ARTIGOS
        fprintf(g, "\"ano\",\"#autores\",\"#artigos\"\n");
        for (i=1;i<estrutura.maxDimAno;i++)     // i=1 pq o array[0] tem os totais
        {   l = estrutura.ano[i].list;
            if (l)
            {   while (l)
            {   anoI = l->nAut;
                anoF = l->nArt;
                printf("\"%d\",\"%d\",\"%d\"\n",(i+ANO_I-1), anoI, anoF);
                fprintf(g,"\"%d\",\"%d\",\"%d\"\n",(i+ANO_I-1), (l->nAut), (l->nArt));
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



int freeEstrutura()
{ int ret = TRUE, i;

    
    for(i=0;i<estrutura.maxDimAno;i++)
    {
        
    }
    
    
    return ret;
}














