/**********************************************************************************
*
*  Raj Maitra
*  Rmaitra
*  pa5  
*  
***********************************************************************************/
#if !defined(_LIST_H_INCLUDE_)
#define _LIST_H_INCLUDE_


/***************************** Exported Types *************************************/
typedef struct List * ListRef;


/************** Constructors-Destructors ******************************************/

/*
*  newList
*  Returns ListRef pointing to new ListStruct which represents an empty List.
*  Initializes front and back fields to NULL, sets length field to 0.  Exported.
*/
ListRef newList(void);

/*
*  freeList
*  Frees all heap memory associated with the ListRef *pL, including all memory
*  in existing Nodes.  Sets *pL to NULL.  Exported.
*/
void freeList(ListRef* pL);


/***************** Access functions ***********************************************/

/*
*  getFront
*  Returns the value at the front of L.
*  Pre: !isEmpty(L)
*/
int getFront(ListRef L);
int getBack(ListRef L);
int getCurrent(ListRef L);

/*
*  getLength
*  Returns the length of Q
*/
int getLength(ListRef L);
int getIndex(ListRef L);

/*
*  isEmpty
*  Returns True if L is empty, otherwise returns false
*/
int isEmpty(ListRef L);
int offEnd(ListRef L);


/****************************** Manipulation procedures ***************************/

void makeEmpty(ListRef L);
void moveTo(ListRef L, int data);
void movePrev(ListRef L);
void moveNext(ListRef L);

/*
*  insertBack
*  Places new data element at the end of Q
*  Post: !isEmpty(Q)
*/
void insertFront(ListRef L, int data);
void insertBack(ListRef L, int data);
void insertBeforeCurrent(ListRef L, int data);
void insertAfterCurrent(ListRef L, int data);

/*
*  deleteFront
*  Deletes element at front of Q
*  Pre: !isEmpty(Q)
*/
void deleteFront(ListRef L);
void deleteBack(ListRef L);
void deleteCurrent(ListRef L);


/*************** Other Functions *************************************************/

/*
*  printQueue
*  Prints data elements in Q on a single line to stdout.
*/
void printList(FILE *out, ListRef L);
void printflist(ListRef L);

/*
*  equals
*  returns true if A is identical to B, false otherwise
*/
int equals(ListRef L, ListRef P);
ListRef copyList(ListRef L);


#endif
