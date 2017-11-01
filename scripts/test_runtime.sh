#!/bin/bash
# My first script

#sudo mv out.txt out100.txt 

for i in 100 1000 10000 100000 100000
do
   for j in 10 20 30 40
   do
      ./DB_Generator $i $(($i * $j / 100)) 1000000
      ./DB_Benchmark -CSR BFS unsorted 200 20 >> result.txt
      ./DB_Benchmark -AL BFS unsorted 200 20 >> result.txt
      ./DB_Benchmark -ALV2 BFS unsorted 200 20 >> result.txt
      str="out"$i"_"$(($i*$j/100))".txt"
      sudo mv out.txt $str
   done
   
done

#./DB_Benchmark -AL BFS sorted 500 40
