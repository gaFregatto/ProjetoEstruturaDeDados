#include "Block.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Strings.h"

typedef struct _block{
	String cep, cstrk, cfill;
	float x, y, w, h;
}block;

Block createBlock(String cep, float x, float y, float w, float h, String cstrk, String cfill){
	block *newBlock = malloc(sizeof(block));
	newBlock->cep = calloc(strlen(cep)+1, sizeof(char));
	strcpy(newBlock->cep, cep);
	newBlock->x = x;
	newBlock->y = y;
	newBlock->w = w;
	newBlock->h = h;
	newBlock->cstrk = calloc(strlen(cstrk)+1, sizeof(char));
	strcpy(newBlock->cstrk, cstrk);
	newBlock->cfill = calloc(strlen(cfill)+1, sizeof(char));
	strcpy(newBlock->cfill, cfill);
	return newBlock;
}

String getBlockCep(Block b){
	block *auxBlock = (block*)b;
	return auxBlock->cep;
}

float getBlockX(Block b){
	block *auxBlock = (block*)b;
	return auxBlock->x;
}

float getBlockY(Block b){
	block *auxBlock = (block*)b;
	return auxBlock->y;
}

float getBlockW(Block b){
	block *auxBlock = (block*)b;
	return auxBlock->w;
}

float getBlockH(Block b){
	block *auxBlock = (block*)b;
	return auxBlock->h;
}

String getBlockStroke(Block b){
	block *auxBlock = (block*)b;
	return auxBlock->cstrk;
}

String getBlockFill(Block b){
	block *auxBlock = (block*)b;
	return auxBlock->cfill;
}

void printBlock(Block b){
	block *auxBlock = (block*)b;
	printf("\nQUADRA - Cep:%s x:%.5f y:%.5f w:%.5f h:%.5f Stroke:%s Fill:%s", auxBlock->cep, auxBlock->x, auxBlock->y, auxBlock->w, auxBlock->h, auxBlock->cstrk, auxBlock->cfill);
}

void freeBlock(Block b){
	if(b != NULL){
		block *auxBlock = (block*)b;
		free(auxBlock->cep);
		auxBlock->cep = NULL;
		free(auxBlock->cstrk);
		auxBlock->cstrk = NULL;
		free(auxBlock->cfill);
		auxBlock->cfill = NULL;
		free(auxBlock);
		auxBlock = NULL;
	}
}

void changeBlockColors(Block b, String stroke, String fill){
	block *auxBlock = (block*)b;
	free(auxBlock->cstrk);
	auxBlock->cstrk = NULL;
	free(auxBlock->cfill);
	auxBlock->cfill = NULL;
	auxBlock->cstrk = calloc(strlen(stroke)+1, sizeof(char));
	strcpy(auxBlock->cstrk, stroke);
	auxBlock->cfill = calloc(strlen(fill)+1, sizeof(char));
	strcpy(auxBlock->cfill, fill);
}

void copyBlock(Block a, Block b){
	block *auxA = (block*)a;
	block *auxB = (block*)b;

	auxA->x = auxB->x;
	auxA->y = auxB->y;
	auxA->w = auxB->w;
	auxA->h = auxB->h;
	free(auxA->cep); auxA->cep = NULL;
	free(auxA->cstrk); auxA->cstrk = NULL;
	free(auxA->cfill); auxA->cfill = NULL;
	auxA->cep = calloc(strlen(auxB->cep)+1, sizeof(char));
	strcpy(auxA->cep, auxB->cep);
	auxA->cstrk = calloc(strlen(auxB->cstrk)+1, sizeof(char));
	strcpy(auxA->cstrk, auxB->cstrk);
	auxA->cfill = calloc(strlen(auxB->cfill)+1, sizeof(char));
	strcpy(auxA->cfill, auxB->cfill);
}

void printBlockSVG(Block b, FILE *arq){
	block *auxB = (block*)b;
	fprintf(arq, "<rect x=\"%.1f\" y=\"%.1f\" width=\"%.1f\" height=\"%.1f\" fill=\"%s\" stroke=\"%s\"/>\n", auxB->x, auxB->y, auxB->w, auxB->h, auxB->cfill, auxB->cstrk);
	fprintf(arq, "<text x=\"%.1f\" y=\"%.1f\" fill=\"%s\">%s</text>\n", auxB->x+15.0, auxB->y+25.0, "white", auxB->cep);
}

void printBlockTXT(Block b, FILE *arq){
	block *auxB = (block*)b;
	 fprintf(arq, "QUADRA - CEP:%s x:%.3f y:%.3f Largura:%.3f Altura:%.3f Borda:%s Preench:%s\n", getBlockCep(auxB), getBlockX(auxB), getBlockY(auxB), getBlockW(auxB), getBlockH(auxB), getBlockStroke(auxB), getBlockFill(auxB));
	}

Block duplicateBlock(Block b){
	block *auxBlock = (block*)b;
	block *newBlock = createBlock(auxBlock->cep, auxBlock->x, auxBlock->y, auxBlock->w, auxBlock->h, auxBlock->cstrk, auxBlock->cfill);
	return newBlock;
}

int equalBlocks(Block a, Block b){
	block *aa = (block*)a;
	block *bb = (block*)b;

	if((strcmp(getBlockCep(aa),getBlockCep(bb)) == 0)
		&& (getBlockX(aa)==getBlockX(bb)) && (getBlockY(aa)==getBlockY(bb)) 
		&& (getBlockW(aa)==getBlockW(bb)) && (getBlockH(aa)==getBlockH(bb)))
		return 1;
	else return 0;
}