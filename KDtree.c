#include "KDtree.h"
#include "List.h"
#include "HashTable.h"
#include "Block.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct _nodeTree{
	Item item;
	struct _nodeTree *right;
	struct _nodeTree *left;
}nodeTree;

typedef struct _kdTree{
	nodeTree *root;
	int size;
}kdTree;

KDtree createKDT(){
	kdTree *newTree = (kdTree*)malloc(sizeof(kdTree));
	newTree->root = NULL;
	newTree->size = 0;
	return newTree;
}

int sizeKDT(KDtree kdt){
	kdTree *auxT = (kdTree*)kdt;
	return auxT->size;
}

void sizeTPP(KDtree kdt){
	kdTree *auxT = (kdTree*)kdt;
	auxT->size++;
}

void sizeTLL(KDtree kdt){
	kdTree *auxT = (kdTree*)kdt;
	if(auxT->size > 0)
		auxT->size--;
}


Posic getRoot(KDtree kdt){
	kdTree *auxT = (kdTree*)kdt;
	return (nodeTree*)auxT->root;
} 

void setRoot(KDtree kdt, Posic newRoot){
	kdTree *auxT = (kdTree*)kdt;
	nodeTree *auxNode = (nodeTree*)newRoot;
	if(auxT->root == NULL)	
		auxT->root = auxNode;
}

/** Função privada -> cria um nó para a árvore. */
nodeTree* createNodeT(Item it){
	nodeTree *newNode = (nodeTree*)malloc(sizeof(nodeTree));
	newNode->item = it;
	newNode->right = NULL;
	newNode->left = NULL;
	return newNode;
}

/** Função privada -> insere recursivamente os nós na árvore. */
Posic insertNodeTree(nodeTree* rootCopy, Item it, getFloatTree getX, getFloatTree getY, int depth){
	if(rootCopy == NULL){ //Finalmente encontra o lugar correto para a inserção e acaba com a recursão.
		rootCopy = createNodeT(it);
		//if(!(depth%2))		printf("\nprofundidade:%d -> resto:%d -> dimensão x", depth, depth%2);
		//else	printf("\nprofundidade:%d -> resto:%d -> dimensão y", depth, depth%2);
	}else if(!(depth%2)){
		if(getX(rootCopy->item) > getX(it))
			rootCopy->left = insertNodeTree(rootCopy->left, it, getX, getY, depth+1);
		else
			rootCopy->right = insertNodeTree(rootCopy->right, it, getX, getY, depth+1);
	}else{
		if(getY(rootCopy->item) > getY(it))
			rootCopy->left = insertNodeTree(rootCopy->left, it, getX, getY, depth+1);
		else
			rootCopy->right = insertNodeTree(rootCopy->right, it, getX, getY, depth+1);
	}
	return rootCopy;
}

void insertKDT(KDtree kdt, Item it, getFloatTree getX, getFloatTree getY){
	nodeTree *root = getRoot(kdt);
	root = insertNodeTree(root, it, getX, getY, 0);
	sizeTPP(kdt);
	setRoot(kdt, root);
}

/** Função privada -> printa os elementos da árvore em pós-ordem, o qual os filhos são tratados antes dos pais. 
	Filho esquerdo, depois filho direito e depois o pai. */
void printNodeTree(nodeTree* root, fr printItem){   
	nodeTree *rootCopy = (nodeTree*)root;
	if(rootCopy == NULL){
		return;
	}
	printNodeTree(rootCopy->left, printItem);
	printNodeTree(rootCopy->right, printItem);
	printItem(rootCopy->item);
}

void printKDT(KDtree kdt, fr printItem){
	kdTree *auxT = (kdTree*)kdt;
	nodeTree *root = getRoot(auxT);
	if(sizeKDT(kdt)==0)
		return;
	printNodeTree(root, printItem);
}

/** Função privada -> percorre a árvore em pós-ordem e libera seus nodes. */
void freeNodesKDT(Posic root, fr ffree){
	nodeTree *rootCopy = (nodeTree*)root;
	if(rootCopy == NULL)
		return;
	freeNodesKDT(rootCopy->left, ffree);
	freeNodesKDT(rootCopy->right, ffree);
	if(rootCopy->item != NULL)	
		ffree(rootCopy->item);	rootCopy->item = NULL;
	if(rootCopy != NULL)  
		free(rootCopy);  rootCopy = NULL;
}

void freeKDT(KDtree kdt, fr ffree){
	kdTree *auxT = (kdTree*)kdt;
	if(auxT == NULL){
		printf("\nErro freeKDT: árvore vazia não pode ser liberada.");
		return;
	}
	nodeTree* auxRoot = getRoot(auxT);
	if(sizeKDT(kdt)<=0)
		return;
	freeNodesKDT(auxRoot, ffree);
	free(auxT);
	auxT = NULL;
}

/** Função privada -> retorna o menor float entre 3 valores. */
float min(float x, float y, float z){
    if((x <= y) && (x <= z))	return x;
    else if(y <= z)		return y;
    else 	return z;
}

/** Função privada -> faz a recursividade para percorrer a árvore e encontrar o menor valor da dimensão. */
float findMinRec(nodeTree* rootCopy, int d, getFloatTree getX, getFloatTree getY, int depth){
	int currentD = depth % 2;
	// Caso base.
	if(rootCopy == NULL)
		return 9999999.99;
	// Se a atual dimensão for a mesma que a pedida, compara o ponto com o root.
	if(currentD == d){
		if(rootCopy->left == NULL){
			if(d == 0)  return getX(rootCopy->item);
			else if(d == 1)  return getY(rootCopy->item);		
		}
		return findMinRec(rootCopy->left, d, getX, getY, depth+1);
	}
	// Se a dimensão atual for diferente da pedida, o valor mínimo pode estar em qualquer lugar da subarvore.
	if(d == 0){		// Percorre a árvore em pré-ordem.
		return min(getX(rootCopy->item), 	
				findMinRec(rootCopy->left, d, getX, getY, depth+1),
				findMinRec(rootCopy->right, d, getX, getY, depth+1));
	}else if(d == 1){	// Percorre a árvore em pré ordem
		return min(getY(rootCopy->item), 	
				findMinRec(rootCopy->left, d, getX, getY, depth+1),
				findMinRec(rootCopy->right, d, getX, getY, depth+1));
	}
}

float findMinKDT(KDtree kdt, int dimension, getFloatTree getX, getFloatTree getY){
	kdTree *auxT = (kdTree*)kdt;
	nodeTree *root = getRoot(auxT);
	return findMinRec(root, dimension, getX, getY, 0);
}

/** Função privada -> Recebe três nó e retorna o nó que tem o menor valor da dimensão desejada. */
Posic minNode(nodeTree* x, nodeTree* y, nodeTree* z, getFloatTree getX, getFloatTree getY, int d){
	nodeTree *res = (nodeTree*)x;
	if(!d){
		if((y != NULL) && (getX(y->item) < getX(res->item)))	res = y;
		if((z != NULL) && (getX(z->item) < getX(res->item)))	res = z;
	}else{
		if((y != NULL) && (getY(y->item) < getY(res->item)))	res = y;
		if((z != NULL) && (getY(z->item) < getY(res->item)))	res = z;
	}
	return res;
}

/** Função privada -> faz a recursividade para percorrer a árvore e encontrar e retornar o nó que possui o menor valor da dimensão. */
Posic minNodeRec(nodeTree* rootCopy, int d, getFloatTree getX, getFloatTree getY, int depth){
	int currentD = depth % 2;
	// Caso base.
	if(rootCopy == NULL)
		return NULL;
	// Se a dimensão corrente é a desejada.
	if(currentD == d){
		if(rootCopy->left == NULL)
			return rootCopy;
		return minNodeRec(rootCopy->left, d, getX, getY, depth+1);
	}
	return minNode(rootCopy,
				minNodeRec(rootCopy->left, d, getX, getY, depth+1),
				minNodeRec(rootCopy->right, d, getX, getY, depth+1), 
				getX, getY, d);
}

Posic minNodeKDT(KDtree kdt, int dimension, getFloatTree getX, getFloatTree getY){
	kdTree *auxT = (kdTree*)kdt;
	nodeTree *root = getRoot(auxT);
	if(sizeKDT(kdt)<=0)
		return NULL;
	return minNodeRec(root, dimension, getX, getY, 0);
}

Posic getItemKDT(KDtree kdt, Posic p){
	kdTree *auxT = (kdTree*)kdt;
	nodeTree* auxNode = (nodeTree*)p;
	return auxNode->item;
}

/** Função privada -> retorna 0 caso se os pontos forem diferentes e 1 se forem iguais. */
int equalItens(Item x, Item y, getFloatTree getX, getFloatTree getY, getStringTree getS){
	if(x!=NULL && y!=NULL)
		if(getX(x) == getX(y) && getY(x) == getY(y))
			if(strcmp(getS(x), getS(y))==0)
				return 1;
	return 0; 
}

/** Função privada -> recebe dois itens e copia e copia o segundo no primeiro. */
void copyItem(Item x, Item y, f copy){
	copy(x, y);
}

/** Função privada -> usa a recursividade para procurar e encontrar o nó dentro da árvore. Quando encontrado 
						o nó é removido e substituído pelo nó que tem o valor mínimo da dimensão desejada, caso necessário. */
Posic removeRec(nodeTree* rootCopy, Item it, int depth, fb equal, getFloatTree getX, getFloatTree getY, fr ffree, f copy){
	int currentD = depth % 2;
	// Caso base
	if(rootCopy==NULL){
		return NULL;
	}
	// O ponto a ser deletado é igual ao currentNode.
	if(equal(rootCopy->item, it)){
		if(rootCopy->right != NULL){
			nodeTree *min = minNodeRec(rootCopy->right, currentD, getX, getY, 0);  // Encontra o menor valor da dimensão corrente da subárvore direita.
			copyItem(rootCopy->item, min->item, copy);  // Copia o valor mínimo encontrado no nó que seria supostamente "deletado"
			rootCopy->right = removeRec(rootCopy->right, min->item, depth+1, equal, getX, getY, ffree, copy);  // Deleta o mínimo que encontramos, recursivamente.
		}else if(rootCopy->left != NULL){
			nodeTree *min = minNodeRec(rootCopy->left, currentD, getX, getY, 0);  // Mesmo processo que o descrito acima, porém, a subárvore explodara é a esquerda.
			copyItem(rootCopy->item, min->item, copy);
			rootCopy->right = removeRec(rootCopy->left, min->item, depth+1, equal, getX, getY, ffree, copy);
			rootCopy->left = NULL;
		}else{	// No a ser deletado é uma folha, então apenas o deletamos.
			ffree(rootCopy->item); 
			free(rootCopy);  
			return NULL;
		}
		return rootCopy;
	}
	// currentNode não está inserido pela dimensão desejada, o nó a ser deletado pode estar em qualquer lugar da subárvore.
	if(!currentD){
		if(getX(it) < getX(rootCopy->item))
			rootCopy->left = removeRec(rootCopy->left, it, depth+1, equal, getX, getY, ffree, copy);
		else
			rootCopy->right = removeRec(rootCopy->right, it, depth+1, equal, getX, getY, ffree, copy);
	}else{
		if(getY(it) < getY(rootCopy->item))
			rootCopy->left = removeRec(rootCopy->left, it, depth+1, equal, getX, getY, ffree, copy);
		else
			rootCopy->right = removeRec(rootCopy->right, it, depth+1, equal, getX, getY, ffree, copy);
	}
	return rootCopy;
}

void removeKDT(KDtree kdt, Item it, fb equal, getFloatTree getX, getFloatTree getY, fr ffree, f copy){
	nodeTree *root = getRoot(kdt);
	//if(sizeKDT(kdt)<=0) Nos testes do t3, isso não resolveu o problema de leak, porém sem ele, menos memória é perdida.
	//	return;
	root = removeRec(root, it, 0, equal, getX, getY, ffree, copy);
	sizeTLL(kdt);
	setRoot(kdt, root);
}

/** Função privada-> usa a recursividade para procurar através dos nós, quais deles estão dentro do retângulo definido pelos quatro floats. */
void rangeSR(nodeTree *root, getFloatTree getX, getFloatTree getY, float x, float y, float w, float h, List inRange, int depth, fi duplicate){
	nodeTree *rootCopy = (nodeTree*)root;
	int currentD = depth % 2;

	if(rootCopy == NULL)
		return;	

	if((getX(rootCopy->item) >= x) && (getX(rootCopy->item) <= x+w) && (getY(rootCopy->item) >= y) && (getY(rootCopy->item) <= y+h)){ // O ponto está dentro do retângulo. 
		insertList(inRange, duplicate(rootCopy->item));
		rangeSR(rootCopy->left, getX, getY, x, y, w, h, inRange, depth+1, duplicate);
		rangeSR(rootCopy->right, getX, getY, x, y, w, h, inRange, depth+1, duplicate);
	}else{  // Como o ponto não está dentro da região, verificamos para qual lado do ponto corrente, o retângulo está.
		if(!currentD){ // Nó corrente na dimensão x.
			if(getX(rootCopy->item) >= x || getX(rootCopy->item) >= x+w)	// Retângulo está a esquerda do ponto.
				rangeSR(rootCopy->left, getX, getY, x, y, w, h, inRange, depth+1, duplicate);
			if(getX(rootCopy->item) < x || getX(rootCopy->item) < x+w)  // Retângulo está a direita do ponto.
				rangeSR(rootCopy->right, getX, getY, x, y, w, h, inRange, depth+1, duplicate);
		}else{ // Nó corrente na dimensão y.
			if(getY(rootCopy->item) >= y || getY(rootCopy->item) >= y+h)	// Retângulo está a abaixo do ponto.
				rangeSR(rootCopy->left, getX, getY, x, y, w, h, inRange, depth+1, duplicate);
			if(getY(rootCopy->item) < y || getY(rootCopy->item) < y+h)	// Retângulo está acima do ponto.
				rangeSR(rootCopy->right, getX, getY, x, y, w, h, inRange, depth+1, duplicate);
		}
		return;
	}
	return;
}

void rangeSearchRect(KDtree kdt, getFloatTree getX, getFloatTree getY, float x, float y, float w, float h, List inRange, fi duplicate){
	nodeTree *root = getRoot(kdt);
	if(sizeKDT(kdt)==0)
		return;
	rangeSR(root, getX, getY, x, y, w, h, inRange, 0, duplicate);
}

/** Função privada -> Recebe um item com coordenadas (x, y) e dois floats que representam outro ponto, e retorna a distância entre eles. */
float distTPoints(Item a, float auxx, float auxy, getFloatTree getX, getFloatTree getY){
	float x, y, d;
	x = getX(a) - auxx;
	x = pow(x, 2);
	y = getY(a) - auxy;
	y = pow(y, 2);
	d = x + y;
	d = pow(d, 0.5);
	return d;
}

void rangeSC(nodeTree *root, getFloatTree getX, getFloatTree getY, float x, float y, float r, List inRange, int depth, fi duplicate){
	nodeTree *rootCopy = (nodeTree*)root;
	int currentD = depth % 2;

	if(rootCopy == NULL)
		return;

	if(distTPoints(rootCopy->item, x, y, getX, getY) <= r){  // O ponto está dentro do círculo.
		insertList(inRange, duplicate(rootCopy->item));
		rangeSC(rootCopy->right, getX, getY, x, y, r, inRange, depth+1, duplicate);
		rangeSC(rootCopy->left, getX, getY, x, y, r, inRange, depth+1, duplicate);
	}else{  // Como o ponto não está dentro do círculo, verificamos para qual lado do ponto corrente, o círculo está.
		if(!currentD){  // Nó corrente na dimensão x.
			if(getX(rootCopy->item) >= x-r || getX(rootCopy->item) >= x+r)  // O círculo está a esquerda do ponto.
				rangeSC(rootCopy->left, getX, getY, x, y, r, inRange, depth+1, duplicate);
			if(getX(rootCopy->item) < x-r || getX(rootCopy->item) < x+r)	// O círculo está a direita do ponto.
				rangeSC(rootCopy->right, getX, getY, x, y, r, inRange, depth+1, duplicate);
		}else{  // Nó corrente na dimensão y.
			if(getY(rootCopy->item) >= y-r || getY(rootCopy->item) >= y+r)  // O círculo está abaixo do ponto.
				rangeSC(rootCopy->left, getX, getY, x, y, r, inRange, depth+1, duplicate);
			if(getY(rootCopy->item) < y-r || getY(rootCopy->item) < y+r)	// O círculo está a acima do ponto.
				rangeSC(rootCopy->right, getX, getY, x, y, r, inRange, depth+1, duplicate);
		}
		return;
	}
	return;
}

void rangeSearchCirc(KDtree kdt, getFloatTree getX, getFloatTree getY, float x, float y, float r, List inRange, fi duplicate){
	nodeTree *root = getRoot(kdt);
	if(sizeKDT(kdt)<=0)
		return;
	rangeSC(root, getX, getY, x, y, r, inRange, 0, duplicate);
}

/** Função privada */
void** vk(nodeTree *rootCopy, List list){
	if(rootCopy == NULL)
		return NULL;
	vk(rootCopy->left, list);
	vk(rootCopy->right, list);
	insertList(list, rootCopy->item);
}

void** vetKDT(KDtree kdt, fr ffree){
	int tam = sizeKDT(kdt);
	nodeTree *root = getRoot(kdt);
	List list = createList();
	if(sizeKDT(kdt)==0)
		return NULL;
	vk(root, list);
	void **vet = vetList(list);
	freeList(list);
	return vet;
}

/** Função privada -> faz a recursão para percorrer a árvore e printar todos seus itens em um arquivo svg. */
void printNTS(nodeTree *root, fa print, FILE *arq){
	nodeTree *rootCopy = (nodeTree*)root;
	if(rootCopy == NULL){
		return;
	}
	printNTS(rootCopy->left, print, arq);
	printNTS(rootCopy->right, print, arq);
	print(rootCopy->item, arq);
}

void printKDTarq(KDtree kdt, fa printItem, FILE *arq){
	nodeTree *root = getRoot(kdt);
	if(sizeKDT(kdt)<=0)
		return;
	printNTS(root, printItem, arq);
}

/** Função privada  -> recursivamente procura a string igual a ident, se verdadeiro troca as cores de borda e preenchimento. */
void ccR(nodeTree *root, getStringTree getString, char* ident, ch changeColors, char* stroke, char* fill){
	nodeTree *rootCopy = (nodeTree*)root;
	if(rootCopy == NULL){
		return;
	}
	if(strcmp(getString(rootCopy->item), ident) == 0){
		changeColors(rootCopy->item, stroke, fill);
		return;
	}
	ccR(rootCopy->left, getString, ident, changeColors, stroke, fill);
	ccR(rootCopy->right, getString, ident, changeColors, stroke, fill);
}

void changeColorsKDT(KDtree kdt, getStringTree getString, char* ident, ch changeColors, char* stroke, char* fill){
	nodeTree *root = getRoot(kdt);
	if(sizeKDT(kdt)<=0)
		return;
	ccR(root, getString, ident, changeColors, stroke, fill);
}

/** Função privada -> recursivamente procura a string igual a ident, se verdadeiro reporta no arquivo txt. */
void reportRec(nodeTree *root, getStringTree getString, char* ident, fa printItem, FILE *arq){
	nodeTree *rootCopy = (nodeTree*)root;
	if(rootCopy == NULL){
		return;
	}
	if(strcmp(getString(rootCopy->item), ident) == 0){
		printItem(rootCopy->item, arq);
		return;
	}
	reportRec(rootCopy->left, getString, ident, printItem, arq);
	reportRec(rootCopy->right, getString, ident, printItem, arq);
}

void reportCepIdKDT(KDtree kdt, getStringTree getString, char* ident, fa printItem, FILE *arq){
	nodeTree *root = getRoot(kdt);
	if(sizeKDT(kdt)<=0)
		return;
	reportRec(root, getString, ident, printItem, arq);
}

void vl(nodeTree *root, List l){
	nodeTree *rootCopy = (nodeTree*)root;
	if(rootCopy == NULL)
		return;
	vl(rootCopy->left, l);
	vl(rootCopy->right, l);
	insertList(l, rootCopy->item);	
}

List listKDT(KDtree kdt){
	nodeTree *root = getRoot(kdt);
	if(sizeKDT(kdt)<=0)
		return NULL;
	List l = createList();
	vl(root, l);
	return l;
}

HashTable buildHashKDT(KDtree kdt, getStringTree getString, fr ffree){
	nodeTree *root = getRoot(kdt);
	Posic p;
	if(sizeKDT(kdt)<=0)
		return NULL;
	//printKDT(kdt, printBlock);
	List l = listKDT(kdt);
	HashTable hash = createHash(1217);
	for(p=getFirst(l); p!=NULL; p=getNext(l, p)){
		insertHashCollision(hash, getItem(l, p), getString);
	}
	freeList(l);
	return hash;
}

KDtree KDTlist(List list, getFloatTree getX, getFloatTree getY){
	kdTree *kdt = createKDT();
	Posic p;
	Item it;

	for(p=getFirst(list); p!=NULL; p=getNext(list, p)){
		it = getItem(list, p);
		insertKDT(kdt, it, getX, getY);
	}
	return kdt;
}

/** Função privada -> recebe dois nós da árvore e calcula a distância entre seus itens. */
float distNodes(nodeTree *a, Item b, getFloatTree getX, getFloatTree getY){
	if(a == NULL || b == NULL)
		return 999999.9;
	float x, y, d;
	x = getX(a->item) - getX(b);
	x = pow(x, 2);
	y = getY(a->item) - getY(b);
	y = pow(y, 2);
	d = x + y;
	d = pow(d, 0.5);
	return d;
}


/** Função privada -> encontra o vizinho mais próximo recursivamente. */
void nnRec(nodeTree* root, Item it, getFloatTree getX, getFloatTree getY, fb equal, float d, f copy, Item nearest, int depth){
	nodeTree *rootCopy = (nodeTree*)root;
	nodeTree *left=NULL, *right=NULL;
	float lx, ly, rx, ry;
	int currentD = depth % 2;

	if(rootCopy == NULL)
		return;

	if(distTPoints(it, getX(rootCopy->item), getY(rootCopy->item), getX, getY) <= d){
		if(!equal(rootCopy->item, it)){	
			copy(nearest, rootCopy->item);
			d = distTPoints(it, getX(rootCopy->item), getY(rootCopy->item), getX, getY);
		}		
	}	
	
		nnRec(rootCopy->left, it, getX, getY, equal, d, copy, nearest, depth+1);
		nnRec(rootCopy->right, it, getX, getY, equal, d, copy, nearest, depth+1);	
	
}

void nearestNeighbor(KDtree kdt, Item it, getFloatTree getX, getFloatTree getY, fb equal, f copy, Item nearest){
	nodeTree *root = getRoot(kdt);
	if(sizeKDT(kdt)<=0)
		return;
	nnRec(root, it, getX, getY, equal, 999999.9, copy, nearest, 0);
}