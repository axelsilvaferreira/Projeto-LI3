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

void init_file_control()
{ int i;
    for (i=0;i<MAX_FILE;i++)
    { file[i]=NULL; }
}

int openFile(char * file_name, char * mode)
{ int index = FALSE;
  
    if (file1)
    file1 = fopen(file_name,mode);
    if (file1) {bool = TRUE;}
    
    return index;
}

void closeFile(char c)
{ switch (c)
        case '1':   fclose(file1);
                    break;
        case '2':   fclose(file2);
                    break;
}

int dynamic_read_line(char** buf, int* size)
{   char* offset;
	int old_size;
    
	if (!fgets(*buf, *size, file))
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
	} while ( fgets(offset, old_size + 1, file) && offset[strlen(offset) - 1] != '\n' );
    
	return 0;
}

















