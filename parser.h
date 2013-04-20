//
//  parser.h
//  LI3
//
//  Created by Axel Ferreira on 2/27/13.
//  Copyright (c) 2013 Axel Ferreira. All rights reserved.
//

#ifndef LI3_A_h
#define LI3_A_h
//////////////////////////////////////////////////////////////////////////////////////////////

typedef struct sStats
{   char * nomes;                   // buffer com os autores
    int nAutores;                   // Numero de autores
    int ano;                        // Ano
}Stats;

//////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Patses a Line 
 * @param buffer the buffer containing the line to be parsed
 * @param ty+he type of the line conference or jounal)
 * @return Struct with all counters.
 */
Stats parseLine(char * buffer, char t);


/**
 * @param pag Sets the minimum number of pages requiered for an article to be accepted.
 */
void setMinPag();

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
 * This function trims the first occurence
 *
 */
char * trim();


#endif
