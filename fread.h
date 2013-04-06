//
//  fread.h
//  LI3
//
//  Created by Axel Ferreira on 4/3/13.
//  Copyright (c) 2013 Axel Ferreira. All rights reserved.
//

#ifndef LI3_Ficheiros_h
#define LI3_Ficheiros_h

#define MAX_FILE 10

/**
 * Initializes the control for the files
 */
void init_file_control();

/**
 * Opens a file.
 * @return file index in control.
 */
int openFile(char * file_name, char * mode);

/**
 * Closes a file.
 * @param file_name the name of the file to be closed.
 */
void closeFile(char * file_name);

/**
 * Reads a line from a file growing the buffer as needed.
 * @return 0 if success -1 otherwise.
 */
int dynamic_read_line(char** buf, int* size);



#endif
