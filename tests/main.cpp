#include <iostream>
#include "../include/ALGraph.h"
#include "../include/CSRGraph.h"
#include "../include/GraphAlgo.h"
#include "../include/CSRGraphV2.h"
#include <chrono>

#define CMP_DFS_ENABLED false // compare dfs latencies
#define CMP_BFS_ENABLED false // compare bfs latencies
#define CMP_DIJIKSTRA_ENABLED false // compare dijikstra latencies

std::vector<int> edges;
std::vector<int> weights;

int main(int argc, char** argv) {

    int* t = new int[100];

    memset(t, 0, sizeof(int) * 2);
    std::cout<<t[0] << " " <<t[1] << " " << t[2] << " " << t[90] << std::endl;

    return 0;
}