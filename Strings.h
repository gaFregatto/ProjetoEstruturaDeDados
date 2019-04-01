#ifndef Strings_h
#define Strings_h

/*  Esse módulo tem como funcão facilitar a manipulacão de strings.  */

#include "Read.h"

/*  Define um novo apelido <String> para char* .   */
typedef char* String;

/*  Pré-condicão: parametros argc e argv válidos.
    Pós-condicão: retorna uma String contendo o path de entrada.
    OBS: necessário dar free na variável quando ela não for mais utilizada.  */
String getPathEntry(int argc, char *argv[], char *pathE);

/*  Pré-condicão: parametros argc e argv válidos.
    Pós-condicão: retorna uma String contendo path de saida.
    OBS: necessário dar free na variável quando ela não for mais utilizada.  */
String getPathOut(int argc, char *argv[]);

/*  Pré-condicão: receber um path valido.
    Pós-condicão: dado um path retorna um diretorio.  */
String getDirectory(String path);

/*  Pré-condicão: receber um path valido.
    Pós-condicão: dado um path retorna a extensao do arquivo.  */
String getExtension(String path);

/*  Pré-condicão: receber um path valido.
    Pós-condicão: dado um path retorna o nome do arquivo sem extensão.  */
String getNameFile(String path);

/*  Pós-condicão: se existir comando E retorna 1, se não retorna 0. (funcão bool)
*/
int comandoE(int argc, char* argv[]);

/*  Pré-condicão: o comando -e deve existir.
    Pós-condicão: retorna o diretorio base de entrada que fica após o comando -e no argv.  */
String getPathE(int argc, char* argv[]);

/*  Pós-condição: retorna um string com o path correto para abrir o arquivo TXT.
    OBS: precisa dar free na variável após o uso.
*/
String setPathTXT(String pathEntry, String pathOut);

/*  Pós-condição: retorna uma string com o path correto para abrir o arquivo SVG.
    OBS: precisa dar free na variável após o uso.
*/
String setPathSVG(String pathEntry, String pathOut);

/*  Pós-condição: retorna uma string com path correto para abrir o arquivo SVG-sufixo.
    OBS: precisa dar free na variável após o uso.
*/
String setPathSVGsufixo(String pathEntry, String pathOut, char sufixo[]);

/**  Pós-condição: se existir comando Q retorna 1, se não retorna 0. (função bool)  */
int comandoQ(int argc, char *argv[]);

/**  Pré-condicão: parametros argc e argv válidos.
    Pós-condicão: retorna uma String contendo o path do arquivo Qry.
    OBS: necessário dar free na variável quando ela não for mais utilizada.  */
String getPathQry(int argc, char *argv[], char *pathE);

/** Pré-condição: parametros argc e argv inválidos.
    Pós-condição: retorna uma String com o path correndo para abrir o arquivo SVG qry. 
    OBS: necessário das free na variável após o uso. */
String setPathSVGqry(char *pathEntry, char *pathOut, char *pathQry);

/** Pós-condição: se existir comando EC retorna 1, se não retorna 0.  */
int comandoEC(int argc, char *argv[]);

/** Pós-condição: se existir comando PM retorna 1, se não retorna 0.  */
int comandoPM(int argc, char *argv[]);

/** Pré-condição: parametros argc e argv válidos.
    Pós-condição: retorna uma String contendo o path do arquivo EC.
    OBS: necessário das free ne variável quando ela não for mais utilizada.  */
String getPathEC(int argc, char *argv[], char *pathE);

/** Pré-condição: parametros argc e argv válidos.
    Pós-condição: retorna uma String contendo o path do arquivo PM.
    OBS: necessário das free ne variável quando ela não for mais utilizada.  */
String getPathPM(int argc, char *argv[], char *pathE);

/** Pós-condição: se existir comando VIA retorna 1, se não retorna 0.  */
int comandoV(int argc, char *argv[]);

/** Pré-condição: parametros argc e argv válidos.
    Pós-condição: retorna uma String contendo o path do arquivo V.
    OBS: necessário dar free na variável após o uso.    */
String getPathV(int argc, char *argv[], char *pathV);

#endif
