#ifndef List_h
#define List_h

/**  Esse é o módulo que auxilia na criacão e manipulacão de uma lista duplamente encadeada que carrega qualquer tipo de item. */

#include <stdio.h>
#include <stdlib.h>

/** Cria apelidos void* para Lista, Posic e Item.
    Lista é uma colecão de itens ordenada por Posic.
    Posic indica a posicão de um determinado item dentro da Lista.
    Item indica o endereco de um item a ser adicionado na Lista.    */
typedef void* List;
typedef void* Posic;
typedef void* Item;
/** Cria um apelido 'fun' para toda funcão que recebe um Item e retorna um char*.   */
typedef char* (*func)(Item);
/** Cria um apelido 'fr' para toda funcão que recebe um Item e retorna void.   */
typedef void (*fr)(Item);
/** Cria um apelido 'sortKey' para toda função que recebe um Item e retorna um float.  */
typedef float (*sortKey)(Item);
/** Cria um apelido 'fa' para toda função que recebe um Item e um arquivo e retorna void.  */
typedef void (*fa)(Item, FILE*);
typedef char* (*getStringList)(Item);

/** Cria uma lista e retorna um ponteiro para ela.   */
List createList();

/** Recebe uma lista.
    Retorna o tamanho da lista.   */
int sizeList(List list);

/** Recebe uma lista válida e um item válido.
    Insere o item no final da lista e retorna um ponteiro para o item adicionado.   */
Posic insertList(List list, Item it);

/** Recebe uma lista válida e uma posicão de um item na lista.
    Remove o item da lista indicado pela posicão.   */
void removeList(List list, Posic p);

/** Recebe uma lista válida e uma posicão de um item na lista.
    Retorna o item da posicão dada.   */
Item getItem(List list, Posic p);

/** Recebe uma lista válida e um item da lista.
    Retorna a posicão do item dado.   */
Posic getNodeList(List list, Item it);

/** Recebe a posicão de um item na lista.
    Insere um item na lista anterior ao item indicado por posic e rertona um ponteiro para o elemento inserido.   */
Posic insertBefore(List list, Posic p, Item it);

/** Recebe a posicão e um item da lista.
    Retorna um item da lista posterior ao item indicado por posic e retorna um ponteiro para o elemento inserido.   */
Posic insertAfter(List list, Posic p, Item it);

/** Recebe um lista válida.
    Retorna a posic do primeiro elemento da lista.    */
Posic getFirst(List list);

/** Recebe uma posic e uma lista válidos.
    Retorna a posic do proximo item apontado por posic, caso posic indique o último elemento da lista, retorna NULL.   */
Posic getNext(List list, Posic p);

/** Recebe uma lista válida.
    Retorna a posic do último elemento da lista.   */
Posic getLast(List list);

/** Recebe uma posic e uma lista válidos.
    Retorna a posic do item anterior ao apontado por posic, caso posic indique o primeiro item da lista, retorna NULL.   */
Posic getPrevious(List list, Posic p);

/** Recebe uma lista válida.
    Libera todos os elementos da lista e os aponta para NULL, sem liberar os espacos para os itens. */
void freeList(List list);

void freeListH(List list);

/** Recebe uma lista válida.
    Libera todos os elementos da lista e os aponta para NULL, incluindo o espaco para os itens. */
void freeL(List list, fr ffree);

/** Recebe uma lista
    Retorna a lista em um vetor.
    OBS: necessário dar free no vetor após o uso.   */
void** vetList(List list);

/** Recebe um vetor.
    Retorna o vetor ordenado. */
void mergeSort(void **vet, int l, int r, sortKey get_Key);

/** Recebe uma lista válida e um posic.
    Retorna a posic que foi retirada da lista, sem dar free em sua posic.  */
Posic removeList2(List list, Posic p);

/** Recebe uma lista válida e uma função para printa o item.
    Printa toda a lista. */
void printList(List list, fr print);

/** Recebe uma lista válida e uma função para printar um item em um arquivo.
    Printa a lista em um arquivo svg ou um arquivo txt. */
void printListArq(List list, fa printItem, FILE *arq);

/** Recebe uma lista válida e uma função para pegar a string do item.
    Tranforma a lista em uma hashTable e retorna uma ferência para ela. */
void* buildHashList(List list, getStringList getString);

#endif
