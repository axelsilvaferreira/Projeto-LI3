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
#define INIT_BUFFER_SIZE 500
#define FILE_NAME_BUFFER 50

#define PATH_MODE               // <------------------------<<<<<<<     Uncomment/Comment to switch PATH_MODE
#ifdef PATH_MODE
    #define L_FILE "/Users/axelferreira/Desktop/dir/lista.txt"
    #define D_FILE "/Users/axelferreira/Desktop/dir/D.txt"
    #define E_FILE "/Users/axelferreira/Desktop/dir/E.txt"
    #define G_FILE "/Users/axelferreira/Desktop/dir/G.txt"
#else 
    #define L_FILE "lista.txt"
    #define D_FILE "D.txt"
    #define E_FILE "E.txt"
    #define G_FILE "G.txt"
#endif

// Contadores do programa main
static int nRej = 0;
static int nJou = 0;
static int nCon = 0;

int leFicheiro(char * bufferList)
{   int indexC_J = -1, ret=TRUE, lRej=0, bLine_size = (INIT_BUFFER_SIZE * sizeof(char));
    char * bufferLine=NULL;
    indexC_J = openFile(bufferList, "r");
    FILE * f2 = getFile(indexC_J);          // apontador para o ficheiro
    bufferLine = (char *) malloc(INIT_BUFFER_SIZE * sizeof(char));
    // ^ Abre o ficheiro no controlo && cria um buffer.
    
    // Caso tenha conseguido abrir o ficheiro e alocar o buffer
    if (indexC_J!=-1 && bufferLine)
    {   char type = bufferList[0];
        // Le cada linha do ficheiro
        while (!feof(f2))
        {   ret=dynamic_read_line(&bufferLine, &bLine_size, indexC_J);
            if (ret==-1) {return ret;}
            struct sStats * entrada=NULL;
            
            // Valida a linha
            entrada = parseLine(bufferLine, type);
            if (entrada)
            {   if (type=='c')     // Caso seja Conf
            {   nCon++;
                // Adiciona dados a estrutura dos contadores
                // Adiciona dados a estrutura dos Autores
            }
            else                        // Caso seja Revista
            {   nJou++;
                // Adiciona dados a estrutura dos contadores
                // Adiciona dados a estrutura dos Autores
            }
                
            }
            else                            // Caso não seja válida
            { lRej++;}
        }
        free(bufferLine);
    }
    closeFile(indexC_J);
    
    return lRej;
}


int main(int argc, const char * argv[])
{   int i, bool = TRUE, indexL=-1;
    char * bufferList;
	int buffer_size = FILE_NAME_BUFFER * sizeof(char);
	int rc;
    
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
	{   // Pede uma linha do ficheiro lista.txt atraves do modulo fread
        rc = dynamic_read_line(&bufferList, &buffer_size, indexL);
        if (rc == -1) { return rc; }            // caso o ficheiro tenha acabado para
        int lRej=0;
        // Funcao que le o ficheiro e retorna o numero de rejeritados nesse ficheiro
        lRej = leFicheiro(bufferList);
        // Imprime o nome do ficheiro e o numero de Rejeitados.
        imprimeE(bool,lRej,bufferList);
        bool = FALSE;
    }
	free(bufferList);
    // Imprime o ficheiro D
    imprimeD(nRej, nJou, nCon);
    
    
    
    
    
    
    
    closeFile(indexL);
    return 0;
}
    
    
    
    
    
    /*
    
    
    int bool = TRUE, i=0;
    char file_Name[FILE_NAME_BUFFER];
    char * line = NULL;
    struct sStats * lInfo = NULL;
    FILE * lista = fopen(L_FILE, "r");
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
    
    */
    


