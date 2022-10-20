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


void rap(){
    
}


int main(int argc, char *argv[]){
    //toma de parametros y rellenado del array
    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);
    int N = atoi(argv[1]);
    Nhilos = atoi(argv[2]);
    srand(time(NULL));

    int* array = (int*)malloc(N*sizeof(int));
    //printf("%d\n", N);
    
    for(int i = 0; i<N; i++){
        array[i] = rand();
    }


    std::thread threads[Nhilos];
    for(auto i = 0;i<Nhilos;i++){
        //threads[i] = std::thread(suma,array,i,N);
    }
    rap();//el propio hilo maestro tiene que hacer el RAP tambien
    for(auto i = 0; i<Nhilos;i++){
        threads[i].join();
    }
}

