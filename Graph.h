/**********************************************************************************
*
*  Raj Maitra
*  Rmaitra
*  pa5  
*  
***********************************************************************************/
#if !defined(_GRAPH_H_INCLUDE_)
#define _GRAPH_H_INCLUDE_
#include "List.h"

/***************************** Exported Types *************************************/
typedef struct Graph * GraphRef;


/************** Constructors-Destructors ******************************************/

GraphRef newGraph(int i);
void freeGraph(GraphRef* pG);


/***************** Access functions ***********************************************/

int getOrder(GraphRef G);
int getSize(GraphRef G);
int getSource(GraphRef G);
int getParent(GraphRef G, int u);
int getDiscover(GraphRef G, int u);
int getFinish(GraphRef G, int u);
int getDist(GraphRef G, int u);
void getPath(ListRef L, GraphRef G, int u);

/****************************** Manipulation procedures ***************************/

void makeNull(GraphRef G);
void resetBFS(GraphRef G);
void addEdge(GraphRef G, int u, int v);
void putEdgeArc(GraphRef G, int u, int v);
void addArc(GraphRef G, int u, int v);
void BFS(GraphRef G, int s);
void DFS(GraphRef G, ListRef S);
void visit(GraphRef G, int u);
void printParent(GraphRef G);
int getTime(GraphRef G);
/*************** Other Functions *************************************************/
void printGraph(FILE *out, GraphRef G);
void printfGraph(GraphRef G);
GraphRef transpose(GraphRef G);
GraphRef copyGraph(GraphRef G);
ListRef SCC(GraphRef G);


#endif
