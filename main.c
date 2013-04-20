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
#include "F.h"
//#include "est_fase2.h"

// Macros
#define TRUE 1
#define FALSE 0
#define INIT_BUFFER_SIZE 500
#define FILE_NAME_BUFFER 50

#define DEBUG_MODE FALSE                   // <-----<<<  Toogle 1/0 to switch DEBUG_MODE ON/OFF
#define PATH_MODE TRUE                     // <-----<<<  Comment to switch PATH_MODE OFF
#define PATH_MOD
#ifdef PATH_MOD
#define L_FILE "/Users/axelferreira/Desktop/dir/lista.txt"
#define D_FILE "/Users/axelferreira/Desktop/dir/D.txt"
#define E_FILE "/Users/axelferreira/Desktop/dir/E.txt"
#define G_FILE "/Users/axelferreira/Desktop/dir/G.csv"
#define D3_FILE "/Users/axelferreira/Desktop/dir/data3.txt"
#define D4_FILE "/Users/axelferreira/Desktop/dir/data4.txt"
#define _PATH_ "/Users/axelferreira/Desktop/dir/"
#else
#define L_FILE "lista.txt"
#define D_FILE "D.txt"
#define E_FILE "E.txt"
#define G_FILE "G.csv"
#define D4_FILE "data3.txt"
#define D3_FILE "data4.txt"
#define _PATH_ "./"
#endif

// Contadores do programa main
static int nRej = 0;
static int nJou = 0;
static int nCon = 0;



int leFicheiro(char * bufferList)
{   int indexC_J = -1, ret=TRUE, lRej=0, bLine_size = (INIT_BUFFER_SIZE * sizeof(char));
    char * bufferLine=NULL;
    char * s = malloc(100 * sizeof(char));

     
    if (PATH_MODE)
    {   strcpy(s, _PATH_);
        strcpy(&s[32], bufferList);
        indexC_J = openFile(s, "r");
    }
    else {indexC_J = openFile(bufferList, "r");}

    bufferLine = (char *) realloc(NULL, INIT_BUFFER_SIZE * sizeof(char));
    // ^ Abre o ficheiro no controlo && cria um buffer.
    
    // Caso tenha conseguido abrir o ficheiro e alocar o buffer
    if (indexC_J!=-1 && bufferLine)
    {   char type = bufferList[0];
        // Le cada linha do ficheiro
        while (ret) 
        { Stats entrada;

            ret=dynamic_read_line(&bufferLine, &bLine_size, indexC_J);
            if (!ret) {break;}

            // Valida a linha
            entrada = parseLine(bufferLine, type);
            if (entrada.nomes)      
            {   // Adiciona dados a estrutura dos contadores
                addnArt(entrada.ano, entrada.nAutores);
                
                // Adiciona dados a estrutura dos Autores
                //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
            
                if (type=='c')      // Caso seja Conf
                {   nCon++; }
                else                // Caso seja Revista
                {   nJou++; }
            }
            else                    // Caso não seja válida
            { lRej++; }
        }
        free(bufferLine);
    }
    closeFile(indexC_J);
    
    return lRej;
}


int main(int argc, const char * argv[])
{   int i, boolE = TRUE, boolG = TRUE, indexL = -1;
    char * bufferList;
	int buffer_size = FILE_NAME_BUFFER * sizeof(char);
	int rc = TRUE;
    
    // inicializa a estrutura F
    initEstrutura();
    
    // Inicializa o controlo & Abre o ficheiro lista.txt && Alloca o buffer
    init_file_control();                        // Inicializa o controlo de ficheiros
    indexL = openFile(L_FILE, "r");             // Abre o ficheiro lista.txt
    bufferList = (char *) malloc(buffer_size);  // Alloca o buffer para cada linha do ficheiro lista.txt
	if (!bufferList) { return -1; }
    
    // Le o numero minimo de paginas.
    rc = dynamic_read_line(&bufferList, &buffer_size, indexL);
    i = atoi(bufferList);                       // Converte num inteiro
    setMinPag(i);                               // Guarda o numero minimo de paginas.

    
    // Ciclo que percorre todo o ficheiro  lista.txt
	while(rc)
	{ int lRej=0;
        
        // Pede uma linha do ficheiro lista.txt atraves do modulo fread
        rc = dynamic_read_line(&bufferList, &buffer_size, indexL);
        
        if (rc)         // caso o ficheiro não tenha acabado para
        {   
            // REMOVE OS \n do BUFFER
            for (i=0;i<buffer_size && bufferList[i]!='\n'; i++) {}
            if (bufferList[i]=='\n') {bufferList[i]='\0';}
            
            // Funcao que le o ficheiro e retorna o numero de rejeitados nesse ficheiro
            lRej = leFicheiro(bufferList);
            nRej+=lRej;
            // Imprime o nome do ficheiro e o numero de Rejeitados.
            imprimeE(boolE,lRej,bufferList, E_FILE);
            boolE = FALSE;
        }
    }
	free(bufferList);
    // Imprime o ficheiro D
    imprimeD(nRej, nJou, nCon, D_FILE);
    
    // Imprime o ficheiro G.csv
    imprimeG(boolG,G_FILE,D3_FILE,D4_FILE);
    boolG = FALSE;
    closeFile(indexL); 
    
    return 0;
}
    

/*
if (DEBUG_MODE==TRUE)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    if (DEBUG_MODE == TRUE);
    {printf("now: \n%d\n-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);}
}
*/
