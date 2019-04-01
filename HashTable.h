#ifndef HashTable_h
#define HashTable_h

typedef void* HashTable;
typedef void* Item;
typedef char* (*getStringHash)(Item);
typedef void (*fl)(void*);
typedef void (*ffff)(void*);

/** Pós-condição: reotrna um ponteiro para uma estrutura hashTable */
HashTable createHash(int sizeHash);

/** Pré-condição: recebe uma string que será a key para gerar o indice
	Pós-condição: tranforma a string em um número inteiro, faz algumas multiplicações para diminuir colisões e o retorna. */
int hashFunction(char* key, int hashSize);

/** Pré-condição: recebe uma hashTable válida e uma função para liberar a lista de colisão( freeList(<nomeDaLista>) ).
	Pós-condição: libera a memória reservada pela hashTable. */
void freeHash(HashTable h, fl fList);

/** Pré-condição: recebe uma HashTable válida, um item a ser inserido e uma função para pegar a string do item e gerar o índice para inserir na HashTable.
	Pós-condição: insere o item em um índice da HashTable. */
void insertHashCollision(HashTable h, Item it, getStringHash getString);

/** Pré-condição: recebe uma HashTable valida e uma chave para encontrar o item.
	Pós-condição: retorna o item indicado pela chave. */
Item getHashCollision(HashTable h, char* key, getStringHash getString);

/** Pré-condição: recebe uma HashTable residentXcep e uma HashTable peopleXcpf e uma chave para encontrar os itens.
	Pós-condição retorna uma lista com todos os itens daquela chave. */
void* getHashList(HashTable h, char* key, getStringHash getString);

/** Pré-condição: recebe uma HashTable válida e uma função que libera o item.
	Pós-condição: libera o item. */
void freeHashItem(HashTable h, char *key, getStringHash getString, ffff fItem);

#endif