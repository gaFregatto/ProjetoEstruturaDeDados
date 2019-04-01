#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Strings.h"
#include "List.h"
#include "City.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Block.h"
#include "KDtree.h"
#include "Equip.h"
#include "Establishment.h"
#include "People.h"
#include "Resident.h"
#include "Description.h"
#include "HashTable.h"
#include "Graph.h"

//  IMPORTANTE LEMBRAR que para verificarmos as contas de região, 
//              no código devemos somar/subtrair as ancoras com sua altura ou largura. O svg para printar faz automaticamente por isso confunde.
//  T5 -> implementar o grafo.

int main(int argc, char *argv[]){ 
  String pathEntry, pathOut, fill, stroke, pathQry, pathEC, pathPM, pathE=NULL, pathV;
  List listCirc=createList(), listRect=createList(), listOverlap=createList(), listDescript=createList(), listEstab=createList(), listPeople=createList(), listResident=createList();
  City city = createCity();
  Graph *graph = createGraph();

  if(comandoE(argc,argv))   pathE = getPathE(argc, argv);
  pathEntry = getPathEntry(argc, argv, pathE);
  pathOut = getPathOut(argc, argv);

  arquivoGEO(pathEntry, pathOut, argc, argv, listCirc, listRect, listOverlap, city);

  if(comandoEC(argc,argv)){
    pathEC = getPathEC(argc, argv, pathE);
    arquivoEC(pathEC, pathEntry, pathOut, listDescript, listEstab);
  }

  if(comandoPM(argc, argv)){
    pathPM = getPathPM(argc, argv, pathE);
    arquivoPM(pathPM, pathEntry, pathOut, listPeople, listResident);
  }

  if(comandoV(arqc, argv)){
    pathV = getPathV(argc, argv, pathE);
    arquivoV(pathV, pathEntry, pathOut, graph);
  }

  if(comandoQ(argc, argv)){    
    pathQry = getPathQry(argc, argv, pathE);
    arquivoQRY(pathQry, pathEntry, pathOut, argc, argv, city, listCirc, listRect, listOverlap, 
                                              listPeople, listResident, listEstab, listDescript);
  }

  printf("\nEncerrando programa..\n\n");
  freeL(listDescript, freeDescript);
  freeL(listEstab, freeEstab);
  freeL(listPeople, freePeople);
  freeL(listResident, freeResident);
  freeL(listCirc, freeCircle);
  freeL(listRect, freeRectangle);
  freeL(listOverlap, freeRectangle);
  freeCity(city);
  if(comandoQ(argc, argv))  free(pathQry);
  if(comandoE(argc, argv))  free(pathE);
  if(comandoEC(argc, argv))  free(pathEC);
  if(comandoPM(argc, argv))  free(pathPM);
  if(comandoV(argc, argv))  free(pathV);
  free(pathEntry);
  free(pathOut);

  return 0;
}
