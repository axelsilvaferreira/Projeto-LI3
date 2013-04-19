//
//  est_fase2.h
//  LI3
//
//  Created by Axel Ferreira on 2/27/13.
//  Copyright (c) 2013 Axel Ferreira. All rights reserved.
//

#ifndef LI3_F_h
#define LI3_F_h



/**
 * This function allows to add an article with a given year and a given #Author
 * @param the year of publication
 * @param nAutor the number of authors that made the article
 * @retuen returns 1 if ok 0 otherwise
 */
int addEntry(int ano, int nAutor);

/**
 * This function creates the file "G.csv" and it's content. If the file alreaddy exists it is rewritten.
 * @param bool if it's first time opens in "w" mode else in "a".
 */
int imprimeG(int bool);
















#endif