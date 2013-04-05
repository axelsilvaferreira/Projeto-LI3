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
#define E_FILE "E.txt"
#define D_FILE "D.txt"


void imprimeE(int bool, int counter, char * path)     //FUNCAO COMPLETA
{   int i=0;
    char inicio[35] = "Lista Rejeitadas\n----------------\n";
    char * output = malloc(100* sizeof(char));
    FILE * e;
    
    if (bool == TRUE)
    {   e = fopen(path, "w");
        if (e) {    fputs(inicio, e);}
        firstTime = FALSE;
    }
    else
    {   e = fopen(path, "a");
    }
    
    // Imprime para o ficheiro o conteúdo
    if (e)
    {   strcpy(output, fileN);
        i=(int) strlen(output);
        //dar espaco
        output[i]=' ';
        i++;
        //Converter inteiro para o buffer
        sprintf(&output[i], "%d\n", counter);
        fputs(output, e);
        fclose(e);
    }
    free(output);
    free(path);
}







void imprimeD(int nPro, int nRej, int nJou, int nCou)                              // FUNCAO COMPLETA
{   int i=38,j=0,p=0;
    char * path = malloc(100*sizeof(char));
    
    FILE * d = fopen(path, "w");
    char * estat_b = malloc( 200 * sizeof(char));
    char * linha = malloc( 100 * sizeof(char));
    char inicio[39] = "Estatistica basica\n------------------\n";
    
    
    if (d)
    {   strcpy(estat_b, inicio);
        
        p=getnProcessed();
        sprintf(&linha[0], "%d entradas\n", p);
        for(j=0;linha[j]!='\0'; j++)
        {   estat_b[i] = linha[j];
            i++;
        }
        p=getnRejected();
        sprintf(&linha[0], "%d rejeitadas\n", p);
        for(j=0;linha[j]!='\0'; j++)
        {   estat_b[i] = linha[j];
            i++;
        }
        p=getnArticles();
        sprintf(&linha[0], "%d artigos\n", p);
        for(j=0;linha[j]!='\0'; j++)
        {   estat_b[i] = linha[j];
            i++;
        }
        p=getnJournals();
        sprintf(&linha[0], "  %d em revista\n", p);
        for(j=0;linha[j]!='\0'; j++)
        {   estat_b[i] = linha[j];
            i++;
        }
        p=getnConferences();
        sprintf(&linha[0], "  %d em conferencia\n", p);
        for(j=0;linha[j]!='\0'; j++)
        {   estat_b[i] = linha[j];
            i++;
        }
        
        
        fputs(estat_b, d);
        fclose(d);
    }
    free(path);
    free(estat_b);
    free(linha);
}



