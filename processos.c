/*No arquivo processos.c terá uma função que simule um processo que pode ser usado como a
rotina inicial de uma thread. */

#include <stdio.h>
#include "processos.h"
#include "sistema.h"
#include "banqueiro.h"
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define tempo 5 //constante de tempo dos processos (entre requisitar e liberar ele aguarda um número aleatório entre 0 e "tempo" segundos )

//importação das varíaveis globais necessárias
extern int* neededResource;
extern int numProcess;

//thread de cada processo
void* processo(void* pid) {
    int* mypid = pid;
    
    //loop de cada processo
    while (1) {


        requisicao_recursos(*mypid);

        sleep(rand() % tempo + 1); // aguarda um tempo aleatório entre 0 e 5 segundos
        
        if(libera_recursos(*mypid)==0){
            break;
        }

        sleep(rand() % tempo + 1); // aguarda um tempo aleatório entre 0 e 5 segundos

    }
    
}

/*
while(true){
    Requer algum recurso menor que(máximo – alocado)
    Dorme por um tempo randômico
    Libera um subconjunto de recursos alocados
    Dorme um tempo randômico
}
*/