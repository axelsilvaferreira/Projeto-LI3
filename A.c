//
//  A.c
//  LI3
//
//  Created by Axel Ferreira on 3/2/13.
//  Copyright (c) 2013 Axel Ferreira. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include "A.h"
#include <limits.h>                 //  so e usado para INT_MAX
#include <string.h>
#include <ctype.h>                  // Verificas os caracteres alfanumericos
#define TRUE 1
#define FALSE 0

//////////////////////////////////////////////////////////////////////////////////////////
#define DEBUG_MODE FALSE             //  Modo debug TRUE / FALSE                         //
#define PATH_MODE FALSE             //  Modo de caminho especificado TRUE / FALSE       //
//////////////////////////////////////////////////////////////////////////////////////////

#define MAX_BUFFER_LIST 80          //  Buffer usado para ler entradas do ficheiro lista.txt
#define MAX_BUFFER_ENTRY 800        //  Buffer usado para ler entradas dos ficheiros c/j-*.txt
#define CONFERENCE 8
#define JOURNAL 6
#define DIMARRAY 6                  //  Dimensao do Array das palavras proibidas
static int nProcessed = 0;          //  numero de entradas processadas
static int nRejected = 0;           //  numero total de entradas rejeitadas
static int nArticles = 0;           //  numero total de Artigos
static int nJournals = 0;           //  numero de Artigos em Revista
static int nConference = 0;         //  numero de Artigos em Conferencia
static int minPag = 0;              //  numero de Pag minimo para artigos
static char * listaTXT = "/Users/axelferreira/Desktop/dir/lista.txt";   //Endereço do ficheiro lista.txt
static char * E_PATH = "/Users/axelferreira/Desktop/dir/E.txt";         // Nome do ficheiro E.txt
static char * E_NAME = "E.txt";
static char * D_PATH = "/Users/axelferreira/Desktop/dir/D.txt";         // Dir dos ficheiros d
static char * D_NAME = "D.txt";
static char * PATH = "/Users/axelferreira/Desktop/dir/";                // Dir da pasta


int getnProcessed()
{   return nProcessed; }

int getnRejected()
{   return nRejected; }

int getnArticles()
{   return nArticles; }

int getnJournals()
{   return nJournals; }

int getnConferences()
{   return nConference; }

int getMinPag()
{   return minPag; }

void incnProcessed()
{   nProcessed ++; }

void incnRejected()
{   nRejected ++; }

void incnArticles()
{   nArticles ++; }

void incnJournals()
{   nJournals ++; }

void incnConferences()
{   nConference ++; }

void setMinPag(int pag)
{   minPag = pag;}

void process()                               //FUNCAO COMPLETA
{   int i=0;
    char fileName[MAX_BUFFER_LIST];    //buffer para entradas lista.txt
    char * min_pag = malloc(6 * sizeof(char));
    FILE * lista = fopen(listaTXT, "r");

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
}

void imprimeE(int counter, char * fileN)     //FUNCAO COMPLETA
{   int i=0;
    char inicio[35] = "Lista Rejeitadas\n----------------\n";
    char * output = malloc(100* sizeof(char));
    char * path = malloc(100*sizeof(char));
    if (PATH_MODE)  {strcpy(path, E_PATH);}
    else    {strcpy(path, E_NAME);}
    FILE * e = fopen(path, "r");
    // Inicializa o ficheiro E.txt com as linhas descritivas
    if (!e)
    {   e = fopen(path, "w");
        if (e) {    fputs(inicio, e);
                    fclose(e);
                }
    }
    // Imprime para o ficheiro o conteúdo
    e = fopen(path, "a");
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

void imprimeD()                              // FUNCAO COMPLETA
{   int i=38,j=0,p=0;
    char * path = malloc(100*sizeof(char));
    if (PATH_MODE==TRUE) {strcpy(path, D_PATH);}
    else {strcpy(path, D_NAME);}
    
    FILE * d = fopen(path, "w");
    char * estat_b = malloc( 200 * sizeof(char));
    char * linha = malloc( 100 * sizeof(char));
    char inicio[39] = "Estatistica Basica\n------------------\n";

    
    if (d)
    {   strcpy(estat_b, inicio);

        p=getnProcessed();
        sprintf(&linha[0], "  Processed: %d\n", p);
        for(j=0;linha[j]!='\0'; j++)
        {   estat_b[i] = linha[j];
            i++;
        }
        p=getnRejected();
        sprintf(&linha[0], "   Rejected: %d\n", p);
        for(j=0;linha[j]!='\0'; j++)
        {   estat_b[i] = linha[j];
            i++;
        }
        p=getnArticles();
        sprintf(&linha[0], "   Articles: %d\n", p);
        for(j=0;linha[j]!='\0'; j++)
        {   estat_b[i] = linha[j];
            i++;
        }
        p=getnJournals();
        sprintf(&linha[0], "   Journals: %d\n", p);
        for(j=0;linha[j]!='\0'; j++)
        {   estat_b[i] = linha[j];
            i++;
        }
        p=getnConferences();
        sprintf(&linha[0], "Conferences: %d", p);
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


int validFile(char * fileN, int tipo)  //FUNCAO COMPLETA
{   int ret=TRUE, cont_rej_local=0, i=0,j=0;
    char *tofree, *token, *string;
    char *fileName = malloc(200*sizeof(char));
    // Cria caminho do ficheiro
    if (PATH_MODE == TRUE)  {   strcpy(fileName,PATH);
                                i =(int) strlen(PATH);
                                strcpy(&fileName[i], fileN);
                            }
    else {   strcpy(fileName, fileN); }
    
    FILE * ficheiro = fopen(fileName, "r");
    if (ficheiro)
    {   char * bLine = malloc(MAX_BUFFER_ENTRY * sizeof(char));
                if(DEBUG_MODE==TRUE) {printf("\n\n--------------------------------------------------------------------------------\n\t\t\t\t\t%s\n--------------------------------------------------------------------------------\n",fileN);}
        //le inha a linha do ficheiro
        while (fgets(bLine, MAX_BUFFER_ENTRY, ficheiro))
        { int flag = TRUE;
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
                    else { flag = validaAutores(token);}
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
                    flag = validaAno(string);
                }
            }
            else ///////// C O N F E R E N C E /////////
            {   if(flag==TRUE)  // Nome Conferencia e Data
                {   if (string[0] == ' ') {string++;}
                    token = strsep(&string, ":");
                    flag = validaNomeConfData(token); }
                if(flag==TRUE)  // Paginas Conferencia
                {   flag = validaPaginas(string); }
                
                if (!flag) {printf("\nFALHA:%s\n", tofree);}

            }
            
            // CONTAGEM
            if (flag==TRUE)
            {   incnArticles();
                if (tipo == JOURNAL)
                {incnJournals();}
                else {incnConferences();}
                if(DEBUG_MODE==TRUE) {printf("ACEITADA\n\n");}
                token =strsep(&tofree, " ");
            }
            else {  incnRejected();
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


//##############################################################################
//######################       ###### ####  ###### ####  #######################
//#####################  ####  #####  ####  ######  ##  ########################
//#####################        #####  ####  #######    #########################
//#####################  ####  #####  ####  ######  ##  ########################
//#####################  #### ######       ######  #### ########################
//##############################################################################


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
    
    if (DEBUG_MODE==TRUE) {printf("%s Not Digit\n", token);}
    
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
{   int i=0 , flag = TRUE, flag2=FALSE;
    
    if (!token) {flag = FALSE;}
    if(DEBUG_MODE==TRUE) {printf("autores:%s\n", token);}
    //Verifica se há autores
    for (i=0;(token[i]!='\0') && flag2==FALSE;i++)
    {   if (isalpha(token[i])!=0) {flag2 = TRUE;}}
    if (flag2==FALSE) { flag = FALSE; if (DEBUG_MODE==TRUE) { printf("No_Authors\n");}}
    
    return flag;
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
{ int i=0,j=0,flag=TRUE;
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

    return flag;
}

int validaAno(char * string)
{ int flag=TRUE;
    char * token = NULL;
    
    if (string[0] == '(') {string++;}
    token = strsep(&string, ")");
    if (!token) {flag = FALSE;}
    if(DEBUG_MODE==TRUE) {printf("ANO    :%s\n", token);}
    
    return flag;
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
