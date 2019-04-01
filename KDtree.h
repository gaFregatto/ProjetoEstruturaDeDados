#ifndef KDtree_h
#define KDtree_h

/** Esse é o módulo KDtree, que auxilia na criação e manipulação de dados através de uma árvore K dimensional.
	Uma kdtree é definida por um node root e seus dois filhos, direito e esquerdo, sendo que a cada nível de profundidade da árvore eles são ordenaos em relação a pontos(x,y) intercaladamente. 
	A estrutura KDtree possui um ponteiro para o nó raíz da árvore e um valor inteiro para armazenar o número de elementos armazenados, que precisa ser atualizado manualmente a cada inserção.  */

#include <stdio.h>
#include <stdlib.h>

/** Cria um apelidos para void*. */
typedef void* KDtree; // Indica a kdtree.
typedef void* Item; // Indica um item.	
typedef void* Posic; // Indica a posição do nó.

typedef float (*getFloatTree)(Item); // Tipo que de função que recebe um Item e retorna um float.
typedef char* (*getStringTree)(Item); // Tipo de função que recebe um Item e retorna uma string.
typedef void (*fr)(Item); // Tipo de função que recebe um Item e não retorna nada.
typedef void (*f)(Item, Item); // Tipo de função que recebe dois Itens e retorna nada.
typedef void (*fa)(Item, FILE*); // Tipo de função que recebe um item e um arquivo e retorna nada.
typedef void* (*fi)(Item); // Tipo de função que recebe um item e retorna um item.
typedef int (*fb)(Item, Item); // Tipo de função que recebe dois itens e retorna um int (função booleana).
typedef void (*ch)(Item, char*, char*); // Tipo de função que recebe um item e duas strings e não retorna nada.

/** Pós-condição: Cria uma KDtree vazia e retorna um ponteiro para ela. */
KDtree createKDT();

/** Pré-condição: Recebe uma KDtree válida.
	Pós-condição: Retorna o número de itens armazenados na KDtree. */
int sizeKDT(KDtree kdt);

/** Pré-condição: Recebe uma KDtree válida.
	Pós-condição: Soma 1 no tamanho da árvore. */
void sizeTPP(KDtree kdt);

/** Pré-condição: Receve uma KDtree válida.
	Pós-condição: Subtrai um em seu tamanho. */
void sizeTLL(KDtree kdt);

/** Pré-condição: Recebe uma KDtree válida.
	Pós-condição: Retorna a raíz da árvore. */
Posic getRoot(KDtree kdt);

/** Pré-condição: Recebe uma KDtree e um nó da árvore.
	Pós-condição: Caso a árvore esteja vazia, atualiza a raíz da árvore, caso contrário não acontece nada. */
void setRoot(KDtree kdt, Posic newRoot);

/** Pré-condição: A árvore deve apontar para algo diferente de NULL.
	Pós-condição: Insere o elemento do parâmetro na árvore e retorna um posic, 
				  pois se a inserção ocorrer na cabeça o ponteiro para root pode mudar.  */
void insertKDT(KDtree kdt, Item it, getFloatTree getX, getFloatTree getY);

/** Pré-condição: A árvore deve apontar para algo diferente de NULL.
	Pós-condição: Imprime na saída padrão todos os elementos contidos na árvore. */
void printKDT(KDtree kdt, fr printItem);

/** Pré-condição: Recebe uma KDtree válida e um ponteiro para qualquer função que receba um item e retorne void.
	Pós-condição: Libera toda a memória alocada para a árvore e aponta tudo para NULL. */
void freeKDT(KDtree kdt, fr ffree);	

/**	Pré-condição: Recebe uma KDtree válida, um inteiro que representa a dimensão desejada do menor, x sendo representado por 0 e y por 1 e 
				  ponteiros para funções que recebem um item e retornam um float.
	Pós-condição: Retorna o menor número da dimensão enviada por parâmetro.*/
float findMinKDT(KDtree kdt, int dimension, getFloatTree getX, getFloatTree getY);

/** Pré-condição: Recebe uma KDtree válida, um inteiro que representa a dimensão desejada do menor, x sendo representado por 0 e y por 1 e 
				  ponteiros para funções que recebem um item e retornam um float.
	Pós-condição: Retorna o nó que contém o menor número da dimensão enviada por parâmetro. */
Posic minNodeKDT(KDtree kdt, int dimension, getFloatTree getX, getFloatTree getY);

/** Pré-condição: Recebe uma KDtree válida e uma posic.
	Pós-condição: Retorna o item armazenado na posic. */
Posic getItemKDT(KDtree kdt, Posic p);

/** Pré-condicão: Recebe uma KDtree válida e uma posic.
	Pós-condição: Libera a memória da posic na árvore. */
void removeKDT(KDtree kdt, Item it, fb equal, getFloatTree getX, getFloatTree getY, fr ffree, f copy);

/** Pré-condição: Recebe uma KDtree válida, 2 funções que para pegar os pontos (x,y) da árvore, quatro floats que definem o retângulo a ser verificado e uma lista.
	Pós-condição: Os pontos que se encontram dentro do retângulo a ser verificado são armazenados na lista inRange. */ 
void rangeSearchRect(KDtree kdt, getFloatTree getX, getFloatTree getY, float x, float y, float w, float h, void* inRange, fi duplicate);

/** Pré-condição: Recebe uma KDtree válida, duas funções para pegar os pontos (x, y) da árvore, três pontos floats que definem o círculo a ser verificado e uma lista.
	Pós-condição: Os pontos que se encontram dentro do círculo a ser verificado são armazenados na lista inRange. */
void rangeSearchCirc(KDtree kdt, getFloatTree getX, getFloatTree getY, float x, float y, float r, void* inRange, fi duplicate);

/** Pré-condição: Recebe uma KDtree válida.
 	Pós-condição: Retorna a KDtree em um vetor.
 	OBS: necessário dar free no vetor após o uso. */
void** vetKDT(KDtree kdt, fr ffree);

/** Pré-condição: Recebe uma KDtree válida, uma função que recebe um item e um arquivo, e um arquivo.
	Pós-condição: Printa toda a árvore no arquivo. */
void printKDTarq(KDtree kdt, fa printItem, FILE *arq);

/** Pré-condição: Recebe uma KDtree válida e uma função para pegar o cep/id do item.
	Pós-condição: Se a string do item for igual ao ident, troca as cores do item.  */
void changeColorsKDT(KDtree kdt, getStringTree getString, char* ident, ch changeColors, char* stroke, char* fill);

/** Pré-condição: Recebe uma KDtree válida, uma função para pegar a string do item na kdt, uma string ident, uma função para printar o item no arquivo TXT e o arquivo. 
	Pós-condição: Se a string do item for igual a string ident, reporta os dados do item em um arquivo txt. */
void reportCepIdKDT(KDtree kdt, getStringTree getString, char* ident, fa printItem, FILE *arq);

/** Pré-condição Recebe uma KDtree válida.
 	Pós-condição: Transforma a KDtree em uma Lista e a retorna. */
void* listKDT(KDtree kdt);

/** Pré-condição: Recebe uma KDtree, uma função para pegar a string do item.
	Pós-condição: Cria e retorna uma referência para uma tabelaHash da árvore. */
void* buildHashKDT(KDtree kdt, getStringTree getString, fr ffree);

/** Pré-condição: Recebe uma lista válida.
	Pós-condição: Transforma a KDtree em uma lista e retorna uma refência. */
KDtree KDTlist(void* list, getFloatTree getX, getFloatTree getY);

/** Pré-condição: Recebe uma árvore, um item e funções para pegar o x e y do item na árvore.
	Pós-condição: Retorna o item mais próximo do item mandado por parâmetro na variável nearest.  */
void nearestNeighbor(KDtree kdt, Item it, getFloatTree getX, getFloatTree getY, fb equal, f copy, Item nearest);

#endif


