#ifndef Circle_h
#define Circle_h

/** Esse é o módulo que auxilia na criacão e manipulacão de círculos.
    Um círculo é definido por um ponto ancora (x,y), com raio, cor de preenchimento e um identificador.*/

/** Cria um apelido void* para Circle.  */
typedef void* Circle;

/** Cria um círculo com id, ponto(x, y), raio e cor.
    Retorna um ponteiro para o círculo.   */
Circle createCircle(int id, float x, float y, float r, char fill[], char stroke[]);

/** Retorna a ID do círculo.  */
int getCircleID(Circle circ);

/** Retorna o ponto X do círculo.  */
float getCircleX(Circle circ);

/** Retorna o ponto Y do círculo.  */
float getCircleY(Circle circ);

/** Retorna o raio do círculo.  */
float getCircleR(Circle circ);

/** Retorna cor do círculo.  */
char* getCircleFill(Circle circ);

/** Retorna cor da borda do círculo.  */
char* getCircleStroke(Circle circ);

/** Libera o círculo. */
void freeCircle(Circle circ);

#endif
