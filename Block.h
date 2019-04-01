#ifndef Block_h
#define Block_h

/** Esse é o módulo Block, que auxília na criação e manipulação de quadras. 
	Uma quadra tem um ponto (x,y) o qual determina sua posição, altura, largura, cor da borda e preenchimento.	*/

#include <stdio.h>
#include <stdlib.h>

/** Define um apelido Block para void*. */
typedef void* Block;

/**	Pré-condição: A estrutura de cores da quadra já deve ter sido criada.
	Pós-condição: Cria uma quadra com seus dados já definidos. */
Block createBlock(char *cep, float x, float y, float w, float h, char *cstrk, char *cfill);

/**	Pré-condição: A quadra deve existir.
	Pós-condição: Retorna o cep da quadra. */
char* getBlockCep(Block b);

/**	Pré-condição: A quadra deve existir.
	Pós-condição: Retorna o ponto x da quadra. */
float getBlockX(Block b);

/**	Pré-condição: A quadra deve existir.
	Pós-condição: Retorna o ponto y da quadra. */
float getBlockY(Block b);

/**	Pré-condição: A quadra deve existir.
	Pós-condição: Retorna o valor da largura da quadra. */
float getBlockW(Block b);

/**	Pré-condição: A quadra deve existir.
	Pós-condição: Retorna o valor da altura da quadra. */
float getBlockH(Block b);

/** Pré-condição: A quadra deve existir.
	Pós-condição: Retorna a cor da borda da quadra. */
char* getBlockStroke(Block b);

/** Pré-condição: A quadra deve existir.
	Pós-condição: Retorna a cor de preechimento da quadra. */
char* getBlockFill(Block b);

/** Pré-condição: A quadra deve existir.
	Pós-condição: Printa na saída padrão todos os dados da quadra. */
void printBlock(Block b);

/** Pré-condição: A quadra deve existir.
	Pós-condição: Libera a quadra. */
void freeBlock(Block b);

/** Pré-condição: A quadra deve existir.
	Pós-condição: Troca as cores da borda e prenchimento da quadra.  */
void changeBlockColors(Block b, char *stroke, char *fill);

/** Pré-condição: Recebe duas quadras não nulas.
	Pós-condição: Copia a segunda quadra na primeira. */
void copyBlock(Block a, Block b);

/** Pré-condição: Recebe uma quadra e um arquivo como parâmetro.
	Pós-condição: Printa a quadra no arquivo svg passado por parâmetro. */
void printBlockSVG(Block b, FILE *arq);

/** Pré-condição: Recebe uma quadra e um arquivo como parâmetro.
	Pós-condição: Printa a quadra no arquivo txt passado por parâmetro. */
void printBlockTXT(Block b, FILE *arq);

/** Pré-condição: Recebe uma quadra.
	Pós-condição: Duplica  o item. */
Block duplicateBlock(Block b);

/** Pré-condição: Recebe duas quadras.
	Pós-condição: Se elas forem iguais retorna 1, se não retorna 0. */
int equalBlocks(Block a, Block b);

#endif