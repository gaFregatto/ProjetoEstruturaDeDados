#include "Resident.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Strings.h"

typedef struct _resid{
	String cpf, cep, compl;
	char face;
	int num;
}resident;

Resident createResident(String cpf, String cep, char face, int num, String compl){
	resident *newResident = malloc(sizeof(resident));
	newResident->cpf = calloc(strlen(cpf)+1, sizeof(char));
	strcpy(newResident->cpf, cpf);
	newResident->cep = calloc(strlen(cep)+1, sizeof(char));
	strcpy(newResident->cep, cep);
	newResident->face = face;
	newResident->num = num;
	newResident->compl = calloc(strlen(compl)+1, sizeof(char));
 	strcpy(newResident->compl, compl);
 	return newResident;
}

String getResidentCpf(Resident r){
	resident *auxResid = (resident*)r;
	return auxResid->cpf;
}

String getResidentCep(Resident r){
	resident *auxResid = (resident*)r;
	return auxResid->cep;
}

char getResidentFace(Resident r){
	resident *auxResid = (resident*)r;
	return auxResid->face;
}

int getResidentNum(Resident r){
	resident *auxResid = (resident*)r;
	return auxResid->num;
}

String getResidentCompl(Resident r){
	resident *auxResid = (resident*)r;
	return auxResid->compl;
}

void printResident(Resident r){
	resident *auxResid = (resident*)r;
	printf("\nMORADOR - CPF:%s  CEP:%s  Face:%c  Num:%d  Compl:%s", auxResid->cpf, auxResid->cep, auxResid->face, auxResid->num, auxResid->compl);
}

void freeResident(Resident r){
	resident *auxResid = (resident*)r;
	free(auxResid->cpf);    auxResid->cpf = NULL;
	free(auxResid->cep);	auxResid->cep = NULL;
	free(auxResid->compl);	auxResid->compl = NULL;
	free(auxResid);		auxResid = NULL;		
}

void fprintResidentTXT(Resident r, FILE* arq){
	resident *auxResid = (resident*)r;
	fprintf(arq, "MORADOR - CPF:%s  CEP:%s  Face:%c  Num:%d  Compl:%s\n", auxResid->cpf, auxResid->cep, auxResid->face, auxResid->num, auxResid->compl);

}

void setResidentCompl(Resident r, char *compl){
	resident *auxResid = (resident*)r;
	free(auxResid->compl); auxResid->compl=NULL;
	auxResid->compl = calloc((strlen(compl)+1), sizeof(char));
	strcpy(auxResid->compl, compl);		
}

void setResidentCep(Resident r, char *cep){
	resident *auxResid = (resident*)r;
	free(auxResid->cep); auxResid->cep=NULL;
	auxResid->cep = calloc((strlen(cep)+1), sizeof(char));
	strcpy(auxResid->cep, cep);			
}

void setResidentFace(Resident r, char face){
	resident *auxR = (resident*)r;
	auxR->face = face;
}

void setResidentNum(Resident r, int num){
	resident *auxR = (resident*)r;
	auxR->num = num;
}
