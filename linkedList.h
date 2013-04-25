//
//  linkedList.h
//  
//
//  Created by Axel Ferreira on 3/20/13.
//  Copyright (c) 2013 Axel Ferreira. All rights reserved.
//

#ifndef linkedList_h
#define linkedList_h

#define TRUE 1
#define FALSE 0

#define MAX_LLIST 10


/**
 * init function initializes the structure
 * 
 * @param size the size of the data.
 * @param function that compares the data type
 * @return number of the pos of the list in the handle, 0 otherwise
 */
int init (int size, int (* compare)(void *, void *));

/**
 * insert function inserts a new node in the list pointed by the handle
 * 
 * @param the pointer to the list.
 * @param the pointer to the data.
 * @return 1 if ok, 0 otherwise
 */
int insert (int handle, void * data);

/**
 * search function finds the data in the list pointed by the handle
 * 
 * @param the pointer to the list.
 * @param the pointer to the data.
 * @return pointer to the node if found, NULL otherwise.
 */
void * searchNode (int handle, void * data);

/**
 * removes the data in the lst pointed by the handle
 * 
 * @param the pointer to the list.
 * @param the pointer to the data.
 * @return 1 if removed, 0 otherwise
 */
int removeNodo (int handle, void * data);

/**
 * frees the hole list pointed by the handle
 * 
 * @param the pointer to the list.
 * @return 1 if ok, 0 otherwise
 */
int clean (int handle);


#endif
