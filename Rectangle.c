#include "Rectangle.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Strings.h"

typedef struct _rectangle{
  int id;
  float x, y, h, w;
  String fill, stroke;
}rectangle;

Rectangle createRectangle(int id, float x, float y, float h, float w, char fill[], char stroke[]){
  rectangle *newRect;
  newRect = (rectangle*)malloc(sizeof(rectangle));
  newRect->id = id;
  newRect->x = x;
  newRect->y = y;
  newRect->h = h;
  newRect->w = w;
  newRect->fill = (String)malloc((strlen(fill)+1)*sizeof(char));
  strcpy(newRect->fill, fill);
  newRect->stroke = (String)malloc((strlen(stroke)+1)*sizeof(char));
  strcpy(newRect->stroke, stroke);
  return newRect;
}

int getRectangleID(Rectangle rect){
  rectangle *auxRect = (rectangle*)rect;
  return auxRect->id;
}

float getRectangleX(Rectangle rect){
  rectangle *auxRect = (rectangle*)rect;
  return auxRect->x;
}

float getRectangleY(Rectangle rect){
  rectangle *auxRect = (rectangle*)rect;
  return auxRect->y;
}

float getRectangleH(Rectangle rect){
  rectangle *auxRect = (rectangle*)rect;
  return auxRect->h;
}

float getRectangleW(Rectangle rect){
  rectangle *auxRect = (rectangle*)rect;
  return auxRect->w;
}

String getRectangleFill(Rectangle rect){
  rectangle *auxRect = (rectangle*)rect;
  return auxRect->fill;
}

String getRectangleStroke(Rectangle rect){
  rectangle *auxRect = (rectangle*)rect;
  return auxRect->stroke;
}

void freeRectangle(Rectangle rect){
  rectangle *auxRect = (rectangle*)rect;
  free(auxRect->fill);
  auxRect->fill = NULL;
  free(auxRect->stroke);
  auxRect->stroke = NULL;
  free(auxRect);
  auxRect = NULL;
}

