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
#define ANO_I 1936          // GET MAX ANO DO PC 	<----------------------------------------------------------########
#define MAX_DATAS 40        // Get MAX CHAR DATAS3/4
#define MAX_LIST 100
//////////////////////////////////////////////////////////////////////////////////////////
#define DEBUG_MODE FALSE            //  Modo debug TRUE / FALSE                         //
#define PATH_MODE TRUE              //  Modo de caminho especificado TRUE / FALSE       //
//////////////////////////////////////////////////////////////////////////////////////////






// Declaracao da estrutura de dados
static struct sList * estrutura[MAX_LIST];


int vaild_ano_list(int ano)
{int i;
    i = (ano-ANO_I+1); //'+1' pq 0 está rezervado
    if (i<MAX_LIST)
    return TRUE;
else return FALSE;
}


int initEstrutura()
{int i=0;
    for (i=0;i < MAX_LIST; i++)
    {   estrutura[i] = (struct sList *) malloc(sizeof(struct sList));
        //estrutura[i]->ano = 0;
        estrutura[i]->nArt = 0;
        estrutura[i]->nAut = 0;
        estrutura[i]->seg = NULL;
    }
    
    return i;
}


int addnArt(int ano, int nAutor)
{
    // Calcula o ano no array
    ano = (ano-ANO_I+1); //'+1' pq 0 está rezervado
    // Verifica se o ano cabe no array
    if (ano <= MAX_LIST)
    {   // Adiciona ao numero total
        if (estrutura[0]->nAut == 0) { estrutura[0]->nArt += 1;}
        // Adiciona a nAutores total correspondente
        estrutura[0]->seg = addList(estrutura[0]->seg, nAutor, 1);
        
        // Adiciona ao contador total do ano
        if (estrutura[ano]->nAut == 0) { estrutura[ano]->nArt += 1;}
        //printf("Ano:%d, nArt:%d\n",ano, estrutura[0]->nArt);
        
        // Adiciona a nAutores do ano correspondente
        estrutura[ano]->seg = addList(estrutura[ano]->seg, nAutor, 1);
        //printf("%d,%d,%d\n", (ano+ANO_I-1), s->nAut, s->nArt);
    }
    
    return 0;
}






struct sList * addListit(struct sList * l, int aut, int art)
{struct sList * l2 = l;
   
    // Avanca ate a posicao de insercao
    if (l) {while (l && l->nAut < aut) {l=l->seg;}}
    
    // Quando nao ha lista ou chega ao fim
    if (!l)
    { struct sList * n = (struct sList *) malloc(sizeof(struct sList));
        n->nArt = art;
        n->nAut = aut;
        n->seg  = NULL;
        l->seg = n;
    }
    
    // Quando insere no meio e já existe quando existe
    if (l->nAut == aut)
    { l->nArt += 1; }
    
    //Quando insere no meio e ainda n nao existe
    if (l->nAut > aut)
    {struct sList * n = (struct sList *) malloc(sizeof(struct sList));
        n->nArt = art;
        n->nAut = aut;
        n->seg  = NULL;
        n->seg  = l->seg;
        l->seg = n;
    }
    
    return l2;
}

struct sList * addList(struct sList * l, int aut, int art)
{ struct sList * n;
    
        
    if (l && l->nAut <= aut)// (!l || l->nAut >= aut)
    {l->seg = addList(l->seg, aut, art);}
    else
    {    // Quando insere no fim
        if (!l)
        {   n = (struct sList *) malloc(sizeof(struct sList));
            if (!n) {return FALSE;}
            n->nAut = aut;
            n->nArt = art;
            n->seg  = NULL;
        }
        // Quando a celula nao existe
        if (l && l->nAut < aut)
        {   n = (struct sList *) malloc(sizeof(struct sList));
            if (!n) {return FALSE;}
            n->nAut = aut;
            n->nArt = art;
            n->seg  = NULL;
            n->seg  = l->seg;
            l->seg  = n;
        }
        // Quando a celula já existe
        if (l && l->nAut == aut) {l->nArt += 1;}
        
    }
  //  else {l->seg = addList(l->seg, aut, art);}
    
    
    return l;
}

int getList(struct sList * l, int aut)
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



int imprimeG(int bool, char * G_PATH, char * DATA3_P, char * DATA4_P)
{ int ret=FALSE, i=0, anoI=-1, anoF=-1, p1=0, p2=0, tot=0;
    char * buffer = malloc(MAX_DATAS*sizeof(char));
    char * token=NULL, *tofree = buffer;
    struct sList * l = NULL;
    FILE * g=NULL, * d3=NULL, * d4=NULL;
    // Open files data3 data4 and G.csv
    if (bool) {g  = fopen(G_PATH, "w");}
    else {g  = fopen(G_PATH, "a");}
    d3 = fopen(DATA3_P, "r");
    d4 = fopen(DATA4_P, "r");
    

    if (g && d3 && d4)
    { 
        // imprime ANO, #AUTORES, #ARTIGOS
        fprintf(g, "\"ano\",\"#autores\",\"#artigos\"\n");
        for (i=1;i<(MAX_LIST-1);i++)     // i=1 pq o array[0] tem os totais
        {   l = estrutura[i];
            if (l && ((l->nArt) > 0))
            {   while (l)
                { //if (l->nArt>0)
                    //{
                        anoI = l->nAut;
                        anoF = l->nArt;
                        if (DEBUG_MODE){ printf("\"%d\",\"%d\",\"%d\"\n",(i+ANO_I-1), anoI, anoF);}
                        fprintf(g,"\"%d\",\"%d\",\"%d\"\n",(i+ANO_I-1), (l->nAut), (l->nArt));
                        l=l->seg;
                   // }
                }
            }
        }
        
        // imprime #AUTORES, #ARTIGOS
        fprintf(g, "\"#autores\",\"#artigos\"\n");
        l = estrutura[0];
        if (l)
        {   while (l)
            {   if ((l->nArt) > 0)
                    {
                        fprintf(g, "\"%d\",\"%d\"\n", (l->nAut), (l->nArt));
                        l=l->seg;
                    }
            }
        }
        
        // imprime Intervalo-ANO, #ARTIGOS
        fprintf(g, "\"intervalo\",\"#artigos\"\n");
        while (fgets(buffer, MAX_DATAS, d3))
        {   token = strsep(&buffer, "-");
            anoI = atoi(token);
            anoF = atoi(buffer);
            for (i=anoI;i<=anoF;i++)
            {   l = estrutura[i];
                if (l)
                {   tot = l->nArt;
                    l=l->seg;
                }
            }
            fprintf(g, "\"%d-%d\",\"%d\"\n", anoI, anoF,tot);
        }
        
        // imprime ANO, #AUTORES, Precentagem
        fprintf(g, "\"ano\",\"#autores\",\"percentagem\"\n");
        tot = 0;
        while (fgets(buffer, 20, d4))
        {   anoI = atoi(buffer);
            anoF = (anoI-ANO_I+1);
            l = estrutura[anoF];
            tot = l->nArt;
            if (l )//&& tot>0)
            { // Avanca o contador total do ano
              l = l->seg;
                while (l)
                { if (l->nArt > 0)
                    {   p1 = (l->nArt)/(tot);
                        p2 = (l->nArt)%(tot);
                        fprintf(g, "\"%d\",\"%d\",\"%d.%d\"\n", (anoI), (l->nAut), p1, p2);
                        l=l->seg;
                    }
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
    struct sList * l, *l2;
    
    for(i=0;i<MAX_LIST;i++)
    { l= estrutura[i];
       while (l)
       { l2 = l->seg;
           free(l);
           l = l2;
       }
    }
    return ret;
}














