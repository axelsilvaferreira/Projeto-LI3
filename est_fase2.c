//
//  est_fase2.c
//  LI3
//
//  Created by Axel Ferreira on 3/2/13.
//  Copyright (c) 2013 Axel Ferreira. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayDinamico.h"
#include "TabelaHash.h"

#define TRUE 1
#define FALSE 0
//////////////////////////////////////////////////////////////////////////////////////////
#define DEBUG_MODE FALSE            //  Modo debug TRUE / FALSE                         //
#define PATH_MODE TRUE              //  Modo de caminho especificado TRUE / FALSE       //
//////////////////////////////////////////////////////////////////////////////////////////

static char * G_PATH    = "/Users/axelferreira/Desktop/dir/G.txt";          // Nome do ficheiro G.csv            //
static char * G_NAME    = "G.csv";                                                                               //
static char * DATA3_P   = "/Users/axelferreira/Desktop/dir/datas3.txt";
static char * DATA4_P   = "/Users/axelferreira/Desktop/dir/datas4.txt";
static char * DATA3     = "datas3.txt";
static char * DATA4     = "datas4.txt";

typedef struct sList
{   int nAut;               // numero de Autores.
    int nArt;               // numero de Artigos.
    struct sList * seg;     // Nodo seguinte
}ANAutores;


int imprimeG(int bool, char * line)
{ int ret=FALSE, i=0, anoI=-1, anoF=-1, p1=0, p2=0;
    char * buffer = malloc(MAX_DATAS*sizeof(char));
    char * token=NULL, *tofree = buffer;
    List * l = NULL;
    FILE * g=NULL, * d3=NULL, * d4=NULL;
    // escolhe o modo Path
    if (PATH_MODE==TRUE) {  g  = fopen(G_PATH, "w");
        d3 = fopen(DATA3_P, "r");
        d4 = fopen(DATA4_P, "r");
    }
    else {  g  = fopen(G_NAME, "w");
        d3 = fopen(DATA3, "r");
        d4 = fopen(DATA4, "r");
    }
    //////////////////////////////////////////////////////////////////////
    ////// IMPRIME ANO[0]   //////////////////////////////////////////////
    //
    l = estrutura.ano[0].list;                                      //
    if (l)                                                          //
    {   while (l)                                                   //
    {   printf("#Autores:%d\n#Artigos:%d\n",l->nAut, l->nArt);  //
        if (l->seg) {l=l->seg;}                                 //
    }                                                           //
    }                                                               //
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














