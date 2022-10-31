#!/bin/bash
g++ -std=c++11 -pthread -o reduccion_2 reduccion_2.cpp -lm

touch resultados.csv

for  ((j=1; j < 17; j = j + 1))
    do 
                
        ./reduccion_2 1000000 $j >> resultados.csv
        sleep 1
    done
            
