/*No arquivo sistema.c, você irá receber os comandos, criará os threads e aguardará a execução
da simulação até sobrar apenas uma thread. Você pode usar o arquivo .h para a prototipação
das funções necessária em seu programa. */


//importação das bibliotecas necessárias
#include <stdio.h>
#include "sistema.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "processos.h"

int numProcess; //número de processos (inserido pelo usuário)
int* resourceArray; //vetor de recursos (definido pelo usuário)
int numDiversityResources; //número de tipos de recursos diferentes (número de colunas da matriz de alocação)



/* matriz de recurso em que cada linha representa um processo
e cada elemento da linha representa a quantidade de recurso que
esse processo precisa */
int* neededResource; //recursos necessários para que cada processo conclua
int* allocatedResource; // recursis alocados por cada processo
int* freeResource; //recursos livres 


/* função responsável por definir a quantidade de recursos que
cada processo precisa para ser concluido*/
void definirRecurso(){
    srand(time(NULL)); //define uma seed
    neededResource = malloc(sizeof(int)*numProcess*numDiversityResources); //aloca o tamanho do vetor
    allocatedResource = malloc(sizeof(int)*numProcess*numDiversityResources); //aloca o tamanho do vetor
    freeResource = malloc(sizeof(int)*numDiversityResources); //aloca o tamanho do vetor
    
    //loop que define o valor armazenado por cada uma das matrizes
    for (int i = 0; i < numProcess; i ++){
        for (int j = 0; j < numDiversityResources; j++){
            neededResource[i*numDiversityResources+j] = rand()%resourceArray[j];
            allocatedResource[i*numDiversityResources+j] = 0;
            freeResource[j] = resourceArray[j];
        }
    }


}

//função que printa uma matriz de numProcess X resourceArrayDiversity
void printMatrix(int* matrix){
    for (int i = 0; i < numProcess; i ++){
        printf("%d:", i+1);
        for (int j = 0; j < numDiversityResources; j++){
            printf(" %d ", matrix[i*numDiversityResources+j]);
        }
        printf("\n");
    }
    printf("\n");
}


//função que trata os inputs do usuários
int trataInput(int argc, char *argv[]){
    numDiversityResources = argc - 4;
    if(numDiversityResources<=0){ //verifica se o número de argumentos está apropriado
        printf("Ta faltando os recursos\n");
        return 5;
    }
    
    resourceArray = malloc(sizeof(int)*numDiversityResources); //alocação do vetor de recursos

    /*tratando os valores recebidos*/
    int temBarraN = 0, temBarraA = 0;
    for (int i = 1; i < argc; i++) {

        /* se for igual a -n o próximo valor será igual ao numProcess*/
        if (!strcmp(argv[i], "-n")) {
            temBarraN = 1;
            if (atoi(argv[i + 1])) {
                numProcess = atoi(argv[i + 1]);
                i++;  // somamos 1 no i para pular um loop desnecessário
                continue;
            } else {
                printf("Ta maluco? tem que botar o numero de processos depois do -n!\n");
                return 1;
            }
        }

        /*se o valor for igual a -a os próximos tam valores serão o resourceArray*/
        if (!strcmp(argv[i], "-a")) {
            temBarraA = 1;
            for (int j = 0; j < numDiversityResources; j++) {
                if (atoi(argv[i + 1])) {
                    resourceArray[j] = atoi(argv[i + j + 1]);
                    
                } else {
                    printf("Vc colocou alguma coisa errada no numero de recursos\n");
                    return 2;
                }
            }
        }

    }
    if (temBarraA == 0){
        printf("É amigo, tu tem que colocar os recursos\n");
        return 3;
    }
    if (temBarraN == 0){
        printf("É amigo, tu tem que colocar a quantidade de processos\n");
        return 4;

    }
    printf("resourceArray: ");
    for (int i = 0; i < numDiversityResources ; i ++){
        printf(" %d", resourceArray[i]);
    }
    printf("\n");
    printf("numProcess: %d\n", numProcess);

    return 0;
};


//função que vai chamar os processos
void iniciaSistema(){
    
    pthread_t* thread_id = malloc(sizeof(pthread_t)*numProcess); //alocação do vetor de ids do 


    // inicializa o mutex
    int* pids = malloc(sizeof(int)*numProcess);

    printMatrix(neededResource);
    for (int i = 0; i < numProcess; i++) {
        pids[i]= i;

        pthread_create(&thread_id[i], NULL, processo, &pids[i]);
    }

    // da join nas threads
    for (int i = 0; i < numProcess; i++){
        pthread_join(thread_id[i], NULL);
    }
    
    printf("\n\n\n-------Fim do programa-------\n\n\n");

}

