#include "Read.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Strings.h"
#include "List.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Shapes.h"
#include "City.h"
#include "Block.h"
#include "Equip.h"
#include "Description.h"
#include "Establishment.h"
#include "People.h"
#include "Resident.h"
#include "KDtree.h" 
#include "HashTable.h"
#include "Graph.h"

void arquivoGEO(String pathEntry, String pathOut, int argc, char *argv[], List listCirc, List listRect, List listOverlap, City city){
  FILE *arq;
  char op[2], stroke[27], fill[27], sufixo[15], ch, cep[20], id_equip[10], stroke_b[27], stroke_h[27], stroke_s[27], stroke_t[27], fill_b[27], fill_h[27], fill_s[27], fill_t[27];
  int i, nMax, id, id1, id2;
  float r, x, y, h, w;
  Circle circ;
  Rectangle rect;
  Block block;
  Equip equip;

  arq = fopen(pathEntry, "r");
  if(arq != NULL) printf("\nArquivo GEO aberto para leitura com sucesso!");
  else  printf("\nFalha na abertura do arquivo GEO.");

  while(!feof(arq) || op[0] == '#'){
    fscanf(arq, "%c", &op[0]);
    switch(op[0]){
      case 'n':
        fscanf(arq, "%c", &op[1]);
        fscanf(arq, "%c", &ch);
        fscanf(arq, "%d", &nMax);
      break;

      case 'c':
        fscanf(arq, "%c", &op[1]);
        switch(op[1]){
          case ' ':
            fscanf(arq, "%d %s %s %f %f %f", &id, stroke, fill, &r, &x, &y);
            circ = createCircle(id, x, y, r, fill, stroke);
            insertList(listCirc, circ);
          break;

          case 'q':
            fscanf(arq, "%s %s", stroke_b, fill_b);
          break;  

          case 'h':
            fscanf(arq, "%s %s", stroke_h, fill_h);
          break;

          case 's':
            fscanf(arq, "%s %s", stroke_s, fill_s);
          break;

          case 't':
            fscanf(arq, "%s %s", stroke_t, fill_t);
          break;

          default:
          break;
        }
      break;

      case 'r':
        fscanf(arq, "%d %s %s %f %f %f %f", &id, stroke, fill, &w, &h, &x, &y);
        rect = createRectangle(id, x, y, h, w, fill, stroke);
        insertList(listRect, rect);
      break;

      case 'o':
        fscanf(arq, "%d %d", &id1, &id2);
        searchIDsOverlap(listCirc, listRect, id1, id2, pathOut, pathEntry, listOverlap);
      break;

      case 'i':
        fscanf(arq, "%d %f %f", &id, &x, &y);
        searchIDsInternalPoint(listCirc, listRect, id, x, y, pathOut, pathEntry);
      break;

      case 'd':
        fscanf(arq, "%d %d", &id1, &id2);
        searchIDsDistance(listCirc, listRect, id1 ,id2, pathOut, pathEntry);
      break;

      case 'a':
        fscanf(arq, "%d %s", &id, sufixo);
        printSVGsufixo(listCirc, listRect, id, sufixo, pathOut, pathEntry);
      break;

      case '#':
        printSVG(listCirc, listRect, pathOut, pathEntry, listOverlap, city);
        printf("\nFechando arquivo GEO.");
      break;

      case 'q' :
        fscanf(arq, "%s %f %f %f %f", cep, &x, &y, &w, &h);
        block = createBlock(cep, x, y, w, h, stroke_b, fill_b);
        setBlock(city, block);
      break;

      case 'h' :
        fscanf(arq, "%s %f %f", id_equip, &x, &y);
        equip = createEquip('h', id_equip, x, y, 3.0, stroke_h, fill_h);
        setHydrant(city, equip);
      break;

      case 's' :
        fscanf(arq, "%s %f %f", id_equip, &x, &y);
        equip = createEquip('s', id_equip, x, y, 3.0, stroke_s, fill_s);
        setSemaphore(city, equip);
      break;

      case 't' :
        fscanf(arq, "%s %f %f", id_equip, &x, &y);
        equip = createEquip('t', id_equip, x, y, 5.0, stroke_t, fill_t);
        setTower(city, equip);
      break;

      default:
      break;
    }
  }
  fclose(arq);
}


void arquivoQRY(char *pathQry, char *pathEntry, char *pathOut, int argc, char *argv[], void *city, void *listCirc, void *listRect, void *listOverlap, void *listPeople, void *listResident, void *listEstab, void *listDescript){
  FILE *arq, *arqSVGqry;
  char face, types[4], op[6], stroke[27], fill[27], cepid[30], cpf[20], cnpj[50], codt[50], compl[60];
  float x, y, w, h, r;
  int num=0;
  String pathSVGqry;
  Rectangle rect;
  Circle circ;
  List dashRectangles=createList(), dashCircles=createList(), 
        listPeopleCirc=createList(), listEstabRect=createList(), listRip=createList(), listDLRect=createList();
  Equip tower1=NULL, tower2=NULL;
  People people;
  Resident resid;
  Description descript;
  Establishment estab;
  HashTable blockXcep = buildHashKDT(getBlocks(city), getBlockCep, freeBlock);
  HashTable hydrantXid = buildHashKDT(getHydrants(city), getEquipId, freeEquip);
  HashTable peopleXcpf = buildHashList(listPeople, getPeopleCpf);
  HashTable residentXcep = buildHashList(listResident, getResidentCep);
  HashTable residentXcpf = buildHashList(listResident, getResidentCpf);
  HashTable estabXcep = buildHashList(listEstab, getEstabCep);
  HashTable estabXcnpj = buildHashList(listEstab, getEstabCnpj);
  HashTable descriptionXcodt = buildHashList(listDescript, getDescriptCodt);

  arq = fopen(pathQry, "r");
  if(arq != NULL)   printf("\nArquivo QRY aberto para leitura com sucesso!");
  else   printf("\nFalha na abertura do arquivo QRY.");

  while(!feof(arq)){
    fscanf(arq, "%c", &op[0]);
    switch(op[0]){

      case 'q': // q? 
        fscanf(arq, "%c", &op[1]);
        fscanf(arq, "%f %f %f %f", &x, &y, &w, &h);
        rect = createRectangle(-1, x, y, h, w, "-", "-");
        insertList(dashRectangles, rect);  
        reportRectangle(city, pathEntry, pathOut, x, y, w, h);
      break;

      case 'Q': // Q? 
        fscanf(arq, "%c", &op[1]);
        fscanf(arq, "%f %f %f", &r, &x, &y);
        circ = createCircle(-1, x, y, r, "none", "black");
        insertList(dashCircles, circ);
        reportCircle(city, pathEntry, pathOut, x, y, r);
      break;

      case 'd':
        fscanf(arq, "%c", &op[1]);
        switch(op[1]){
          case 'q': // dq 
            fscanf(arq, "%f %f %f %f", &x, &y, &w, &h);
            rect = createRectangle(-1, x, y, h, w, "-", "-");
            insertList(dashRectangles, rect);
            removeBlockR(city, pathEntry, pathOut, x, y, w, h);
          break;

          case 'l': // dle 
            fscanf(arq, "%c", &op[2]);
            fscanf(arq, "%s %f %f %f %f", types, &x, &y, &w, &h);
            removeEquipR(city, pathEntry, pathOut, types, x, y, w, h);
          break;

          case 'm':  //dm?
            fscanf(arq, "%c", &op[2]);
            fscanf(arq, "%s", cpf);
            reportResidentByCpf(residentXcpf, peopleXcpf, blockXcep, cpf, pathEntry, pathOut, pathQry, listPeopleCirc);
          break;

          case 'e':  //de?
            fscanf(arq, "%c", &op[2]);
            fscanf(arq, "%s", cnpj);
            reportEstabByCnpj(estabXcnpj, descriptionXcodt, blockXcep, cnpj, pathEntry, pathOut, pathQry, listEstabRect);
          break;

          case 'p':  //dpr
            fscanf(arq, "%c", &op[2]);
            //printf("\nCaso dpr -> para implementar.");
            fscanf(arq, "%f %f %f %f", &x, &y, &w, &y);
            dpr(city, listPeopleCirc, listEstabRect, blockXcep, hydrantXid, peopleXcpf, residentXcpf, residentXcep, 
                  estabXcep, estabXcnpj, descriptionXcodt, pathEntry, pathOut, x, y, w, h);
          break;

          case 'c':
            //...
          break;

          default:
          break;
        }
      break;

      case 'D':
        fscanf(arq, "%c", &op[1]);
        switch(op[1]){
          case 'q': // Dq 
            fscanf(arq, "%f %f %f", &r, &x, &y);
            circ = createCircle(-1, x, y, r, "none", "black");
            insertList(dashCircles, circ);
            removeBlockC(city, pathEntry, pathOut, x, y, r);
          break;

          case 'l': // Dle 
            fscanf(arq, "%c", &op[2]);
            fscanf(arq, "%s %f %f %f", types, &x, &y, &r);
            removeEquipC(city, pathEntry, pathOut, types, x, y, r);
          break;

          default:  
          break;
        }
      break;

      case 'c':
        fscanf(arq, "%c", &op[1]);
        switch(op[1]){
          case 'c': // cc 
            fscanf(arq, "%s %s %s", cepid, stroke, fill);
            changeColor(city, cepid, stroke, fill);
          break;

          case 'r':
            fscanf(arq, "%c", &op[2]);
            switch(op[2]){
              case 'd': // crd? 
                fscanf(arq, "%c", &op[3]);
                fscanf(arq, "%s", cepid);
                searchCepId(city, pathEntry, pathOut, cepid);
              break;

              case 'b': // crb? 
                fscanf(arq, "%c", &op[3]);
                fscanf(arq, "%c", &op[4]);
                closestTowers(city, pathEntry, pathOut, &tower1, &tower2);
              break;

              default:
              break;
            }
          break;

          default:
          break;
        }
      break;

      case 'm':
      fscanf(arq, "%c", &op[1]);
      switch(op[1]){
        case '?':  //m?
          fscanf(arq, "%s", cepid);
          reportResidentByCep(residentXcep, peopleXcpf, cepid, pathEntry, pathOut);
        break;

        case 'r':
          fscanf(arq, "%c", &op[2]); //mr?
          fscanf(arq, "%f %f %f %f", &x, &y, &w, &h);
          reportResidentRect(city, residentXcep, peopleXcpf, pathEntry, pathOut, x, y, w, h);
        break;

        case 'u':
          fscanf(arq, "%c", &op[2]);
          fscanf(arq, "%c", &op[3]);
          switch(op[3]){
            case 'e':  //mudec
              fscanf(arq, "%c", &op[4]);
              fscanf(arq, "%s %s %c %d", cnpj, cepid, &face, &num);
              mudec(city, estabXcnpj, blockXcep, descriptionXcodt, cnpj, cepid, face, num, pathEntry, pathOut, listEstabRect, listDLRect);
            break;

            case ' ':  //mud
              fscanf(arq, "%s %s %c %d %s", cpf, cepid, &face, &num, compl);
              mud(city, peopleXcpf, blockXcep, residentXcpf, cpf, cepid, face, num, compl, pathEntry, pathOut, listPeopleCirc, listDLRect);
            break;
          }
        break;

        default:
        break;
      }
      break;

      case 'r':  //rip
        fscanf(arq, "%c", &op[1]);
        switch(op[1]){
          case 'i':
            fscanf(arq, "%c", &op[2]);
            fscanf(arq, "%s", cpf);
            rip(residentXcpf, peopleXcpf, blockXcep, cpf, pathEntry, pathOut, pathQry, listRip);
          break;

          case 'a':
            //...
          break; 

          default:
          break;
        }
      break;

      case 'e':
        fscanf(arq, "%c", &op[1]);
        fscanf(arq, "%c", &op[2]);
        switch(op[2]){
          case 'q':  //ecq?
            fscanf(arq, "%c", &op[3]);
            fscanf(arq, "%s", cepid);
            reportEstabByCep(estabXcep, cepid, pathEntry, pathOut);
          break;

          case 'r':  //ecr?
            fscanf(arq, "%c", &op[3]);
            fscanf(arq, "%s %f %f %f %f", codt, &x, &y, &w, &h);
            reportCodtRect(city, estabXcep, descriptionXcodt, codt, x, y, w, h, pathEntry, pathOut);
          break;

          default:
          break;
        }
      break;

      case 't':
        fscanf(arq, "%c", &op[1]);
        fscanf(arq, "%c", &op[2]);
        fscanf(arq, "%c", &op[3]);
        switch(op[3]){
          case 'q':  //tecq?
            fscanf(arq, "%c", &op[4]);
            fscanf(arq, "%s", cepid);
            reportEstabBlock(blockXcep, estabXcep, cepid, pathEntry, pathOut);
          break;

          case 'r':  //tecr?
            fscanf(arq, "%c", &op[4]);
            fscanf(arq, "%f %f %f %f", &x, &y, &w, &h);
            reportEstabTypeRect(city, blockXcep, estabXcep, descriptionXcodt, x, y, w, h, pathEntry, pathOut);
          break;

          default:
          break;
        }
      break;

      case 'h':
        fscanf(arq, "%c", &op[1]);
        fscanf(arq, "%c", &op[2]);
        fscanf(arq, "%c", &op[3]);
        switch(op[3]){
          case 'e':  //hmpe?
            fscanf(arq, "%c", &op[4]);
            fscanf(arq, "%s %c %d", cepid, &face, &num);
            closestHydrant(city, blockXcep, cepid, face, num, pathEntry, pathOut, listDLRect);
          break;

          case '?':  //hmp?
          fscanf(arq, "%s", cepid);
          closestHydrants(city, hydrantXid, cepid, pathEntry, pathOut, listDLRect);
          break;

          default:
          break;
        }
      break;

      case 'f':  //fec
        fscanf(arq, "%c", &op[1]);
        fscanf(arq, "%c", &op[2]);
        fscanf(arq, "%s", cnpj);
        closeEstab(estabXcnpj, blockXcep, cnpj, pathEntry, pathOut, listEstabRect);
      break;

      case '@':
        fscanf(arq, "%c", op[1]);
        switch(op[1]){

          case 'm':
            //...
          break;

          case 'e':
            //...
          break;

          case 'g':
            //...
          break;

          case 'x':
            //...
          break;

          case 't':
            //...
          break;

          case 'p':
            //...
          break;

          case 's':
            //...
          break;

          default:
          break;
        }
      break;

      case 'a':
        //...
      break;

      default:
      break;
    }
  }  
  
  printSVGqry(pathEntry, pathOut, pathQry, listCirc, listRect, listOverlap, city, 
                dashRectangles, dashCircles, tower1, tower2, listPeopleCirc, listEstabRect, listRip, listDLRect);
  printf("\nFechando arquivo QRY.");
  freeHash(blockXcep, freeList);
  freeHash(hydrantXid, freeList);
  freeHash(peopleXcpf, freeList);
  freeHash(residentXcep, freeList);
  freeHash(estabXcep, freeList);
  freeHash(estabXcnpj, freeList);
  freeHash(residentXcpf, freeList);
  freeHash(descriptionXcodt, freeList);
  freeL(dashRectangles, freeRectangle);
  freeL(dashCircles, freeCircle);
  freeL(listPeopleCirc, freeCircle);
  freeL(listEstabRect, freeRectangle);
  freeL(listRip, freeCircle);
  freeL(listDLRect, freeRectangle);
  fclose(arq);
}

void arquivoEC(String pathEC, String pathEntry, String pathOut, List listDescript, List listEstab){
  FILE *arq;
  char op, face, cnpj[50], codt[50], descript[50], cep[30], nome[50];
  int num;
  Description desc;
  Establishment estab;

  arq = fopen(pathEC, "r");
  if(arq!=NULL) printf("\nArquivo EC aberto para a leitura com sucesso!");
  else  printf("\nFalha na abertura do arquivo EC.");

  while(!feof(arq)){
    fscanf(arq, "%c", &op);
    switch(op){
      case 't':
        fscanf(arq, "%s %s", codt, descript);
        desc = createDescript(codt, descript);
        insertList(listDescript, desc);
        //printf("\nTESTE-> codt:%s  descript:%s", codt, descript);
      break;

      case 'e':
        fscanf(arq, "%s %s %s %c %d %s", cnpj, codt, cep, &face, &num, nome);
        estab = createEstab(cnpj, codt, cep, face, num, nome);
        insertList(listEstab, estab);
        //printf("\nTESTE-> cnpj:%s  codt:%s  cep:%s  face:%c  num:%d  nome:%s", cnpj, codt, cep, face, num, nome);
      break;

      default:
      break;
    }
  }
  fclose(arq);
}

void arquivoPM(String pathPM, String pathEntry, String pathOut, List listPeople, List listResident){
  FILE *arq;
  char op, sexo, face, cpf[20], nome[50], sobrenome[50], nasc[11], cep[30], compl[50];
  int num;
  People people;
  Resident resident;

  arq = fopen(pathPM, "r");
  if(arq!=NULL) printf("\nArquivo PM aberto para leitura com sucesso!");
  else  printf("\nFalha na abertura do arquivo PM.");

  while(!feof(arq)){
    fscanf(arq, "%c", &op);
    switch(op){
      case 'p':
        fscanf(arq, "%s %s %s %c %s", cpf, nome, sobrenome, &sexo, nasc);
        people = createPeople(cpf, nome, sobrenome, sexo, nasc);
        insertList(listPeople, people);
        //printf("\nTESTE-> cpf:%s  nome:%s  sobrenome:%s  sexo:%c  nasc:%s", cpf, nome, sobrenome, sexo, nasc);
      break;

      case 'm':
        fscanf(arq, "%s %s %c %d %s", cpf, cep, &face, &num, compl);
        resident = createResident(cpf, cep, face, num, compl);
        insertList(listResident, resident);
        //printf("\nTESTE-> cpf:%s cep:%s face:%c num:%d compl:%s", cpf, cep, face, num, compl);
      break;

      default:
      break;
    }
  }
  fclose(arq);
}

void arquivoVIA(String pathVIA, String pathEntry, String pathOut, Graph *graph){
  FILE *arq; 
  char op;
  char id[10], i[10], j[10], ldir[30], lesq[30], nome[100];
  float x, y, cmp, vm;

  arq = fopen(pathVIA, "r");
  if(arq != NULL) printf("\nArquivo VIA aberto para leitura com sucesso!");
  else  printf("\nFalha na abertura do arquivo VIA.");

  while(!feof(arq)){
    fscanf(arq, "%c" &op);
    switch(op){

      case 'v' :
        fscanf(arq, "%s %f %f", id, &x, &y);
        printf("\nTESTE-> vértice id:%s x:%f y:%f", id, x, y);
      break;

      case 'e' :
        fscanf(arq, "%s %s %s %s %f %f %s", i, j, ldir, lesq, &cmp, &vm, nome);
        printf("\nTESTE-> aresta i:%s j:%s ldir:%s lesq:%s cmp:%f vm:%f, nome:%s", i, j, ldir, lesq, cmp, vm, nome);
      break;

      default:
      break;
    }
  }
  fclose(arq);
}