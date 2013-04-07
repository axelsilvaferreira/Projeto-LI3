//
//  fwrite.h
//  LI3
//
//  Created by Axel Ferreira on 4/3/13.
//  Copyright (c) 2013 Axel Ferreira. All rights reserved.
//

#ifndef LI3_fwrite_h
#define LI3_fwrite_h



/**
 * This function outputs the number of rejected entries in each file to the "E.txt" file. If the file does not exist, it is created.
 * @param int counter number of invalid entries in the file.
 * @param char * fileN the name of the courent file.
 */
void imprimeE(int bool, int counter, char * file, char * path);

/**
 * This function creates the file "D.txt" and it's content. If the file alreaddy exists, it is rewritten.
 * @param nRej the number of rejected entries
 * @param nJou the number of Journals
 * @param nCou the number of Counferences
 * @param path the path of the file to be written to.
 */
void imprimeD(int nRej, int nJou, int nCou, char * path);



#endif
