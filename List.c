/**********************************************************************************
*  
*  Raj Maitra
*  Rmaitra
*  pa5 
*
***********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

/************** Private Structs: not exported *************************************/

typedef struct Node{
   int data;
   struct Node* next;
   struct Node* previous;
} Node;

typedef Node* NodeRef;

typedef struct List{
   NodeRef front;
   NodeRef back;
   NodeRef current;
   int length;
   int index;
} List;


/************** Constructors-Destructors ******************************************/

/*
*  newNode
*  Returns pointer to new Node struct. Initializes next field to NULL, and sets
*  data field to input parameter node_data. Private.
*/
NodeRef newNode(int node_data){
   NodeRef N = malloc(sizeof(Node));
   N->data = node_data;
   N->next = NULL;
   N->previous = NULL;
   return(N);
}

/*
*  freeNode
*  Frees heap memory pointed to by pN. Private.
*/
void freeNode(NodeRef* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}


/*
*  newList
*  Returns ListRef pointing to new ListStruct which represents an empty List.
*  Initializes front and back fields to NULL, sets length field to 0.  Exported.
*/
ListRef newList(void){
   ListRef L = malloc(sizeof(List));
   L->front = NULL;
   L->back = NULL;
   L->current = NULL;
   L->length = 0;
   L->index = -1; 
   return(L);
}

/*
*  freeList
*  Frees all heap memory associated with the ListRef *pL, including all memory
*  in existing Nodes.  Sets *pL to NULL.  Exported.
*/
void freeList(ListRef* pL){
   if(pL==NULL || *pL==NULL) { return; }
   while( !isEmpty(*pL) ) { deleteBack(*pL); }
   free(*pL);
   *pL = NULL;
}



/***************** Access functions ***********************************************/


/*  getFront  */
int getFront(ListRef L){
   if( L==NULL ){
      printf("List Error: calling getFront() on NULL ListRef\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling getFront() on an empty List\n");
      exit(1);
   }
   return(L->front->data);
}
/*
*  getBack
*  Returns the value at the front of L.
*  Pre: !isEmpty(Q)
*/
int getBack(ListRef L){
   if( L==NULL ){
      printf("List Error: calling getBack() on NULL ListRef\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling getBack() on an empty List\n");
      exit(1);
   }
   return(L->back->data);
}
/*
*  getCurrent
*  Returns the value at the front of L.
*  Pre: !isEmpty(L)
*/
int getCurrent(ListRef L){
   if( L==NULL ){
      printf("List Error: calling getCurrent() on NULL ListRef\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling getCurrent() on an empty List\n");
      exit(1);
   }
   if( offEnd(L) ){
      printf("List Error: calling getCurrent() when off the end of the List\n");
      exit(1);
   }
   return(L->current->data);
}

/*
*  getLength
*  Returns the length of Q
*/
int getLength(ListRef L){
   if( L==NULL ){
      printf("List Error: calling getLength() on NULL ListRef\n");
      exit(1);
   }
   return(L->length);
}
/*
*  getIndex
*  Returns the length of Q
*/
int getIndex(ListRef L){
   if( L==NULL ){
      printf("List Error: calling getIndex() on NULL ListRef\n");
      exit(1);
   }
   return(L->index);
}

/*
*  isEmpty
*  Returns True if Q is empty, otherwise returns 0
*/
int isEmpty(ListRef L){
   if( L==NULL ){
      printf("List Error: calling isEmpty() on NULL ListRef\n");
      exit(1);
   }
   return(L->length==0);
}

int offEnd(ListRef L){
   if( L->index==-1 ){
      printf("List Error: calling offEnd() when not on the List\n");
      exit(1);
   }
   return(0);
}


/**************** Manipulation procedures ****************************************/

/*   makeEmpty   */
void makeEmpty(ListRef L){
  while(L->length > 0){
     deleteBack(L);
  }  
} 

/*   moveTo   */
void moveTo(ListRef L, int i){
   int j;
   if( isEmpty(L) ){
      printf("List Error: calling moveNext() on Empty List\n");
      exit(1);
   }
   if(i == 0){
      L->current = L->front;
      L->index = 0;
   } 
   if(i == L->length-1){
      L->current = L->back;
      L->index = 0;
   }
   else{
      L->current = L->front;
      L->index = 0;
      for(j = 0; j<i; j++){
         moveNext(L);
      } 
   }
}

/*     movePrev   */
void movePrev(ListRef L){
   if( L==NULL ){
      printf("List Error: calling moveNext() on NULL ListRef\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling moveNext() on Empty List\n");
      exit(1);
   }
   if( L->index==-1 || L->index<=0){
      printf("List Error: calling offEnd() when not on the List\n");
      exit(1);
   }
   L->current = L->current->previous;
   L->index--;
}

/*   moveNext  */
void moveNext(ListRef L){
   if( L==NULL ){
      printf("List Error: calling moveNext() on NULL ListRef\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling moveNext() on Empty List\n");
      exit(1);
   }
   if( L->index ==-1 || L->index >= L->length){
      printf("List Error: calling offEnd() when not on the List\n");
      exit(1);
   }
   L->current = L->current->next;
   L->index++;
}


/* insertFront */
void insertFront(ListRef L, int data){

   if( L==NULL ){
      printf("List Error: calling insertFront() on NULL ListRef\n");
      exit(1);
   }
   NodeRef N = newNode(data);
   if( isEmpty(L) ){
      L->front = L->back = N;
      L->current = N;
      L->index = 0;  
   }
   else{        
      N->next = L->front;           
      L->front->previous = N;      
      L->front = N;               
      L->current = L->front;
      L->index = 0;
   }
   L->length++;
}

/* insert Back*/
void insertBack(ListRef L, int data){
   if( L==NULL ){
      printf("List Error: calling insertBack() on NULL ListRef\n");
      exit(1);
   }
   NodeRef N = newNode(data);
   if( isEmpty(L) ){
      L->front = L->back = N;
      L->current = N; 
      L->index = 0;
   }
   else{             
      N->previous = L->back;               
      L->back->next = N;                 
      L->back = N;                        
      L->current = L->back;
      L->index = L->length-1;
   }
   L->length++;
}

/*/insertBeforeCurrent*/
void insertBeforeCurrent(ListRef L, int data){

   if( L==NULL ){
      printf("List Error: calling insertBeforeCurrent() on NULL ListRef\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling insertBeforeCurrent() on an Empty List\n");
      exit(1);
   }
   if( getIndex(L) ==0){
     insertFront(L, data); 
   }
   else{ 
      NodeRef N = newNode(data);
      N->next = L->current;
      N->previous = L->current->previous;
      L->current->previous->next = N;
      L->current->previous = N;
      L->current = L->current->previous;
      L->current->next = N->next;
      L->current->previous = N->previous;
      L->length++;
   }
}

/*/insertAfterCurrent*/
void insertAfterCurrent(ListRef L, int data){

   if( L==NULL ){
      printf("List Error: calling insertAfterCurrent() on NULL ListRef\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling insertAfterCurrent() on an Empty List\n");
      exit(1);
   }
   if( getIndex(L)==getLength(L)-1){
      insertBack(L, data);
   }
   else{ 
      NodeRef N = newNode(data);
      N->previous = L->current;
      N->next = L->current->next;
      L->current->next->previous = N;
      L->current->next = N;
      L->current = L->current->next;
      L->current->next = N->next;
      L->current->previous = N->previous;
      L->index++; 
   }
}


/*  deleteFront  */
void deleteFront(ListRef L){
   NodeRef N = NULL;

   if( L==NULL ){
      printf("List Error: calling deleteFront() on NULL ListRef\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling deleteFront() on an empty List\n");
      exit(1);
   }
   N = L->front;
   if( getLength(L)>1 ){
      L->front = L->front->next;
      L->front->previous = NULL;
      L->current = L->front;
   }
   else { 
      L->front = L->back = NULL; 
      L->current = NULL;
   }
   L->length--;
   freeNode(&N);
}

/*   deleteBack  */
void deleteBack(ListRef L){
   NodeRef N = NULL;

   if( L==NULL ){
      printf("List Error: calling deleteBack() on NULL ListRef\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling deleteBack() on an empty List\n");
      exit(1);
   }
   N = L->back;
   if( getLength(L)>1 ){
      L->back = L->back->previous; 
      L->back->next = NULL;
      L->current = L->back;
   }
   else { 
      L->front = L->back = NULL; 
      L->current = NULL;
   }
   L->length--;
   freeNode(&N);
}

/*   deleteCurrent  */
void deleteCurrent(ListRef L){
   NodeRef N = NULL;

   if( L==NULL ){
      printf("List Error: calling deleteCurrent() on NULL ListRef\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling deleteCurrent() on an empty List\n");
      exit(1);
   }
   if(L->index == L->length-1){
      deleteBack(L);
   }
   else if(L->index == 0){
      deleteFront(L);
   }
   else if( getLength(L)>1 ){
      N = L->current;
      L->current->next->previous = L->current->previous;
      L->current->previous->next = L->current->next;
      L->current = NULL; 
      L->length--;
   }
   else { 
      N = L->current;
      L->front = L->back = NULL; 
      L->current = NULL;
      L->length--;
   }
   L->index = -1;
   freeNode(&N);
}

/*************** Other Functions *************************************************/

/*
*  printList
*  Prints data elements in L on a single line to stdout.
*/
void printList(FILE *out, ListRef L){
   int i;  

   if( L==NULL ){
      printf("List Error: calling printList() on NULL ListRef\n");
      exit(1);
   }
   for(i = 1; i<=getLength(L); i++){
      moveTo(L, i-1); 
      fprintf(out, "%d", getCurrent(L));
      if(i<getLength(L)){
         fprintf(out, " ");
      }
   }
}

/*
*  equals
*  returns 1 if A is identical to B, 0 otherwise
*/
int equals(ListRef A, ListRef B){
   int flag = 1;
   Node* N = NULL;
   Node* M = NULL;

   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL ListRef\n");
      exit(1);
   }
   N = A->front;
   M = B->front;
   if( A->length != B->length ) { return 0; }
   while( flag && N!=NULL){
      flag = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return flag;
}
 
/* copyList  */
ListRef copyList(ListRef L){
   ListRef X = newList();
   int i;
   if( L == NULL){
      printf("List Error: calling printList() on NULL ListRef\n");
      exit(1);
   }
   moveTo(L, 0);
   insertBack(X, getCurrent(L));
   for(i = 1; i<L->length; i++){
      moveNext(L);
      insertBack(X, getCurrent(L));
   }
   return(X);
} 
void printflist(ListRef L){
   Node* N = NULL;

   if( L==NULL ){
      printf("Queue Error: calling printQueue() on NULL QueueRef\n");
      exit(1);
   }
   for(N = L->front; N != NULL; N = N->next){
      printf("%d ", N->data);
   }
   printf("\n");
}






