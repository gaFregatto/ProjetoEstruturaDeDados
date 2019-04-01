#include "People.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Strings.h"

typedef struct _people{
	String cpf, name, lastname, birth;
	char gender;
}people;

People createPeople(String cpf, String name, String lastname, char gender, String birth){
	people *newPeople = (people*)malloc(sizeof(people));
	newPeople->cpf = calloc(strlen(cpf)+1, sizeof(char));
	strcpy(newPeople->cpf, cpf);
	newPeople->name = calloc(strlen(name)+1, sizeof(char));
	strcpy(newPeople->name, name);
	newPeople->lastname = calloc(strlen(lastname)+1, sizeof(char));
	strcpy(newPeople->lastname, lastname);
	newPeople->gender = gender;
	newPeople->birth = calloc(strlen(birth)+1, sizeof(char));
	strcpy(newPeople->birth, birth);
	return newPeople;
}

String getPeopleCpf(People p){
	people *auxPeople = (people*)p;
	return auxPeople->cpf;
}

String getPeopleName(People p){
	people *auxPeople = (people*)p;
	return auxPeople->name;
}

String getPeopleLastname(People p){
	people *auxPeople = (people*)p;
	return auxPeople->lastname;
}

char getPeopleGender(People p){
	people *auxPeople = (people*)p;
	return auxPeople->gender;
}

String getPeopleBirth(People p){
	people *auxPeople = (people*)p;
	return auxPeople->birth;
}

void printPeople(People p){
	people *auxPeople = (people*)p;
	printf("\nPESSOA - CPF:%s  Nome:%s  Sobrenome:%s  Genero:%c  Nasc:%s", auxPeople->cpf, auxPeople->name, auxPeople->lastname, auxPeople->gender, auxPeople->birth);
}

void freePeople(People p){
	people *auxPeople = (people*)p;
	free(auxPeople->cpf);	auxPeople->cpf = NULL;
	free(auxPeople->name);	auxPeople->name = NULL;
	free(auxPeople->lastname);	auxPeople->lastname = NULL;
	free(auxPeople->birth);	auxPeople->birth = NULL;
	free(auxPeople);	auxPeople = NULL;
}

void fprintPeopleTXT(People p, FILE* arq){
	people *auxPeople = (people*)p;
	fprintf(arq, "PESSOA - CPF:%s  Nome:%s  Sobrenome:%s  Genero:%c  Nasc:%s\n", auxPeople->cpf, auxPeople->name, auxPeople->lastname, auxPeople->gender, auxPeople->birth);
}

void setPeopleName(People p, char *name){
	people *auxPeople = (people*)p;
	free(auxPeople->name);  auxPeople->name = NULL;
	auxPeople->name = calloc((strlen(name)+1), sizeof(char));
	strcpy(auxPeople->name, name);	
}

int equalPeoples(People a, People b){
	people *aa = (people*)a;
	people *bb = (people*)b;

	if(strcmp(getPeopleCpf(aa),getPeopleCpf(bb))==0)
		return 1;
	else return 0;
}