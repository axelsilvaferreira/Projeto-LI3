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
#define ANO_I 0001          // GET MAX ANO DO PC 	<----------------------------------------------------------########
#define MAX_DATAS 40        // Get MAX CHAR DATAS3/4
#define MAX_LIST 3001
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
        estrutura[i]->nArt = 0;
        estrutura[i]->nAut = 0;
        estrutura[i]->seg  = NULL;
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



//######################## RECURSIVA #############################
struct sList * addList(struct sList * l, int aut, int art)
{ struct sList * n = NULL;
    
    // Insercao no fim ou quando nao ha lista.
    if (!l)
    { n = (struct sList *) malloc(sizeof(struct sList));
        n->nArt  = art;
        n->nAut  = aut;
        n->seg   = NULL;
        return n;
    }
    // Incremento quando o nodo ja existe
    else if (l->nAut == aut)
    { l->nArt++;
        return l;
    }
    // Chamada recusriva
    else if (l->nAut < aut)
    {   l->seg = addList(l->seg,aut,art);
        return l;
    }
    // Quando o nodo não existe
    else if (l->nAut > aut)
    { n = (struct sList *) malloc(sizeof(struct sList));
        n->nArt  = art;
        n->nAut  = aut;
        n->seg   = l->seg;
        return n;
    }
    return n;
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

void printaStruct()
{int i;
    struct sList * l=NULL;
    
    for (i=0;i<(MAX_LIST-1);i++)
    {l = estrutura[i];
        printf("Ano:%d",(i+ANO_I-1));
        while(l)
        {   printf("      Autor:%d Artigos:%d\n", l->nAut, l->nArt);
            l=l->seg;
        }
    }
}

int imprimeG(int bool, char * G_PATH, char * DATA3_P, char * DATA4_P)
{ int ret=FALSE, i=0, anoI=-1, anoF=-1, tot=0;
    float p1=0;
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
            if (l)
            {   while (l)
                {   anoI = l->nAut;
                    anoF = l->nArt;
                    if (DEBUG_MODE){ printf("\"%d\",\"%d\",\"%d\"\n",(i+ANO_I-1), anoI, anoF);}
                    if (l->nAut > 0)
                    {fprintf(g,"\"%d\",\"%d\",\"%d\"\n",(i+ANO_I-1), (l->nAut), (l->nArt));}
                    l=l->seg;
                }
            }
        }
        
        // imprime #AUTORES, #ARTIGOS
        fprintf(g, "\"#autores\",\"#artigos\"\n");
        l = estrutura[0]->seg;
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
            {   l = estrutura[i];
                if (l)
                {   tot += l->nArt;
                }
            }
            fprintf(g, "\"%d-%d\",\"%d\"\n", anoI, anoF,tot);
            tot=0;
        }
        
        // imprime ANO, #AUTORES, Precentagem
        fprintf(g, "\"ano\",\"#autores\",\"percentagem\"\n");
        tot = 0;
        while (fgets(buffer, 20, d4))
        {   anoI = atoi(buffer);
            anoF = (anoI-ANO_I+1);
            l = estrutura[anoF];
            tot = l->nArt;
            if (l)
            { // Avanca o contador total do ano
              l = l->seg;
                while (l)
                { if (l->nArt > 0)
                    {   p1 =(float) (((l->nArt)*100))/(tot);
                        //p2 = (l->nArt)%(tot);
                        fprintf(g, "\"%d\",\"%d\",\"%.2f\"\n", (anoI), (l->nAut), p1);
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














