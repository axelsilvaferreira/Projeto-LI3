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
#define DEBUG_MODE TRUE            //  Modo debug TRUE / FALSE
#define MAX_BUFFER_LIST 80          //  Buffer usado para ler entradas do ficheiro lista.txt
#define MAX_BUFFER_ENTRY 800        //  Buffer usado para ler entradas dos ficheiros c/j-*.txt
#define CONFERENCE 8
#define JOURNAL 6
#define DIMARRAY 6                  //  Dimensao do Array das palavras proibidas

static int minPag = 0;              //  numero de Pag minimo para artigos


Stats parseLine(char * buffer, char t)
{   int flag = TRUE, ano=0;
    char * autores=NULL, * token=NULL;
    Stats s;
    s.nomes=NULL;
    s.ano=FALSE;
    

    /////////   P  A  R  S  E  R   ////////////
    if (DEBUG_MODE) {printf("_______________________________________________\n");}
    if (DEBUG_MODE) {printf("%s",buffer);}
    
    // Valida numero inicial
    token = strsep(&buffer, " ");
    token = trim(token);
    flag = validaNumeroI(token);
    if (!flag || !buffer) {return s;}
    if (DEBUG_MODE) {printf("Numero I  :%s#\n",token);}
    
    // Valida Autores
    autores = strsep(&buffer, ":");
    token = trim(token);
    flag = validaAutores(autores);
    if (!flag || !buffer) {return s;}
    if (DEBUG_MODE) {printf("Autores   :%s#\n",autores);}
    
    // Valida Titulo
    token = strsep(&buffer, ".");
    token = trim(token);
    flag = validaTitulo(token);
    if (!flag || !buffer) {return s;}
    if (DEBUG_MODE) {printf("Titulo    :%s#\n",token);}
    
    
    if (t == 'j')           /////////// ( J O U R N A L ) ///////////
    {   // Valida Nome da Revista
        token = strsep(&buffer, "(");
        flag = validaNomeJour(token);
        if (!flag || !buffer) {return s;}
        if (DEBUG_MODE) {printf("J Nome    :%s#\n",token);}
        
        // Valida Sigla da Revista
        token = strsep(&buffer, ")");
        flag = validaSiglaJour(token);
        if (!flag || !buffer) {return s;}
        if (DEBUG_MODE) {printf("J Sigla   :%s#\n",token);}
        
        // Valida Volume da Revista
        token = strsep(&buffer, "(");
        flag = validaVolume(token);
        if (!flag || !buffer) {return s;}
        if (DEBUG_MODE) {printf("J Volume   :%s#\n",token);}
        
        // Valida Numero da Revista
        token = strsep(&buffer, ")");
        flag = validaNumeroR(token);
        if (!flag || !buffer) {return s;}
        if (DEBUG_MODE) {printf("J N Revista:%s#\n",token);}
        
        // Valida Paginas da Revista
        token = strsep(&buffer, "(");
        flag = validaPaginas(token);
        if (!flag || !buffer) {return s;}
        if (DEBUG_MODE) {printf("J Paginas  :%s#\n",token);}
        
        // Valida Ano da Revista
        token = strsep(&buffer, ")");
        s.ano = validaAno(token);
        if (!s.ano) {return s;}
        if (DEBUG_MODE) {printf("J Ano     :%s#\n",token);}
    }
    else if (t == 'c')      /////////// ( C O N F E R E N C E ) ///////////
    {   // Valida Nome da Conferencia
        token = strsep(&buffer, ":");
        ano = validaNomeConfData(token);
        if (!ano || !buffer) {return s;}
        if (DEBUG_MODE) {printf("C Nome  Data:%s#\n",token);}
        
        // Valida Paginas da Conferencia
        flag = validaPaginas(buffer);
        if (!flag) {return s;}
        if (DEBUG_MODE) {printf("C Paginas  :%s#\n",token);}
    }
    
    ///////////  Valida  Autores  ///////////
    if (!flag) { return s; }
    else {  // Copia os autores para a estrutura a devolver
            s.nomes = strdup(autores);
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
    
    // testa se e numero ##########################
    for (i=0;token[i]!='\0';i++)
    {   if (!(isdigit(token[i]))) {flag2 = FALSE;}}
    if (flag2==FALSE) {flag = FALSE;}    
    
    return flag;
}



int validaVolume(char * token)
{   int i=0,flag = TRUE;
        
    if (!token) {return FALSE;}
    
    for (i=0;token[i]!='\0';i++)
    {   if (!(isdigit(token[i])))
        {flag = FALSE;}
    }
    
    return flag;
}

int validaNumeroI(char * token)
{int i=0, flag = TRUE;
    
    if (!token) {return FALSE;}
    
    for(i=0;token[i]!='\0';i++)
    {   if (!(isdigit(token[i])))
        {  flag=FALSE; }
    }
    
    return flag;
}

int validaTitulo(char * token)
{   int flag = TRUE, flag2=FALSE, i=0;
    static char *forbiddenW[DIMARRAY] = {"ISBN","PREFACE","EDITORIAL","ERRATA","OBITUARY","IN MEMORY OF"};
    char * tofree=NULL, * string=NULL;
    

    if (!token) {return FALSE;}
    
    // PROCURA PALAVRAS PROIBIDAS
    tofree = string = strdup(token);
    //converte tudo para maiusculas
    for (i=0;token[i]!='\0';i++)
    {   token[i] = toupper(token[i]); }
    //procura palavras proibidas
    for (i=0;(flag==TRUE) && (i<(DIMARRAY-1));i++)
    {   if (strstr(token, forbiddenW[i])) { return FALSE; } }
    
    // verifica se tem titulo (pelo menos um char)
    for (i=0;(token[i]!='\0') && flag2==FALSE;i++)
    {   if (isalnum(token[i])!=0) {flag2 = TRUE; } }
    if (flag2==FALSE) { flag = FALSE;}
    
    free(tofree);
    return flag;
}


int validaAutores(char * token)
{   int i=0 , flag = TRUE, flag2=FALSE;
    
    if (!token) {return FALSE;}
    
    //Verifica se há autores
    for (i=0;(token[i]!='\0' && !flag2) && flag2==FALSE;i++)
    {   if (isalpha(token[i])) { flag2 = TRUE; } }
    if (flag2==FALSE) { flag = FALSE; }
    
    return flag;
}


int validaSiglaJour(char * token)
{   int i=0, flag = TRUE;
    
    if (!token) {return FALSE;}
    
    for (i=0;token[i]!='\0';i++)
    {   if (!isalpha(token[i]) || !isupper(token[i]))
        { return FALSE; }
    }
    
    return flag;
}

int validaNomeJour(char * token)
{ int flag=TRUE, i=0, flag2=FALSE;
    
    if (!token) {return FALSE;}
        
        for (i=0;token[i]!='\0';i++)
        { if (isalnum(token[i])!=0) {flag2 = TRUE;} }
        
        if (flag2 == FALSE) {flag = FALSE;}
    
    return flag;
}

int validaNomeConfData(char * token)
{ int i=0,j=0,flag=TRUE,ano=FALSE;
    char * data = NULL;
    
    if (!token) {return FALSE;}
    
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
    
    if (flag) { ano = atoi(string); }
    
    return ano;
}


int validaPaginas(char * string)
{ char * token=NULL;
    int i=0,j=0,flag =TRUE;
    
    if (!string) {return FALSE;}
    
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
    for(;token[0]==' ';token++){}
    
    return token;
}
