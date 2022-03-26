#ifndef SISTEMA_H_INCLUDED
#define SISTEMA_H_INCLUDED
/* ^^ these are the include guards */

/* Prototypes for the functions */
/* Sums two ints */


int trataInput(int argc, char *argv[]);
void iniciaSistema(void);
int requisicao_recursos(int pid);
int libera_recursos(int pid);
void definirRecurso();
void printMatrix();

#endif