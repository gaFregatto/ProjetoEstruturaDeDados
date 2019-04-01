#include "Strings.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*  Funcao privada -> (bool) verifica se existe comando -f  */
int comandoF(int argc, char *argv[]){
  int i=1, b=0;
  while(i<argc){
    if(strcmp(argv[i], "-f")==0)  b=1;
    i++;
  }
  return b;
}

/*  Funcao privada -> (bool) verifica se existe comando -o  */
int comandoO(int argc, char *argv[]){
  int i=1, b=0;
  while(i<argc){
    if(strcmp(argv[i], "-o")==0)  b=1;
    i++;
  }
  return b;
}

String getPathEntry(int argc, char *argv[], char *pathE){
  int i=1;
  String path, pathAux=NULL;

  if(pathE == NULL){
    if(!comandoF(argc, argv)){
      return NULL;
    }else{
      while(i<argc){
        if(strcmp(argv[i], "-f")==0){
          path = (String)malloc((strlen(argv[i+1])+1)*sizeof(char));
          strcpy(path, argv[i+1]);
        }
        i++;
      }
    }
    return path;
  }else{
    if(!comandoF(argc, argv)){
      return NULL;
    }else{
      while(i<argc){
        if(strcmp(argv[i], "-f")==0){
          path = (String)malloc((strlen(argv[i+1])+1)*sizeof(char));
          strcpy(path, argv[i+1]);
        }
        i++;
      }
      pathAux = (String)calloc((strlen(path)+strlen(pathE)+2), sizeof(char));
      strcpy(pathAux, pathE);
      if(pathAux[strlen(pathAux)-1] != '/')   strcat(pathAux, "/");
      strcat(pathAux, path);
      free(path);
      path = NULL;
    }
    return pathAux;
  }
}

String getPathOut(int argc, char *argv[]){
  int i=1;
  String path;

  if(!comandoO(argc, argv)){
    return NULL;
  }else{
    while(i<argc){
      if(strcmp(argv[i], "-o")==0){
        path = (String)malloc((strlen(argv[i+1])+2)*sizeof(char));
        strcpy(path, argv[i+1]);
        if(path[strlen(argv[i+1])-1] != '/')  strcat(path, "/\0");
        else strcat(path, "\0\0");
      }
      i++;
    }
    return path;
  }
}

String getDirectory(String path){
  String direct;
  int size, j;

  if(path == NULL)  return path;
  size = strlen(path);
  j = size-1;
  while(path[j] != '/') j--;
  j++;
  direct = (String)malloc((j+1)*sizeof(char)); /*  J tem o tamanho do diretorio, +1 para o \0  */
  size = 0;
  while(size<j){
    direct[size] = path[size];
    size++;
  }
  direct[size] = '\0';
  return direct;
}

String getExtension(String path){
  String extension;
  int size, j, i=0;

  if(path == NULL)  return path;
  size = strlen(path);
  j = size-1;
  while(path[j] != '.') j--;
  extension = (String)malloc(5*sizeof(char)); /*  '.' 't' 'x' 't' '\0'  */
  while(j<size){
    extension[i] = path[j];
    j++;
    i++;
  }
  extension[i] = '\0';
  return extension;
}

String getNameFile(String path){
  String nameF;
  int size, j, i=0;

  if(path == NULL)  return path;
  size = strlen(path);
  j = size-1;
  while(path[j] != '/') j--;
  j++;
  nameF = (String)malloc((size-j-3)*sizeof(char));
  while(path[j] != '.'){
    nameF[i] = path[j];
    i++;
    j++;
  }
  nameF[i] = '\0';
  return nameF;
}

int comandoE(int argc, char *argv[]){
  int i=1, b=0;
  while(i<argc){
    if(strcmp(argv[i], "-e")==0)  b=1;
    i++;
  }
  return b;
}

String getPathE(int argc, char *argv[]){
  int i=1;
  String pathE;

  if(!comandoE(argc, argv)){
    return NULL;
  }else{
    while(i<argc){
      if(strcmp(argv[i], "-e")==0){
        pathE = (String)malloc((strlen(argv[i+1])+1)*sizeof(char));
        strcpy(pathE, argv[i+1]);
      }
      i++;
    }
  }
  return pathE;
}

String setPathTXT(String pathEntry, String pathOut){
  String nameFile = getNameFile(pathEntry);
  String pathTXT = (String)malloc((strlen(pathOut)+strlen(nameFile)+5)*sizeof(char));

  strcpy(pathTXT, pathOut);
  strcat(pathTXT, nameFile);
  free(nameFile);
  strcat(pathTXT, ".txt");
  return pathTXT;
}

String setPathSVG(String pathEntry, String pathOut){
  String nameFile = getNameFile(pathEntry);
  String pathSVG = (String)malloc((strlen(pathOut)+strlen(nameFile)+5)*sizeof(char));

  strcpy(pathSVG, pathOut);
  strcat(pathSVG, nameFile);
  free(nameFile);
  strcat(pathSVG, ".svg");
  return pathSVG;
}

String setPathSVGsufixo(String pathEntry, String pathOut, char sufixo[]){
  String nameFile = getNameFile(pathEntry);
  String pathSVGsuf = (String)malloc((strlen(pathOut)+strlen(nameFile)+strlen(sufixo)+6)*sizeof(char));

  strcpy(pathSVGsuf, pathOut);
  strcat(pathSVGsuf, nameFile);
  free(nameFile);
  strcat(pathSVGsuf, "-");
  strcat(pathSVGsuf, sufixo);
  strcat(pathSVGsuf, ".svg");
  return pathSVGsuf;
}

int comandoQ(int argc, char *argv[]){
  int i=1, b=0;
  while(i<argc){
    if(strcmp(argv[i], "-q")==0)  b=1;
    i++;
  }
  return b;
}

String getPathQry(int argc, char *argv[], char *pathE){
  int i=1;
  String path, pathAux=NULL;

  if(pathE == NULL){
    if(!comandoQ(argc, argv)){
      return NULL;
    }else{
      while(i<argc){
        if(strcmp(argv[i], "-q")==0){
          path = (String)malloc((strlen(argv[i+1])+1)*sizeof(char));
          strcpy(path, argv[i+1]);
        }
        i++;
      }
    }
    return path;
  }else{
    if(!comandoQ(argc, argv)){
      return NULL;
    }else{
      while(i<argc){
        if(strcmp(argv[i], "-q")==0){
          path = (String)malloc((strlen(argv[i+1])+1)*sizeof(char));
          strcpy(path, argv[i+1]);
        }
        i++;
      }
      pathAux = (String)calloc((strlen(path)+strlen(pathE)+2), sizeof(char));
      strcpy(pathAux, pathE);
      if(pathAux[strlen(pathAux)-1] != '/')   strcat(pathAux, "/");
      strcat(pathAux, path);
      free(path);
      path = NULL;
    }
    return pathAux;
  }
}

String setPathSVGqry(String pathEntry, String pathOut, String pathQry){
  String nameGeoFile, nameQryFile, pathSVGqry;
  nameGeoFile = getNameFile(pathEntry);
  nameQryFile = getNameFile(pathQry);
  pathSVGqry = (String)calloc(strlen(pathOut)+strlen(nameGeoFile)+strlen(nameQryFile)+10, sizeof(char));

  strcpy(pathSVGqry, pathOut);
  strcat(pathSVGqry, nameGeoFile);
  strcat(pathSVGqry, "-");
  strcat(pathSVGqry, nameQryFile);
  strcat(pathSVGqry, ".svg");
  free(nameGeoFile);
  free(nameQryFile);
  return pathSVGqry;
}

int comandoEC(int argc, char *argv[]){
  int i=1, b=0;
  while(i<argc){
    if(strcmp(argv[i], "-ec")==0)  b=1;
    i++;
  }
  return b;
}

int comandoPM(int argc, char *argv[]){
  int i=1, b=0;
  while(i<argc){
    if(strcmp(argv[i], "-pm")==0)  b=1;
    i++;
  }
  return b;
}

String getPathEC(int argc, char *argv[], char *pathE){
  int i=1;
  String path, pathAux=NULL;

  if(pathE == NULL){
    if(!comandoEC(argc, argv)){
      return NULL;
    }else{
      while(i<argc){
        if(strcmp(argv[i], "-ec")==0){
          path = (String)malloc((strlen(argv[i+1])+1)*sizeof(char));
          strcpy(path, argv[i+1]);
        }
        i++;
      }
    }
    return path;
  }else{
    if(!comandoEC(argc, argv)){
      return NULL;
    }else{
      while(i<argc){
        if(strcmp(argv[i], "-ec")==0){
          path = (String)malloc((strlen(argv[i+1])+1)*sizeof(char));
          strcpy(path, argv[i+1]);
        }
        i++;
      }
      pathAux = (String)calloc((strlen(path)+strlen(pathE)+2), sizeof(char));
      strcpy(pathAux, pathE);
      if(pathAux[strlen(pathAux)-1] != '/')   strcat(pathAux, "/");
      strcat(pathAux, path);
      free(path);
      path = NULL;
    }
    return pathAux;
  }

}

String getPathPM(int argc, char *argv[], char *pathE){
  int i=1;
  String path, pathAux=NULL;

  if(pathE == NULL){
    if(!comandoPM(argc, argv)){
      return NULL;
    }else{
      while(i<argc){
        if(strcmp(argv[i], "-pm")==0){
          path = (String)malloc((strlen(argv[i+1])+1)*sizeof(char));
          strcpy(path, argv[i+1]);
        }
        i++;
      }
    }
    return path;
  }else{
    if(!comandoPM(argc, argv)){
      return NULL;
    }else{
      while(i<argc){
        if(strcmp(argv[i], "-pm")==0){
          path = (String)malloc((strlen(argv[i+1])+1)*sizeof(char));
          strcpy(path, argv[i+1]);
        }
        i++;
      }
      pathAux = (String)calloc((strlen(path)+strlen(pathE)+2), sizeof(char));
      strcpy(pathAux, pathE);
      if(pathAux[strlen(pathAux)-1] != '/')   strcat(pathAux, "/");
      strcat(pathAux, path);
      free(path);
      path = NULL;
    }
    return pathAux;
  } 
}

int comandoV(int argc, char *argv[]){
  int i=1, b=0;
  while(i<argc){
    if(strcmp(argv[i], "-v")==0)  b=1;
    i++;
  }
  return b;
}

String getPathV(int argc, char *argv[], char *pathE){
  int i=1;
  String path, pathAux=NULL;

  if(pathE == NULL){
    if(!comandoPM(argc, argv)){
      return NULL;
    }else{
      while(i<argc){
        if(strcmp(argv[i], "-v")==0){
          path = (String)malloc((strlen(argv[i+1])+1)*sizeof(char));
          strcpy(path, argv[i+1]);
        }
        i++;
      }
    }
    return path;
  }else{
    if(!comandoPM(argc, argv)){
      return NULL;
    }else{
      while(i<argc){
        if(strcmp(argv[i], "-v")==0){
          path = (String)malloc((strlen(argv[i+1])+1)*sizeof(char));
          strcpy(path, argv[i+1]);
        }
        i++;
      }
      pathAux = (String)calloc((strlen(path)+strlen(pathE)+2), sizeof(char));
      strcpy(pathAux, pathE);
      if(pathAux[strlen(pathAux)-1] != '/')   strcat(pathAux, "/");
      strcat(pathAux, path);
      free(path);
      path = NULL;
    }
    return pathAux;
  } 
}