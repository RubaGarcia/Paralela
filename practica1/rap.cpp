#include <pthread.h>
#include <thread>
#include <stdio.h>
#include <cmath>
#include <mutex>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <string.h>

int sumaTotal = 0;
int Nhilos;//numeroHilos
int indiceR=1;

bool ultimoIndiceAtendido = false;
std::mutex g_m;


float time_diff(struct timeval *start, struct timeval *end) ;
void rap(int* array, int* R, int N);


int main(int argc, char *argv[]){
    //toma de parametros y rellenado del array
    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);
    int N = atoi(argv[1]);
    Nhilos = atoi(argv[2]);
    
    srand(time(NULL));

    int* R = (int*)malloc((N-1)*sizeof(int));
    int* array = (int*)malloc(N*sizeof(int));
    //printf("%d\n", N);
    R[0] = 1;
    for(int i = 0; i<N; i++){
        //array[i] = 1;
        array[i] = rand();
    }


    std::thread threads[Nhilos];

    for(auto i = 0; i<Nhilos; i++){
        threads[i] = std::thread(rap,array,R, N);   
    }
    rap(array, R, N);

    for(auto j = 0; j<Nhilos;j++){
        threads[j].join();
    }
    
    gettimeofday(&end, NULL);

    printf("%f, %d, %d\n", time_diff(&start, &end), N, Nhilos);
}

float time_diff(struct timeval *start, struct timeval *end) {
    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}

void rap(int* array, int* R, int N){
    do{
        {
        std::lock_guard<std::mutex>guard(g_m);
        indiceR++;
        //printf("%d\n",indiceR); 
        }
        R[indiceR]=R[indiceR-1] + array[indiceR];
    }while(indiceR < N);
}