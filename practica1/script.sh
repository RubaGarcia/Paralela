#!/bin/bash
g++ -std=c++11 -pthread -o reduccion reduccion.cpp -lm

touch resultados.csv

for  ((i=1; i < 6; i = i + 2))
    do
        for  ((j=1; j < 12; j = j + 2))
            do 
                aux=$(($i*100000000));
                
                
                ./reduccion $aux $j >> resultados.csv
            done
    sleep 1        
    done
