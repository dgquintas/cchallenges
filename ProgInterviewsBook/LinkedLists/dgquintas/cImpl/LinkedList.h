#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <assert.h> 
#include <stdlib.h> 

/*
 * we use typedef to be able to save the "struct" bit
 * every time we wanna refer to the newly created type.
 * Hadn't I used it, I'd have to always instantiate elements
 * by using "struct ListElement_" instead of just "ListElement"
 * @see http://publications.gbdirect.co.uk/c_book/chapter6/structures.html
 */

/** 
 * @struct ListElement
 * A "link" in the chain.
 */
typedef struct ListElement_ {
  struct ListElement_ *next; /**< pointer to the next element. Or NULL if none */
  void *data; /**< the actual data contained in this element. */
} ListElement;

/** 
 * @struct List.
 * The list "handle"
 */
typedef struct List_ {
  ListElement *head; /**< Beginning of the single linked list. */
  ListElement *tail; /**< End of the list. ie, its *next -> NULL */

  int size; /**< List's length. Duh */

  /** Destructor function. 
   *
   * Sometimes, the data stored in *data needs to be fred in an 
   * special way. It's this function's responsability to do so. 
   * In general, it'd usually be just the standard "free" function */
  void (*destroy)(void *data); 
} List;

/* LIST INTERFACE */

/** Initialize list. 
 *
 * @arg list the list.
 * @arg destroy a function pointer: the destructor for the list data.
 *
 * */
void list_init(List* const list, void (*destroy)(void *data));


/** Destroy list */

/** Get element.
 *
 * @arg list the list
 * @arg i the index 
 *
 * @return the value of the i-th element of the list
 *
 * */
void* list_get(const List* const list, int i);


/** Get head.
 *
 * @arg list the list
 *
 * @return the first element of the list
 *
 * */
#define list_getHead(list) ((list)->size)

/** Get tail
 *
 * @arg list the list.
 *
 * @return the last element of the list.
 *
 * */
#define list_getTail(list) ((list)->tail)

/** Get size.
 *
 * @arg list the list 
 *
 * @return the size of @a list
 * */
#define list_getSize(list) ((list)->size)

/** Add element.
 *
 * Adds to the end of the list (appends)
 *
 * @arg data the data to be added.
 *
 * @return 0 upon success. Else otherwise.
 *
 */
int list_add(List* const list, void* data);

/** Insert element.
 *
 * @arg list the list.
 * @arg pos the index before which to insert the new data. 
 * @arg data the data to insert
 *
 * @return 0 upon success. Else otherwise.
 * */
int list_insert(List* const list, const int pos, void* data);


/** Remove element.
 *
 * @arg list the list.
 * @arg pos the index of the element to remove. 
 *
 * @return 0 upon success. Else otherwise. 
 *
 * */
int list_remove(List* const list, const int pos);



#endif


