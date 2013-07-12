/**********************************************************************************
*  
*  Raj Maitra
*  Rmaitra
*  pa5 
*
***********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"

/************** Private Structs: not exported *************************************/

typedef struct Graph{
   ListRef *adj;
   int *color;
   int *parent;
   int *distance;
   int *discover;
   int *finish;
   int size;
   int order;
   int source;
} Graph;


/************** Constructors-Destructors ******************************************/

/*GraphRef Constructor*/
GraphRef newGraph(int n){
   int i; 

   GraphRef G = malloc(sizeof(Graph));
   G->adj = calloc(n+1, sizeof(ListRef));
   G->color = calloc(n+1, sizeof(int));
   G->parent = calloc(n+1, sizeof(int));
   G->distance = calloc(n+1, sizeof(int));
   G->discover = calloc(n+1, sizeof(int));
   G->finish = calloc(n+1, sizeof(int));
   for(i=1;i<=n;i++){
      G->adj[i] = newList();
      G->color[i] = 1;
      G->parent[i] = -1;
      G->distance[i] = -1;
      G->discover[i] = 0;
      G->finish[i] = 0;
   }
   G->order = n;
   G->size = 0;
   G->source = 0;
   return(G);
}

/* freeGraph */
void freeGraph(GraphRef* pG){
   int i;
   if(pG==NULL || *pG==NULL) { return; }
   for(i=0;i<=(*pG)->order;i++){
      freeList(&(*pG)->adj[i]);
   }
   free((*pG)->adj);
   free((*pG)->color);
   free((*pG)->parent);
   free((*pG)->distance);
   free((*pG)->discover);
   free((*pG)->finish);
   free(*pG);
   *pG = NULL;
}



/***************** Access functions ***********************************************/

/* getOrder */
int getOrder(GraphRef G){
   return(G->order);
}

/* getSize */
int getSize(GraphRef G){
   return(G->size);
}

/* getSource */
int getSource(GraphRef G){
   return(G->source);
}

/* getParent */
int getParent(GraphRef G, int u){
   if(G->parent[u] == -1){
      printf("Graph Error: calling getParent() on graph without running DFS \n");
      exit(1);
   }
   return(G->parent[u]);
}

/* getDiscover */
int getDiscover(GraphRef G, int u){
   if(G->discover[u] == -1){
      printf("Graph Error: calling getDiscover() on graph without running DFS \n");
      exit(1);
   }
   return(G->discover[u]);
}

/* getFinish */
int getFinish(GraphRef G, int u){
   if(G->finish[u] == -1){
      printf("Graph Error: calling getFinish() on graph without running DFS \n");
      exit(1);
   }
   return(G->finish[u]);
}
/* getDist */
int getDist(GraphRef G, int u){
   if(G->parent[u] == 0){
      return(0);
   }
   return(G->distance[u]);
}

/*  getPath */
void getPath(ListRef L, GraphRef G, int u){
   int w;

   makeEmpty(L);
   if(getSource(G) == 0){
      printf("Graph Error: calling getPath() on graph without running BFS \n");
      exit(1);
   }
   if(G->color[u] == 1){
      return;
   }
   else{
      insertFront(L, u);
      w = u;
      while(G->distance[w] > 0){
         insertFront(L, G->parent[w]);
         w = G->parent[w];
      }
   }     
}

/**************** Manipulation procedures ****************************************/

/*   makeNull */
void makeNull(GraphRef G){
   int i;

   G->size = 0;
   for(i=1;i<=G->order;i++){
      makeEmpty(G->adj[i]);
      G->color[i] = 1;
      G->parent[i] = 0;
      G->distance[i] = -1;
   }
}
 
/*   resetBFS  */
void resetBFS(GraphRef G){
   int i;

   G->source = 0;
   for(i=1;i<=G->order;i++){
      G->color[i] = 1;
      G->parent[i] = 0;
      G->distance[i] = -1;
   }
}

/*   addEdge */
void addEdge(GraphRef G, int u, int v){
   if(isEmpty(G->adj[u])){ 
      insertBack(G->adj[u], v);
   }
   else if(!isEmpty(G->adj[u])){
      putEdgeArc(G, u, v);
   }
   if(isEmpty(G->adj[v])){ 
      insertBack(G->adj[v], u);
   }
   else if(!isEmpty(G->adj[v])){
      putEdgeArc(G, v, u);
   }
   G->size++;
} 

/*   putEdgeArc */
void putEdgeArc(GraphRef G, int u, int v){
    moveTo(G->adj[u], 0);
    while(1){
       if(getCurrent(G->adj[u]) < v && getIndex(G->adj[u]) < getLength(G->adj[u])-1){
          moveNext(G->adj[u]);
       }
       else if(getCurrent(G->adj[u]) > v ){
          insertBeforeCurrent(G->adj[u], v);
          break;
       }
       else{
          insertBack(G->adj[u], v);
          break;
       }
    }
}

/*   addArc */
void addArc(GraphRef G, int u, int v){
   if(isEmpty(G->adj[u])){ 
      insertBack(G->adj[u], v);
   }
   else if(!isEmpty(G->adj[u])){
      putEdgeArc(G, u, v);
   }
   G->size++;
}

/*   BFS   */
void BFS(GraphRef G, int s){
   ListRef Q = newList();
   int v, w, i;
   G->source = s;
   
   insertFront(Q, s);
   G->color[s] = 2;
   G->distance[s] = 0;
   while(getLength(Q) > 0){
      moveTo(Q, 0);
      v = getCurrent(Q);
      G->color[v] = 3;
      deleteCurrent(Q);
      if(!isEmpty(G->adj[v])){
         moveTo(G->adj[v], 0);
         for(i=0;i<getLength(G->adj[v]);i++){
            w = getCurrent(G->adj[v]);
            if(G->color[w] < 2){
               G->color[w] = 2;
               G->parent[w] = v;
               G->distance[w] = G->distance[v]+1;
               insertBack(Q, w);
            }
            if(i<getLength(G->adj[v])-1){
               moveNext(G->adj[v]);
            }
         }
      }
   }
   freeList(&Q);
}

/* DFS */
void DFS(GraphRef G, ListRef S){
   int i, s, top, low;

   moveTo(S, 0);
   s = getCurrent(S);
   G->parent[s] = 0;
   for(i=0;i<=getLength(S);i++){
      if(G->color[s] == 1){
         G->parent[s] = 0;
         visit(G, s);
      }
      if(i<getLength(S)-1){
         moveNext(S);
         s = getCurrent(S);
      }
   }
   makeEmpty(S);
   top = getTime(G);
   while(getLength(S) < getOrder(G)){
      low = 0;
      for(i=1;i<=getOrder(G);i++){
         if(top > G->finish[i] && low < G->finish[i]){
            low = G->finish[i];
            s = i;
         }
      }
      insertBack(S, s);
      top = low;
   }
}

/* visit */
void visit(GraphRef G, int u){
   int i, w;
   G->color[u] = 2;
   G->discover[u] = getTime(G);
   if(!isEmpty(G->adj[u])){
      moveTo(G->adj[u], 0);
      for(i=0;i<getLength(G->adj[u]);i++){
         w = getCurrent(G->adj[u]);
         if(G->color[w] < 2){
            G->parent[w] = u;
            visit(G, w);
         }
         if(i<getLength(G->adj[u])-1){
            moveNext(G->adj[u]);
         }
      }
   }
   G->color[u] = 3;
   G->finish[u] = getTime(G);
   return;
}

int getTime(GraphRef G){
   int i, d, f;
   int time = 0;
   for(i=1;i<=getOrder(G);i++){
      d = G->discover[i];
      f = G->finish[i];
      if(d > time){
         time = d;
      }
      if(f > time){
         time = f;
      }
   }
   time = time+1;
   return(time);
}

void printParent(GraphRef G){
   int i;
   printf("parent=[");
   for(i=1;i<=G->order;i++){
      printf("%d", G->parent[i]);
      if(i<G->order){
         printf(" ");
      }
   }
   printf("]\n");
   printf("color=[");
   for(i=1;i<=G->order;i++){
      printf("%d", G->color[i]);
      if(i<G->order){
         printf(" ");
      }
   }
   printf("]\n");
   printf("discover=[");
   for(i=1;i<=G->order;i++){
      printf("%d", G->discover[i]);
      if(i<G->order){
         printf(" ");
      }
   }
   printf("]\n");
   printf("finish=[");
   for(i=1;i<=G->order;i++){
      printf("%d", G->finish[i]);
      if(i<G->order){
         printf(" ");
      }
   }
   printf("]\n");
}


/*************** Other Functions *************************************************/
 
/* printGraph */
void printGraph(FILE *out, GraphRef G){
   int i;  

   if( G==NULL ){
      printf("Graph Error: calling printGraph() on NULL GraphRef\n");
      exit(1);
   }
   for(i = 1; i<=getOrder(G); i++){
      fprintf(out, "%d: ", i);
      printList(out, G->adj[i]);
      fprintf(out, "\n");
   }
}

void printfGraph(GraphRef G){
   int i;  

   if( G==NULL ){
      printf("Graph Error: calling printGraph() on NULL GraphRef\n");
      exit(1);
   }
   for(i = 1; i<=getOrder(G); i++){
      printf("%d: ", i);
      printflist(G->adj[i]);
      printf("\n");
   }
}

GraphRef transpose(GraphRef G){
   int i, j;
   GraphRef Q = newGraph(G->order);

   for(i=1;i<=G->order;i++){
      if(!isEmpty(G->adj[i])){
         moveTo(G->adj[i], 0);
         for(j=0;j<getLength(G->adj[i]);j++){
            addArc(Q, getCurrent(G->adj[i]),i);
            if(j<getLength(G->adj[i])-1){
               moveNext(G->adj[i]);
            }
         }
      }
   }
   return(Q);
}

GraphRef copyGraph(GraphRef G){
   int i, j;
   GraphRef Q = newGraph(G->order);

   for(i=1;i<=G->order;i++){
      if(!isEmpty(G->adj[i])){
         moveTo(G->adj[i], 0);
         for(j=0;j<getLength(G->adj[i]);j++){
            addArc(Q, i, getCurrent(G->adj[i]));
            if(j<getLength(G->adj[i])-1){
               moveNext(G->adj[i]);
            }
         }
      }
   }
   return(Q);
}














