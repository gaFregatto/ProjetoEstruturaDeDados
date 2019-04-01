#include "Circle.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Strings.h"

typedef struct _circle{
  int id;
  float x, y, r;
  String fill, stroke;
}circle;

Circle createCircle(int id, float x, float y, float r, char fill[], char stroke[]){
  circle *newCircle;
  newCircle = (circle*)malloc(sizeof(circle));
  newCircle->id = id;
  newCircle->x = x;
  newCircle->y = y;
  newCircle->r = r;
  newCircle->fill = (String)malloc((strlen(fill)+1)*sizeof(char));
  strcpy(newCircle->fill, fill);
  newCircle->stroke = (String)malloc((strlen(stroke)+1)*sizeof(char));
  strcpy(newCircle->stroke, stroke);
  return newCircle;
}

int getCircleID(Circle circ){
  circle *auxCirc = (circle*)circ;
  return auxCirc->id;
}

float getCircleX(Circle circ){
  circle *auxCirc = (circle*)circ;
  return auxCirc->x;
}

float getCircleY(Circle circ){
  circle *auxCirc = (circle*)circ;
  return auxCirc->y;
}

float getCircleR(Circle circ){
  circle *auxCirc = (circle*)circ;
  return auxCirc->r;
}

String getCircleFill(Circle circ){
  circle *auxCirc = (circle*)circ;
  return auxCirc->fill;
}

String getCircleStroke(Circle circ){
  circle *auxCirc = (circle*)circ;
  return auxCirc->stroke;
}

void freeCircle(Circle circ){
  circle *auxCircle = (circle*)circ;
  free(auxCircle->fill);
  auxCircle->fill = NULL;
  free(auxCircle->stroke);
  auxCircle->stroke = NULL;
  free(auxCircle);
  auxCircle = NULL;
}