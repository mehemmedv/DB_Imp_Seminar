#!/bin/bash

for i in 100 1000 10000 100000 100000
do
   for j in 10 30 50 
   do
      ./DB_Generator $i $(($i * $j / 100)) 1000000 # Generate a graph
      
      # Test DFS for unsorted graph
      ./DB_Benchmark -CSR DFS unsorted 200 20 >> result.txt
      ./DB_Benchmark -AL DFS unsorted 200 20 >> result.txt
      ./DB_Benchmark -ALV2 DFS unsorted 200 20 >> result.txt
      
      # Test BFS for unsorted graph
      ./DB_Benchmark -CSR BFS unsorted 200 20 >> result.txt
      ./DB_Benchmark -AL BFS unsorted 200 20 >> result.txt
      ./DB_Benchmark -ALV2 BFS unsorted 200 20 >> result.txt
      
      # Test Dijkstra for unsorted graph
      ./DB_Benchmark -CSR Dijkstra unsorted 200 20 >> result.txt
      ./DB_Benchmark -AL Dijkstra unsorted 200 20 >> result.txt
      ./DB_Benchmark -ALV2 Dijkstra unsorted 200 20 >> result.txt
      
      # Test DFS for sorted graph
      ./DB_Benchmark -CSR DFS sorted 200 20 >> result.txt
      ./DB_Benchmark -AL DFS sorted 200 20 >> result.txt
      ./DB_Benchmark -ALV2 DFS sorted 200 20 >> result.txt
      
      # Test BFS for sorted graph
      ./DB_Benchmark -CSR BFS sorted 200 20 >> result.txt
      ./DB_Benchmark -AL BFS sorted 200 20 >> result.txt
      ./DB_Benchmark -ALV2 BFS sorted 200 20 >> result.txt

      # Test Dijkstra for sorted graph
      ./DB_Benchmark -CSR Dijkstra sorted 200 20 >> result.txt
      ./DB_Benchmark -AL Dijkstra sorted 200 20 >> result.txt
      ./DB_Benchmark -ALV2 Dijkstra sorted 200 20 >> result.txt
      
      # Test DFS for mixed workload
      ./DB_Benchmark -CSR DFS mixed 200 4 >> result.txt
      ./DB_Benchmark -AL DFS mixed 200 4 >> result.txt
      ./DB_Benchmark -ALV2 DFS mixed 200 4 >> result.txt
      
      # Test BFS for mixed workload
      ./DB_Benchmark -CSR BFS mixed 200 4 >> result.txt
      ./DB_Benchmark -AL BFS mixed 200 4 >> result.txt
      ./DB_Benchmark -ALV2 BFS mixed 200 4 >> result.txt
      
      str1="out"$i"_"$j".txt"
      mv out.txt $str1
      str2="result"$i"_"$j".txt"
      mv result.txt $str2
      echo "" > result.txt
      
   done
   
done
