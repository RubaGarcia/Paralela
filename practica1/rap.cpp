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

/**
 * este metodo es menos óptimo que una mierda
 * TODO
*/
void rap(int* array, int* R, int i){
    for(int j = 0;j<i;j++){
        R[i]+=array[j];
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
    
    for(int j = 0; j<N; j++){
        array[j] = rand();
    }


    std::thread threads[Nhilos];
    for(auto j = 0;j<(N-1);j++){
        threads[j] = std::thread(rap,array,R,j);
    }

    //rap();//el propio hilo maestro tiene que hacer el RAP tambien
    for(auto j = 0; j<Nhilos;j++){
        threads[j].join();
    }
    for (int i =0;i<N-1;i++){
        printf("%d",R[i]);
    }
}

