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


Stats parseLine(char * buffer, char t)
{   int flag = TRUE;
    char * autores=NULL, * token=NULL;
    Stats s;
    s.nomes=NULL;
    s.ano=FALSE;
    s.nAutores=0;

    /////////   P  A  R  S  E  R   ////////////
    if (DEBUG_MODE) {printf("_______________________________________________\n");}
    if (DEBUG_MODE) {printf("%s\n",buffer);}
    
    // Valida numero inicial
    buffer = trim(buffer);
    token = strsep(&buffer, " \t");
    flag = validaNumeroI(token);
    if (!flag || !buffer) {return s;}
    if (DEBUG_MODE) {printf("%dNumero I :%s#\n",flag ,token);}
    
    // Valida Autores
    autores = strsep(&buffer, ":");
    autores = trim(autores);
    flag = validaAutores(autores);
    if (!flag || !buffer) {return s;}
    if (DEBUG_MODE) {printf("%dAutores  :%s#\n",flag,autores);}
    
    // Valida Titulo
    token = strsep(&buffer, ".");
    token = trim(token);
    flag = validaTitulo(token);
    if (!flag || !buffer) {return s;}
    if (DEBUG_MODE) {printf("%dTitulo   :%s#\n",flag,token);}
    
    if (t == 'j')           /////////// ( J O U R N A L ) ///////////
    {   // Valida Nome da Revista
        token = strsep(&buffer, "(");
        token = trim(token);
        flag = validaNomeJour(token);
        if (!flag || !buffer) {return s;}
        if (DEBUG_MODE) {printf("%dJ Nome   :%s#\n",flag,token);}

        // Valida Sigla da Revista
        token = strsep(&buffer, ")");
        token = trim(token);
        flag = validaSiglaJour(token);
        if (!flag || !buffer) {return s;}
        if (DEBUG_MODE) {printf("%dJ Sigla  :%s#\n",flag,token);}
        
        // Valida Volume da Revista
        token = strsep(&buffer, "(");
        token = trim(token);
        flag = validaVolume(token);
        if (!flag || !buffer) {return s;}
        if (DEBUG_MODE) {printf("%dJ Volume  :%s#\n",flag,token);}
        
        // Valida Numero da Revista
        token = strsep(&buffer, ")");
        token = trim(token);
        flag = validaNumeroR(token);
        if (!flag || !buffer) {return s;}
        if (DEBUG_MODE) {printf("%dJ N Revist:%s#\n",flag,token);}
        
        // Valida Paginas da Revista
        token = strsep(&buffer, "(");
        token = trim(token); token++; // Ignora os ':' e ' '
        flag = validaPaginas(token);
        if (!flag || !buffer) {return s;}
        if (DEBUG_MODE) {printf("%dJ Paginas :%s#\n",flag,token);}
        
        // Valida Ano da Revista
        token = strsep(&buffer, ")");
        s.ano = validaAno(token);
        if (!s.ano) {return s;}
        if (DEBUG_MODE) {printf("%dJ Ano    :%s#\n",flag,token);}
    }
    else if (t == 'c')      /////////// ( C O N F E R E N C E ) ///////////
    {   // Valida Nome da Conferencia
        token = strsep(&buffer, ":");
        s.ano = validaNomeConfData(token);
        if (!s.ano || !buffer) {return s;}
        if (DEBUG_MODE) {printf("%dC Nome Data:%s#\n",flag,token);}
        
        // Valida Paginas da Conferencia
        flag = validaPaginas(buffer);
        if (!flag) {return s;}
        if (DEBUG_MODE) {printf("%dC Paginas :%s#\n",flag,token);}
    }
    
    ///////////  Valida  Autores  ///////////
    if (!flag) { return s; }
    else {  int i=0;
            // Copia os autores para a estrutura a devolver
            s.nomes = strdup(autores);
            for (i=0;strsep(&autores, ",");i++) {}
            s.nAutores = i;
         }
    
    
    return s;
}


void setMinPag(int pag)
{   minPag = pag;}


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
    
    if (!token) {return FALSE;}
    if (DEBUG_MODE==2) {printf("NumeroR   :%s#\n",token);}
    
    // testa se e numero ##########################
    for (i=0;token[i]!='\0';i++)
    {   if (!(isdigit(token[i]))) {flag2 = FALSE;}}
    if (flag2==FALSE) {flag = FALSE;}    
    
    return flag;
}



int validaVolume(char * token)
{   int i=0,flag = TRUE;
        
    if (!token) {return FALSE;}
    if (DEBUG_MODE==2) {printf("Volume    :%s#\n",token);}
    for (i=0;token[i]!='\0';i++)
    {   if (!(isdigit(token[i])))
        {flag = FALSE;}
    }
    
    return flag;
}

int validaNumeroI(char * token)
{int i=0, flag = TRUE;
    
    if (!token) {return FALSE;}
    if (DEBUG_MODE==2) {printf("NumeroI:%s#\n",token);}
    for(i=0;token[i]!='\0';i++)
    {   if (!(isdigit(token[i])))
        {  flag=FALSE; }
    }
    
    return flag;
}

int validaTitulo(char * token)
{   int flag = TRUE, i=0;
    static char *forbiddenW[DIMARRAY] = {"ISBN", "PREFACE", "EDITORIAL", "ERRATA", "OBITUARY", "IN MEMORY OF"};

    if (!token) {return FALSE;}
    if (DEBUG_MODE==2) {printf("Titulo    :%s#\n",token);}

    //converte tudo para maiusculas
    for (i=0;token[i]!='\0';i++)
    {   token[i] = toupper(token[i]); }
    //procura palavras proibidas
    for (i=0;(flag==TRUE) && (i<(DIMARRAY));i++)
    {   if (strstr(token, forbiddenW[i])) { flag = FALSE; } }

    return flag;
}


int validaAutores(char * token)
{   int i=0 , flag = TRUE, flag2=FALSE;
    
    if (!token) {return FALSE;}
    if (DEBUG_MODE==2) {printf("Autores   :%s#\n",token);}
    //Verifica se há autores
    for (i=0;(token[i]!='\0' && !flag2) && flag2==FALSE;i++)
    {   if (isalpha(token[i])) { flag2 = TRUE; } }
    if (flag2==FALSE) { flag = FALSE; }
    
    return flag;
}


int validaSiglaJour(char * token)
{   int i=0, flag = TRUE;
    
    if (!token) {return FALSE;}
    if (DEBUG_MODE==2) {printf("Sigla Jou :%s#\n",token);}
    for (i=0;token[i]!='\0';i++)
    {   if (!isalpha(token[i]) || !isupper(token[i]))
        { return FALSE; }
    }
    
    return flag;
}

int validaNomeJour(char * token)
{ int flag=TRUE, i=0, flag2=FALSE;
    
    if (!token) {return FALSE;}
    if (DEBUG_MODE==2) {printf("Nome Jou  :%s#\n",token);}
        for (i=0;token[i]!='\0';i++)
        { //if (isalnum(token[i])!=0) {flag2 = TRUE;} }
            if (isalpha(token[i])!=0) {flag2 = TRUE; }}
        if (flag2 == FALSE) {flag = FALSE;}
    
    return flag;
}

int validaNomeConfData(char * token)
{ int i=0,j=0,flag=TRUE,ano=FALSE;
    char * data = NULL;
    
    if (!token) {return FALSE;}
    if (DEBUG_MODE==2) {printf("Nome Dat C:%s#\n",token);}
    i = (int) strlen(token);
    j = (i-4);
    data = strdup(&token[j]);
    token[j]='\0';
    if ((token==NULL) || (data==NULL)) {flag = FALSE;}
    for (i=0;data[i]!='\0';i++)
    { if (isdigit(token[i])==0) {flag = TRUE;} }
    
    ano=atoi(data);

    return ano;
}

int validaAno(char * string)
{ int flag=TRUE, ano=FALSE;
    
    if (!string) {return FALSE;}
    if (DEBUG_MODE==2) {printf("Ano       :%s#\n",string);}
    if (flag) { ano = atoi(string); }
    
    return ano;
}


int validaPaginas(char * string)
{ char * token=NULL;
    int i=0,j=0,flag =TRUE;
    
    if (!string) {return FALSE;}
    if (DEBUG_MODE==2) {printf("Paginas   :%s#\n",string);}
    token = strsep(&string, "-");
    if (!token || !string) {return FALSE;}
    else
    {   i = atoi(token);
        token = strsep(&string, " \n\0(");
        if (!token) {return FALSE;}
        else
        {   j=atoi(token);
            if ((j-i+1) < minPag) {return FALSE;}
        }
    }
    return flag;
}

char * trim(char * token)
{
    for(;token && (token[0]==' ' || token[0]=='\t');token++){}
    
    return token;
}



