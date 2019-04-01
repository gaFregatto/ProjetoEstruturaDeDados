#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Strings.h"
#include "List.h"
#include "HashTable.h"
#include "Graph.h"

struct graph{	/* Grafo que aponta para a cabeça e cauda dos vértices */
	int size;
	Vertex *begin;
	Vertex *end;
	HashTable *hash;
}; 

struct vertex{
	Graph *header;
	Edge *edge;		/* Aponta para a primeira aresta da lista desse vértice */
	Edge *finalEdge;	/* Aponta para o última aresta da lista desse vértice */
	int index;
	char id[50];	/* ID para ser localizado */
	float x, y;		/* Coordenadas X e Y do vértice */
	Vertex *next;	/* Existirá uma lista dos vértices, esta variável aponta para seu próximo elemento	*/
	Vertex *previous;	/* Esta variável aponta para o elemento anterior */
};

struct edge{
	Vertex *begin;		/* Vértice de origem */
	Vertex *destiny;	/* Vértide destino */
	String right, left;	/* CEP das quadras posicionadas do lado direito e esquerdo da aresta  */
	float cost;
	float cmp, vm;	/* Comprimento e velocidade, serão usadas para calcular o custo */
	String name;	/* Nome da rua ou aresta */
	Edge *next;
};

struct graphPath{
	Edge *node;
	GraphPath *next;
	GraphPath *previous;
}

Graph* createGraph(){
	Graph * g;
	
	g = malloc(sizeog(Graph));
	g->begin = NULL;
	g->end = NULL;
	g->size = 0;
	g->hash = createHash(1217);

	return g;
}

/** Funções Vertex */


/** Funções Básicas Graph */
void insertVertex(Graph *header, float x, float y, char id[50]){
	Vertex *vert;
	Vertex *aux;

	if(header == NULL)	return;

	header->size += 1; /* Incrementa o número de elementos do grafo */

	vert = malloc(sizeof(Vertex));
	vert->header = header;
	vert->edge = NULL;
	vert->finalEdge = NULL;
	vert->index = header->size - 1;
	vert->x = x;
	vert->y = y;
	strcpy(vert->id, id);
	vert->next = NULL;
	vert->previous = NULL;

	if(header->end != NULL){	/* Verifica se o final da lista é NULL */
		aux = header->end;		/* Salva a última posição da lista */
		header->end->prox = vert;	/* Atualiza a última posição da lista */
		vert->previous = aux;		/* Faz com que a última posição aponte para a penúltima */
	}else{
		header->begin = vert;
	}
	header->end = vert;

	insertHashCollision(header->hash, vert, getVertexId);

	printf("\nTESTE Vertice %s, (%.2f, %.2f) -- Inserido com sucesso! \n", id, x, y);
}

void insertEdge(Graph *header, char *idBegin, char *idDestiny, char *right, char *left, float cmp, float vm, char *name){
	Vertex *origin, *destiny;
	Edge *edge;

	origin = getHashCollision(header->hash, idBegin, getVertexId);
	destiny = getHashCollision(header->hash, idDestiny, getVertexId);

	edge = malloc(sizeof(Edge));
	edge->begin = origin;
	edge->end = destiny;
	edge->right = right;
	edge->left = left;
	edge->cmp = cmp;
	edge->vm = vm;
	edge->next = NULL;
	edge->name = name;

	if(origin->finalEdge != NULL){
		origin->finalEdge->prox = edge;
	}else{
		origin->edge = edge;
	}
	origin->finalEdge = edge;
}
