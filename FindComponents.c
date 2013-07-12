/*****************************************************************************
* 
*  Raj Maitra
*  Rmaitra
*  Assignment: pa5 
* 
******************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"
#include "List.h"

#define MAX_LEN 250

int main(int argc, char * argv[]){

   int u, v, i;
   FILE *in, *out;
   char line[MAX_LEN];
   char tokenlist[MAX_LEN];
   char* token;
   int var;

   ListRef numList = newList();
   ListRef L = newList();
   ListRef scc = newList();

   /* check command line for correct number of arguments */
   if( argc != 3 ){
      printf("Usage: %s infile outfile\n", argv[0]);
      exit(1);
   }

   /* open files for reading and writing */
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   
   /* read each line of input file, then count and print tokens */
   fgets(line, MAX_LEN, in); 
   token = strtok(line, " ");
   tokenlist[0] = '\0';
   sscanf(token, "%d", &var);
  
   /* Initialize Graph G */  
   GraphRef G = newGraph(var);
   GraphRef Q = newGraph(var);

   /* Make Adjacency List */
   while( fgets(line, MAX_LEN, in) != NULL)  {
      token = strtok(line, " ");
      tokenlist[0] = '\0';
      while( token!=NULL ){
         sscanf(token, "%d", &var);
         insertBack(numList, var);
         token = strtok(NULL, " \n");
      }
      if(var == 0){
         break;
      }
      moveTo(numList, 0);
      u = getCurrent(numList);
      moveNext(numList);
      v = getCurrent(numList);
      addArc(G, u, v);
      makeEmpty(numList);
   }
   makeEmpty(numList);

   /* build Adj */
   while( fgets(line, MAX_LEN, in) != NULL)  {
      token = strtok(line, " ");
      tokenlist[0] = '\0';
      while( token!=NULL ){
         sscanf(token, "%d", &var);
         insertBack(numList, var);
         token = strtok(NULL, " \n");
      }
      if(var == 0){
         break;
      }
      moveTo(numList, 0);
      u = getCurrent(numList);
      moveNext(numList);
      v = getCurrent(numList);
   }

   /* DFS */
   for(i=1;i<=getOrder(G);i++){
      insertBack(L, i);
   }
   DFS(G, L);
   Q = transpose(G);
   DFS(Q, L);
   
   moveTo(L, 0);
   u = getCurrent(L);
   moveNext(L);
   v = 0;
   for(i=1;i<=getOrder(Q);i++){
      insertFront(scc, u);  
      if(getParent(Q, u) == 0){
         v = v+1;
      }
      if(getIndex(L) < getLength(L)){
         u = getCurrent(L);
         moveNext(L);
      }
   }
   
   fprintf(out, "Adjacency list representation of G:\n"); 
   printGraph(out, G);
   fprintf(out, "\n\n");
   fprintf(out, "G contains %d strongly connected components:\n", v); 
   
   makeEmpty(L);
   moveTo(scc, 0);
   u = getCurrent(scc);
   var = v+1;

   while(v > 0){
      if(getParent(Q, u) != 0){ 
         insertFront(L, u);
      }
      else{
         insertFront(L, u);
         fprintf(out, "Component %d: ", var-v); 
         printList(out, L);
         makeEmpty(L);
         fprintf(out, "\n"); 
         v = v-1;
      }
      if(getIndex(scc)<getLength(scc)-1){
         moveNext(scc);
         u = getCurrent(scc);
      }
   }
   
   freeList(&L);
   freeList(&scc);
   freeList(&numList);
   freeGraph(&G);
   freeGraph(&Q);
    
   /* close files */
   fclose(in);
   fclose(out);

   return(0);
}


