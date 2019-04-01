#ifndef People_h
#define People_h

#include <stdio.h>
#include <stdlib.h>

/** Esse é o módulo People, ele auxília na criação e manipulação de pessoas. Uma pessoa 
	possui CPF, nome, sobrenome, sexo e uma data de nascimento. */

/** Cria um apelido People para void*. */
typedef void* People;

/** Pós-condição: Cria uma pessoa e retorna o ponteiro para sua estrutura. */
People createPeople(char *cpf, char *name, char *lastname, char gender, char *birth);

/** Pós-condição: Retorna o cpf da pessoa enviada por parâmetro. */
char* getPeopleCpf(People p);

/** Pós-condição: Retorna o nome da pessoa enviada por parâmetro. */
char* getPeopleName(People p);

/** Pós-condição: Retorna o sobrenome da pessoa enviada por parâmetro. */
char* getPeopleLastname(People p);

/** Pós-condição: Retorna o gênero da pessoa enviada por parâmentro. */
char getPeopleGender(People p);

/** Pós-condição: Retorna a data de nascimento da pessoa enviada por parâmentro. */
char* getPeopleBirth(People p);

/** Pós-condição: Printa uma pessoa na saída padrão. */
void printPeople(People p);

/** Pós-condição: Libera a memória ocupada pela estrutura da pessoa enviada por parâmentro e aponta os blocos para nulo. */
void freePeople(People p);

/** Pós-condição: Printa os dados da pessoa em um arquivo texto. */
void fprintPeopleTXT(People p, FILE* arq);

/** Pré-condição: Recebe uma pessoa e uma nova string. 
	Pós-condição: Seta a string como novo nome da pessoa. */
void setPeopleName(People p, char *name);

int equalPeoples(People a, People b);

#endif