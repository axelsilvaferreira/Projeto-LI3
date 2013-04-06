//
//  parser.h
//  LI3
//
//  Created by Axel Ferreira on 2/27/13.
//  Copyright (c) 2013 Axel Ferreira. All rights reserved.
//

#ifndef LI3_A_h
#define LI3_A_h
//typedef struct sStats;

/**
 * @return Struct with all counters.
 */
struct sStats parseLine(char * buffer, char t);


/**
 * @param pag Sets the minimum number of pages requiered for an article to be accepted.
 */
void setMinPag();


/**
 * Opens the "lista.txt" file and saves the minimum page number for an article to be accepted.
 * Also for every file listed it opens the file and cals the function @func validEntry() with every entry in each file.
 */
void process();




/**
 * This function validates each entry for a B file.
 * The function calls a function for each token, validating every entry.
 * It also increments the counters: Conference and/or Journal and/or Article and/or Rejected.
 * @param char * fileN the name of the file to be validated.
 * @param int tipo tels if it's a Conference or Journal.
 */
int validFile();


/**
 * This function validates the Journal number. By checking if any of the characters are not digits, if so the function returns the flag as FALSE.
 * @param char * token to be validated.
 * @return flag the flag (TRUE if valid field, FALSE otherwise)
 */
int validaNumeroR();

/**
 * This function validates the Journal volume. By checking if any of the characters are not digits, if so the function returns the flag as FALSE.
 * @param char * token to be validated.
 * @return flag the flag (TRUE if valid field, FALSE otherwise)
 */
int validaVolume();

/**
 * This function validates the initial number. By checking if any of the characters are not digits, if so the function returns the flag as FALSE.
 * @param char * token to be validated.
 * @return flag the flag (TRUE if valid field, FALSE otherwise)
 */
int validaNumeroI();

/**
 * This function validates the title of the Entry. By checking if the title is NULL, if so the function returns the flag as FALSE.
 * @param char * token to be validated.
 * @return flag the flag (TRUE if valid field, FALSE otherwise)
 */
int validaTitulo();

/**
 * This function validates the authors of the Entry. By checking if the authors field is NULL, if so the function returns the flag as FALSE.
 * @param char * token to be validated.
 * @return flag the flag (TRUE if valid field, FALSE otherwise)
 */
int validaAutores();

/**
 * This function validates the Journal acronym. By checking if the acronym token is NULL, if so the function returns the flag as FALSE.
 * @param char * token to be validated.
 * @return flag the flag (TRUE if valid field, FALSE otherwise)
 */
int validaSiglaJour();

/**
 * This function validates the Journal Name. By checking if the name is NULL, if so the function returns the flag as FALSE.
 * @param char * token to be validated.
 * @return flag the flag (TRUE if valid field, FALSE otherwise)
 */
int validaNomeJour();

/**
 * This function validates the Name of the Conference. By checking if the name is NULL, if so the function returns the flag as FALSE.
 * @param char * token to be validated.
 * @return flag the flag (TRUE if valid field, FALSE otherwise)
 */
int validaNomeConfData();

/**
 * This function validates the Year in the Entry. By checking if the characters are not digits. If so the function returns the flag as FALSE.
 * @param char * token to be validated.
 * @return flag the flag (TRUE if valid field, FALSE otherwise)
 */
int validaAno();

/**
 * This function validates the minimum page number. By checking if the characters are both all digits and the difference between them is greater than the minimum acceptable pages. If not the function returns the flag as FALSE.
 * @param char * token to be validated.
 * @return flag the flag (TRUE if valid field, FALSE otherwise)
 */
int validaPaginas();


/**
 *
 **/
int leNumero();

/**
 *
 **/
int leAutores();

/**
 *
 **/




#endif
