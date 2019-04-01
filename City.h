#ifndef City_h
#define City_h

/**	Esse é o módulo City, que auxília na criação e manipulação de elementos e dados de uma cidade. 
	Uma cidade contém quadras e equipamentos urbanos, os quais possuem suas respectivas cores. */

/**	Define City como apelido para void*. */
typedef void* City;

/**	Pós-condição: Aloca espaço na memória para a estrutura City, e retorna um ponteiro para a mesma. */
City createCity();

/**	Pré-condição: O espaço para a estrutura City já deve ter sido reservado.
	Pós-condição: Funções que setam os elementos urbanos. */
void setBlock(City ct, void *block);
void setHydrant(City ct, void *hydrant);
void setSemaphore(City ct, void *semaphore);
void setTower(City ct, void *tower);

/** Pré-condição: Pelo menos um elemento do respectivo get já deve ter sito criado, se não retorna NULL. 
	Pós-condição: Retorna um ponteiro para o root da árvore do respectivo elemento urbano. */
void* getBlocks(City ct);
void* getHydrants(City ct);
void* getSemaphores(City ct);
void* getTowers(City ct);

/** Pré-condição: Recebe uma cidade válida.
	Pós-condição: Libera toda a cidade e a aponta para NULL. */
void freeCity(City ct);

#endif