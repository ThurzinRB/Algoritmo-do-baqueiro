/*
Trabalho final de Sistemas Operacionais.
 - Arthur Reis Bello - 11811EMT009
 - Erick Tomaz Oliveira 11911EMT020
 - Eduardo Apolinario Lopes – 11621EMT005
 - Rayssa Alves Guimarães - 11621EMT015

*/

/*No arquivo banqueiro.c deverá fornecer a implementação das funções requisicao_recursos( )
e liberaçao_recursos( ), que empregados pelo algoritmo do banqueiro permite determinar se o 2
resultado da requisição é segura ou insegura. No entanto, deve-se observar que os threads
podem chamar as funções simultâneas e torna-se necessário a implementação de estratégias
de sincronização (algoritmo de sincronização). */


//importação das bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "processos.h"
#include "sistema.h"
#include "banqueiro.h"

//importando varíaveis globais dos outros códigos
extern int numProcess;          
extern int* resourceArray;  
extern int numDiversityResources;
extern int* neededResource; 

extern int* allocatedResource;
extern int* freeResource;


pthread_mutex_t lock; //variáveis responsável pela sincronização!


//função que define se o processo receberá ou não os recursos necessários
int requisicao_recursos(int pid){
    pthread_mutex_lock(&lock); //impede que outros processos executem a mesma função ao mesmo tempo

    //definição dos créditos
    int* credit = malloc(numDiversityResources*sizeof(int));

    //definição do vetor de recursos liberados
    int* given = malloc(numDiversityResources*sizeof(int));;
    
    printf("\n------------------------\n");
    
    printf("Processo %d pede recursos\n", pid+1);
    printf("------------------------\n");
    printf("Necessário:\n");
    printMatrix(neededResource);

    //gera os créditos aleatoriamente 
    for(int i = 0; i < numDiversityResources; i++){
        if (freeResource[i] == 0){
            credit[i] = 0;
        }else{
            credit[i] = rand() % freeResource[i] + 1;

        }

    }

    printf("Credito: \n");
    
    //limita o valor liberado com base nos créditos
    for(int i = 0; i < numDiversityResources; i++){
        int index = pid*numDiversityResources + i;
        
        if(neededResource[index] - allocatedResource[index]>credit[i]){
            given[i]=credit[i];
        }else{
            given[i] = neededResource[index] - allocatedResource[index];
        }
        printf(" %d ", given[i]);

    }

    printf("\n\n");

    printf("Recursos livres (antes): \n");
    for(int i = 0; i < numDiversityResources; i++){
        printf(" %d ", freeResource[i]);
    }

    printf("\n\n");


    int inseguro = 0; //flag que marca se permitir que o processo aloque recursos deixará o sistema inseguro
    for (int j = 0; j < numDiversityResources; j++){
        int index = pid*numDiversityResources + j;

        if(neededResource[index] - allocatedResource[index] > freeResource[j]  ){//condição para ser inseguro
                    inseguro++;
                    break;           
        }     
    }

    if(inseguro != 0){ 
        printf("---> ESTADO INSEGURO\n");
    }else{
        printf("---> ESTADO SEGURO\n");

        //se o estado for seguro aloca os recursos
        for(int j = 0; j < numDiversityResources; j++){
            int index = pid*numDiversityResources + j;
            allocatedResource[index] += given[j];
            freeResource[j] = resourceArray[j] - allocatedResource[index];
        }
    }
    printf("\n");
    printf("Recurso livre (depois): \n");

    for(int i = 0; i < numDiversityResources; i++){
        printf(" %d ", freeResource[i]);
    }

    printf("\n\n");
    printf("Matriz de recursos alocados: \n");
    printMatrix(allocatedResource);

    pthread_mutex_unlock(&lock);  //libera a função para utilização de outros processos
    
    return 0;
}

//libera os recursos após um tempo alocado
int libera_recursos(int pid){
    pthread_mutex_lock(&lock); //impede que outros processos executem a mesma função ao mesmo tempo
    int isDone = 1; //flag responsável por guardar o estado da verificação se o processo terminou

    //o processo só termina se ele tiver alocado todos os recursos que ele precisa para isso
    //o loop verifica se a matriz de alocação é igual à matriz de recursos necessários inicialmente para a linha do processo
    for(int i = 0; i < numDiversityResources; i++){
        int index = pid*numDiversityResources + i;
        if(neededResource[index] != allocatedResource[index]){
            isDone = 0;
            break;
        }
    }

    if(isDone == 1){
        printf("===============================\n\n");
        printf("     Processo: %d terminou.     \n\n", pid+1);
        printf("===============================\n\n");

        //loop que de fato desaloca os recursos após a conclusão do processo
        for (int i = 0; i< numDiversityResources ; i++){

            int index = pid*numDiversityResources + i;
            freeResource[i] += allocatedResource[index];
            allocatedResource[index] = 0;
    

        }

        pthread_mutex_unlock(&lock); //libera a função para utilização de outros processos
        return 0; //liberou recurso sem erro
    }else{
        pthread_mutex_unlock(&lock); //libera a função para utilização de outros processos
        return 1; //ainda nao alocou o que precisa pra terminar
    }
    pthread_mutex_unlock(&lock); //libera a função para utilização de outros processos
    return 1;

}



int main(int argc, char *argv[]){
    if (pthread_mutex_init(&lock, NULL) != 0){ // inicia o mutex que sincroniza os processos
        printf("\n mutex init failed\n");
        return 1;
    }

    /* --- Início do setup ---*/
    if(trataInput(argc, argv)){//função que irá tratar os inputs do usuário
        printf("erro\n");
        return 1;
    }

    definirRecurso(); //define os recursos de cada processo
    iniciaSistema(); 

    return 0;
}

