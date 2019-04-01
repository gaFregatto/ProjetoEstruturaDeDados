#include "List.h"
#include "HashTable.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _nodeList{
  Item item;
  struct _nodeList *next;
  struct _nodeList *prev;
}nodeList;

typedef struct _Tlist{
  nodeList *head;
  nodeList *tail;
  int size;
}Tlist;

List createList(){
  Tlist *newList;
  newList = (Tlist*)malloc(sizeof(Tlist));
  newList->head = NULL;
  newList->tail = NULL;
  newList->size = 0;
  return newList;
}

int sizeList(List list){
  Tlist *listAux = (Tlist*)list;
  return listAux->size;
}

Posic insertList(List list, Item it){
  Tlist *listAux;
  nodeList *node, *nodeAux;

  listAux = (Tlist*)list;
  node = (nodeList*)malloc(sizeof(nodeList));

  if(listAux->size == 0){
    node->item = it;
    node->next = NULL;
    node->prev = NULL;
    listAux->head = node;
    listAux->tail = node;
    listAux->size++;
  }else{
    node->item = it;
    node->next = NULL;
    node->prev = listAux->tail;
    nodeAux = listAux->tail;
    nodeAux->next = node;
    listAux->tail = node;
    listAux->size++;
  }
  return node;
}

void removeList(List list, Posic p){
  Tlist *listAux;
  nodeList *node, *nodeAux;

  listAux = (Tlist*)list;
  node = (nodeList*)p;

  if(listAux->head == node && listAux->tail == node){   /*  Um único elemento na lista  */
    listAux->head = NULL;
    listAux->tail = NULL;
    listAux->size--;
    free(node);
  }else if(listAux->head == node){    /*  Comeco da lista  */
    nodeAux = node->next;
    nodeAux->prev = NULL;
    listAux->head = nodeAux;
    listAux->size--;
    free(node);
  }else if(listAux->tail == node){    /*  Fim da lista  */
    nodeAux = node->prev;
    nodeAux->next = NULL;
    listAux->tail = nodeAux;
    listAux->size--;
    free(node);
  }else{    /*  Meio da lista  */
    nodeAux = node->prev;
    nodeAux->next = node->next;
    nodeAux = node->next;
    nodeAux->prev = node->prev;
    listAux->size--;
    free(node);
  }
}

Item getItem(List list, Posic p){
  Tlist *listAux;
  nodeList *node;

  listAux = (Tlist*)list;
  node = (nodeList*)p;

  if(listAux->size == 0){
    return NULL;
  }else{
    return node->item;
  }
}

Posic getNodeList(List list, Item it){
  Tlist *listAux;
  Item *itm;
  nodeList *node;
  int i;

  listAux = (Tlist*)list;
  itm = (Item*)it;
  node = listAux->head; /*  getFirst(listAux);  */
  i = 0;

  while(i<listAux->size){
    if(node->item == itm){
      return node;
    }
    node = node->next;  /*  getNext(listAux, node);  */
    i++;
  }
  return NULL; 
}

Posic insertBefore(List list, Posic p, Item it){
  Tlist *listAux;
  Item *itm;
  nodeList *node, *nodeItem, *nodeAux;

  listAux = (Tlist*)list;
  node = (nodeList*)p;
  itm = (Item*)it;
  nodeItem = (nodeList*)malloc(sizeof(nodeList));

  if(listAux->size == 1){   /*  Um único elemento na lista  */
    nodeItem->item = itm;
    nodeItem->prev = NULL;
    nodeItem->next = node;
    node->prev = nodeItem;
    listAux->size++;
    listAux->head = nodeItem;
  }else if(listAux->size > 1){
    if(node->prev == NULL){   /*  Inserir no comeco da lista  */
      nodeItem->item = itm;
      nodeItem->prev = NULL;
      nodeItem->next = node;
      node->prev = nodeItem;
      listAux->size++;
      listAux->head = nodeItem;
    }else{    /*  Inserir no meio da lista  */
      nodeAux = node->prev;
      nodeAux->next = nodeItem;
      nodeItem->prev = nodeAux;
      nodeItem->item = itm;
      nodeItem->next = node;
      node->prev = nodeItem;
      listAux->size++;
    }
  }else{  /*  Lista vazia  */
    return NULL;
  }
  return nodeItem;
}

Posic insertAfter(List list, Posic p, Item it){
  Tlist *listAux;
  nodeList *node, *nodeItem, *nodeAux;
  Item *itm;

  listAux = (Tlist*)list;
  node = (nodeList*)p;
  itm = (Item*)it;
  nodeItem = (nodeList*)malloc(sizeof(nodeList));

  if(listAux->size == 1){   /*  Um único elemento na lista  */
    nodeItem->item = itm;
    nodeItem->next = NULL;
    nodeItem->prev = node;
    node->next = nodeItem;
    listAux->size++;
    listAux->tail = nodeItem;
  }else if(listAux->size > 1){
    if(node->next == NULL){   /*  Inserir no final da lista  */
      nodeItem->item = itm;
      nodeItem->next = NULL;
      nodeItem->prev = node;
      node->next = nodeItem;
      listAux->size++;
      listAux->tail = nodeItem;
    }else{    /*  Inserir no meio da lista  */
      nodeItem->item = itm;
      nodeAux = node->next;
      nodeAux->prev = nodeItem;
      nodeItem->next = nodeAux;
      nodeItem->prev = node;
      node->next = nodeItem;
      listAux->size++;
    }
  }else{    /*  Lista vazia  */
    return NULL;
  }
  return nodeItem;
}

Posic getFirst(List list){
  Tlist *listAux = (Tlist*)list;
  return listAux->head;
}

Posic getNext(List list, Posic p){
  Tlist *listAux = (Tlist*)list;
  nodeList *node = (nodeList*)p;

  if(listAux->size != 0){
    return (nodeList*)node->next;
  }else{
    return (nodeList*)NULL;
  }
}

Posic getLast(List list){
  Tlist *listAux = (Tlist*)list;
  return listAux->tail;
}

Posic getPrevious(List list, Posic p){
  Tlist *listAux = (Tlist*)list;
  nodeList *node = (nodeList*)p;

  if(listAux->size != 0){
    return node->prev;
  }else{
    return NULL;
  }
}

void freeList(List list){
  Tlist *listAux = (Tlist*)list;
  nodeList *node, *nodeAux;
  Item *itm;

  if(listAux != NULL){
    node = (nodeList*)listAux->head;
    while(node != NULL){
      nodeAux = node->next;
      free(node);  
      node = nodeAux;
      listAux->size--;
    }
  free(list);
  list = NULL;
  }
}

void freeListH(List list){
  Tlist *listAux = (Tlist*)list;
  nodeList *node, *nodeAux;
  Item *itm;

  if(listAux != NULL){
    node = (nodeList*)listAux->head;
    while(node != NULL){
      nodeAux = node->next;
      free(node);  
      node = nodeAux;
      listAux->size--;
    }
  //free(list);
  list = NULL;
  }
}

void freeL(List list, fr ffree){
  Tlist *listAux = (Tlist*)list;
  nodeList *node, *nodeAux;
  Item *itm;

  if(listAux != NULL){
    node = (nodeList*)listAux->head;
    while(node != NULL){
      nodeAux = node->next;
      itm = (Item*)getItem(listAux, node);
      ffree(itm);
      free(node);
      node = nodeAux;
      listAux->size--;
    }
  free(list);
  list = NULL;
  }
}

void** vetList(List list){
  void **vet = malloc(sizeList(list)*sizeof(Item));
  int k=0;
  Posic p;
  Item itm;

  for(p=getFirst(list); p!=NULL; p=getNext(list,p)){
    itm = getItem(list, p);
    vet[k] = itm;
    k++;
  }
  return vet;
}

/** Função privada. */
void merge(void **vet, int left, int mid, int right, sortKey get_Key){

  int i, j, k;
  int n1 = mid - left + 1;
  int n2 = right - mid;
  /** Vetores temporários para a ordenação. */
  void* L[n1];
  void* R[n2];
  /** Copia os dados para os vetores temporários. */
  for(i=0; i<n1; i++)   L[i] = vet[left+i];
  for(j=0; j<n2; j++)   R[j] = vet[mid+1+j];
  /** Fundi os vetores temporários de volta para o vetor vet. */
  i = 0;
  j = 0;
  k = left;
  while(i<n1 && j<n2){
    if(get_Key(L[i]) <= get_Key(R[j])){
      vet[k] = L[i];
      i++;
    }else{
      vet[k] = R[j];
      j++;
    }
    k++;
  }
  /** Copia os elementos restantes do vetor da esquerda para o vetor vet se restar algum. */
  while(i<n1){
    vet[k] = L[i];
    i++;
    k++;
  }
  /** Copia os elementos restantes do vetor da direita para o vetor vet se restar algum. */
  while(j<n2){
    vet[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(void **vet, int left, int right, sortKey get_Key){
  int mid;

  if(left < right){
    mid = left + (right-left)/2;

    mergeSort(vet, left, mid, get_Key);
    mergeSort(vet, mid+1, right, get_Key);
    merge(vet, left, mid, right, get_Key);
  }
}

Posic removeList2(List list, Posic p){
  Tlist *listAux;
  nodeList *node, *nodeAux;

  listAux = (Tlist*)list;
  node = (nodeList*)p;

  if(listAux->head == node && listAux->tail == node){   /*  Um único elemento na lista  */
    listAux->head = NULL;
    listAux->tail = NULL;
    listAux->size--;
    //free(node);
    return node;
  }else if(listAux->head == node){    /*  Comeco da lista  */
    nodeAux = node->next;
    nodeAux->prev = NULL;
    listAux->head = nodeAux;
    listAux->size--;
    //free(node);
    return node;
  }else if(listAux->tail == node){    /*  Fim da lista  */
    nodeAux = node->prev;
    nodeAux->next = NULL;
    listAux->tail = nodeAux;
    listAux->size--;
    //free(node);
    return node;
  }else{    /*  Meio da lista  */
    nodeAux = node->prev;
    nodeAux->next = node->next;
    nodeAux = node->next;
    nodeAux->prev = node->prev;
    listAux->size--;
    //free(node);
    return node;
  }
}

void printList(List list, fr print){
  Tlist *auxL = (Tlist*)list;
  Posic p;
  Item it;
  for(p=getFirst(auxL); p!=NULL; p=getNext(auxL, p)){
    it = getItem(auxL, p);
    print(it);
  }
}

void printListArq(List list, fa printItem, FILE *arq){
  Tlist *auxL = (Tlist*)list;
  Posic p;
  Item it;
  for(p=getFirst(auxL); p!=NULL; p=getNext(auxL, p)){
    it = getItem(auxL, p);
    printItem(it, arq);
  }
}

HashTable buildHashList(List list, getStringList getString){
  Tlist *l = (Tlist*)list;
  Posic p;
  if(sizeList(l)<=0)
      return NULL;

  HashTable hash = createHash(1217);  
  for(p=getFirst(l); p!=NULL; p=getNext(l, p))
    insertHashCollision(hash, getItem(l, p), getString);
  
  return hash;
}