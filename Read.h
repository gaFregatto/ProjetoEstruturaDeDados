#ifndef Read_h
#define Read_h

/*  Esse módulo possui a funcão de fazer o tratamento de quaisquer arquivos de entrada. */

/** Pré-condicão: path de entrada e path de saida devem estar setados corretamente nos parametros.
    Pós-condicão: le todo o arquivo GEO de entrada e realiza seus commando linha por linha.  */
void arquivoGEO(char *pathEntry, char *pathOut, int argc, char *argv[], 
				void *listCirc, void *listRect, void* listOverlap, void *city);

/** Pré-condição: path de entrada e path de saida devem estar setados corretamento nos parametros.
	Pós-condição: le todo o arquivo QRY de entrada e realiza seus comandos linha por linha.	 */
void arquivoQRY(char *pathQry, char *pathEntry, char *pathOut, int argc, char *argv[], void *city, 
				void *listCirc, void *listRect, void *listOverlap, void *listPeople, void *listResident,
				void *listEstab, void *listDescript);	

/** Pré-condição: path de entrada e path de saida devem estar setados corretamente nos parametros.
	Pós-condição: le todo o arquivo EC de entrada e realiza seus comandos linha por linha.  */
void arquivoEC(char *pathEC, char *pathEntry, char *pathOut, void *listDescript, void *listEstab);

/** Pré-condição: path de entrada e path de saida devem estar setados corretatmente nos parametros.
	Pós-condição: le todo o arquivo EC de entrada e realiza seus comandos linha por linha.  */
void arquivoPM(char *pathPM, char *pathEntry, char *pathOut, void *listPeople, void *listResident);

/** Pré-condição: path de entrada e path de saida devem estar setados corretamente.
	Pós-condições: le todo o arquivo via de entrada e realiza seus comandos linha por linha.  */
voud arquivoVIA(char *pathVIA, char *pathEntry, char *pathOut, void *graph);

#endif
