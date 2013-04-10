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
        output[i-1]=' ';
        //i++;
        //Converter inteiro para o buffer
        //fprintf(e, "%s %d\n",file, counter);
        sprintf(&output[i], "%d\n", counter);
        fputs(output, e);
        fclose(e);
    }
    free(output);
}


void imprimeD(int nRej, int nJou, int nCou, char * path)           // FUNCAO COMPLETA
{   FILE * d = fopen(path, "w");
    printf("%d\n%d\n%d\n", nRej, nJou, nCou);
    
    if (d)
    {   fprintf(d, "Estatistica basica\n------------------\n");
        fprintf(d, "%d entradas\n", (nRej+nJou+nCou));
        fprintf(d, "%d rejeitadas\n", nRej);
        fprintf(d, "%d artigos\n", (nJou+nCou));
        fprintf(d, "  %d revista\n", nJou);
        fprintf(d, "  %d conferencia\n", nCou);
        
        fclose(d);
    }
}



/*  
 // int i=38,j=0;
 char * estat_b = malloc( 200 * sizeof(char));
 char * linha = malloc( 100 * sizeof(char));
 char inicio[39] = "Estatistica basica\n------------------\n";
 


 //strcpy(estat_b, inicio);
 
 sprintf(&linha[0], "%d entradas\n", (nRej+nJou+nCou));
 for(j=0;linha[j]!='\0'; j++)
 {   estat_b[i] = linha[j];
 i++;
 }
 sprintf(&linha[0], "%d rejeitadas\n", nRej);
 for(j=0;linha[j]!='\0'; j++)
 {   estat_b[i] = linha[j];
 i++;
 }
 sprintf(&linha[0], "%d artigos\n", (nJou+nCou));
 for(j=0;linha[j]!='\0'; j++)
 {   estat_b[i] = linha[j];
 i++;
 }
 sprintf(&linha[0], "  %d em revista\n", nJou);
 for(j=0;linha[j]!='\0'; j++)
 {   estat_b[i] = linha[j];
 i++;
 }
 sprintf(&linha[0], "  %d em conferencia\n", nCou);
 for(j=0;linha[j]!='\0'; j++)
 {   estat_b[i] = linha[j];
 i++;
 }
 
 // free(estat_b);
 // free(linha);

 fputs(estat_b, d);
 */
