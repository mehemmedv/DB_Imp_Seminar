#!/bin/bash

for i in 100 1000 10000 100000 100000
do
   for j in 10 20 30 40
   do
      ./DB_Generator $i $(($i * $j / 100)) 1000000
      ./DB_Benchmark -CSR DFS unsorted 200 20 >> result.txt
      ./DB_Benchmark -AL BFS unsorted 200 20 >> result.txt
      ./DB_Benchmark -ALV2 Dijkstra unsorted 200 20 >> result.txt
      ./DB_Benchmark -CSR DFS sorted 200 20 >> result.txt
      ./DB_Benchmark -AL BFS sorted 200 20 >> result.txt
      ./DB_Benchmark -ALV2 Dijkstra sorted 200 20 >> result.txt
      ./DB_Benchmark -CSR DFS sorted 200 5 >> result.txt
      ./DB_Benchmark -AL BFS sorted 200 5 >> result.txt
      ./DB_Benchmark -ALV2 Dijkstra sorted 200 5 >> result.txt
      str="out"$i"_"$(($i*$j/100))".txt"
      mv out.txt $str
   done
   
done
