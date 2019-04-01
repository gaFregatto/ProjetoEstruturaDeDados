#ifndef Graph_h
#define Graph_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "List.h"
#include "HashTable.h"

typedef struct graph Graph;
typedef struct vertex Vertex;
typedef struct edge Edge;
typedef struct graphPath GraphPath;

/** Funções Vertex */
char* getVertexId(Vertex *vertex);

/** Funções Edge */


/** Funções básicas */
Graph* createGraph();
void insertVertex(Graph *header, float x, float y, char id[50]);
void insertEdge(Graph *header, char *idBegin, char *idDestiny, char *right, char *left, float cmp, float vm, char *name);

#endif 