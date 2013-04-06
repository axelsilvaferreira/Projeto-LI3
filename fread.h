//
//  fread.h
//  LI3
//
//  Created by Axel Ferreira on 4/3/13.
//  Copyright (c) 2013 Axel Ferreira. All rights reserved.
//

#ifndef LI3_Ficheiros_h
#define LI3_Ficheiros_h

//Macro for the maximum number of files to be used at once
#define MAX_FILE 60


/**
 * Returns the file of a given index.
 */
FILE * getFile(int index);

/**
 * Initializes the control for the files
 */
void init_file_control();

/**
 * Opens a file.
 * @return file index in control, or -1 if failed.
 */
int openFile(char * file_name, char * mode);

/**
 * Closes a file.
 * @param index of the file to be closed.
 */
void closeFile(int index);

/**
 * Reads a line from a file growing the buffer as needed.
 * @param a reference to the buffer reference.
 * @param a reference for the size of the buffer.
 * @param file index in control.
 * @return 0 if success -1 otherwise.
 */
int dynamic_read_line(char** buf, int* size, int file);



#endif
