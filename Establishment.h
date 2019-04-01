#ifndef Establishment_h
#define Establishment_h

#include <stdio.h>
#include <stdlib.h>

/** Esse é o módulo estabelecimento, que auxilia na criação e manipulação de estabelecimenos.
	Um estabelecimento é definido por um cnpj, condt, cep, face, num, nome. */

/** Cria um apelido Establishment para void*. */
typedef void* Establishment;

/** Pós-condição: Cria e retorna um ponteiro para o estabelecimento. */
Establishment createEstab(char *cnpj, char *codt, char *cep, char face, int num, char *name);

/** Pós-condição: Retorna o cnpj do estabelecimento passado por parâmetro. */
char* getEstabCnpj(Establishment e);

/** Pós-condição: Retorna o codt do estabelecimento passado por parâmentro. */
char* getEstabCodt(Establishment e);

/** Pós-condição: Retorna o cep do estabelecimento passado por parâmentro. */
char* getEstabCep(Establishment e);

/** Pós-condição: Retorna a face da quadra em que o estabelecimento está instalado. */
char getEstabFace(Establishment e);

/** Pós-condição: Retorna o numero do endereço em que o estabelecimento está instalado. */
int getEstabNum(Establishment e);

/** Pós-condição: Retorna o nome do estabelecimento passado por parâmentro. */
char* getEstabName(Establishment e);

/** Pós-condição: Printa na saida padrão todos os dados do estabaleciemnto. */
void printEstab(Establishment e);

/** Pós-condição: Libera e a ponta para null todos os blocos de memória alocados para o estabelecimento. */
void freeEstab(Establishment e);

/** Pós-condição: Printa o estabelecimento em um arquivo texto. */
void fprintEstabTXT(Establishment e, FILE* arq);

/** Pós-condição: Seta uma nova string para nome */
void setEstabName(Establishment e, char *s);

void setEstabCep(Establishment e, char *cep);

void setEstabFace(Establishment e, char face);

void setEstabNum(Establishment e, int num);

int equalEstabs(Establishment a, Establishment b);

#endif