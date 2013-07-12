/**********************************************************************************
*  
*   Raj Maitra
*   Rmaitra
*   Assignment: pa5
*  
***********************************************************************************/

#include<stdio.h>
#include"List.h"

int main(int argc, char* argv[]){
   int i;
   ListRef A = newList();
   ListRef B = newList();
   ListRef X = NULL;
  
   /* Test Initialized Access Functions */
   printf("---------------Test Initializations:----------------\n");
   printf("Index\n");
   printf("%d\n", getIndex(A));
   printf("Length\n");
   printf("%d\n\n", getLength(A));

   /* Test Insertion Back and Insertion Front */
   printf("---------------Test Insertion Back and Front:----------------\n");
   printf("Inserting Back for List A and Front for List B...\n");
   for(i=1; i<=6; i++){
      insertBack(A, i);
      insertFront(B, i);
      printflist(A);
      printflist(B);
   }
   printf("Inserting Front for List A and Back for List B...\n");
   for(i=1; i<=6; i++){
      insertFront(A, i);
      insertBack(B, i);
      printflist(A);
      printflist(B);
   }

   /* Test Move To */
   printf("------------------Test moveTo:-----------------------\n");
   printf("Move A to index:3\n");
   moveTo(A, 3);
   printf("%d\n", getIndex(A));
   printf("Move B to index:9\n");
   moveTo(B, 9);
   printf("%d\n\n", getIndex(B));

   /* Test Current Marker Functions */
   printf("----------------Test current:---------------------\n");
   printf("getCurrent(A) should be index 3:\n");
   printflist(A);
   printf("%d\n", getCurrent(A));
   printf("getCurrent(B) should be index 9:\n");
   printflist(B);
   printf("%d\n\n", getCurrent(B));
   

   /* Test Equals Function */
   printf("----------------Test Equals:---------------------\n");
   printf("equals(A,B)?\n");
   printf("%s\n", equals(A,B)?"true":"false");
   printf("equals(A,A)?\n");
   printf("%s\n", equals(A,A)?"true":"false");
   printf("\n");

   /* Test delete Back, Front and Current Functions */
   printf("----------------Test Delete Functions:---------------------\n");
   printf("deleteCurrent A and B\n");
   printflist(A);
   printflist(B);
   deleteCurrent(A);
   deleteCurrent(B);
   printflist(A);
   printflist(B);
   printf("deleteBack A and B\n");
   printflist(A);
   printflist(B);
   deleteBack(A);
   deleteBack(B);
   printflist(A);
   printflist(B);
   printf("deleteFront A and B\n");
   printflist(A);
   printflist(B);
   deleteFront(A);
   deleteFront(B);
   printflist(A);
   printflist(B);

   /* Test insert Current Before and After List */
   printf("----------------Test insertCurrent Before and After:---------------------\n");
   printf("Move A to index:2\n");
   moveTo(A, 2);
   printf("%d\n", getIndex(A));
   printf("Move B to index:4\n");
   moveTo(B, 4);
   printf("%d\n\n", getIndex(B));
   printf("insertCurrentBefore A\n");
   insertBeforeCurrent(A, 99);
   printf("insertCurrentBefore B\n");
   insertBeforeCurrent(B, 99);
   printflist(A);
   printflist(B);
   printf("insertCurrentAfter A\n");
   insertAfterCurrent(A, 44);
   printf("insertCurrentAfter B\n");
   insertAfterCurrent(B, 44);
   printflist(A);
   printflist(B);
   
   /* Test makeEmpty List */
   printf("----------------Test makeEmpty:---------------------\n");
   printf("Length of A:%d\n", getLength(A));
   printf("Length of B:%d\n", getLength(B));
   X = copyList(A);
   makeEmpty(A);
   makeEmpty(B);
   printflist(A);
   printflist(B);

   /* Test makeEmpty List */
   printf("----------------Test Last Insert:---------------------\n");
   insertBack(A, 1);
   insertBack(B, 8);
   printflist(A);
   printflist(B);

   /* Test copy List */
   printf("----------------Test Copy List:---------------------\n");
   printflist(X);
   
   freeList(&X);
   freeList(&B);
   freeList(&A);
 

   return(0);
}
