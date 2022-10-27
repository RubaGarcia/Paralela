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

std::mutex g_m;


void rap(int* array, int* R, int N){
//fprintf(stdout,"asdjkgchkj\n");
    while(indiceR+1 < N){
        {
        std::lock_guard<std::mutex>guard(g_m);
        R[indiceR]=R[indiceR-1] + array[indiceR];
        indiceR++;
        }
    }
}


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
    
    for(int i = 0; i<N; i++){
        array[i] = 1;
        //array[i] = rand();
    }


    std::thread threads[Nhilos];

    for(auto i = 0; i<Nhilos; i++){
        threads[i] = std::thread(rap,array,R, N);   
    }
    rap(array, R, N);
    

    
    for(auto j = 0; j<Nhilos;j++){
        threads[j].join();
    }
    
    for (int i =0;i<N-1;i++){
    }
    printf("%d\n",R[N-1]);
}

