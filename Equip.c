#include "Equip.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Strings.h"

typedef struct _equip{
	char type;
	String id, cstrk, cfill;
	float x, y, r;
}equip;

Equip createEquip(char type, String id, float x, float y, float r, String cstrk, String cfill){
	equip *newEquip = malloc(sizeof(equip));
	newEquip->type = type;
	newEquip->id = calloc(strlen(id)+1, sizeof(char));
	strcpy(newEquip->id, id);
	newEquip->x = x;
	newEquip->y = y;
	newEquip->r = r;
	newEquip->cstrk = calloc(strlen(cstrk)+1, sizeof(char));
	strcpy(newEquip->cstrk, cstrk);
	newEquip->cfill = calloc(strlen(cfill)+1, sizeof(char));
	strcpy(newEquip->cfill, cfill);
	return newEquip;
}

char getEquipType(Equip e){
	equip *auxEquip = (equip*)e;
	return auxEquip->type;
}

String getEquipId(Equip e){
	equip *auxEquip = (equip*)e;
	return auxEquip->id;
}

float getEquipX(Equip e){
	equip *auxEquip = (equip*)e;
	return auxEquip->x;
}

float getEquipY(Equip e){
	equip *auxEquip = (equip*)e;
	return auxEquip->y;
}

float getEquipR(Equip e){
	equip *auxEquip = (equip*)e;
	return auxEquip->r;
}

String getEquipStroke(Equip e){
	equip *auxEquip = (equip*)e;
	return auxEquip->cstrk;
}

String getEquipFill(Equip e){
	equip *auxEquip = (equip*)e;
	return auxEquip->cfill;
}

void printEquip(Equip e){
	equip *auxEquip = (equip*)e;
	if(auxEquip->type == 'h')
		printf("\nHIDRANTE - ID:%s x:%.5f y:%.5f r:%.5f Stroke:%s Fill:%s", auxEquip->id, auxEquip->x, auxEquip->y, auxEquip->r, auxEquip->cstrk, auxEquip->cfill);
	else if(auxEquip->type == 's')
		printf("\nSEMAFORO - ID:%s x:%.5f y:%.5f r:%.5f Stroke:%s Fill:%s", auxEquip->id, auxEquip->x, auxEquip->y, auxEquip->r, auxEquip->cstrk, auxEquip->cfill);
	else if(auxEquip->type == 't')
		printf("\nTORRE - ID:%s x:%.5f y:%.5f r:%.5f Stroke:%s Fill:%s", auxEquip->id, auxEquip->x, auxEquip->y, auxEquip->r, auxEquip->cstrk, auxEquip->cfill);
}

void freeEquip(Equip e){
	if(e != NULL){
		equip *auxEquip = (equip*)e;
		free(auxEquip->id);
		auxEquip->id = NULL;
		free(auxEquip->cstrk);
		auxEquip->cstrk = NULL;
		free(auxEquip->cfill);
		auxEquip->cfill = NULL;
		free(auxEquip);
		auxEquip = NULL;
	}
}

void changeEquipColors(Equip e, String stroke, String fill){
	equip *auxEquip = (equip*)e;
	free(auxEquip->cstrk);
	auxEquip->cstrk = NULL;
	free(auxEquip->cfill);
	auxEquip->cfill = NULL;
	auxEquip->cstrk = calloc(strlen(stroke)+1, sizeof(char));
	strcpy(auxEquip->cstrk, stroke);
	auxEquip->cfill = calloc(strlen(fill)+1, sizeof(char));
	strcpy(auxEquip->cfill, fill);
}

void copyEquip(Equip a, Equip b){
	equip *auxA = (equip*)a;
	equip *auxB = (equip*)b;

	auxA->x = auxB->x;
	auxA->y = auxB->y;
	auxA->r = auxB->r;
	free(auxA->id); auxA->id = NULL;
	free(auxA->cstrk); auxA->cstrk = NULL;
	free(auxA->cfill); auxA->cfill = NULL;
	auxA->id = calloc(strlen(auxB->id)+1, sizeof(char));
	strcpy(auxA->id, auxB->id);
	auxA->cstrk = calloc(strlen(auxB->cstrk)+1, sizeof(char));
	strcpy(auxA->cstrk, auxB->cstrk);
	auxA->cfill = calloc(strlen(auxB->cfill)+1, sizeof(char));
	strcpy(auxA->cfill, auxB->cfill);
}

void printEquipSVG(Equip e, FILE *arq){
	equip *auxEquip = (equip*)e;
	fprintf(arq, "<circle cx=\"%.1f\" cy=\"%.1f\" r=\"%.1f\" fill=\"%s\" stroke=\"%s\"/>\n", auxEquip->x, auxEquip->y, auxEquip->r, auxEquip->cfill, auxEquip->cstrk);
}

void printEquipTXT(Equip e, FILE *arq){
	equip *auxEquip = (equip*)e;
	if(auxEquip->type == 'h')
		fprintf(arq, "HIDRANTE - ID:%s x:%.5f y:%.5f r:%.5f Stroke:%s Fill:%s\n", auxEquip->id, auxEquip->x, auxEquip->y, auxEquip->r, auxEquip->cstrk, auxEquip->cfill);
	else if(auxEquip->type == 's')
		fprintf(arq, "SEMAFORO - ID:%s x:%.5f y:%.5f r:%.5f Stroke:%s Fill:%s\n", auxEquip->id, auxEquip->x, auxEquip->y, auxEquip->r, auxEquip->cstrk, auxEquip->cfill);
	else if(auxEquip->type == 't')
		fprintf(arq, "TORRE - ID:%s x:%.5f y:%.5f r:%.5f Stroke:%s Fill:%s\n", auxEquip->id, auxEquip->x, auxEquip->y, auxEquip->r, auxEquip->cstrk, auxEquip->cfill);
}

Equip duplicateEquip(Equip e){
	equip *auxE = (equip*)e;
	equip *newEquip = createEquip(auxE->type, auxE->id, auxE->x, auxE->y, auxE->r, auxE->cstrk, auxE->cfill);
	return newEquip;
}

int equalEquips(Equip a, Equip b){
	equip *aa = (equip*)a;
	equip *bb = (equip*)b;

	if((strcmp(getEquipId(aa),getEquipId(bb)) == 0)	&& (getEquipX(aa)==getEquipX(bb)) 
		&& (getEquipY(aa)==getEquipY(bb)) && (getEquipR(aa)==getEquipR(bb)))
		return 1;
	else return 0;
}