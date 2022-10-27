#!/bin/bash
g++ -std=c++11 -pthread -o reduccion_2 reduccion_2.cpp -lm

touch resultados.csv

for  ((i=1; i < 6; i = i + 1))
    do
        for  ((j=1; j < 17; j = j + 1))
            do 
                aux=$(($i*100000000));
                #aux=$(1000000);
                
                ./reduccion_2 $aux $j >> resultados.csv
 
            done
        sleep 1    
    done
