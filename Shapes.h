#ifndef Shapes_h
#define Shapes_h

#include "List.h" 

/** Esse é o módulo Shapes, ele é responsável pelas operações necessárias para realizar os comadnos lidos nos arquivos de entrada. */

/** Pré-condição: deve existir uma lista de círculos e uma de retângulos já criados.
    Pós-condição: printa um arquivo SVG com todos os círculos e retângulos. */
void printSVG(void *listCirc, void *listRect, char *pathOut, char *pathEntry, void *listOverlap, void *city);

/** Comando O ~
    Pré-condicão: deve existir uma lista de circulos e uma de retangulos.
    Pós-condicão: procura nas listas as figuras de acordo com as ids passadas e verifica se elas se sobrepoe. */
void searchIDsOverlap(void *listCirc, void *listRect, int id1, int id2, char *pathOut, char *pathEntry, void *listOverlap);
/** Comando I ~
    Pré-condição: deve existir uma lista de círculos e uma de retângulos.
    Pós-condição: procura nas listas uma figura de acordo com a it e verifica se o ponto x e y é interno a esta figura. */
void searchIDsInternalPoint(void *listCirc, void *listRect, int id, float X, float Y, char *pathOut, char *pathEntry);

/** Comando D ~
    Pré-condição: deve existir uma lista de círculos e uma de retângulos.
    Pós-condição: procura nas listas as figuras de acordo com as ids passadas e calcula a distancia entre seus centros de massa.  */
void searchIDsDistance(void *listCirc, void *listRect, int id1, int id2, char *pathOut, char *pathEntry);

/** Comando A ~
    Pré-condição: deve existir uma lista de círculos e uma de retângulos.
    Pós-condição: printa um arquivo SVG sufixo com e
                  traça uma linha do centro de massa da figura referente à id para
                  o centro de massa de todas as outras figuras, printando também seu comprimento. */
void printSVGsufixo(void *listCirc, void *listRect, int id, char sufixo[], char *pathOut, char *pathEntry);

/** Pré-condição: deve existir uma cidade.
    Pós-condição: printa o arquivo SVGqry, que contém a cidade após o arquivo qry. */
void printSVGqry(char *pathEntry, char *pathOut, char *pathQry, void *listCirc, void *listRect, void *listOverlap, void *city, 
                  void *dashRectangles, void *dashCircles, void *tower1, void *tower2, void *listPeopleCirc, void *listEstabRect, void *listRip, void *listDLRect);

/** Comando q? ~
    Pré-condição: deve existir uma cidade.
    Pós-condição: procura na cidade todos as quadras e equipamentos urbanos que estiverem inteiramente dentro do retângulo passado por parêmtro,
                  se verdadeiro reporta todos respectivos dados no arquivo texto .*/
void reportRectangle(void *city, char *pathEntry, char *pathOut, float x, float y, float w, float h);

/** Comando Q? ~
    Pré-condição: deve existir uma cidade.
    Pós-condição: procura na cidade todas as quadras e equipamentos urbanos que estiverem inteiramente dentro do círculo passado por parâmetro,
                  se verdadeiro reporta todos respectivos dados no arquivo texto. */
void reportCircle(void *city, char *pathEntry, char *pathOut, float x, float y, float r);

/** Comando dq ~
    Pré-condição; deve existir uma cidade.
    Pós-condição: remove todas as quadras que estiverem dentro do retângulo passado por parâmetro,
                  se verdadeiro reporta seu cep no arquivo texto. */
void removeBlockR(void *city, char *pathEntry, char *pathOut, float x, float y, float w, float h);

/** Comando dle ~
    Pré-condição: deve existir uma cidade.
    Pós-condição: remove todos os equipamentos urbanos que estiverem inteiramente dentro do retângulo passado por parâmetro,                           
                  se verdadeiro reporta o id do equipamento no arquivo texto. */
void removeEquipR(void *city, char *pathEntry, char *pathOut, char *types, float x, float y, float w, float h);

/** Comando Dq ~
    Pré-condição: deve existir uma cidade.
    Pós-condição: remove todas as quadras que estiverem inteiramente dentro do círculo passado por parâmetro,
                  se verdadeiro, reporta o cep no arquivo texto. */
void removeBlockC(void *city, char *pathEntry, char* pathOut, float x, float y, float r);

/** Comando Dle ~
    Pré-condição: deve existir uma cidade.
    Pós-condição: remove todos os equipamentos urbanos que estiverem inteiramente dentro do círculo passado por parâmetro,
                  se verdadeiro reporta o id no arquivo texto. */
void removeEquipC(void *city, char *pathEntry, char *pathOut, char *types, float x, float y, float r);

/** Comando cc ~
    Pré-condição: deve existir uma cidade.
    Pós-condição: troca a cor da borda e preenchimento do elemento identificado pelo cep ou id. */
void changeColor(void *city, char *cepid, char *stroke, char *fill);

/** Comando crd? ~
    Pré-condição: deve existir uma cidade.
    Pós-condição: reporta no arquivo texto os dados da quadra ou equipamento identificado pelo cep ou id. */
void searchCepId(void *city, char *pathEntry, char *pathOut, char *cepid);

/** Comando crb? ~
    Pré-condição: deve existir uma cidade.
    Pós-condição: destaca as torres no arquivo svg e reporta o id e a distância das torres no arquivo txt.*/
void closestTowers(void *city, char *pathEntry, char *pathOut, void **tower1, void **tower2);

/** Comando m? ~
    Pré-condição: Recebe uma hashTable, o cep a ser procurado.
    Pós-condição: Reporta no arquivo texto os residentes da quadra do cep enviado na entrada. */
void reportResidentByCep(void *hash, void *hashh, char *cepid, char *pathEntry, char *pathOut);

/** Comando mr? ~
    Pré-condição: Recebe uma city, uma HashTable residentXcep, uma HashTable peopleXcpf, o path de entrada e saida e as dimensões do retângulo.  
    Pós-condição: Reporta no arquivo texto todos os residentes das quadras inteiramente dentro da região. */
void reportResidentRect(void *city, void *hash, void *hashh, char *pathEntry, char *pahthOut, float x, float y, float w, float h);

/** Comando dm? ~
    Pré-condição: Recebe uma HasTable residentXcpf e uma HasTable peopleXcpf e uma HashTable blockXcep, o cpf, pathEntey, pathOut, pathQry e uma lista de pessoas que serão printadas no arquivo SVG.
    Pós-condição: Reporta em um arquivo texto os dados do morador identificado com cpf. No arquivo svg, printa uma forma geométrica no local onde a pessoa mora. */
void reportResidentByCpf(void *hash, void *hashh, void *hashhh, char *cpf, char *pathEntry, char *pathOut, char *pathQry, void *listPeopleCirc);

/** Comando de? ~
    Pré-condição: Recebe três hashTabels, estabXcnpj, descriptionXcodt, blockXcep, um cnpj que será a chave, paths de entrada, saida, qry e uma lista para os estabelecimentos a serem printados no SVG. 
    Pós-condição: Imprime em um arquivo texto todos os dados do estabelecimento identificado pelo cnpj. Armazena na lista o estabelecimento que será printado no arquivo SVG.*/
void reportEstabByCnpj(void *hash, void *hashh, void *hashhh, char *cnpj, char *pathEntry, char *pathout, char *pathQry, void *listEstabRect);

/** Comando rip ~
    Pré-condição: Recebe três HashTables, residentXcpf, peopleXcpf, blockXcep, paths de entrada, o cpf e uma lista.
    Pós-condição: Armazena na lista as pessoas com o cpf, printa no arquivo texto que ela morreu. */
void rip(void *hash, void *hashh, void *hashhh, char *cpf, char *pathEntry, char *pathOut, char *pathQry, void * listRip);

/** Comando ecq? ~
    Pré-condição: Recebe uma HashTable estabXcep um cep que será a chave, e os paths de entrada e saida.
    Pós-condição: Reporta no arquivo texto todos os estabelecimentos da quadra enviada no parâmetro. */
void reportEstabByCep(void *hash, char *cep, char *pathEntry, char *pathOut);

/** Comando ecr? ~
    Pré-condição: Recebe uma cidade, duas HashTables estabXcep, descriptionXcodt, o codt que éa chave, dimensão de um retângulo e os paths de entrada e saida. 
    Pós-condição: Caso o codt de entrada esteja presente dentro da região, lista os estabelecimentos comerciais do tipo. */
void reportCodtRect(void *city, void *hash, void *hashh, char *codt, float x, float y, float w, float h, char *pathEntry, char *pathOut);

/** Comando tecq? ~
    Pré-condição: Recebe duas HashTables blockXcep e estabXecp, uma chave cepid os paths de entrada e saida.
    Pós-condição: Reporta todos os estabelecimentos quadra. */
void reportEstabBlock(void *hash, void *hashh, char *cepid, char *pathEntry, char *pathOut);

/** Comando tecr? ~
    Pré-condição: Recebe uma cidade, três Hashtables blockXcep, estabXcep, descriptionXcodt, dimensões de uma retângulo e os paths de entrada e saida. 
    Pós-condição: Printa no arquivo TXT todos os tipos de estabelecimentos presentes naquela região. */
void reportEstabTypeRect(void *city, void *hash, void *hashh, void *hashhh, float x, float y, float w, float h, char *pathEntry, char *pathOut);

/** Comando hmpe? ~
    Pré-condição: Recebe uma cidade, uma hash blockXcep, um endereço(cepid, face, num), os paths de entrada e saida, e uma lista para guardar as linhas que vão printar um X no arquivo SVG no endereco.
    Pós-condição: Procura o hidrante mais próximo do ponto X definido pelo endereço. */
void closestHydrant(void *city, void *hash, char *cepid, char face, int num, char *pathEntry, char *pathOut, void *listDLRect);

/** Comando hmp? ~
    Pré-condição: Recebe uma cidade, uma hashTable hydrantXid, uma id chave, os paths de entrada e saida e uma lista onde serão guardados os pontos para imprimir a linha no svg.
    Pós-condição: Procura o o hidrante mais próximo do hidrante identificado pela id. Reporta os dados de ambos no arquivo texto e traça uma linha tracejada no svg ligando-os. */
void closestHydrants(void *city, void *hash, char *id, char *pathEntry, char *pathOut, void *listDLRect);

/** Comando fec ~
    Pré-condição: Recebe uma HashTable estabXcnpj, um chave cnpj e os paths de entrada e saida.
    Pós-condição: Os estabelecimentos listados pelo cnpj são fechados, tem seus dados printados em um arquivo texto e não aparecem mais no svg. */
void closeEstab(void *hash, void *hashh, char *cnpj, char *pathEntry, char *pathOut, void *listEstabRect);

/** Comando mud ~
    Pré-condição: Recebe cidade, 3 hashs poepeleXcpf, blockXcep, residentXcep, cpf chave, endereco destino e os paths de entrada e saoda. 
    Pós-condição: Traça uma linha pontilhada no arquivo svg do endereco antigo ate o endereco destino. Reporta a mudança no arquivo texto. */
void mud(void *city, void *hash, void *hashh, void *hashhh, char *cpf, char *cepid, char face, int num, char *compl, char *pathEntry, char *pathOut, void *listP, void *listDLRect);

/** Comando mudec ~
    Pré-condição: Recebe cidade, 3 hashs estabXcnpj, blockXcep, descriptionXcodt, um cnpj que será a chave, o novo endereço, paths de entrada e saida e listas para armazenar informações a serem printadas no svg.
    Pós-condição: Traça uma linha pontilhada no arquivo svg partindo do velho endereço ao novo endereço. Reporta a mudança no arquivo texto.*/
void mudec(void *city, void *hash, void *hashh, void *hashhh, char *cnpj, char *cepid, char face, int num, char *pathEntry, char *pathOut, void *listE, void *listDLRect);

/** Comando dpr ~
    Pré-condição: Recebe todas as estruturas que armazenam dados do programa e os paths de entrada e saida.
    Pós-condição: Desapropria tudo o que estiver dentro do retaângulo passado por parâmetro. */
void dpr(void *city, void *listPeople, void *listEstab, void *blockXcep, void *hydrantXid, void *peopleXcpf, 
        void *residentXcpf, void *residentXcep, void *estabXcep, void *estabXcnpj, void *descriptionXcodt, char *pathEntry, 
        char *pathOut, float x, float y, float w, float h);

#endif
