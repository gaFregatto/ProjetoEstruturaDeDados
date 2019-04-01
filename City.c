#include "City.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Block.h"
#include "Equip.h"
#include "KDtree.h"

typedef struct _city{
	KDtree treeBlock;
	KDtree treeHydrant;
	KDtree treeSemaphore;
	KDtree treeTower;
}city;

City createCity(){
	city *newCity;
	newCity = (city*)malloc(sizeof(city));
	newCity->treeBlock = createKDT();
	newCity->treeHydrant = createKDT();
	newCity->treeSemaphore = createKDT();
	newCity->treeTower = createKDT();
	return newCity;
}

void setBlock(City ct, Block block){
	city *auxCity = (city*)ct;
	insertKDT(auxCity->treeBlock, block, getBlockX, getBlockY);
}

void setHydrant(City ct, Equip hydrant){
	city *auxCity = (city*)ct;
	insertKDT(auxCity->treeHydrant, hydrant, getEquipX, getEquipY);
}

void setSemaphore(City ct, Equip semaphore){
	city *auxCity = (city*)ct;
	insertKDT(auxCity->treeSemaphore, semaphore, getEquipX, getEquipY);
}

void setTower(City ct, Equip tower){
	city *auxCity = (city*)ct;
	insertKDT(auxCity->treeTower, tower, getEquipX, getEquipY);
}

KDtree getBlocks(City ct){
	city *auxCity = (city*)ct;
	return auxCity->treeBlock;
}

KDtree getHydrants(City ct){
	city *auxCity = (city*)ct;
	return auxCity->treeHydrant;
}

KDtree getSemaphores(City ct){
	city *auxCity = (city*)ct;
	return auxCity->treeSemaphore;
}

KDtree getTowers(City ct){
	city *auxCity = (city*)ct;
	return auxCity->treeTower;
}

void freeCity(City ct){
	city *auxCity = (city*)ct;

	if(sizeKDT(auxCity->treeBlock)<=0){
		free(auxCity->treeBlock); 
		auxCity->treeBlock = NULL; 
	}else{
		freeKDT(auxCity->treeBlock, freeBlock);	
	} 

	if(sizeKDT(auxCity->treeHydrant)<=0){
		free(auxCity->treeHydrant);  
		auxCity->treeHydrant = NULL;
	}else{
		freeKDT(auxCity->treeHydrant, freeEquip);
	} 

	if(sizeKDT(auxCity->treeSemaphore)<=0){
		free(auxCity->treeSemaphore);
		auxCity->treeSemaphore = NULL;
	}else{
		freeKDT(auxCity->treeSemaphore, freeEquip);
	}

	if(sizeKDT(auxCity->treeTower)<=0){
		free(auxCity->treeTower);
		auxCity->treeTower = NULL;
	}else{
		freeKDT(auxCity->treeTower, freeEquip);	
	} 

	free(auxCity);
	auxCity = NULL;
}