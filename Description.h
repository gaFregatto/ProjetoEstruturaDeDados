#ifndef Description_h
#define Description_h

#include <stdio.h>
#include <stdlib.h>

/** Esse é o módulo descrição, que auxilia na criacão e manipulação de descricóes dos estabelecimentos.
	Uma descricão é definida pelo codt e a prórpia descrição ligada a ele. */

/** Cria um apelido Description para void*. */
typedef void* Description;

/** Pós-condição: Cria uma descrição e retorna um ponteiro para ela. */
Description createDescript(char *codt, char *desc);

/** Pós-condição: Retorna o codt da descrição. */	
char* getDescriptCodt(Description d); 

/** Pós-condição: Retorna a descrição. */
char* getDescriptD(Description d);

/** Pós-condição: Printa na saída padrão todos os dados da descrição. */
void printDescript(Description d);

/** Pós-condição: Libera e aponta para null todos os dados da descricão passada por parâmetro. */
void freeDescript(Description d);

/** Pós-condição: Printa a descrição em um arquivo texto. */
void fprintDescriptTXT(Description d, FILE* arq);

#endif