#ifndef Rectangle_h
#define Rectangle_h

/** Esse é um módulo que auxilia na criacão e manipulacão de retângulos.
    Um retângulo é definido por um ponto ancora (x, y), uma altura, largura, cor e um identificador.  */

/** Cria um apelido void* para Rectangle.   */
typedef void* Rectangle;

/** Cria um retângulo com id, ponto x,y, altura, largura e cor definidos.
    Retorna um ponteiro para o retângulo.   */
Rectangle createRectangle(int id, float x, float y, float h, float w, char fill[], char stroke[]);

/** Retorna a ID do retângulo.    */
int getRectangleID(Rectangle rect);

/** Retorna o ponto X do retângulo.    */
float getRectangleX(Rectangle rect);

/** Retorna o ponto Y do retângulo.    */
float getRectangleY(Rectangle rect);

/** Retorna a altura do retângulo.    */
float getRectangleH(Rectangle rect);

/** Retorna a largura do retângulo.    */
float getRectangleW(Rectangle rect);

/** Retorna a cor do retângulo.    */
char* getRectangleFill(Rectangle rect);

/** Retorna a cor da borda do retângulo.  */
char* getRectangleStroke(Rectangle rect);

/** Libera o retângulo. */
void freeRectangle(Rectangle rect);

#endif
