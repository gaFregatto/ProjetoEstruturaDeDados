#ifndef Equip_h
#define Equip_h

/** Esse é o módulo Equip, que auxília na criação e manipulação de equipamentos urbanos.
	Um equipamento urbano possui sempre um ponto (x,y), raio, tipo (h, s ou t) para hidrante, 
	semáforo e torre respectivamente. Possui também cor de preenchimento e borda. */

#include <stdio.h>
#include <stdlib.h>

/** Define um apelido Equip para void*. */
typedef void* Equip;

/** Pré-condição: A estrutura de cores dos equipamentos já deve ter sido criada.
	Pós-condição: Cria um equipamento com seus dados já definidos. */
Equip createEquip(char type, char *id, float x, float y, float r, char *cstrk, char *cfill);

/** Pré-condição: O equipamento já deve existir.
	Pós-condição: Retorna o tipo do equipamento. */
char getEquipType(Equip e);

/** Pré-condição: O equipamento já deve existir.
	Pós-condição: Retorna a identificação do equipamento. */
char* getEquipId(Equip e);

/** Pré-condição: O equipamento já deve existir.
	Pós-condição: Retorna o ponto x do equipamento. */
float getEquipX(Equip e);

/** Pré-condição: O equipamento já deve existir.
	Pós-condição: Retorna o ponto y do equipamento. */
float getEquipY(Equip e);

/** Pré-condição: O equipamento já deve existir.
	Pós-condição: Retorna o ponto r do equipamento. */
float getEquipR(Equip e);

/** Pré-condição: O equipamento já deve existir.
	Pós-condição: Retorna a cor da borda do equipamento. */
char* getEquipStroke(Equip e);

/** Pré-condição: O equipamento já deve existir.
	Pós-condição: Retorna a cor de preenchimento do equipamento. */
char* getEquipFill(Equip e);

/** Pré-condição: O equipamento já deve existir.
	Pós-condição: Printa na saída padrão todos os dados do equipamento. */
void printEquip(Equip e);

/** Pré-condição: O equipamento já deve existir.
	Pós-condição: Libera o equipamento. */
void freeEquip(Equip e);

/** Pré-condição: O equipamento já deve existir.
	Pós-condição: Troca as cores da borda e preenchimento do equipamento.  */
void changeEquipColors(Equip e, char *stroke, char *fill);

/** Pré-condição: Recebe dois equipamentos não nulos.
	Pós-condição: Copia o segundo equipamento no primeiro. */
void copyEquip(Equip a, Equip b);

/** Pré-condição: Recebe um equipamento e um arquivo como parâmetro.
	Pós-condição: Printa o equipamento no arquivo svg passado por parâmetro. */
void printEquipSVG(Equip e, FILE *arq);

/** Pré-condição: Recebe um equipamento e um arquivo como parâmetro.
	Pós-condição: Printa o equipamento no arquivo txt passado por parâmetro. */
void printEquipTXT(Equip e, FILE *arq);

/** Pré-condição: Recebe um equipamento.
	Pós-condição: Duplica o equipamento.  */
Equip duplicateEquip(Equip e);

/** Pré-condição: Recebe dois equips.
	Pós-condição: Se eles forem iguais retorna 1, se não retorna 0. */
int equalEquips(Equip a, Equip b);

#endif