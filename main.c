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
#define LISTA "lista.txt"


// Contadores do programa main
static int nPro = 0;
static int nRej = 0;
static int nJou = 0;
static int nCon = 0;


int main(int argc, const char * argv[])
{   int bool = TRUE;
    char * file_Name = NULL;
    char * line = NULL;
    struct sStats * lInfo = NULL;
    
    
    // Processa os ficheiros todos
    while ((file_Name = (leLista(LISTA))))
    {   int file_rej=0;
        char t = file_Name[0];
        // Processa as linhas todas do ficheiro
        while ((line = (leLinha(file_Name, t))))
        {   lInfo = parseLine(line);
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
        if (bool==TRUE) { bool=FALSE; }
        imprimeE(bool,file_rej, file_Name);
    }
    // Imprime o Ficheiro D
    imprimeD(nPro,nRej,nJou,nCon);
    
    
    
if (DEBUG_MODE==TRUE)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    if (DEBUG_MODE == TRUE);
    {printf("now: \n%d\n-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);}
}
    
    
    
    
    return 0;
}

