#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "HashTable.h"
#include "Strings.h"
#include "List.h"
#include "Block.h"

typedef struct _ht{
	int stored, size;
	List *itens;
}hashTable;

HashTable createHash(int sizeHash){
	hashTable *newHash = (hashTable*)malloc(sizeof(hashTable));
	int i=0;

	if(newHash != NULL){
		newHash->size = sizeHash;
		newHash->itens = (List*)malloc(sizeHash * sizeof(Item*));
		if(newHash->itens == NULL){
			free(newHash);
			return NULL;
		}
		newHash->stored = 0;

		for(i=0; i<sizeHash; i++)
			newHash->itens[i] = NULL;
		
		return newHash;
	}
}

int hashFunction(String key, int sizeHash){
	int i=0, g=31, hash=0, sizeStr;
	double x=0.6180339887, aux;

	sizeStr = strlen(key);
	for(i=0; i<sizeStr; i++){
		hash = g * hash + key[i];
	}
	if(hash < 0)
		hash = hash * (-1);

	aux = (double) hash * x;
	aux = aux - floor(aux);  // Pega  a parte decimal de 'a'
	return (int) (aux * sizeHash);
}

void freeHash(HashTable h, fl fList){
	hashTable *auxH = (hashTable*)h;
	if(auxH != NULL){
		int i=0;
		for(i=0; i<auxH->size; i++){
			if(auxH->itens[i] != NULL)
				fList(auxH->itens[i]);
		}
		free(auxH->itens);
		free(auxH);
	}
}

void insertHashCollision(HashTable h, Item it, getStringHash getString){
	hashTable *hh = (hashTable*)h;
	if(hh == NULL || hh->stored == hh->size)
		return;
	String key = getString(it);
	int index = hashFunction(key, hh->size);
	if(it == NULL)
		return;

	if(hh->itens[index] == NULL){
		hh->itens[index] = createList();
	}
	insertList(hh->itens[index], it);
	hh->stored++;
}

Item getHashCollision(HashTable h, String key, getStringHash getString){
	hashTable *hh = (hashTable*)h;
	Posic p;
	int index;
	Item it = NULL;

	if(hh == NULL)
		return NULL;
	
	index = hashFunction(key, hh->size);
	if(hh->itens[index] != NULL){
		p = getFirst(hh->itens[index]);
		while(p != NULL){
			it = getItem(hh->itens[index], p);
			if(strcmp(getString(it), key)==0)
				return getItem(hh->itens[index], p);
			p = getNext(hh->itens[index], p);
		}
	}else{
		return NULL;
	}
}

List getHashList(HashTable h, String key, getStringHash getString){
	hashTable *hh = (hashTable*)h;
	Posic p;
	int index;
	Item it = NULL;

	if(hh == NULL)
		return NULL;
	
	index = hashFunction(key, hh->size);
	if(hh->itens[index] != NULL)
		return hh->itens[index];
	else
		return NULL;	
}

void freeHashItem(HashTable h, char *key, getStringHash getString, ffff fItem){
	hashTable *hh = (hashTable*)h;
	Posic p;
	int index;
	Item it = NULL;

	if(hh == NULL)
		return;
	
	index = hashFunction(key, hh->size);
	if(hh->itens[index] != NULL){
		p = getFirst(hh->itens[index]);
		while(p != NULL){
			it = getItem(hh->itens[index], p);
			if(strcmp(getString(it), key)==0)
				fItem(getItem(hh->itens[index], p));
			p = getNext(hh->itens[index], p);
		}
	}else{
		return;
	}
}