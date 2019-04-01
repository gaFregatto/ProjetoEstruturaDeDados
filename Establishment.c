#include "Establishment.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Strings.h"

typedef struct _estab{
	String cnpj, codt, cep, name;
	char face;
	int num;
}estab;

Establishment createEstab(String cnpj, String codt, String cep, char face, int num, String name){
	estab* newEstab = malloc(sizeof(estab));
	newEstab->cnpj = calloc(strlen(cnpj)+1, sizeof(char));
	strcpy(newEstab->cnpj, cnpj);
	newEstab->codt = calloc(strlen(codt)+1, sizeof(char));
	strcpy(newEstab->codt, codt);
	newEstab->cep = calloc(strlen(cep)+1, sizeof(char));
	strcpy(newEstab->cep, cep);
	newEstab->face = face;
	newEstab->num = num;
	newEstab->name = calloc(strlen(name)+1, sizeof(char));
	strcpy(newEstab->name, name);
	return newEstab;
}

String getEstabCnpj(Establishment e){
	estab *auxEstab = (estab*)e;
	return auxEstab->cnpj;
}

String getEstabCodt(Establishment e){
	estab *auxEstab = (estab*)e;
	return auxEstab->codt;
}

String getEstabCep(Establishment e){
	estab *auxEstab = (estab*)e;
	return auxEstab->cep;
}

char getEstabFace(Establishment e){
	estab *auxEstab = (estab*)e;
	return auxEstab->face;
}

int getEstabNum(Establishment e){
	estab *auxEstab = (estab*)e;
	return auxEstab->num;
}

String getEstabName(Establishment e){
	estab *auxEstab = (estab*)e;
	return auxEstab->name;
}

void printEstab(Establishment e){
	estab* auxEstab = (estab*)e;
	printf("\nESTABELECIMENTO - Cnpj:%s  Codt:%s  Cep:%s  Face:%c  Num:%d  Nome:%s", auxEstab->cnpj, auxEstab->codt, auxEstab->cep, auxEstab->face, auxEstab->num, auxEstab->name);
}

void freeEstab(Establishment e){
	estab *auxEstab = (estab*)e;
	free(auxEstab->cnpj);	auxEstab->cnpj = NULL;
	free(auxEstab->codt);	auxEstab->codt = NULL;
	free(auxEstab->cep);	auxEstab->cep = NULL;
	free(auxEstab->name);	auxEstab->name = NULL;
	free(auxEstab);		auxEstab = NULL;
}

void fprintEstabTXT(Establishment e, FILE* arq){
	estab* auxEstab = (estab*)e;
	fprintf(arq, "ESTABELECIMENTO - Cnpj:%s  Codt:%s  Cep:%s  Face:%c  Num:%d  Nome:%s\n", auxEstab->cnpj, auxEstab->codt, auxEstab->cep, auxEstab->face, auxEstab->num, auxEstab->name);
}

void setEstabName(Establishment e, String s){
	estab *auxEstab = (estab*)e;
	free(auxEstab->name); auxEstab->name=NULL;
	auxEstab->name = calloc((strlen(s)+1), sizeof(char));
	strcpy(auxEstab->name, s);
}

void setEstabCep(Establishment e, char *cep){
	estab *auxE = (estab*)e;
	free(auxE->cep); auxE->cep = NULL;
	auxE->cep = calloc((strlen(cep)+1), sizeof(char));
	strcpy(auxE->cep, cep);
}

void setEstabFace(Establishment e, char face){
	estab *auxE = (estab*)e;
	auxE->face = face;
}

void setEstabNum(Establishment e, int num){
	estab *auxE = (estab*)e;
	auxE->num = num;
}

int equalEstabs(Establishment a, Establishment b){
	estab *aa = (estab*)a;
	estab *bb = (estab*)b;
	if(strcmp(getEstabCnpj(aa), getEstabCnpj(bb))==0)
		return 1;
	else return 0;
}