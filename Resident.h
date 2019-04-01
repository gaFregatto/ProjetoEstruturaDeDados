#ifndef Resident_h
#define Resident_h

#include <stdio.h>
#include <stdlib.h>

/** Esse é o módulo moradores, que auxília na criação e manipulação de operações com moradores. 
	Um morador é definido por um cpf, cep, face, número e complemento. */

/** Cria um apelido Resident para void*. */
typedef void* Resident;

/** Pós-condição: Cria e retorna um um ponteiro para um morador. */
Resident createResident(char *cpf, char *cep, char face, int num, char *compl);

/** Pós-condição: Retorna o cpf do morador enviado por parâmetro. */
char* getResidentCpf(Resident r);

/** Pós-condição: Retorna o cep do morador enviado por parâmetro. */
char* getResidentCep(Resident r);

/** Pós-condição: Retorna a face da quadra em que o morador mora enviado por parâmetro mora. */
char getResidentFace(Resident r);

/** Pós-condição: Retorna o numero da casa em que o morador enviado por parâmetro mora. */
int getResidentNum(Resident r);

/** Pós-condição: Retorna o complemento do endereço do morador enviado por parâmetro. */
char* getResidentCompl(Resident r);

/** Pós-condição: Printa na saída padrão todos os dados do morador. */
void printResident(Resident r);

/** Pós-condição: Libera e aponta para null todos os espaçoes de memória alocados para o morador enviado por parâmentro. */ 
void freeResident(Resident r);

/** Pós-condição: Printa os dados do morador em um arquivo texto. */
void fprintResidentTXT(Resident r, FILE* arq);

/** Pré-condição: Recebe um residente e uma string.
	Pós-condição: Seta a string como novo complemento. */
void setResidentCompl(Resident r, char *compl);

void setResidentCep(Resident r, char *cep);

void setResidentFace(Resident r, char face);

void setResidentNum(Resident r, int num);

#endif 