//
//  parser.c
//  LI3
//
//  Created by Axel Ferreira on 3/2/13.
//  Copyright (c) 2013 Axel Ferreira. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>                  // Verificas os caracteres alfanumericos
#include "parser.h"

#define TRUE 1
#define FALSE 0
#define DEBUG_MODE FALSE            //  Modo debug TRUE / FALSE
#define MAX_BUFFER_LIST 80          //  Buffer usado para ler entradas do ficheiro lista.txt
#define MAX_BUFFER_ENTRY 800        //  Buffer usado para ler entradas dos ficheiros c/j-*.txt
#define CONFERENCE 8
#define JOURNAL 6
#define DIMARRAY 6                  //  Dimensao do Array das palavras proibidas

static int minPag = 0;              //  numero de Pag minimo para artigos

//////////////////////////////////////////////////////////////////////////////////////////////

typedef struct sStats
{   char * nome;        // buffer com os autores
    int n;              // Numero de autores
    int ano;            // Ano
}Stats;

//////////////////////////////////////////////////////////////////////////////////////////////

Stats * parseLine()
{   Stats *s=NULL;
    
    
    
    return s;
}


void setMinPag(int pag)
{   minPag = pag;}


void process()                               //FUNCAO COMPLETA
{   int i=0;
    char fileName[MAX_BUFFER_LIST];    //buffer para entradas lista.txt
    char * min_pag = malloc(6 * sizeof(char));
    FILE * lista=NULL;
    if (PATH_MODE==TRUE) { lista = fopen(listaTXT, "r");}
    else { lista = fopen("lista.txt", "r"); }
/////////////////////////////////////////////////////////////////////////////////////////
    initEstrutura();
/////////////////////////////////////////////////////////////////////////////////////////
    if (lista)
    {   // Ver numero min de pag a considerar.
        fgets(min_pag, sizeof(min_pag), lista);
        i = atoi(min_pag);
        setMinPag(i);
        
        // Percorrer a Lista.txt
        while ( fgets(fileName, sizeof(fileName), lista) )
        {   // Substituir o char final do fileName '\n' POR '\0'
            for (i=0; fileName[i]!='\n' && fileName[i]!= '\0'; i++) {}
            fileName[i] = '\0';
            
            // definir tipo Conferencia ou revista
            if (fileName[0] == 'c') //&& buffer[1]=='-')
            {   validFile(fileName, CONFERENCE);
            }
            else
            {   validFile(fileName, JOURNAL);
            }
            imprimeD();
        }
        fclose(lista);
    }
    free(min_pag);
    
/////////////////////////////////////////////////////////////////////////////////////////
    imprimeG();
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
    freeEstrutura();
/////////////////////////////////////////////////////////////////////////////////////////
    
}





int validFile(char * fileN, int tipo)  //FUNCAO COMPLETA
{   int ret=TRUE, cont_rej_local=0, i=0,j=0;
    char *tofree=NULL, *token=NULL, *string=NULL;
    char *fileName = malloc(200*sizeof(char));
    // Cria caminho do ficheiro
    if (PATH_MODE == TRUE)  {   strcpy(fileName,PATH);
        i =(int) strlen(PATH);
        strcpy(&fileName[i], fileN);
    }
    else {   strcpy(fileName, fileN); }
    
    FILE * ficheiro = fopen(fileName, "r");
    if (ficheiro)
    {   char * bLine = realloc(NULL,MAX_BUFFER_ENTRY * sizeof(char));
        if(DEBUG_MODE==TRUE) {printf("%s\n",fileN);}
        
        //le inha a linha do ficheiro
        while (fgets(bLine, MAX_BUFFER_ENTRY, ficheiro))
        { int flag = TRUE, ano=0,nAut=0;
            tofree = string = strdup(bLine);
            static char *forbiddenW[DIMARRAY] = {"ISBN","PREFACE","EDITORIAL","ERRATA","OBITUARY","IN MEMORY OF"};
            
            
            //converte tudo para maiusculas
            for (i=0;bLine[i]!='\0';i++)
            {   bLine[i] = toupper(bLine[i]); }
            //procura palavras proibidas
            for (i=0;(flag==TRUE) && (i<DIMARRAY);i++)
            {   if (strstr(bLine, forbiddenW[i])) { flag=FALSE;
                if(DEBUG_MODE) {printf("REJEITADA\nContém:%s\n",forbiddenW[i]);}
            }
            }   // incrementa os processados
            incnProcessed();
            
            if(flag==TRUE)  // Numero Inicial
            {   token = strsep(&string, " ");
                if (!token || !string) { flag = FALSE; }
                else { flag = validaNumeroI(token); }
            }
            if(flag==TRUE)  // Autores
            {   token = strsep(&string, ":");
                if (!token || !string) { flag = FALSE; }
                else {  nAut = validaAutores(token);
                        if (nAut == FALSE) {flag = FALSE;}
                        else {flag = TRUE;}
                     }
            }
            if(flag==TRUE)  // Titulo
            {   if (string[0] == ' ') { string++; }
                token = strsep(&string, ".");
                if (!token || !string) { flag = FALSE; }
                else { flag = validaTitulo(token); }
            }
            if (tipo == JOURNAL) ///////// J O U R N A L /////////
            { 
                if(flag==TRUE)  // Nome Journal
                {   if (string[0] == ' ') {string++;}
                    token = strsep(&string, "(");
                    flag = validaNomeJour(token);
                }
                if(flag==TRUE)  // Sigla Journal
                {   token = strsep(&string, ")");
                    flag = validaSiglaJour(token);
                }
                if(flag==TRUE)  // Volume
                {   if (string[0] == ' ') {string++;}
                    token = strsep(&string, "(");
                    if (!token || !string) {flag = FALSE;}
                    flag = validaVolume(token);
                }
                if(flag==TRUE)  // Numero Revista
                {   token = strsep(&string, ")");
                    if (!token || !string) {flag = FALSE;}
                    flag = validaNumeroR(token);
                }
                if(flag==TRUE)  // Paginas Revista
                { int x=getMinPag();
                    // valida o numero de paginas
                    if (string[0] == ':') {string++;}
                    token = strsep(&string, "-");
                    if (!token || !string) {flag = FALSE;}
                    else
                    {   // testa se e numero###############################
                        i=0;
                        j=0;
                        i=atoi(token);
                        if(DEBUG_MODE==TRUE) {printf("PagI:%s\n", token);}
                        token = strsep(&string, " ");
                        if (!token || !string) {flag = FALSE;}
                        else {  // testa se e numero ########################
                            j=atoi(token);
                            if (((j-i)+1) < minPag)
                            {flag=FALSE;}
                            if(DEBUG_MODE==TRUE) {printf("PagF:%s\nnMinP:%d\n", token,x);}
                        }
                    }
                }
                if(flag==TRUE)  // Ano Revista
                {   // Valida o ano
                    ano = validaAno(string);
                    if (ano == FALSE) {flag = FALSE;}
                    else {flag = TRUE;}
                }

            }
            else ///////// C O N F E R E N C E /////////
            { char * whatever=tofree;
                if(flag==TRUE)  // Nome Conferencia e Data
                {   if (string[0] == ' ') {string++;}
                    token = strsep(&string, ":");
                    ano = validaNomeConfData(token);
                    if (ano == FALSE) {flag = FALSE;}
                    else {  flag = TRUE;
                         }
                }
                if(flag==TRUE)  // Paginas Conferencia
                {   flag = validaPaginas(string); }
                
                if (!flag)  {   if(DEBUG_MODE==TRUE) {  printf("\nFALHA:%s\n", tofree); }
                    if(DEBUG_MODE==TRUE) {  token  = strsep(&whatever, " ");
                        printf("%s\n", token);
                    }
                }
            }
            
            ///////////// CONTAGEM ////////////////////////
            if (flag==TRUE)
            {   incnArticles();
                addnArt(ano,nAut);
                if (tipo == JOURNAL)
                {   incnJournals(); }
                else
                {   incnConferences(); }
                if(DEBUG_MODE==TRUE) {printf("ACEITADA\n\n");}
            }
            else
            {   incnRejected();
                cont_rej_local++;
                if(DEBUG_MODE==TRUE) {printf("REJEITADA\n\n");}
            }
            
            free(tofree);
        }
        free(bLine);
        fclose(ficheiro);
    }
    else { ret = FALSE; }
    if (cont_rej_local>0) { imprimeE(cont_rej_local, fileN); }
    free(fileName);
    return ret;
}

//_______________________________________________________________________________\\
//###############################################################################\\
//######################/ _____   |######/ |####|  |#####/ \###/  /##############\\
//#####################|  |####|  |#####|  |####|  |#####\  \#/  /###############\\
//#####################|   ____   |#####|  |####|  |######      #################\\
//#####################|  |####|  |#####|  |####|  |####/  /#\   \###############\\
//#####################|__|####|__/#####|__________/###/__/###\__/###############\\
//###############################################################################\\
//-------------------------------------------------------------------------------\\

int validaNumeroR(char * token)
{ int i=0, flag = TRUE, flag2 = TRUE;
    
    // testa se e numero ##########################
    for (i=0;token[i]!='\0';i++)
    {   if (!(isdigit(token[i]))) {flag2 = FALSE;}}
    if (flag2==FALSE) {flag = FALSE;}
    if(DEBUG_MODE==TRUE) {printf("NumeroR:%s\n", token);}
    
    
    
    return flag;
}



int validaVolume(char * token)
{   int i=0,flag = TRUE;
    
    for (i=0;token[i]!='\0';i++)
    {   if (!(isdigit(token[i])))
    {flag = FALSE;}
    }
    if(DEBUG_MODE==TRUE) {printf("Volume:%s\n", token);}
    
    
    return flag;
}

int validaNumeroI(char * token)
{int i=0, flag = TRUE;
    
    
    if (DEBUG_MODE==TRUE) {printf("numero :%s\n", token);}
    for(i=0;token[i]!='\0';i++)
    {   if (!(isdigit(token[i])))
    {   flag=FALSE; }
    }
    
    if (DEBUG_MODE==TRUE && (flag==FALSE)) {printf("%s Not Digit\n", token);}
    
    return flag;
}

int validaTitulo(char * token)
{   int flag = TRUE, flag2=FALSE, i=0;
    
    if(DEBUG_MODE==TRUE) {printf("titulo :%s\n", token);}
    
    
    // verifica se tem titulo (pelo menos um char)
    for (i=0;(token[i]!='\0') && flag2==FALSE;i++)
    {   if (isalnum(token[i])!=0) {flag2 = TRUE; } }
    if (flag2==FALSE) { flag = FALSE;
        if (DEBUG_MODE==TRUE) { printf("No_Titulo");}}
    
    return flag;
}


int validaAutores(char * token)
{   int i=0 , flag = TRUE, flag2=FALSE, nAut=0;
    
    if (!token) {flag = FALSE;}
    if(DEBUG_MODE==TRUE) {printf("autores:%s\n", token);}
    //Verifica se há autores
    for (i=0;(token[i]!='\0') && flag2==FALSE;i++)
    {   if (isalpha(token[i])!=0) {flag2 = TRUE;}}
    if (flag2==FALSE) { flag = FALSE; if (DEBUG_MODE==TRUE) { printf("No_Authors\n");}}
    // Conta o numero de autores
    else {  for(i=0;strsep(&token, ",");i++) {}
            nAut = i;
         }
    
    return nAut;
}


int validaSiglaJour(char * token)
{   int i=0, flag = FALSE;
    
    if (!token) {flag = FALSE;}
    for (i=0;token[i]!='\0';i++)
    {   if (isalpha(token[i])) {flag = TRUE;}}
    if(DEBUG_MODE==TRUE) {printf("SIGLA:%s\n", token);}
    //ADICIONAR FUNCAO DE TESTAR SE E UPPER
    for (i=0;token[i]!='\0';i++)
    {   if (!isupper(token[i]))
        {   flag = FALSE;
        }
    }
    return flag;
}

int validaNomeJour(char * token)
{ int flag=TRUE, i=0, flag2=FALSE;
    
    if (!token) {flag = FALSE;}
    else
    {   if(DEBUG_MODE==TRUE) {printf("NomeR:%s\n", token);}
        
        for (i=0;token[i]!='\0';i++)
        { if (isalnum(token[i])!=0) {flag2 = TRUE;} }
        
        if (flag2 == FALSE) {flag = FALSE;}
    }
    return flag;
}

int validaNomeConfData(char * token)
{ int i=0,j=0,flag=TRUE,ano=FALSE;
    char * data = NULL;
    
    if (token==NULL) {flag = FALSE;}
    i = (int) strlen(token);
    j = (i-4);
    data = strdup(&token[j]);
    token[j]='\0';
    if ((token==NULL) || (data==NULL)) {flag = FALSE;}
    for (i=0;data[i]!='\0';i++)
    { if (isdigit(token[i])==0) {flag = TRUE;} }
    if(DEBUG_MODE==TRUE) { printf("NomeC  :%s\nData   :%s\n", token, data); }

        ano=atoi(data);

    return ano;
}

int validaAno(char * string)
{ int flag=TRUE, ano=FALSE;
    char * token = NULL;
    
    if (string[0] == '(') {string++;}
    token = strsep(&string, ")");
    
    
    
    /////////////////////////////////////////////////////////////
    // Adiciona o ano a estrutura de dados
    if (flag==TRUE)
    {   ano=atoi(token); }
    
    return ano;
}


int validaPaginas(char * string)
{ char * token=NULL;
    int i=0,j=0,flag =TRUE;
    token = strsep(&string, "-");
    if (token==NULL) {flag = FALSE;}
    else
    {   i = atoi(token);
        token = strsep(&string, " \0");
        if (token==NULL) {flag = FALSE;}
        else
        {   j=atoi(token);
            if ((j-i+1) < minPag)
            {flag=FALSE;}
            if(DEBUG_MODE==TRUE) {printf("PagI   :%d\nPagF   :%d\n", i, j);}
            
        }
    }
    return flag;
}



