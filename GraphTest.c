/**********************************************************************************
*  
*   Raj Maitra
*   Rmaitra
*   Assignment: pa5
*  
***********************************************************************************/

#include<stdio.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[]){
   int i;
   GraphRef G = newGraph(6);
   GraphRef Q;
   ListRef L = newList();
  
   /* Test Initialized Access Functions */
   printf("---------------Test Initializations:----------------\n");
   printf("Order\n");
   printf("%d\n", getOrder(G));
   printf("Size\n");
   printf("%d\n\n", getSize(G));
   printf("Source\n");
   printf("%d\n\n", getSource(G));
   printfGraph(G);

   /* Test Insertion Back and Insertion Front */
   printf("---------------Test addEdge:----------------\n");
   printf("add arc between 1 -> 2\n");
   addArc(G, 1, 2);
   printf("Size\n");
   printf("%d\n\n", getSize(G));
   printf("add arc between 1 -> 3\n");
   addArc(G, 1, 3);
   printf("Size\n");
   printf("%d\n\n", getSize(G));
   printf("add arc between 2 -> 4\n");
   addArc(G, 2, 4);
   printf("Size\n");
   printf("%d\n\n", getSize(G));
   printf("add arc between 2 -> 5\n");
   addArc(G, 2, 5);
   printf("Size\n");
   printf("%d\n\n", getSize(G));
   printf("add arc between 4 -> 6\n");
   addArc(G, 4, 6);
   printf("Size\n");
   printf("%d\n\n", getSize(G));
   printfGraph(G);
   

   /* Test DFS */
   printf("------------------Test DFS:-----------------------\n");
   for(i=1;i<=getOrder(G);i++){
      insertBack(L, i);
   }
   DFS(G, L);
   printflist(L);

 
   /* Test Transpose */
   printf("------------------Test Transpose:-----------------------\n");
   Q = transpose(G);
   printfGraph(Q);

   /* Test Copy */
   printf("------------------Test Copy:-----------------------\n");
   Q = copyGraph(G);
   printfGraph(Q);
   
   freeList(&L);
   freeGraph(&G);

   return(0);
}
