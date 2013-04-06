//
//  main.c
//  LI3
//
//  Created by Axel Ferreira on 2/27/13.
//  Copyright (c) 2013 Axel Ferreira. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>                  // Verifica os caracteres alfanumericos
#include "fread.h"
#include "fwrite.h"
#include "parser.h"

// Macros
#define TRUE 1
#define FALSE 0
#define DEBUG_MODE FALSE
//#define LINE_BUFFER           <-----------------------<<<< Not Here
#define FILE_NAME_BUFFER 50
#define LISTA "lista.txt"   //  <-----------------------<<<< Not Here
#define D_TXT "D.txt"
#define E_TXT "E.txt"

// Contadores do programa main
static int nPro = 0;
static int nRej = 0;
static int nJou = 0;
static int nCon = 0;


int main(int argc, const char * argv[])
{   int bool = TRUE, i=0;
    char file_Name[FILE_NAME_BUFFER];
    char * line = NULL;
    struct sStats * lInfo = NULL;
    FILE * lista = fopen(LISTA, "r");
//////////////////
    char fileName[FILE_NAME_BUFFER];    //buffer para entradas lista.txt
    char * min_pag = malloc(4 * sizeof(char));
    
    if (lista)
    {   // Ver numero min de pag a considerar.
        fgets(min_pag, sizeof(min_pag), lista);
        i = atoi(min_pag);
        setMinPag(i);
    
        //////////////////
        
        // Processa os ficheiros todos
        while (fgets(fileName, sizeof(fileName), LISTA))
        {   int file_rej=0;
            char t = file_Name[0];
            // Processa as linhas todas do ficheiro
            while ((line = (leLinha(file_Name, t))))
            {  // lInfo = parseLine(line);
                nPro++;
            
                if (!lInfo) // Verifica se é ou não válida e incrementa os contadores respetivos
                { file_rej++; nRej++; }
                else
                {   if (t=='c') { nCon++;}
                    else { nJou++;}
                    process(); // guardar lInfo autores e ano | adicionar os contadores no ano...  <----------------<<<<<<
                }
            }
            // Imprime o Ficheiro E
            imprimeE(bool,file_rej, file_Name);
            if (bool==TRUE) { bool=FALSE; }
        }
        // Imprime o Ficheiro D
        imprimeD(nPro,nRej,nJou,nCon);
    
    }
    
if (DEBUG_MODE==TRUE)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    if (DEBUG_MODE == TRUE);
    {printf("now: \n%d\n-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);}
}
    
    
    
    
    return 0;
}

