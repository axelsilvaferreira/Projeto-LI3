//
//  fread.c
//  LI3
//
//  Created by Axel Ferreira on 4/3/13.
//  Copyright (c) 2013 Axel Ferreira. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fread.h"
#define TRUE 1
#define FALSE 0

static FILE * file[MAX_FILE];

int vaild_index(int i)
{   if (i<MAX_FILE-1)
    return TRUE;
    else return FALSE;
}

FILE * getFile(int index)
{ FILE * f=NULL;
    int i = vaild_index(index);
    if (i)
    { f=file[index];
        return f;
    }
    else return NULL;
}

void init_file_control()
{ int i;
    for (i=0;i<MAX_FILE;i++)
    { file[i]=NULL; }
}

int openFile(char * file_name, char * mode)
{ int index = FALSE;
    // Find control index for file
    for (index=0;index<MAX_FILE && file[index]!=NULL;index++) {}
        
    if (file[index]==NULL)
    {file[index] = fopen(file_name,mode);
    }
    else {index = -1;}
    
    return index;
}

void closeFile(int index)
{   // Verify if index is valid
    if (vaild_index(index))
    { fclose(file[index]); }
}

int dynamic_read_line(char** buf, int* size, int index)
{   char* offset;
	int old_size;
    
	if (!fgets(*buf, *size, file[index]))
    {   return -1; }
    
	if ((*buf)[strlen(*buf) - 1] == '\n')
    {   return 0; }
    
	do  {   // we haven't read the whole line so grow the buffer
            old_size = *size;
            *size *= 2;
            *buf =(char *) realloc(*buf, *size);
            if (NULL == *buf) {
			return -1;
        }
		offset = &((*buf)[old_size - 1]);
	} while ( fgets(offset, old_size + 1, file[index]) && offset[strlen(offset) - 1] != '\n' );
    
	return 0;
}














