//
// Created by mahammad on 10/12/17.
//

#include <iostream>
#include "../include/ALGraph.h"
#include "../include/CSRGraph.h"
#include "../src/GraphAlgo.cpp"
#include "../include/ALGraphV2.h"
#include <chrono>
#include <memory>


#define CMP_DFS_ENABLED true // compare dfs latencies
#define CMP_BFS_ENABLED true // compare bfs latencies
#define CMP_DIJIKSTRA_ENABLED true // compare dijikstra latencies

std::vector<int> edges;
std::vector<int> weights;

int main(int argc, char** argv) {

    std::string str1 = argv[1];
    std::string algo = argv[2];
    std::string sorted = argv[3];

    freopen("out.txt", "r", stdin);
    int v, ssize, to, e;
    std::cin>>v>>e;



    return 0;
}