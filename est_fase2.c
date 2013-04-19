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

static char * G_PATH    = "/Users/axelferreira/Desktop/dir/G.csv";          // Nome do ficheiro G.csv            //
static char * G_NAME    = "G.csv";                                                                               //
static char * DATA3_P   = "/Users/axelferreira/Desktop/dir/datas3.txt";
static char * DATA4_P   = "/Users/axelferreira/Desktop/dir/datas4.txt";
static char * DATA3     = "datas3.txt";
static char * DATA4     = "datas4.txt";

typedef struct sCelAno
{   int nAut;               // numero de Autores.
    int nArt;               // numero de Artigos.
    ArrayDinamico * array;
}CelAno;

typedef struct sCelArAu
{   int nAutor;
    int nArtigo;
}CelArAu;


static ArrayDinamico ano;
static CelAno arAnos[100];

void init()
{ int i;
    for (i=0;i<100;i++)
    {   arAnos[i].array = NULL;
        arAnos[i].nArt  = -1;
        arAnos[i].nAut  = -1;
    }
}

int addEntry(int ano, int nAutor)
{
    
}


int imprimeG(int bool, char * G_PATH, char * DATA3_P, char * DATA4_P)
{   int i=0, j=0, ret=FALSE;
    FILE * g=NULL, * d3=NULL, * d4=NULL;
    // escolhe o modo Path
    g  = fopen(G_PATH, "w");
    d3 = fopen(DATA3_P, "r");
    d4 = fopen(DATA4_P, "r");

    
    if (g && d3 && d4)
    {
        // imprime ANO, #AUTORES, #ARTIGOS
        fprintf(g, "\"ano\",\"#autores\",\"#artigos\"\n");

        // imprime #AUTORES, #ARTIGOS
        fprintf(g, "\"#autores\",\"#artigos\"\n");

        // imprime Intervalo-ANO, #ARTIGOS
        fprintf(g, "\"intervalo\",\"#artigos\"\n");

        // imprime ANO, #AUTORES, Precentagem
        fprintf(g, "\"ano\",\"#autores\",\"percentagem\"\n");
       
        
        
        ret = TRUE;
        fclose(d3);
        fclose(d4);
        fclose(g);
    }
    
    return ret;
}








