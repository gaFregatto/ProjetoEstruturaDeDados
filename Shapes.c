#include "Shapes.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "Strings.h"
#include "List.h"
#include "Circle.h"
#include "Rectangle.h"
#include "City.h"
#include "Block.h"
#include "Equip.h"
#include "KDtree.h"
#include "HashTable.h"
#include "People.h"
#include "Resident.h"
#include "Description.h"
#include "Establishment.h"

/** Função interna <<
    Procura na lista definida pelo tipo, a figura com a id desejada.
        c -> lista de circulos.
        r -> lista de retangulos.
    Retorna o item com a id. Se nao encontrar retorna NULL.
*/
void* searchListID(List list, char tipo, int id){
  Posic p;
  Circle circ;
  Rectangle rect;
  int idt;

  if(tipo == 'c'){
    for(p=getFirst(list); p!=NULL; p=getNext(list, p)){
      circ = getItem(list, p);
      idt = getCircleID(circ);
      if(idt == id)   return circ;
    }
    return NULL;
  }else if(tipo == 'r'){
    for(p=getFirst(list); p!=NULL; p=getNext(list, p)){
      rect = getItem(list, p);
      idt = getRectangleID(rect);
      if(idt == id)   return rect;
    }
    return NULL;
  }
  return NULL;
}

/** Função privada -> Recebe quatro floats que representam dois pontos, e retorna a distância entre eles. */
float dist2points(float xx, float yy, float auxx, float auxy){
  float x, y, d;
  x = xx - auxx;
  x = pow(x, 2);
  y = yy - auxy;
  y = pow(y, 2);
  d = x + y;
  d = pow(d, 0.5);
  return d;
}

/** Funcão privada -> printa um círculo no svg. */
void fprintfCircSVG(Circle circ, FILE *arq){
  fprintf(arq,"<circle cx=\"%.1f\" cy=\"%.1f\" r=\"%.1f\" fill=\"%s\" stroke=\"%s\"/>\n", getCircleX(circ),getCircleY(circ), getCircleR(circ), getCircleFill(circ), getCircleStroke(circ));
}

/** Função privada -> printa um círculo pontilhado no svg. */
void fprintfDashCircSVG(Circle circ, FILE *arq){
  fprintf(arq, "<circle cx=\"%.1f\" cy=\"%.1f\" r=\"%.1f\" fill=\"%s\" stroke=\"%s\" stroke-dasharray=\"5\" />\n", getCircleX(circ), getCircleY(circ), getCircleR(circ), getCircleFill(circ), getCircleStroke(circ));
}

/** Função privada -> printa um ret6angulo pontilhado no svg. */
void fprintfDashRectSVG(Rectangle rect, FILE *arq){
  fprintf(arq, "<rect x=\"%.1f\" y=\"%.1f\" width=\"%.1f\" height=\"%.1f\" stroke=\"%s\" fill-opacity=\"0\" stroke-width=\"1\" stroke-dasharray=\"5\" />\n", getRectangleX(rect), getRectangleY(rect), getRectangleW(rect), getRectangleH(rect), getRectangleStroke(rect));
}

/** Funcão privada -> printa um retângulo no svg. */
void fprintfRectSVG(Rectangle rect, FILE *arq){
  fprintf(arq,"<rect x=\"%.1f\" y=\"%.1f\" width=\"%.1f\" height=\"%.1f\" fill=\"%s\" stroke=\"%s\"/>\n", getRectangleX(rect), getRectangleY(rect), getRectangleW(rect), getRectangleH(rect), getRectangleFill(rect), getRectangleStroke(rect));
}

/** Funcão privada -> printa uma linha no svg.  */
void fprintfLineSVG(FILE *arq, float x1, float y1, String stroke, float x2, float y2){
  fprintf(arq, "<line x1=\"%.1f\" y1=\"%.1f\" x2=\"%.1f\" y2=\"%.1f\" stroke=\"%s\"/>\n", x1, y1, x2, y2, stroke);
}

/** Funcão privada -> printa uma linha pontilhada no svg.   */
void fprintfDashLineSVG(FILE *arq, float x1, float y1, String stroke, float x2, float y2){
  fprintf(arq, "<line x1=\"%.1f\" y1=\"%.1f\" x2=\"%.1f\" y2=\"%.1f\" stroke=\"%s\" stroke-dasharray=\"5\"/>\n", x1, y1, x2, y2, stroke);
}

/** Funcão privada -> printa uma linha pontilhada no svg.   */
void fprintfStrongDashLineSVG(FILE *arq, float x1, float y1, String stroke, float x2, float y2){
  fprintf(arq, "<line x1=\"%.1f\" y1=\"%.1f\" x2=\"%.1f\" y2=\"%.1f\" stroke=\"%s\" stroke-dasharray=\"5\" stroke-width=\"5\"/>\n", x1, y1, x2, y2, stroke);
}

/** Funcão privada -> printa um texto em determinado um ponto no svg.   */
void fprintfTextSVG(FILE *arq, float x, float y, String text){
  fprintf(arq, "<text x=\"%.1f\" y=\"%.1f\" fill=\"%s\">%s</text>\n", x, y, "yellow", text);
}

/** Funcão privada -> printa a distancia entre os centros de massa das figuras no svg.  */
void fprintfDistSVG(FILE *arq, float x1, float y1, float x2, float y2, String stroke){
  float d, daux, x, y;
  x = x1 - x2;
  x = pow(x, 2);
  y = y1 - y2;
  y = pow(y, 2);
  d = x + y;
  d = pow(d, 0.5);
  fprintf(arq, "<text x=\"%.1f\" y=\"%.1f\" fill=\"%s\" style=\"font:5px Arial;\">%.2f</text>\n", x2, y2, stroke, d);
}

/** Função privada -> printa toda a cidade no arquivo svg. */
void fprintfCitySVG(City city, FILE *arq){
  KDtree blocks, hydrants, semaphores, towers;
  Block block;
  Equip equip;
  Posic p;

  blocks = getBlocks(city);
  printKDTarq(blocks, printBlockSVG, arq);
  hydrants = getHydrants(city);
  printKDTarq(hydrants, printEquipSVG, arq);
  semaphores = getSemaphores(city);
  printKDTarq(semaphores, printEquipSVG, arq);
  towers = getTowers(city);
  printKDTarq(towers, printEquipSVG, arq);
}

void printSVG(List listCirc, List listRect, String pathOut, String pathEntry, List listOverlap, City city){
  FILE *arqSVG, *arqTXT;
  String pathSVG, pathTXT;
  Circle circ;
  Rectangle rect;
  Posic p;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  fprintf(arqTXT, "\n");
  fclose(arqTXT);
  free(pathTXT);

  pathSVG = setPathSVG(pathEntry, pathOut);
  arqSVG = fopen(pathSVG, "w");
  if(arqSVG == NULL)  printf("\nFalha na abertura do arquivo SVG.");
  else  printf("\nArquivo SVG aberto com sucesso!");

  fprintf(arqSVG, "<!--Guilherme Arai Fregatto-->\n");
  fprintf(arqSVG, "<svg>\n");
  fprintfCitySVG(city, arqSVG);
  for(p=getFirst(listCirc); p!=NULL; p=getNext(listCirc, p)){
    circ = getItem(listCirc, p);
    fprintfCircSVG(circ, arqSVG);
  }
  for(p=getFirst(listRect); p!=NULL; p=getNext(listRect, p)){
    rect = getItem(listRect, p);
    fprintfRectSVG(rect, arqSVG);
  }
  for(p=getFirst(listOverlap); p!=NULL; p=getNext(listOverlap, p)){
    rect = getItem(listOverlap, p);
    fprintfTextSVG(arqSVG, getRectangleX(rect)-0.5, getRectangleY(rect)-0.5, "sobrepõe");
    fprintfDashLineSVG(arqSVG, getRectangleX(rect), getRectangleY(rect), "black", getRectangleW(rect), getRectangleY(rect));
    fprintfDashLineSVG(arqSVG, getRectangleX(rect), getRectangleY(rect), "black", getRectangleX(rect), getRectangleH(rect));
    fprintfDashLineSVG(arqSVG, getRectangleX(rect), getRectangleH(rect), "black", getRectangleW(rect), getRectangleH(rect));
    fprintfDashLineSVG(arqSVG, getRectangleW(rect), getRectangleH(rect), "black", getRectangleW(rect), getRectangleY(rect));
  }
  fprintf(arqSVG, "</svg>\n");

  printf("\nFechando arquivo SVG.");
  free(pathSVG);
  fclose(arqSVG);
}

void searchIDsOverlap(List listCirc, List listRect, int id1, int id2, String pathOut, String pathEntry, List listOverlap){
  FILE *arqTXT;
  String pathTXT;
  Circle circ1=NULL, circ2=NULL;
  Rectangle rect1=NULL, rect2=NULL, rectOver=NULL;
  float overX, overY, overW, overH, x1, y1, r1, w1, h1, x2, y2, r2, w2, h2, result, distX, distY, corner, X, Y;
  int overlapX=-1, overlapY=-1;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT == NULL)  printf("\nFalha na abertura do arquivo TXT.");
  else  printf("\nArquivo TXT aberto com sucesso!");

  /** Procura pelas figuras de id1 e id2 e armazenas em suas devidas variaveis. */
  circ1 = searchListID(listCirc, 'c', id1);
  if(circ1 == NULL)  rect1 = searchListID(listRect, 'r', id1);
  circ2 = searchListID(listCirc, 'c', id2);
  if(circ2 == NULL)  rect2 = searchListID(listRect, 'r', id2);

  if(circ1 != NULL){
    x1 = getCircleX(circ1);
    y1 = getCircleY(circ1);
    r1 = getCircleR(circ1);
  }
  if(circ2 != NULL){
    x2 = getCircleX(circ2);
    y2 = getCircleY(circ2);
    r2 = getCircleR(circ2);
  }
  if(rect1 != NULL){
    x1 = getRectangleX(rect1);
    y1 = getRectangleY(rect1);
    h1 = getRectangleH(rect1);
    w1 = getRectangleW(rect1);
  }
  if(rect2 != NULL){
    x2 = getRectangleX(rect2);
    y2 = getRectangleY(rect2);
    h2 = getRectangleH(rect2);
    w2 = getRectangleW(rect2);
  }

  /** Círculo com círculo.  */
  if(circ1 != NULL && circ2 != NULL){
    result = sqrt(pow(abs(x1-x2),2)+pow(abs(y1-y2),2));
    if((r1+r2)>=result){
      fprintf(arqTXT, "\nAs figuras de id %d e %d se sobrepoem.", id1, id2);
      /** Prepara as variáveis para printar o retângulo que sinaliza a sobreposicão no SVG. */
      if(x1-r1 < x2-r2)   overX = x1-r1;
      else if(x2-r2 <= x1-r1)   overX = x2-r2;
      if(y1-r1 < y2-r2)   overY = y1-r1;
      if(y2-r2 <= y1-r1)   overY = y2-r2;
      if(x1+r1 > x2+r2)   overW = x1+r1;
      if(x2+r2 >= x1+r1)   overW = x2+r2;
      if(y1+r1 > y2+r2)   overH = y1+r1;
      else if(y2+r2 >= y1+r1)   overH = y2+r2;
      rectOver = createRectangle(-1, overX, overY, overH, overW, "-", "-");
      insertList(listOverlap, rectOver);
    }else{
      fprintf(arqTXT, "\nAs figuras de id %d e %d nao se sobrepoem.", id1, id2);
    }
  }
  /** Retângulo com retângulo.  */
  if(rect1 != NULL && rect2 != NULL){
    if(x1 <= x2){
      if(x2 <= (x1+w1))
        overlapX = 1;
    }else{
      if(x1 <= (x2+w2))
        overlapX = 1;
    }
    if(y1 <= y2){
      if(y2 <= (y1+h1))
        overlapY = 1;
    }else{
      if(y1 <= (y2+h2))
        overlapY = 1;
    }
    if(overlapX == 1 && overlapY == 1){
      fprintf(arqTXT, "As figuras de id %d e %d se sobrepoem.\n", id1, id2);
      /** Prepara as variáveis para printar o retângulo que sinaliza a sobreposicão no SVG. */
      if(x1 < x2)   overX = x1;
      else if(x2 <= x1)   overX = x2;
      if(y1 < y2)    overY = y1;
      else if(y2 <= y1)   overY = y2;
      if(x1+w1 > x2+w2)   overW = x1+w1;
      else if(x2+w2 >= x1+w1)   overW = x2+w2;
      if(y1+h1 > y2+h2)   overH = y1+h1;
      else if(y2+h2 >= y1+h1)   overH = y2+h2;
      rectOver = createRectangle(-1, overX, overY, overH, overW, "-", "-");
      insertList(listOverlap, rectOver);
    }else{
      fprintf(arqTXT, "As figuras de id %d e %d nao se sobrepoem.\n", id1, id2);
    }
  }
  /** Retângulo com círculo.  */
  if(rect1 != NULL && circ2 != NULL){
    X = x1 + w1/2;
    Y = y1 + h1/2;
    distX = abs(x2 - X);
    distY = abs(y2 - Y);
    if((distX > (w1/2 + r2)) || (distY > (h1/2 + r2))){
      fprintf(arqTXT, "As figuras de id %d e %d nao se sobrepoem.\n", id1, id2);
    }else{
      if((distX <= (w1/2)) || (distY <= (h1/2))){
        fprintf(arqTXT, "As figuras de id %d e %d se sobrepoem.\n", id1, id2);
        /** Prepara as variáveis para printar o retângulo que sinaliza a sobreposicão no SVG. *******************************/
        if(x1 < x2-r2)    overX = x1;
        else if(x2-r2 <= x1)    overX = x2-r2;
        if(y1 < y2-r2)    overY = y1;
        else if(y2 - r2 <= y1)    overY = y2-r2;
        if(x1+w1 > x2+r2)    overW = x1+w1;
        else if(x2+r2 >= x1+w1)    overW = x2+r2;
        if(y1+h1 > y2+r2)    overH = y1+h1;
        else if(y2+r2 >= y1+h1)   overH = y2+r2;
        rectOver = createRectangle(-1, overX, overY, overH, overW, "-", "-");
        insertList(listOverlap, rectOver);
      }else{
        corner = pow((distX - w1/2), 2) + pow((distY - h1/2), 2);
        if(corner <= pow(r2, 2))
          fprintf(arqTXT, "As figuras de id %d e %d se sobrepoem.\n", id1, id2);
          /** Prepara as variáveis para printar o retângulo que sinaliza a sobreposicão no SVG. */
          if(x1 < x2-r2)    overX = x1;
          else if(x2-r2 <= x1)    overX = x2-r2;
          if(y1 < y2-r2)    overY = y1;
          else if(y2 - r2 <= y1)    overY = y2-r2;
          if(x1+w1 > x2+r2)    overW = x1+w1;
          else if(x2+r2 >= x1+w1)    overW = x2+r2;
          if(y1+h1 > y2+r2)    overH = y1+h1;
          else if(y2+r2 >= y1+h1)    overH = y2+r2;
          rectOver = createRectangle(-1, overX, overY, overH, overW, "-", "-");
          insertList(listOverlap, rectOver);
      }
    }
  }
  /** Círculo com retângulo. */
  if(circ1 != NULL && rect2 != NULL){
    X = x2 + w2/2;
    Y = y2 + h2/2;
    distX = abs(x1 - X);
    distY = abs(y1 - Y);
    if((distX > (w2/2 + r1)) || (distY > (h2/2 + r1))){
      fprintf(arqTXT, "As figuras de id %d e %d nao se sobrepoem.\n", id1, id2);
    }else{
      if((distX <= (w2/2)) || (distY <= (h2/2))){
        fprintf(arqTXT, "As figuras de id %d e %d se sobrepoem.\n", id1, id2);
        /** Prepara as variáveis para printar o retângulo que sinaliza a sobreposicão no SVG. */
        if(x1-r1 < x2)    overX = x1-r1;
        else if(x2 <= x1-r1)   overX = x2;
        if(y1-r1 < y2)    overY = y1-r1;
        else if(y2 <= y1-r1)    overY = y2;
        if(x1+r1 > x2+w2)     overW = x1+r1;
        else if(x2+w2 >= x1+r1)   overW = x2+w2;
        if(y1+r1 > y2+h2)    overH = y1+r1;
        else if(y2+h2 >= y1+r1)   overH = y2+h2;
        rectOver = createRectangle(-1, overX, overY, overH, overW, "-", "-");
        insertList(listOverlap, rectOver);
      }else{
        corner = pow((distX - w2/2), 2) + pow((distY - h2/2), 2);
        if(corner <= pow(r1, 2))
          fprintf(arqTXT, "As figuras de id %d e %d se sobrepoem.\n", id1, id2);
          /** Prepara as variáveis para printar o retângulo que sinaliza a sobreposicão no SVG. */
          if(x1-r1 < x2)    overX = x1-r1;
          else if(x2 <= x1-r1)   overX = x2;
          if(y1-r1 < y2)    overY = y1-r1;
          else if(y2 <= y1-r1)    overY = y2;
          if(x1+r1 > x2+w2)     overW = x1+r1;
          else if(x2+w2 >= x1+r1)   overW = x2+w2;
          if(y1+r1 > y2+h2)    overH = y1+r1;
          else if(y2+h2 >= y1+r1)   overH = y2+h2;
          rectOver = createRectangle(-1, overX, overY, overH, overW, "-", "-");
          insertList(listOverlap, rectOver);
      }
    }
  }
  free(pathTXT);
  printf("\nFechando arquivo TXT.");
  fclose(arqTXT);
}

void searchIDsInternalPoint(List listCirc, List listRect, int id, float X, float Y, String pathOut, String pathEntry){
  FILE *arqTXT;
  String pathTXT;
  Circle circ=NULL;
  Rectangle rect=NULL;
  float x, y, xw, yh, r, aux, aux2, d, daux;

  circ=searchListID(listCirc, 'c', id);
  rect=searchListID(listRect, 'r', id);

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT == NULL)  printf("\nFalha na abertura do arquivo TXT.");
  else  printf("\nArquivo TXT aberto com sucesso!");

  if(circ != NULL){ /** A figura é um círculo. */
    x = getCircleX(circ);
    y = getCircleY(circ);
    r = getCircleR(circ);
    aux = pow((X-x), 2);
    aux2 = pow((Y-y), 2);
    daux = (aux + aux2);
    d = sqrt(daux);
    if(d <= r)
      fprintf(arqTXT, "\nCirculo ID: %d  Ponto(x:%.3f, y:%.3f) esta dentro do circulo.", id, X, Y);
    else
      fprintf(arqTXT, "\nCirculo ID: %d Ponto(x:%.3f, y:%.3f) esta fora do circulo.", id, X, Y);
  }
  if(rect != NULL){ /** A figura é um retângulo. */
    x = getRectangleX(rect);
    y = getRectangleY(rect);
    xw = x + getRectangleW(rect);
    yh = y + getRectangleH(rect);
    if((x <= X) && (xw >= X) && (y <= Y) && (yh >= Y))
      fprintf(arqTXT, "\nRetangulo ID: %d  Ponto(x:%.3f, y:%.3f) esta dentro do retangulo.", id, X, Y);
    else
      fprintf(arqTXT, "\nRetangulo ID: %d  Ponto(x:%.3f, y:%.3f) esta fora do retangulo.", id, X, Y);
  }
  free(pathTXT);
  printf("\nFechando arquivo TXT.");
  fclose(arqTXT);
}

void searchIDsDistance(List listCirc, List listRect, int id1, int id2, String pathOut, String pathEntry){
  FILE *arqTXT;
  String pathTXT;
  Circle circ1=NULL, circ2=NULL;
  Rectangle rect1=NULL, rect2=NULL;
  float x1=0, y1=0, x2=0, y2=0, x=0, y=0, d=0;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT == NULL)  printf("\nFalha na abertura do arquivo TXT.");
  else  printf("\nArquivo TXT aberto com sucesso!");

  /** Procura pelas figuras de id1 e id2 e armazenas em suas devidas variaveis. */
  circ1 = searchListID(listCirc, 'c', id1);
  if(circ1 == NULL)  rect1 = searchListID(listRect, 'r', id1);
  circ2 = searchListID(listCirc, 'c', id2);
  if(circ2 == NULL)  rect2 = searchListID(listRect, 'r', id2);

  if(circ1 != NULL){
    x1 = getCircleX(circ1);
    y1 = getCircleY(circ1);
  }
  if(circ2 != NULL){
    x2 = getCircleX(circ2);
    y2 = getCircleY(circ2);
  }
  if(rect1 != NULL){
    x1 = getRectangleX(rect1);
    y1 = getRectangleY(rect1);
  }
  if(rect2 != NULL){
    x2 = getRectangleX(rect2);
    y2 = getRectangleY(rect2);
  }
  x = x1 - x2;
  x = pow(x, 2);
  y = y1 - y2;
  y = pow(y, 2);
  d = x + y;
  d = pow(d, 0.5);
  fprintf(arqTXT, "\nDistancia do centro de massa %.4f das figuras de ID %d e %d.", d, id1, id2);

  free(pathTXT);
  printf("\nFechando arquivo TXT.");
  fclose(arqTXT);
}

void printSVGsufixo(List listCirc, List listRect, int id, char sufixo[], String pathOut, String pathEntry){
  FILE *arqSVGsuf;
  String pathSVGsuf, stroke;
  Circle circ=NULL, circ2=NULL;
  Rectangle rect=NULL, rect2=NULL;
  Posic p;
  float x, y, x2, y2, w2, h2;

  pathSVGsuf = setPathSVGsufixo(pathEntry, pathOut, sufixo);
  arqSVGsuf = fopen(pathSVGsuf, "a");
  if(arqSVGsuf == NULL) printf("\nFalha na abertura do arquivo SVG sufixo.");
  else  printf("\nArquivo SVG sufixo aberto com sucesso!");

  circ=searchListID(listCirc, 'c', id);
  if(circ==NULL)  rect=searchListID(listRect, 'r', id);
  if(circ != NULL){ /** A figura é um círculo. */
    x = getCircleX(circ);
    y = getCircleY(circ);
    stroke = getCircleStroke(circ);
  }
  if(rect != NULL){ /** A figura é um retângulo. */
    x = getRectangleX(rect);
    y = getRectangleY(rect);
    stroke = getRectangleStroke(rect);
  }
  if(circ==NULL && rect==NULL){
    printf("\nERRO na escrita do arquivo SVG sufixo!!");
  }else{
    fprintf(arqSVGsuf, "<!--Guilherme Arai Fregatto-->\n");
    fprintf(arqSVGsuf, "<svg>\n");
    for(p=getFirst(listCirc); p!=NULL; p=getNext(listCirc, p)){
      circ2 = getItem(listCirc, p);
      x2 = getCircleX(circ2);
      y2 = getCircleY(circ2);
      if(circ != NULL && getCircleID(circ) != getCircleID(circ2)){
        fprintfLineSVG(arqSVGsuf, x, y, stroke, x2, y2);
        fprintfDistSVG(arqSVGsuf, x, y, x2, y2, stroke);
      }
    }
    for(p=getFirst(listRect); p!=NULL; p=getNext(listRect, p)){
      rect2 = getItem(listRect, p);
      x2 = getRectangleX(rect2);
      y2 = getRectangleY(rect2);
      w2 = getRectangleW(rect2);
      h2 = getRectangleH(rect2);
      if(rect != NULL && getRectangleID(rect) != getRectangleID(rect2)){
        fprintfLineSVG(arqSVGsuf, x, y, stroke, x2+(w2-w2/2), y2+(h2-h2/2));
        fprintfDistSVG(arqSVGsuf, x, y, x2+(w2-w2/2), y2+(h2-h2/2), stroke);
      }
    }
    fprintf(arqSVGsuf, "</svg>\n");
  }

  free(pathSVGsuf);
  printf("\nFechando arquivo SVG sufixo.");
  fclose(arqSVGsuf);
}

void printSVGqry(String pathEntry, String pathOut, String pathQry, List listCirc, List listRect, List listOverlap, City city, List dashRectangles, List dashCircles, Equip tower1, Equip tower2, List listPeopleCirc, List listEstabRect, List listRip, List listDLRect){
  FILE *arqSVGqry;
  String pathSVGqry;
  Circle circ, circ1, circ2;
  Rectangle rect;
  Posic p;

  if((tower1 != NULL) && (tower2 != NULL)){
    circ1 = createCircle(-1, getEquipX(tower1), getEquipY(tower1), getEquipR(tower1)+1.5, "transparent", "green");
    circ2 = createCircle(-1, getEquipX(tower2), getEquipY(tower2), getEquipR(tower2)+1.5, "transparent", "green");
  }

  pathSVGqry = setPathSVGqry(pathEntry, pathOut, pathQry);
  arqSVGqry = fopen(pathSVGqry, "w");
  if(arqSVGqry == NULL)  printf("\nFalha na abertura do arquivo SVG.");
  else  printf("\nArquivo SVG aberto com sucesso!");

  fprintf(arqSVGqry, "<!--Guilherme Arai Fregatto-->\n");
  fprintf(arqSVGqry, "<svg>\n");

  fprintfCitySVG(city, arqSVGqry);
  for(p=getFirst(listCirc); p!=NULL; p=getNext(listCirc, p)){
    circ = getItem(listCirc, p);
    fprintfCircSVG(circ, arqSVGqry);
  }
  if((tower1 != NULL) && (tower2 != NULL)){
    fprintfCircSVG(circ1, arqSVGqry);
    fprintfCircSVG(circ2, arqSVGqry);
    free(getCircleStroke(circ1));
    free(getCircleFill(circ1));
    free(circ1);
    free(getCircleStroke(circ2));
    free(getCircleFill(circ2));
    free(circ2);
  }
  for(p=getFirst(listRect); p!=NULL; p=getNext(listRect, p)){
    rect = getItem(listRect, p);
    fprintfRectSVG(rect, arqSVGqry);
  }
  for(p=getFirst(listOverlap); p!=NULL; p=getNext(listOverlap, p)){
    rect = getItem(listOverlap, p);
    fprintfTextSVG(arqSVGqry, getRectangleX(rect)-0.5, getRectangleY(rect)-0.5, "sobrepõe");
    fprintfDashLineSVG(arqSVGqry, getRectangleX(rect), getRectangleY(rect), "black", getRectangleW(rect), getRectangleY(rect));
    fprintfDashLineSVG(arqSVGqry, getRectangleX(rect), getRectangleY(rect), "black", getRectangleX(rect), getRectangleH(rect));
    fprintfDashLineSVG(arqSVGqry, getRectangleX(rect), getRectangleH(rect), "black", getRectangleW(rect), getRectangleH(rect));
    fprintfDashLineSVG(arqSVGqry, getRectangleW(rect), getRectangleH(rect), "black", getRectangleW(rect), getRectangleY(rect));
  }
  for(p=getFirst(dashRectangles); p!=NULL; p=getNext(dashRectangles, p)){
    rect = getItem(dashRectangles, p);
    fprintfDashLineSVG(arqSVGqry, getRectangleX(rect), getRectangleY(rect), "black", getRectangleW(rect)+getRectangleX(rect), getRectangleY(rect));
    fprintfDashLineSVG(arqSVGqry, getRectangleX(rect), getRectangleY(rect), "black", getRectangleX(rect), getRectangleH(rect)+getRectangleY(rect));
    fprintfDashLineSVG(arqSVGqry, getRectangleX(rect), getRectangleH(rect)+getRectangleY(rect), "black", getRectangleW(rect)+getRectangleX(rect), getRectangleH(rect)+getRectangleY(rect));
    fprintfDashLineSVG(arqSVGqry, getRectangleW(rect)+getRectangleX(rect), getRectangleH(rect)+getRectangleY(rect), "black", getRectangleW(rect)+getRectangleX(rect), getRectangleY(rect)); 
  }
  for(p=getFirst(dashCircles); p!=NULL; p=getNext(dashCircles, p)){
    circ = getItem(dashCircles, p);
    fprintfDashCircSVG(circ, arqSVGqry);
  }
  for(p=getFirst(listPeopleCirc); p!=NULL; p=getNext(listPeopleCirc, p)){ 
    circ = getItem(listPeopleCirc, p);
    fprintfCircSVG(circ, arqSVGqry);
    //O cpf da pessoa está armazenado no campo stroke do círculo
    fprintfTextSVG(arqSVGqry, getCircleX(circ), getCircleY(circ), getCircleStroke(circ));
  }
  for(p=getFirst(listEstabRect); p!=NULL; p=getNext(listEstabRect, p)){
    rect = getItem(listEstabRect, p);
    fprintfRectSVG(rect, arqSVGqry);
  }
  for(p=getFirst(listRip); p!=NULL; p=getNext(listRip, p)){
    circ = getItem(listRip, p);
    fprintf(arqSVGqry, "<polyline points=\"%f,%f %f,%f %f,%f %f,%f %f,%f\" fill=\"%s\" stroke=\"%s\" />\n", 
                      getCircleX(circ),getCircleY(circ)-14.0, getCircleX(circ)-7.0,getCircleY(circ), getCircleX(circ),getCircleY(circ)+14.0, getCircleX(circ)+7.0,getCircleY(circ), getCircleX(circ),getCircleY(circ)-14.0, "red", "black" );
    fprintfLineSVG(arqSVGqry, getCircleX(circ)-3.5, getCircleY(circ)-3.0, "black", getCircleX(circ)+3.5, getCircleY(circ)-3.0);
    fprintfLineSVG(arqSVGqry, getCircleX(circ), getCircleY(circ)-6.0, "black", getCircleX(circ), getCircleY(circ)+6.0);
  }
  for(p=getFirst(listDLRect); p!=NULL; p=getNext(listDLRect, p)){
    rect = getItem(listDLRect, p);
    fprintfStrongDashLineSVG(arqSVGqry, getRectangleX(rect), getRectangleY(rect), getRectangleStroke(rect), getRectangleW(rect), getRectangleH(rect));
  }
  fprintf(arqSVGqry, "</svg>\n");

  printf("\nFechando arquivo SVGqry.");
  free(pathSVGqry);
  fclose(arqSVGqry);
}

void reportRectangle(City city, String pathEntry, String pathOut, float x, float y, float w, float h){
  FILE *arqTXT;
  String pathTXT;
  KDtree blocksK, hydrantsK, semaphoresK, towersK;
  List blocks, hydrants, semaphores, towers;
  void **vetB, **vetH, **vetS, **vetT;
  int i=0, tB, tH, tS, tT;
  Block block;
  Equip equip;
  Posic p;
  float xx, yy, ww, hh, rr;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");
  free(pathTXT);

  blocks = createList();
  blocksK = getBlocks(city);
  rangeSearchRect(blocksK, getBlockX, getBlockY, x, y, w, h, blocks, duplicateBlock);  // Armazena na lista blocks, todos as quadras que tem o ponto âncora dentro da região.
  vetB = vetList(blocks);
  tB = sizeList(blocks);
  for(i=0; i<tB; i++){
    xx = getBlockX(vetB[i]);
    yy = getBlockY(vetB[i]);
    ww = getBlockW(vetB[i]);
    hh = getBlockH(vetB[i]);
    if((xx>=x) && (yy>=y) && (xx+ww<=x+w) && (yy+hh<=y+h))
      printBlockTXT(vetB[i], arqTXT);    
  }
  hydrants = createList();
  hydrantsK = getHydrants(city);
  rangeSearchRect(hydrantsK, getEquipX, getEquipY, x, y, w, h, hydrants, duplicateEquip);
  vetH = vetList(hydrants);
  tH = sizeList(hydrants);
  for(i=0; i<tH; i++){
    xx = getEquipX(vetH[i]);
    yy = getEquipY(vetH[i]);
    rr = getEquipR(vetH[i]);
    if((xx-rr>=x) && (xx+rr<=x+w) && (yy-rr>=y) && (yy+rr<=y+h))
      printEquipTXT(vetH[i], arqTXT);
  }
  semaphores = createList();
  semaphoresK = getSemaphores(city);
  rangeSearchRect(semaphoresK, getEquipX, getEquipY, x, y, w, h, semaphores, duplicateEquip);
  vetS = vetList(semaphores);
  tS = sizeList(semaphores);
  for(i=0; i<tS; i++){
    xx = getEquipX(vetS[i]);
    yy = getEquipY(vetS[i]);
    rr = getEquipR(vetS[i]);
    if((xx-rr>=x) && (xx+rr<=x+w) && (yy-rr>=y) && (yy+rr<=y+h))
      printEquipTXT(vetS[i], arqTXT);
  }
  towers = createList();
  towersK = getTowers(city);
  rangeSearchRect(towersK, getEquipX, getEquipY, x, y, w, h, towers, duplicateEquip);
  vetT = vetList(towers);
  tT = sizeList(towers);
  for(i=0; i<tT; i++){
    xx = getEquipX(vetT[i]);
    yy = getEquipY(vetT[i]);
    rr = getEquipR(vetT[i]);
    if((xx-rr>=x) && (xx+rr<=x+w) && (yy-rr>=y) && (yy+rr<=y+h))
      printEquipTXT(vetT[i], arqTXT);
  }
  printf("\nFechando arquivo TXT.");
  freeL(blocks, freeBlock);
  free(vetB);
  freeL(hydrants, freeEquip);
  free(vetH);
  freeL(semaphores, freeEquip);
  free(vetS);
  freeL(towers, freeEquip);
  free(vetT);  fclose(arqTXT);
}

void reportCircle(City city, String pathEntry, String pathOut, float x, float y, float r){
  FILE *arqTXT;
  String pathTXT;
  KDtree blocksK, hydrantsK, semaphoresK, towersK;
  List blocks, hydrants, semaphores, towers;
  void **vetB, **vetH, **vetS, **vetT;
  int i=0, tB, tH, tS, tT;
  Block block;
  Equip equip;
  Posic p;
  float xx, yy, ww, hh, rr;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");
  free(pathTXT);

  blocks = createList();
  blocksK = getBlocks(city);
  rangeSearchCirc(blocksK, getBlockX, getBlockY, x, y, r, blocks, duplicateBlock);  // Armazena na lista blocks todas as quadras que tiverem o ponto âncora dentro da região.
  vetB = vetList(blocks);
  tB = sizeList(blocks);
  for(i=0; i<tB; i++){   // Verifica se a quadra toda está dentro da região.
    xx = getBlockX(vetB[i]);
    yy = getBlockY(vetB[i]);
    ww = getBlockW(vetB[i]);
    hh = getBlockH(vetB[i]);
    if((dist2points(xx,yy,x,y) <= r) && (dist2points(ww+xx,yy,x,y) <= r) && (dist2points(xx,hh+yy,x,y) <= r) && (dist2points(ww+xx,hh+yy,x,y) <= r))  
      // Printa no arquivo txt se todas vértices da quadra estiverem dentro da região.  
      printBlockTXT(vetB[i], arqTXT);
  }
  hydrants = createList();
  hydrantsK = getHydrants(city);
  rangeSearchCirc(hydrantsK, getEquipX, getEquipY, x, y, r, hydrants, duplicateEquip);
  vetH = vetList(hydrants);
  tH = sizeList(hydrants);
  for(i=0; i<tH; i++){
    xx = getEquipX(vetH[i]);
    yy = getEquipY(vetH[i]);
    rr = getEquipR(vetH[i]);
    if((xx-rr>=x-r) && (xx+rr<=x+r) && (yy-rr>=y-r) && (yy+rr<=y+r))
      printEquipTXT(vetH[i], arqTXT);
  }
  semaphores = createList();
  semaphoresK = getSemaphores(city);
  rangeSearchCirc(semaphoresK, getEquipX, getEquipY, x, y, r, semaphores, duplicateEquip);
  vetS = vetList(semaphores);
  tS = sizeList(semaphores);
  for(i=0; i<tS; i++){
    xx = getEquipX(vetS[i]);
    yy = getEquipY(vetS[i]);
    rr = getEquipR(vetS[i]);
    if((xx-rr>=x-r) && (xx+rr<=x+r) && (yy-rr>=y-r) && (yy+rr<=y+r))
      printEquipTXT(vetS[i], arqTXT);
  }
  towers = createList();
  towersK = getTowers(city);
  rangeSearchCirc(towersK, getEquipX, getEquipY, x, y, r, towers, duplicateEquip);
  vetT = vetList(towers);
  tT = sizeList(towers);
  for(i=0; i<tT; i++){
    xx = getEquipX(vetT[i]);
    yy = getEquipY(vetT[i]);
    rr = getEquipR(vetT[i]);
    if((xx-rr>=x-r) && (xx+rr<=x+r) && (yy-rr>=y-r) && (yy+rr<=y+r))
      printEquipTXT(vetT[i], arqTXT);      
  }
  printf("\nFechando arquivo TXT.");
  freeL(blocks, freeBlock);
  free(vetB);
  freeL(hydrants, freeEquip);
  free(vetH);
  freeL(semaphores, freeEquip);
  free(vetS);
  freeL(towers, freeEquip);
  free(vetT);
  fclose(arqTXT);
}

void removeBlockR(City city, String pathEntry, String pathOut, float x, float y, float w, float h){
  FILE *arqTXT;
  String pathTXT;
  KDtree blocksK;
  List blocks;
   Block block, b;
  Posic p=NULL;
  float xx, yy, ww, hh;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");
  free(pathTXT);

  blocks = createList();
  blocksK = getBlocks(city);
  rangeSearchRect(blocksK, getBlockX, getBlockY, x, y, w, h, blocks, duplicateBlock);
  //for(p=getFirst(blocks); p!=NULL; p=getNext(blocks, p)){  assim não consegue encontrar todos depois da remoção dos primeiros.
  for(p=getLast(blocks); p!=NULL; p=getPrevious(blocks, p)){  
    block = getItem(blocks, p);
    xx = getBlockX(block);
    yy = getBlockY(block);
    ww = getBlockW(block);
    hh = getBlockH(block);
    if((xx>=x) && (xx+ww<=x+w) && (yy>=y) && (yy+hh<=y+h)){
      removeKDT(blocksK, block, equalBlocks, getBlockX, getBlockY, freeBlock, copyBlock); 
      fprintf(arqTXT, "\nQuadra removida -> CEP %s", getBlockCep(block));
    }
  }
  printf("\nFechando arquivo TXT.");
  freeL(blocks, freeBlock);
  fclose(arqTXT);
}

void removeEquipR(City city, String pathEntry, String pathOut, String types, float x, float y, float w, float h){
  FILE *arqTXT;
  String pathTXT;
  KDtree hydrantsK, semaphoresK, towersK;
  List hydrants, semaphores, towers;
  Equip equip;
  Posic p;
  float xx, yy, rr;
  int i=0;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");
  free(pathTXT);

  while(types[i] != '\0'){
    if(types[i] == 'h'){
      hydrants = createList();
      hydrantsK = getHydrants(city);
      rangeSearchRect(hydrantsK, getEquipX, getEquipY, x, y, w, h, hydrants, duplicateEquip);
      //for(p=getFirst(hydrants); p!=NULL; p=getNext(hydrants, p)){
      for(p=getLast(hydrants); p!=NULL; p=getPrevious(hydrants, p)){
        equip = getItem(hydrants, p);
        xx = getEquipX(equip);
        yy = getEquipY(equip);
        rr = getEquipR(equip);
        if((xx-rr>=x) && (xx+rr<=x+w) && (yy-rr>=y) && (yy+rr<=y+h)){
          removeKDT(hydrantsK, equip, equalEquips, getEquipX, getEquipY, freeEquip, copyEquip);
          fprintf(arqTXT, "\nHidrante removido -> ID: %s", getEquipId(equip));
        }
      }
      freeL(hydrants, freeEquip);
    }else if(types[i] == 's'){
      semaphores = createList();
      semaphoresK = getSemaphores(city);
      rangeSearchRect(semaphoresK, getEquipX, getEquipY, x, y, w, h, semaphores, duplicateEquip);
      //for(p=getFirst(semaphores); p!=NULL; p=getNext(semaphores, p)){
      for(p=getLast(semaphores); p!=NULL; p=getPrevious(semaphores, p)){  
        equip = getItem(semaphores, p);
        xx = getEquipX(equip);
        yy = getEquipY(equip);
        rr = getEquipR(equip);
        if((xx-rr>=x) && (xx+rr<=x+w) && (yy-rr>=y) && (yy+rr<=y+h)){
          removeKDT(semaphoresK, equip, equalEquips, getEquipX, getEquipY, freeEquip, copyEquip);
          fprintf(arqTXT, "\nSemaforo removido -> ID: %s", getEquipId(equip));
        }
      }
    freeL(semaphores, freeEquip);
    }else if(types[i] == 't'){
      towers = createList();
      towersK = getTowers(city);
      rangeSearchRect(towersK, getEquipX, getEquipY, x, y, w, h, towers, duplicateEquip);
      //for(p=getFirst(towers); p!=NULL; p=getNext(towers, p)){
      for(p=getLast(towers); p!=NULL; p=getPrevious(towers, p)){  
        equip = getItem(towers, p);
        xx = getEquipX(equip);
        yy = getEquipY(equip);
        rr = getEquipR(equip);
        if((xx-rr>=x) && (xx+rr<=x+w) && (yy-rr>=y) && (yy+rr<=y+h)){
          removeKDT(towersK, equip, equalEquips, getEquipX, getEquipY, freeEquip, copyEquip);
          fprintf(arqTXT, "\nTorre removida -> ID: %s", getEquipId(equip));
        }
      }
      freeL(towers, freeEquip);
    }
    i++;  
  }

  printf("\nFechando arquivo TXT.");
  fclose(arqTXT);
}

void removeBlockC(City city, String pathEntry, String pathOut, float x, float y, float r){
  FILE *arqTXT;
  String pathTXT;
  KDtree blocksK;
  List blocks;
  Block block;
  Posic p;
  float xx, yy, ww, hh;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");
  free(pathTXT);

  blocks = createList();
  blocksK = getBlocks(city);
  rangeSearchCirc(blocksK, getBlockX, getBlockY, x, y, r, blocks, duplicateBlock);
  for(p=getLast(blocks); p!=NULL; p=getPrevious(blocks, p)){
    block = getItem(blocks, p);
    xx = getBlockX(block);
    yy = getBlockY(block);
    ww = getBlockW(block);
    hh = getBlockH(block);
    if((dist2points(xx,yy,x,y) <= r) && (dist2points(ww+xx,yy,x,y) <= r) && (dist2points(xx,hh+yy,x,y) <= r) && (dist2points(ww+xx,hh+yy,x,y) <= r)){
      removeKDT(blocksK, block, equalBlocks, getBlockX, getBlockY, freeBlock, copyBlock);
      fprintf(arqTXT, "Quadra removida -> CEP: %s\n", getBlockCep(block));
    }
  }
  freeL(blocks, freeBlock); 
  printf("\nFechando arquivo TXT");
  fclose(arqTXT);
}

void removeEquipC(void *city, char *pathEntry, char *pathOut, char *types, float x, float y, float r){
  FILE *arqTXT;
  String pathTXT;
  KDtree hydrantsK, semaphoresK, towersK;
  List hydrants, semaphores, towers;
  Equip equip;
  Posic p;
  float xx, yy, rr;
  int i=0;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");
  free(pathTXT);

  while(types[i] != '\0'){

    if(types[i] == 'h'){
      hydrants = createList();
      hydrantsK = getHydrants(city);
      rangeSearchCirc(hydrantsK, getEquipX, getEquipY, x, y, r, hydrants, duplicateEquip);
      for(p=getLast(hydrants); p!=NULL; p=getPrevious(hydrants, p)){
        equip = getItem(hydrants, p);
        xx = getEquipX(equip);
        yy = getEquipY(equip);
        rr = getEquipR(equip);
        if((xx-rr>=x-r) && (xx+rr<=x+r) && (yy-rr>=y-r) && (yy+rr<=y+r)){
          removeKDT(hydrantsK, equip, equalEquips, getEquipX, getEquipY, freeEquip, copyEquip);
          fprintf(arqTXT, "Hidrante removido -> ID: %s\n", getEquipId(equip));
        }
      }
      freeL(hydrants, freeEquip);
    }else if(types[i] == 's'){
      semaphores = createList();
      semaphoresK = getSemaphores(city);
      rangeSearchCirc(semaphoresK, getEquipX, getEquipY, x, y, r, semaphores, duplicateEquip);
      for(p=getLast(semaphores); p!=NULL; p=getPrevious(semaphores, p)){
        equip = getItem(semaphores, p);
        xx = getEquipX(equip);
        yy = getEquipY(equip);
        rr = getEquipR(equip);
        if((xx-rr>=x-r) && (xx+rr<=x+r) && (yy-rr>=y-r) && (yy+rr<=y+r)){
          removeKDT(semaphoresK, equip, equalEquips, getEquipX, getEquipY, freeEquip, copyEquip);
          fprintf(arqTXT, "Semaforo removido -> ID: %s\n", getEquipId(equip));
        }
      }
      freeL(semaphores, freeEquip);
    }else if(types[i] == 't'){
      towers = createList();
      towersK = getTowers(city);
      rangeSearchCirc(towersK, getEquipX, getEquipY, x, y, r, towers, duplicateEquip);
      for(p=getLast(towers); p!=NULL; p=getPrevious(towers, p)){
        equip = getItem(towers, p);
        xx = getEquipX(equip);
        yy = getEquipY(equip);
        rr = getEquipR(equip);
        if((xx-rr>=x-r) && (xx+rr<=x+r) && (yy-rr>=y-r) && (yy+rr<=y+r)){
          removeKDT(towersK, equip, equalEquips, getEquipX, getEquipY, freeEquip, copyEquip);
          fprintf(arqTXT, "Torre removida -> ID: %s\n", getEquipId(equip));
        }
      }
      freeL(towers, freeEquip);
    }
      
    i++;
  }
  printf("\nFechando arquivo TXT");
  fclose(arqTXT);  
}

void changeColor(City city, String cepid, String stroke, String fill){
  List blocks, hydrants, semaphores, towers;
  Block block;
  Equip equip;
 
  blocks = getBlocks(city);
  changeColorsKDT(blocks, getBlockCep, cepid, changeBlockColors, stroke, fill);

  hydrants = getHydrants(city);
  changeColorsKDT(hydrants, getEquipId, cepid, changeEquipColors, stroke, fill);
  
  semaphores = getSemaphores(city);
  changeColorsKDT(semaphores, getEquipId, cepid, changeEquipColors, stroke, fill);

  towers = getTowers(city);
  changeColorsKDT(towers, getEquipId, cepid, changeEquipColors, stroke, fill);
}

void searchCepId(City city, String pathEntry, String pathOut, String cepid){
  FILE *arqTXT;
  String pathTXT;
  KDtree blocks, hydrants, semaphores, towers;
  Block block;
  Equip equip;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");
  free(pathTXT);

  blocks = getBlocks(city);
  reportCepIdKDT(blocks, getBlockCep, cepid, printBlockTXT, arqTXT);

  hydrants = getHydrants(city);
  reportCepIdKDT(hydrants, getEquipId, cepid, printEquipTXT, arqTXT);

  semaphores = getSemaphores(city);
  reportCepIdKDT(semaphores, getEquipId, cepid, printEquipTXT, arqTXT);

  towers = getTowers(city);
  reportCepIdKDT(towers, getEquipId, cepid, printEquipTXT, arqTXT);

  printf("\nFechando arquivo TXT.");
  fclose(arqTXT);
}

/** Função privada -> calcula a distância entre dois pontos. */
float dist(void *p1, void *p2, sortKey get_X, sortKey get_Y){
  return sqrt( (get_X(p1)-get_X(p2)) * (get_X(p1)-get_X(p2)) +
                (get_Y(p1)-get_Y(p2)) * (get_Y(p1)-get_Y(p2)) );
}

/** Função privada. -> retorna menor distância do vetor p (ordenados em função de x). */
float bruteForce(void **P, int n, sortKey get_X, sortKey get_Y, Equip *tower1, Equip *tower2){
  float min = FLT_MAX;
  for(int i=0; i<n ; ++i)
    for(int j=i+1; j<n; ++j)
      if (dist(P[i], P[j], get_X, get_Y) < min){
        min = dist(P[i], P[j], get_X, get_Y);
        *tower1 = P[i];
        *tower2 = P[j];
      }

  return min;
}

/** Função privada -> retorna a menor valor entre dois floats. */
float smallestD(float x, float y){
  return(x < y) ? x : y;
}

/** Função privada -> retorna menor distância do vetor strip (pontos localizados na fronteira). */
float stripClosest(void **strip, int size, float d, sortKey get_X, sortKey get_Y, Equip *tower1, Equip *tower2){
  float min = d;
  int i=0, j=0;
  mergeSort(strip, 0, size-1, get_Y);

  for(i=0; i<size; ++i)
    for(j=i+1; j<size && (get_Y(strip[j]) - get_Y(strip[i]))<min; ++j)
      if(dist(strip[i], strip[j], get_X, get_Y) < min){
        min = dist(strip[i], strip[j], get_X, get_Y);
        *tower1 = strip[i];
        *tower2 = strip[j];
      }
  return min;
}

/** Função privada -> procura e retorna a menor distância entre dois pontos. */
float closestUtil(void **Px, int n, sortKey get_X, sortKey get_Y, Equip *tower1, Equip *tower2){

  if(n<=3)
    return bruteForce(Px, n, get_X, get_Y, tower1, tower2);

  int mid=n/2, i=0, j=0;
  Equip midPoint = Px[mid]; /** Define o ponto central. */
  float dl, dr, d;
  void *strip[n];

  /** Calcula a menor distância dos pontos de cada um dos lados. */
  dl = closestUtil(Px, mid, get_X, get_Y, tower1, tower2);
  dr = closestUtil(Px+mid, n-mid, get_X, get_Y, tower1, tower2);
  /** Pega a menor distância entre as duas calculados, do lado esquerdo ou do lado direito do ponto central. */
  d = smallestD(dl, dr);
  /** Contrução do vetor strip, que contem os pontos com distâncias menores que d, ignorando agora os lados definidos pelo ponto central. */
  j=0;
  for(i=0; i<n; i++){
    if(abs(get_X(Px[i]) - get_X(midPoint))<d){
      strip[j] = Px[i];
      j++;
    }
  }
  return smallestD(d, stripClosest(strip, j, d, get_X, get_Y, tower1, tower2));
}

void closestTowers(City city, String pathEntry, String pathOut, Equip *tower1, Equip *tower2){
  FILE *arqTXT;
  String pathTXT;
  KDtree towers;
  void **vetorX;
  int k = 0;
  float d;

  towers = getTowers(city);
  vetorX = vetKDT(towers, freeEquip);
  mergeSort(vetorX, 0, sizeKDT(towers)-1, getEquipX);
  k = (sizeKDT(towers)*sizeof(vetorX))/sizeof(vetorX[0]);
  d = closestUtil(vetorX, k, getEquipX, getEquipY, tower1, tower2);
  //printf("\n@@@@@@@@@@@----------> MENOR DISTANCIA: %f", d);
  free(vetorX);

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");
  
  fprintf(arqTXT, "Torres mais próximas -> Torre1_ID:%s  Torre2_ID:%s  Distância:%.3f\n", getEquipId(*tower1), getEquipId(*tower2), d);

  free(pathTXT);
  printf("\nFechando arquivo TXT.");
  fclose(arqTXT);
}

void reportResidentByCep(HashTable hash, HashTable hashh, String cepid, String pathEntry, String pathOut){
  FILE *arqTXT;
  String pathTXT;
  People people;
  Resident resid;
  List list;
  Posic p;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");

  list = getHashList(hash, cepid, getResidentCep);
  if(list != NULL){
    for(p=getFirst(list); p!=NULL; p=getNext(list, p)){
      resid = getItem(list, p);
      people = getHashCollision(hashh, getResidentCpf(resid), getPeopleCpf);
      if(people == NULL)
        continue;
      fprintf(arqTXT, "Morador:%s_%s Quadra:%s Face:%c Numero:%d Complemento:%s\n", getPeopleName(people), getPeopleLastname(people), getResidentCep(resid), getResidentFace(resid), getResidentNum(resid), getResidentCompl(resid));
    }
  }else{
    printf("\nERRO comando m? -> cep da quadra não existe.");
    fprintf(arqTXT, "ERRO comando m? -> cep da quadra nao existe.\n");
  }

  free(pathTXT);
  printf("\nFechando arquivo TXT.");
  fclose(arqTXT);
}

void reportResidentRect(City city, HashTable hash, HashTable hashh, String pathEntry, String pathOut, float x, float y, float w, float h){
  FILE *arqTXT;
  String pathTXT;
  List blocks, list;
  KDtree blocksK;
  Resident resid;
  People people;
  Block block;
  Posic p;
  float xx, yy, ww, hh;
  int c=0, cc=0;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");

  blocks = createList();
  blocksK = getBlocks(city);
  rangeSearchRect(blocksK, getBlockX, getBlockY, x, y, w, h, blocks, duplicateBlock);
  for(p=getFirst(blocks); p!=NULL; p=getNext(blocks, p)){ 
  //for(p=getLast(blocks); p!=NULL; p=getPrevious(blocks, p)){  
    block = getItem(blocks, p);
    xx = getBlockX(block);
    yy = getBlockY(block);
    ww = getBlockW(block);
    hh = getBlockH(block);
    if((xx>=x) && (xx+ww<=x+w) && (yy>=y) && (yy+hh<=y+h)){
      c++;
      resid = getHashCollision(hash, getBlockCep(block), getResidentCep);
      if(resid != NULL){
        cc++;
        people = getHashCollision(hashh, getResidentCpf(resid), getPeopleCpf);
        if(people != NULL)  
          printf("\nMorador:%s_%s Quadra:%s Face:%c Numero:%d Complemento:%s\n", getPeopleName(people), getPeopleLastname(people), getResidentCep(resid), getResidentFace(resid), getResidentNum(resid), getResidentCompl(resid));
        //fprintf(arqTXT, "Morador:%s_%s Quadra:%s Face:%c Numero:%d Complemento:%s\n", getPeopleName(people), getPeopleLastname(people), getResidentCep(resid), getResidentFace(resid), getResidentNum(resid), getResidentCompl(resid));
      }
    }
  }
  if(c==0){
    printf("\nERRO comando mr? -> não existem quadras na região.");
    fprintf(arqTXT, "ERRO comando mr? -> nao existem quadras na região.\n");
  }else if(c!=0 && cc==0){
    printf("\nERRO comando mr? -> não existem moradores nas quadras que estão totalmente dentro da região.");
    fprintf(arqTXT, "ERRO comando mr? -> nao existem moradores nas quadras que estão totalmente dentro da região.\n");
  }
  freeL(blocks, freeBlock);
  free(pathTXT);
  printf("\nFechando arquivo TXT.");
  fclose(arqTXT);  
}

void reportResidentByCpf(HashTable hash, HashTable hashh, HashTable hashhh, String cpf, String pathEntry, String pathOut, String pathQry, List listPeopleCirc){
  FILE *arqTXT;
  String pathTXT;
  People people;
  Resident resid;
  Block block;
  List list, blocks;
  Posic p, pp;
  Circle circ;
  float xm=0, ym=0;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");


  list = getHashList(hash, cpf, getResidentCpf);
  if(list != NULL){
    for(p=getFirst(list); p!=NULL; p=getNext(list, p)){
      resid = getItem(list, p);
      people = getHashCollision(hashh, getResidentCpf(resid), getPeopleCpf);
      if(people == NULL || resid == NULL)
        continue;
      if(strcmp(getPeopleName(people), "rip")==0 || strcmp(getResidentCompl(resid), "rip")==0 )
        continue;
      fprintf(arqTXT, "Morador:%s_%s Quadra:%s Face:%c Numero:%d Complemento:%s\n", getPeopleName(people), getPeopleLastname(people), getResidentCep(resid), getResidentFace(resid), getResidentNum(resid), getResidentCompl(resid));
      blocks = getHashList(hashhh, getResidentCep(resid), getBlockCep);
      if(blocks != NULL){
        for(pp=getFirst(blocks); pp!=NULL; pp=getNext(blocks, pp)){
          block = getItem(blocks, pp);
          if(block!=NULL){
            if(strcmp(getBlockCep(block), getResidentCep(resid))==0){
              if(getResidentFace(resid) == 'N'){
                xm =  getBlockX(block) + getResidentNum(resid);
                ym = getBlockY(block) + getBlockH(block);
              }else if(getResidentFace(resid) == 'S'){
                xm = getBlockX(block) + getResidentNum(resid);
                ym = getBlockY(block);
              }else if(getResidentFace(resid) == 'L'){
                xm = getBlockX(block);
                ym = getBlockY(block) + getResidentNum(resid);
              }else if(getResidentFace(resid) == 'O'){
                xm = getBlockX(block) + getBlockW(block);
                ym = getBlockY(block) + getResidentNum(resid);
              }
            }
          }
        }
      }
    }
    if(xm==0 && ym==0){
      printf("\nA seguinte pessoa não possui uma casa, por isso não será representada no arquivo SVG.");
    }else{  
      circ = createCircle(-1, xm, ym, 4.5, "yellow", getResidentCpf(resid));
      insertList(listPeopleCirc, circ);
    }
  }else{
    printf("\nERRO comando dm? -> não existe morador com cpf de entrada.");
    fprintf(arqTXT, "ERRO comando dm? -> nao existe morador com cpf de entrada.\n");
  }

  free(pathTXT);
  printf("\nFechando arquivo TXT.");
  fclose(arqTXT);
}

void reportEstabByCnpj(HashTable hash, HashTable hashh, HashTable hashhh, String cnpj, String pathEntry, String pathOut, String pathQry, List listEstabRect){
  FILE *arqTXT;
  String pathTXT;
  Establishment estab;
  Description descript;
  Block block;
  List list, blocks;
  Posic p, pp;
  Rectangle rect;
  float xe=0, ye=0;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");

  list = getHashList(hash, cnpj, getEstabCnpj);
  if(list != NULL){
    for(p=getFirst(list); p!=NULL; p=getNext(list, p)){
      estab = getItem(list, p);
      descript = getHashCollision(hashh, getEstabCodt(estab), getDescriptCodt);
      if(estab == NULL || descript == NULL)
        continue;
      fprintf(arqTXT, "Nome:%s Codt:%s Descricao:%s Cep:%s Face:%c Num:%d Cnpj:%s\n", getEstabName(estab), getDescriptCodt(descript), getDescriptD(descript), getEstabCep(estab), getEstabFace(estab), getEstabNum(estab), getEstabCnpj(estab));
      blocks = getHashList(hashhh, getEstabCep(estab), getBlockCep);
      if(blocks!=NULL){
        for(pp=getFirst(blocks); pp!=NULL; pp=getNext(blocks, pp)){
          block = getItem(blocks, pp);
          if(block!=NULL){
            if(getEstabFace(estab) == 'N'){
              xe = getBlockX(block) + getEstabNum(estab);
              ye = getBlockY(block) + getBlockH(block) - 7.0;
            }else if(getEstabFace(estab) == 'S'){
              xe = getBlockX(block) + getEstabNum(estab);
              ye = getBlockY(block);
            }else if(getEstabFace(estab) == 'L'){
              xe = getBlockX(block);
              ye = getBlockY(block) + getEstabNum(estab);
            }else if(getEstabFace(estab) == 'O'){
              xe = getBlockX(block) + getBlockW(block) - 10.0;
              ye = getBlockY(block) + getEstabNum(estab);
            }
            rect = createRectangle(-1, xe, ye, 7.0, 10.0, "green", "black");
            insertList(listEstabRect, rect);
          }
        }
      }
    }
  }else{
    printf("\nERRO comando de? -> não existe estabelecimento com cnpj de entrada.");
    fprintf(arqTXT, "ERRO comando de? -> nao existe estabelecimento com cnpj de entrada.\n");
  }

  free(pathTXT);
  printf("\nFechando arquivo TXT.");
  fclose(arqTXT);
}

void rip(HashTable hash, HashTable hashh, HashTable hashhh, String cpf, String pathEntry, String pathOut, String pathQry, List listRip){
  FILE *arqTXT;
  String pathTXT;
  Resident resid;
  People people;
  Block block;
  Circle circ;
  Posic p, pp;
  List list, blocks;
  float xm=0, ym=0;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");

  list = getHashList(hash, cpf, getResidentCpf);
  if(list != NULL){
    for(p=getFirst(list); p!=NULL; p=getNext(list, p)){
      resid = getItem(list, p);
      people = getHashCollision(hashh, getResidentCpf(resid), getPeopleCpf);
      if(people == NULL || resid == NULL)
        continue;
      fprintf(arqTXT, "RIP Morador:%s_%s CPF:%s Sexo:%c Nasc:%s Quadra:%s Face:%c Numero:%d Complemento:%s\n", getPeopleName(people), getPeopleLastname(people), getPeopleCpf(people), getPeopleGender(people), getPeopleBirth(people), getResidentCep(resid), getResidentFace(resid), getResidentNum(resid), getResidentCompl(resid));
      blocks = getHashList(hashhh, getResidentCep(resid), getBlockCep);
      if(blocks != NULL){
        for(pp=getFirst(blocks); pp!=NULL; pp=getNext(blocks, pp)){
          block = getItem(blocks, pp);
          if(block != NULL){
            if(strcmp(getBlockCep(block), getResidentCep(resid))==0){
              if(getResidentFace(resid) == 'N'){
                xm =  getBlockX(block) + getResidentNum(resid);
                ym = getBlockY(block) + getBlockH(block);
              }else if(getResidentFace(resid) == 'S'){
                xm = getBlockX(block) + getResidentNum(resid);
                ym = getBlockY(block);
              }else if(getResidentFace(resid) == 'L'){
                xm = getBlockX(block);
                ym = getBlockY(block) + getResidentNum(resid);
              }else if(getResidentFace(resid) == 'O'){
                xm = getBlockX(block) + getBlockW(block);
                ym = getBlockY(block) + getResidentNum(resid);
              }
              setResidentCompl(resid, "rip");
              setPeopleName(people, "rip");
            }
            circ = createCircle(-1, xm, ym, 4.5, "blue", "black");
            insertList(listRip, circ);
          }
        }
      }
    }
  }else{
    printf("\nERRO comando rip -> não existe morador com cpf de entrada.");
    fprintf(arqTXT, "ERRO comando rip -> nao existe morador com cpf de entrada.\n");
  }

  free(pathTXT);
  printf("\nFechando arquivo TXT.");
  fclose(arqTXT);  
}

void reportEstabByCep(HashTable hash, String cep, String pathEntry, String pathOut){
  FILE *arqTXT;
  String pathTXT;
  List list;
  Establishment estab;
  Posic p;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");

  list = getHashList(hash, cep, getEstabCep);
  if(list != NULL){
    for(p=getFirst(list); p!=NULL; p=getNext(list, p)){
      estab = getItem(list, p);
      if(estab == NULL)
        continue;
      fprintf(arqTXT, "Cnpj:%s Nome:%s Tipo:%s Cep:%s Face:%c Num:%d\n", getEstabCnpj(estab), getEstabName(estab), getEstabCodt(estab), getEstabCep(estab), getEstabFace(estab), getEstabNum(estab));
    }
  }else{
    printf("\nERRO comando ecq? -> nao existe estabelecimento na quadra de entrada.");
    fprintf(arqTXT, "ERRO comando ecq? -> nao existe estabelecimento na quadra de entrada.\n");
  }

  free(pathTXT);
  printf("\nFechando arquivo TXT.");
  fclose(arqTXT);  
}

void reportCodtRect(City city, HashTable hash, HashTable hashh, String codt, float x, float y, float w, float h, String pathEntry, String pathOut){
  FILE *arqTXT;
  String pathTXT;
  List blocks, estabs;
  KDtree blocksK;
  Establishment estab=NULL;
  Posic p, pp;
  Block block;
  Description descript=NULL;  
  float xx=0, ww=0, yy=0, hh=0;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");

  blocks = createList();
  blocksK = getBlocks(city);
  rangeSearchRect(blocksK, getBlockX, getBlockY, x, y, w, h, blocks, duplicateBlock);
  for(p=getFirst(blocks); p!=NULL; p=getNext(blocks, p)){
    block = getItem(blocks, p);
    xx = getBlockX(block);
    yy = getBlockY(block);
    ww = getBlockW(block);
    hh = getBlockH(block);
    if((xx>=x) && (xx+ww<=x+w) && (yy>=y) && (yy+hh<=y+h)){
      estab = getHashList(hash, getBlockCep(block), getEstabCep);
      //for(pp=getFirst(estabs); pp!=NULL; pp=getNext(estabs, pp)){
        //estab = getItem(estabs, pp);
        if(estab == NULL)
          continue;
        if(strcmp(getEstabCodt(estab), codt)==0)
          descript = getHashCollision(hashh, getEstabCodt(estab), getDescriptCodt);
        if(descript == NULL){
          printf("\nERROR comando ecr? -> nao existem estabelecimentos do tipo codt na região de entrada.");      
          fprintf(arqTXT, "ERROR comando ecr? -> nao existem estabelecimentos do tipo codt na região de entrada.\n");          
        }else if(estab != NULL && descript != NULL){
          fprintf(arqTXT, "Nome:%s Codt:%s Descricao:%s Cep:%s Face:%c Num:%d Cnpj:%s\n", getEstabName(estab), getDescriptCodt(descript), getDescriptD(descript), getEstabCep(estab), getEstabFace(estab), getEstabNum(estab), getEstabCnpj(estab));
        }
    }
  }

  freeL(blocks, freeBlock);
  free(pathTXT);
  printf("\nFechando arquivo TXT.");
  fclose(arqTXT);  
}

void reportEstabBlock(HashTable hash, HashTable hashh, String cepid, String pathEntry, String pathOut){
  FILE *arqTXT;
  String pathTXT;
  Block block;
  Establishment estab;
  Description descript;
  Posic p;
  List blocks;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");

  blocks = getHashList(hash, cepid, getBlockCep);
  if(blocks != NULL){
    for(p=getFirst(blocks); p!=NULL; p=getNext(blocks, p)){
      block = getItem(blocks, p);
      estab = getHashCollision(hashh, getBlockCep(block), getEstabCep);
      if(block != NULL && estab != NULL){
        fprintf(arqTXT, "Tipo estabelecimento:%s Nome:%s\n", getEstabCodt(estab), getEstabName(estab));
      }else{
        printf("\nERRO comando tecq? -> nao existe estabelecimento na quadra de entrada.");
        fprintf(arqTXT, "ERRO comando tecq? -> não existe estabelecimento na quadra de entrada.\n");
      } 
    }
  }else{
    printf("\nERRO comando tecq? -> nao existe quadra com o cep de entrada.");
    fprintf(arqTXT, "ERRO comando tecq? -> nao existe quadra com o cep de entrada.\n");
  }

  free(pathTXT);
  printf("\nFechando arquivo TXT.");
  fclose(arqTXT);  
}

void reportEstabTypeRect(City city, HashTable hash, HashTable hashh, HashTable hashhh, float x, float y, float w, float h, String pathEntry, String pathOut){
  FILE *arqTXT;
  String pathTXT;
  Block block;
  List blocks, estabs;
  KDtree blocksK;
  Establishment estab;
  Description descript;
  Posic p, pp;
  float xx=0, yy=0, ww=0, hh=0;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");
  
  blocks = createList();
  blocksK = getBlocks(city);
  rangeSearchRect(blocksK, getBlockX, getBlockY, x, y, w, h, blocks, duplicateBlock);
  for(p=getFirst(blocks); p!=NULL; p=getNext(blocks, p)){
    block = getItem(blocks, p);
    xx = getBlockX(block);
    yy = getBlockY(block);
    ww = getBlockW(block);
    hh = getBlockH(block);
    if((xx>=x) && (xx+ww<=x+w) && (yy>=y) && (yy+hh<=y+h)){
      estabs = getHashList(hashh, getBlockCep(block), getEstabCep);
      if(estabs != NULL){
        for(pp=getFirst(estabs); pp!=NULL; pp=getNext(estabs, pp)){
          estab = getItem(estabs, pp);
          descript = getHashCollision(hashhh, getEstabCodt(estab), getDescriptCodt);
          if(descript != NULL && estab != NULL){
            fprintf(arqTXT, "Tipo do estabelecimento:%s Descricao:%s\n", getDescriptCodt(descript), getDescriptD(descript));
          }else{
            printf("\nERRO comando tecr? -> nao existe estabelecimento nas quadras dentro da região.");
            fprintf(arqTXT, "ERRO comando tecr? -> nao existe estabelecimento nas quadras dentro da região.\n");
          }
        }
      }else{
        printf("\nERRO comando tecr? -> nao existe estabelecimento na quadra de entrada.");
        fprintf(arqTXT, "ERRO comando tecr? -> nao existe estabelecimento na quadra de entrada.\n");
      }
    }
  }  
  freeL(blocks, freeBlock);
  free(pathTXT);
  printf("\nFechando arquivo TXT.");
  fclose(arqTXT);  
}

void closestHydrant(City city, HashTable hash, String cepid, char face, int num, String pathEntry, String pathOut, List listDLRect){
  FILE *arqTXT;
  String pathTXT;
  List blocks;
  Posic p;
  Block block;
  Rectangle rect, rect2, rect3;
  Equip nearestHydrant, qryHydrant;
  float x, y, d;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");

  blocks = getHashList(hash, cepid, getBlockCep);
  if(blocks != NULL){
    for(p=getFirst(blocks); p!=NULL; p=getNext(blocks, p)){
      block = getItem(blocks, p);
      if(block != NULL){
        if(strcmp(getBlockCep(block), cepid)==0){
          if(face == 'N'){
            x = getBlockX(block) + num;
            y = getBlockY(block) + getBlockH(block);
          }else if(face == 'S'){
            x = getBlockX(block) + num;
            y = getBlockY(block);
          }else if(face == 'L'){
            x = getBlockX(block);
            y = getBlockY(block) + num;
          }else if(face == 'O'){
            x = getBlockX(block) + getBlockW(block);
            y = getBlockY(block) + num;
          }
        }
        rect = createRectangle(-1, x-8, y-8, y+8, x+8, "red", "red"); // uma linha do x
        insertList(listDLRect, rect);
        rect2 = createRectangle(-1, x-8, y+8, y-8, x+8, "red", "red"); // outra linha do x
        insertList(listDLRect, rect2);
        nearestHydrant = createEquip('h', "none", 0, 0, 0, "none", "none");
        qryHydrant = createEquip('h', "none", x, y, 0, "none", "none");
        nearestNeighbor(getHydrants(city), qryHydrant, getEquipX, getEquipY, equalEquips, copyEquip, nearestHydrant);
        if(nearestHydrant != NULL){
          printEquip(nearestHydrant);
          fprintf(arqTXT, "Hidrante mais proximo - ");
          printEquipTXT(nearestHydrant, arqTXT);
          d = dist2points(x, y, getEquipX(nearestHydrant), getEquipY(nearestHydrant));
          fprintf(arqTXT, "Distancia: %f\n", d);
          rect3 = createRectangle(-1, x, y, getEquipY(nearestHydrant), getEquipX(nearestHydrant), "red", "red");
          insertList(listDLRect, rect3);
          freeEquip(nearestHydrant);
        } 
        freeEquip(qryHydrant);
      }
    }
  }else{
    printf("\nERRO comando hmpe? -> não existe quadra com o cep de entrada.");
    fprintf(arqTXT, "ERRO comando hmpe? -> nao existe quadra com o cep de entrada.\n");
  }

  free(pathTXT);
  printf("\nFechando arquivo TXT.");
  fclose(arqTXT);
}

void closestHydrants(City city, HashTable hash, String id, String pathEntry, String pathOut, List listDLRect){
  FILE *arqTXT;
  String pathTXT; 
  Equip hydrant, nearestHydrant;
  KDtree hydrantsK;
  Rectangle rect;
  float d = 0;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");

  hydrantsK = getHydrants(city);
  hydrant = getHashCollision(hash, id, getEquipId);
  if(hydrant != NULL){
    nearestHydrant = createEquip('h', "none", 0, 0, 0, "none", "none");
    nearestNeighbor(hydrantsK, hydrant, getEquipX, getEquipY, equalEquips, copyEquip, nearestHydrant);
    if(nearestHydrant != NULL){
      fprintf(arqTXT, "Hidrante de entrada - ");
      printEquipTXT(hydrant, arqTXT);
      fprintf(arqTXT, "Hidrante mais proximo - ");
      printEquipTXT(nearestHydrant, arqTXT);
      d = dist2points(getEquipX(hydrant), getEquipY(hydrant), getEquipX(nearestHydrant), getEquipY(nearestHydrant));
      fprintf(arqTXT, "Distancia: %f\n", d);
      rect = createRectangle(-1, getEquipX(hydrant), getEquipY(hydrant), getEquipY(nearestHydrant), getEquipX(nearestHydrant), "red", "red");
      insertList(listDLRect, rect);
      freeEquip(nearestHydrant);
    } 
  }else{
    printf("\nERRO comando hmp? -> não existe hidrante com a id de entrada.");
    fprintf(arqTXT, "ERRO comando hmp? nao existe hidrante com a id de entrada.\n");
  }

  free(pathTXT);
  printf("\nFechando arquivo TXT.");
  fclose(arqTXT);  
}

void closeEstab(HashTable hash, HashTable hashh, String cnpj, String pathEntry, String pathOut, List listEstabRect){
  FILE *arqTXT;
  String pathTXT;
  Establishment estab;
  List estabs, blocks;
  Posic p, pp;
  Rectangle rect;
  Block block;
  float xe=0, ye=0;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");

  estabs = getHashList(hash, cnpj, getEstabCnpj);
  if(estabs != NULL){
    for(p=getFirst(estabs); p!=NULL; p=getNext(estabs, p)){
      estab = getItem(estabs, p);
      if(estab == NULL) continue;
      fprintf(arqTXT, "ESTABELECIMENTO FECHADO - Cnpj:%s Nome:%s Tipo:%s Cep:%s Face:%c Num:%d\n", getEstabCnpj(estab), getEstabName(estab), getEstabCodt(estab), getEstabCep(estab), getEstabFace(estab), getEstabNum(estab));
      blocks = getHashList(hashh, getEstabCep(estab), getBlockCep);
      if(blocks!=NULL)
        for(pp=getFirst(blocks); pp!=NULL; pp=getNext(blocks, pp)){
          block = getItem(blocks, pp);
          if(getEstabFace(estab) == 'N'){
            xe = getBlockX(block) + getEstabNum(estab);
            ye = getBlockY(block) + getBlockH(block) - 7.0;
          }else if(getEstabFace(estab) == 'S'){
            xe = getBlockX(block) + getEstabNum(estab);
            ye = getBlockY(block);
          }else if(getEstabFace(estab) == 'L'){
            xe = getBlockX(block);
            ye = getBlockY(block) + getEstabNum(estab);
          }else if(getEstabFace(estab) == 'O'){
            xe = getBlockX(block) + getBlockW(block) - 10.0;
            ye = getBlockY(block) + getEstabNum(estab);
          }
          rect = createRectangle(-1, xe, ye, 7.0, 10.0, getBlockFill(block), getBlockFill(block));
          insertList(listEstabRect, rect);
        }
    }
  }else{
    printf("\nERRO comando fec -> não existe estabelecimento com o cnpj de entrada.");
    fprintf(arqTXT, "ERRO comando fec -> nao existe estabelecimento com o cnpj de entrada.\n");
  }

  free(pathTXT);
  printf("\nFechando arquivo TXT.");
  fclose(arqTXT);    
}

void mud(City city, HashTable hash, HashTable hashh, HashTable hashhh, String cpf, String cepid, char face, int num, String compl, String pathEntry, String pathOut, List listP, List listDLRect){
  FILE *arqTXT;
  String pathTXT;
  People people;
  Resident resid;
  Block block;
  Rectangle rect;
  List blocks;
  Posic p;
  float xa=0, ya=0, xd=0, yd=0;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");
  
  people = getHashCollision(hash, cpf, getPeopleCpf);
  if(people != NULL){
    resid = getHashCollision(hashhh, getPeopleCpf(people), getResidentCpf);
    if(resid != NULL){
      blocks = getHashList(hashh, getResidentCep(resid), getBlockCep);
      if(blocks != NULL){
        for(p=getFirst(blocks); p!= NULL; p=getNext(blocks, p)){
          block = getItem(blocks, p);
          if(block != NULL){
            if(strcmp(getResidentCep(resid), getBlockCep(block))==0){
              if(getResidentFace(resid) == 'N'){
                xa = getBlockX(block) + getResidentNum(resid);
                ya = getBlockY(block) + getBlockH(block);
              }else if(getResidentFace(resid) == 'S'){
                xa = getBlockX(block) + getResidentNum(resid);
                ya = getBlockY(block);
              }else if(getResidentFace(resid) == 'L'){
                xa = getBlockX(block);
                ya = getBlockY(block) + getResidentNum(resid);
              }else if(getResidentFace(resid) == 'O'){
                xa = getBlockX(block) + getBlockW(block);
                ya = getBlockY(block) + getResidentNum(resid);
              }
              fprintf(arqTXT, "Nome:%s_%s CPF:%s Sexo:%c Nascimento:%s\nEndereco antigo - CEP:%s Face:%c Num:%d Complemento:%s\n", getPeopleName(people), getPeopleLastname(people), getPeopleCpf(people), getPeopleGender(people), getPeopleBirth(people), getResidentCep(resid), getResidentFace(resid), getResidentNum(resid), getResidentCompl(resid));
              setResidentCep(resid, cepid);
              setResidentFace(resid, face);
              setResidentNum(resid, num);
              setResidentCompl(resid, compl);
              fprintf(arqTXT, "Endereco novo - CEP:%s Face:%c Num:%d Complemento:%s\n", getResidentCep(resid), getResidentFace(resid), getResidentNum(resid), getResidentCompl(resid));
              block = getHashCollision(hashh, cepid, getBlockCep);
              if(block != NULL){  
                if(getResidentFace(resid) == 'N'){
                  xd = getBlockX(block) + getResidentNum(resid);
                  yd = getBlockY(block) + getBlockH(block);
                }else if(getResidentFace(resid) == 'S'){
                  xd = getBlockX(block) + getResidentNum(resid);
                  yd = getBlockY(block);
                }else if(getResidentFace(resid) == 'L'){
                  xd = getBlockX(block);
                  yd = getBlockY(block) + getResidentNum(resid);
                }else if(getResidentFace(resid) == 'O'){
                  xd = getBlockX(block) + getBlockW(block);
                  yd = getBlockY(block) + getResidentNum(resid);
                }
                rect = createRectangle(-1, xa, ya, yd, xd, "yellow", "yellow");
                insertList(listDLRect, rect);
              }
            }
          }
        }
      }
    }
  }else{
    printf("\nERROR comando mud -> nenhuma pessoa com o cpf de entrada.");
    fprintf(arqTXT ,"ERROR comando mud -> nenhuma pessoa com o cpf de entrada.\n");
  }

  free(pathTXT);
  printf("\nFechando arquivo TXT.");
  fclose(arqTXT);    
}

void mudec(City city, HashTable hash, HashTable hashh, HashTable hashhh, String cnpj, String cepid, char face, int num, String pathEntry, String pathOut, List listE, List listDLRect){
  FILE *arqTXT;
  String pathTXT;
  Establishment estab;
  Block block;
  Description descript;
  Rectangle rect;
  List blocks;
  Posic p;
  float xa=0, ya=0, xd=0, yd=0;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");

  estab = getHashCollision(hash, cnpj, getEstabCnpj);
  if(estab != NULL){
    descript = getHashCollision(hashhh, getEstabCodt(estab), getDescriptCodt);
    if(descript != NULL){
      blocks = getHashList(hashh, getEstabCep(estab), getBlockCep);
      if(blocks != NULL){
        for(p=getFirst(blocks); p!=NULL; p=getNext(blocks, p)){
          block = getItem(blocks, p);
          if(block != NULL){
            if(strcmp(getEstabCep(estab), getBlockCep(block))==0){
              if(getEstabFace(estab) == 'N'){
                xa = getBlockX(block) + getEstabNum(estab);
                ya = getBlockY(block) + getBlockH(block) - 7.0;
              }else if(getEstabFace(estab) == 'S'){
                xa = getBlockX(block) + getEstabNum(estab);
                ya = getBlockY(block);
              }else if(getEstabFace(estab) == 'L'){
                xa = getBlockX(block);
                ya = getBlockY(block) + getEstabNum(estab);
              }else if(getEstabFace(estab) == 'O'){
                xa = getBlockX(block) + getBlockW(block) - 10.0;
                ya = getBlockY(block) + getEstabNum(estab);
              }
              fprintf(arqTXT, "Codt:%s Descricao:%s Nome:%s Cnpj:%s\nEndereco antigo - Cep:%s Face:%c Num:%d\n", getDescriptCodt(descript), getDescriptD(descript), getEstabName(estab), getEstabCnpj(estab), getEstabCep(estab), getEstabFace(estab), getEstabNum(estab));
              setEstabCep(estab, cepid);
              setEstabFace(estab, face);
              setEstabNum(estab, num);
              fprintf(arqTXT, "Novo endereco - Cep:%s Face:%c Num:%d", getEstabCep(estab), getEstabFace(estab), getEstabNum(estab));
              block = getHashCollision(hashh, cepid, getBlockCep);
              if(block != NULL){  
                if(getEstabFace(estab) == 'N'){
                  xd = getBlockX(block) + getEstabNum(estab);
                  yd = getBlockY(block) + getBlockH(block) - 7.0;
                }else if(getEstabFace(estab) == 'S'){
                  xd = getBlockX(block) + getEstabNum(estab);
                  yd = getBlockY(block);
                }else if(getEstabFace(estab) == 'L'){
                  xd = getBlockX(block);
                  yd = getBlockY(block) + getEstabNum(estab);
                }else if(getEstabFace(estab) == 'O'){
                  xd = getBlockX(block) + getBlockW(block) - 10.0;
                  yd = getBlockY(block) + getEstabNum(estab);
                }
                rect = createRectangle(-1, xa, ya, yd, xd, "green", "green");
                insertList(listDLRect, rect);
              }
            }
          }
        }
      }
    }
  }else{
    printf("\nERROR comando mudec -> nenhuma estabelecimento com o cnpj de entrada.");
    fprintf(arqTXT ,"ERROR comando mudec -> nenhum estabelecimento com o cnpj de entrada.\n");
  }

  free(pathTXT);
  printf("\nFechando arquivo TXT.");
  fclose(arqTXT); 
}

void dpr(City city, List listPeople, List listEstab, HashTable blockXcep, HashTable hydrantXid, HashTable peopleXcpf, HashTable residentXcpf, 
        HashTable residentXcep, HashTable estabXcep, HashTable estabXcnpj, HashTable descriptionXcodt, String pathEntry, String pathOut, float x, float y, float w, float h){
  FILE *arqTXT;
  String pathTXT;
  Block block;
  Equip equip, equipAux;
  KDtree blocksK, hydrantsK, semaphoresK, towersK;
  List blocks, residents, estabs, towers, semaphores, hydrants, listAux, estabs2, descriptions, peoples;
  Posic p, pp, pe, paux=NULL, peAux, ppaux=NULL, ppp, pppaux=NULL, pest, pestaux=NULL, rp;
  Establishment estab, estabAux, e; 
  Description descript;
  People people;
  Resident resid, r;
  Rectangle rect;
  Circle circ;
  float xe=0, ye=0, xp=0, yp=0, xx=0, yy=0, rr=0, xee=0, yee=0, xest=0, yest=0, ww=0, hh=0, xr=0, yr=0;

  pathTXT = setPathTXT(pathEntry, pathOut);
  arqTXT = fopen(pathTXT, "a");
  if(arqTXT != NULL)  printf("\nArquivo TXT aberto para escrita com sucesso!");
  else printf("\nFalha na abertura do arquivo TXT.");

  blocks = createList();
  blocksK = getBlocks(city);
  rangeSearchRect(blocksK, getBlockX, getBlockY, x, y, w, h, blocks, duplicateBlock);
  if(blocks!=NULL){
    for(p=getLast(blocks); p!=NULL; p=getPrevious(blocks, p)){
      block = getItem(blocks, p);
      if(block != NULL){
        
        residents = getHashList(residentXcep, getBlockCep(block), getResidentCep);
        if(residents != NULL){
          for(rp=getFirst(residents); rp!=NULL; rp=getNext(residents, rp)){
            if(paux != NULL){
              free(paux);
              paux = NULL;
            }
            resid = getItem(residents, rp);
            if(getResidentFace(resid) == 'N'){
              xr = getBlockX(block) + getResidentNum(resid);
              yr = getBlockY(block) + getBlockH(block);
            }else if(getResidentFace(resid) == 'S'){
              xr = getBlockX(block) + getResidentNum(resid);
              yr = getBlockY(block);
            }else if(getResidentFace(resid) == 'L'){
              xr = getBlockX(block);
              yr = getBlockY(block) + getResidentNum(resid);
            }else if(getResidentFace(resid) == 'O'){
              xr = getBlockX(block) + getBlockW(block);
              yr = getBlockY(block) + getResidentNum(resid);
            }
            if(xr>=x && xr<=x+w && yr>=y && yr<=y+h){
              paux = removeList2(residents, rp);
            }
            listAux = getHashList(residentXcpf, getResidentCpf(resid), getResidentCpf);
            if(listAux !=NULL){
              for(pp=getFirst(listAux); pp!=NULL; pp=getNext(listAux, pp)){
                if(ppaux !=NULL){
                  free(ppaux);
                  ppaux = NULL;
                }
                r=getItem(listAux, pp);
                if(getResidentFace(r) == 'N'){
                  xr = getBlockX(block) + getResidentNum(r);
                  yr = getBlockY(block) + getBlockH(block);
                }else if(getResidentFace(resid) == 'S'){
                  xr = getBlockX(block) + getResidentNum(r);
                  yr = getBlockY(block);
                }else if(getResidentFace(r) == 'L'){
                  xr = getBlockX(block);
                  yr = getBlockY(block) + getResidentNum(r);
                }else if(getResidentFace(r) == 'O'){
                  xr = getBlockX(block) + getBlockW(block);
                  yr = getBlockY(block) + getResidentNum(r);
                }
                if(xr>=x && xr<=x+w && yr>=y && yr<=y+h){
                  paux = removeList2(listAux, pp);
                }     
                peoples = getHashList(peopleXcpf, getResidentCpf(r), getPeopleCpf);
                if(peoples!=NULL){
                  for(ppp=getFirst(peoples); ppp!=NULL; ppp=getNext(peoples, ppp)){
                    if(pppaux != NULL){
                      free(pppaux);
                      pppaux = NULL;
                    }
                    people = getItem(peoples, ppp);
                    pppaux = removeList2(peoples, ppp);
                  }
                  if(pppaux!=NULL){
                    free(pppaux);
                    pppaux = NULL;
                  }
                }
              }
              if(ppaux !=NULL){
                free(ppaux);
                ppaux = NULL;
              }
            }
          }
          if(paux != NULL){
            free(paux);
            paux = NULL;
          }
        }

        estabs = getHashList(estabXcep, getBlockCep(block), getEstabCep);
        if(estabs != NULL){
          for(pe=getFirst(estabs); pe!=NULL; pe=getNext(estabs, pe)){
            if(paux != NULL){
              free(paux);
              paux=NULL;
            }
            estab = getItem(estabs, pe);
            if(estab!=NULL){
              if(getEstabFace(estab) == 'N'){
                xe = getBlockX(block) + getEstabNum(estab);
                ye = getBlockY(block) + getBlockH(block) - 7.0;
              }else if(getEstabFace(estab) == 'S'){
                xe = getBlockX(block) + getEstabNum(estab);
                ye = getBlockY(block);
              }else if(getEstabFace(estab) == 'L'){
                xe = getBlockX(block);
                ye = getBlockY(block) + getEstabNum(estab);
              }else if(getEstabFace(estab) == 'O'){
                xe = getBlockX(block) + getBlockW(block) - 10.0;
                ye = getBlockY(block) + getEstabNum(estab);
              }   
              if(xe>=x && xe<=x+w && ye>=y && ye<=y+h){
                paux = removeList2(estabs, pe);  
              }
            }
            
            estabs2 = getHashList(estabXcnpj, getEstabCnpj(estab), getEstabCnpj);
            if(estabs2 != NULL){
              for(peAux=getFirst(estabs2); peAux!=NULL; peAux=getNext(estabs2, peAux)){
                if(ppaux != NULL){
                  free(ppaux);
                  ppaux=NULL;
                }
                estabAux = getItem(estabs2, peAux);
                if(estabAux!=NULL){
                  if(getEstabFace(estab) == 'N'){
                    xee = getBlockX(block) + getEstabNum(estab);
                    yee = getBlockY(block) + getBlockH(block) - 7.0;
                  }else if(getEstabFace(estab) == 'S'){
                    xee = getBlockX(block) + getEstabNum(estab);
                    yee = getBlockY(block);
                  }else if(getEstabFace(estab) == 'L'){
                    xee = getBlockX(block);
                    yee = getBlockY(block) + getEstabNum(estab);
                  }else if(getEstabFace(estab) == 'O'){
                    xee = getBlockX(block) + getBlockW(block) - 10.0;
                    yee = getBlockY(block) + getEstabNum(estab);
                  }   
                  if(xee>=x && xee<=x+w && yee>=y && yee<=y+h){
                    ppaux = removeList2(estabs2, peAux);  
                  }
                }
              }
              if(ppaux != NULL){
                free(ppaux);
                ppaux=NULL;
              }    
            }

            descriptions = getHashList(descriptionXcodt, getEstabCodt(estab), getDescriptCodt);
            if(descriptions != NULL){
              for(ppp=getFirst(descriptions); ppp!=NULL; ppp=getNext(descriptions, ppp)){
                if(pppaux != NULL){
                  free(pppaux);
                  pppaux = NULL;
                }
                descript = getItem(descriptions, ppp);
                if(strcmp(getEstabCodt(estab), getDescriptCodt(descript))==0){
                  pppaux = removeList2(descriptions, ppp);
                }
              }
              if(pppaux != NULL){
                free(pppaux);
                pppaux = NULL;
              }
            }

          }
          if(paux != NULL){
            free(paux);
            paux=NULL;
          }
        }
        xx = getBlockX(block);
        yy = getBlockY(block);
        ww = getBlockW(block);
        hh = getBlockH(block);
        if((xx>=x) && (xx+ww<=x+w) && (yy>=y) && (yy+hh<=y+h))
          removeKDT(blocksK, block, equalBlocks, getBlockX, getBlockY, freeBlock, copyBlock);
      }else{
       // continue;
      }
    }
  }else{
    printf("\nERRO comando dpr -> não existe nenhuma quadra inteiramente dentro da região.");
    fprintf(arqTXT, "ERRO comando dpr -> nao existe nenhuma quadra dentro da regiao.\n");
  }
  semaphores = createList();
  semaphoresK = getSemaphores(city);
  rangeSearchRect(semaphoresK, getEquipX, getEquipY, x, y, w, h, semaphores, duplicateEquip);
  if(semaphores != NULL){
    for(pe=getLast(semaphores); pe!=NULL; pe=getPrevious(semaphores, pe)){
      equip = getItem(semaphores, pe);
      xx = getEquipX(equip);
      yy = getEquipY(equip);
      rr = getEquipR(equip);
      if((xx-rr>=x-3) && (xx+rr<=x+3) && (yy-rr>=y-3) && (yy+rr<=y+3)){
        removeKDT(semaphoresK, equip, equalEquips, getEquipX, getEquipY, freeEquip, copyEquip);
        fprintf(arqTXT, "Semaforo removido -> ID: %s\n", getEquipId(equip));
      }
    }
  }
  towers = createList();
  towersK = getTowers(city);
  rangeSearchRect(towersK, getEquipX, getEquipY, x, y, w, h, towers, duplicateEquip);
  if(towers != NULL){
    for(pe=getLast(towers); pe!=NULL; pe=getNext(towers, pe)){
      equip = getItem(towers, pe);
      xx = getEquipX(equip);
      yy = getEquipY(equip);
      rr = getEquipR(equip);
      if((xx-rr>=x-5) && (xx+rr<=x+5) && (yy-rr>=y-5) && (yy+rr<=y+5)){
        removeKDT(towersK, equip, equalEquips, getEquipX, getEquipY, freeEquip, copyEquip);
        fprintf(arqTXT, "Torre removida -> ID: %s\n", getEquipId(equip));
      }
    }
  }
  hydrants = createList();
  hydrantsK = getHydrants(city);
  rangeSearchRect(hydrantsK, getEquipX, getEquipY, x, y, w, h, hydrants, duplicateEquip);
  if(hydrants != NULL){
    for(pe=getLast(hydrants); pe!=NULL; pe=getPrevious(hydrants, pe)){
      equip = getItem(hydrants, pe);
      xx = getEquipX(equip);
      yy = getEquipY(equip);
      rr = getEquipR(equip);
      listAux = getHashList(hydrantXid, getEquipId(equip), getEquipId);
      for(peAux=getFirst(listAux); peAux!=NULL; peAux=getNext(listAux, peAux)){
        if(paux != NULL){
          free(paux);
          paux=NULL;
        }
        equipAux = getItem(listAux, peAux);
        if(equalEquips(equip, equipAux)){
          paux = removeList2(listAux, peAux); 
        }
      }
      if(paux != NULL){
        free(paux);
        paux = NULL;
      }
      if((xx-rr>=x-3) && (xx+rr<=x+3) && (yy-rr>=y-3) && (yy+rr<=y+3)){
        removeKDT(hydrantsK, equip, equalEquips, getEquipX, getEquipY, freeEquip, copyEquip);
        fprintf(arqTXT, "Hidrante removido -> ID: %s\n", getEquipId(equip));
      }
    }
  }

  for(pest=getFirst(listEstab); pest!=NULL; pest=getNext(listEstab, pest)){
    if(pestaux != NULL){
      free(pestaux);
      pestaux = NULL;
    }
    rect = getItem(listEstab, pest);
    if(rect!=NULL){
      if(getRectangleX(rect)>=x && getRectangleX(rect)+getRectangleW(rect)<=x+w && getRectangleY(rect)>=y && getRectangleY(rect)+getRectangleH(rect)<=y+h){
        pestaux = removeList2(listEstab, pest);  
      }   
    }
  }
  if(pestaux != NULL){
    free(pestaux);
    pestaux = NULL;
  }

  for(p=getFirst(listPeople); p!=NULL; p=getNext(listPeople, p)){
    if(paux != NULL){
      free(paux);
      paux = NULL;
    }
    circ = getItem(listPeople, p);
    if(getCircleX(circ)>=x && getCircleX(circ)<=x+w && getCircleY(circ)>=y && getCircleY(circ)<=h+y){
      paux = removeList2(listPeople, p);
    }
  }
  if(paux != NULL){
    free(paux);
    paux = NULL;
  }

  freeL(semaphores, freeEquip);
  freeL(towers, freeEquip);
  freeL(hydrants, freeEquip);
  freeL(blocks, freeBlock);
  free(pathTXT);
  printf("\nFechando arquivo TXT.");
  fclose(arqTXT);
}