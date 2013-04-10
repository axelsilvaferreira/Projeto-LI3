//
//  fwrite.c
//  LI3
//
//  Created by Axel Ferreira on 4/3/13.
//  Copyright (c) 2013 Axel Ferreira. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fwrite.h"

#define TRUE 1
#define FALSE 0


void imprimeE(int bool, int counter, char * file, char * path)     //FUNCAO COMPLETA
{   int i=0;
    char inicio[35] = "Lista Rejeitadas\n----------------\n";
    char * output = malloc(100* sizeof(char));
    FILE * e;
    
    // Verifica se é a primeira escrita para o ficheiro
    if (bool == TRUE)
    {   e = fopen(path, "w");
        if (e) {    fputs(inicio, e);}
    }
    else
    {   e = fopen(path, "a"); }
    
    // Imprime para o ficheiro o conteúdo
    if (e)
    {   strcpy(output, file);
        i=(int) strlen(output);
        //dar espaco
        output[i]=' ';
        //i++;
        //Converter inteiro para o buffer
        //fprintf(e, "%s %d\n",file, counter);
        sprintf(&output[i+1], "%d\n", counter);
        fputs(output, e);
        fclose(e);
    }
    free(output);
}


void imprimeD(int nRej, int nJou, int nCou, char * path)           // FUNCAO COMPLETA
{   FILE * d = fopen(path, "w");
    
    if (d)
    {   fprintf(d, "Estatistica basica\n------------------\n");
        fprintf(d, "%d entradas\n", (nRej+nJou+nCou));
        fprintf(d, "%d rejeitadas\n", nRej);
        fprintf(d, "%d artigos\n", (nJou+nCou));
        fprintf(d, "  %d em revista\n", nJou);
        fprintf(d, "  %d em conferencia\n", nCou);
        
        fclose(d);
    }
}


