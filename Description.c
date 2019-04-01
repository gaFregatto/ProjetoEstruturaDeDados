#include "Description.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Strings.h"

typedef struct _desc{
	String codt, desc;
}description;

Description createDescript(String codt, String desc){
	description *newDescript = malloc(sizeof(description));
	newDescript->codt = calloc(strlen(codt)+1, sizeof(char));
	strcpy(newDescript->codt, codt);
	newDescript->desc = calloc(strlen(desc)+1, sizeof(char));
	strcpy(newDescript->desc, desc);
	return newDescript;
}

String getDescriptCodt(Description d){
	description *auxD = (description*)d;
	return auxD->codt;
}

String getDescriptD(Description d){
	description *auxD = (description*)d;
	return auxD->desc;
}

void printDescript(Description d){
	description *auxD = (description*)d;
	printf("\nDESCRICAO - Codt:%s  Descricao:%s", auxD->codt, auxD->desc);
}

void freeDescript(Description d){
	description *auxD = (description*)d;
	free(auxD->codt);	auxD->codt = NULL;
	free(auxD->desc);	auxD->desc = NULL;
	free(auxD);		auxD = NULL;
}

void fprintDescriptTXT(Description d, FILE* arq){
	description *auxD = (description*)d;
	fprintf(arq, "DESCRICAO - Codt:%s  Descricao:%s\n", auxD->codt, auxD->desc);	
}