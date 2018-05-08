#include <iostream>
#include "../include/ALGraph.h"
#include "../include/CSRGraph.h"
#include "../include/GraphAlgo.h"
#include "../include/CSRGraphV2.h"
#include "../include/ARTGraph.h"
#include <chrono>
#include <algorithm>
#include <sys/time.h>

#define CMP_DFS_ENABLED false // compare dfs latencies
#define CMP_BFS_ENABLED false // compare bfs latencies
#define CMP_DIJIKSTRA_ENABLED false // compare dijikstra latencies

std::vector<int> edges;

int main(int argc, char** argv) {

    ARTGraph* graph = new ARTGraph(5, 0);
    uint64_t ttime = 0;
    for(int i = 0; i <= 1000000; ++i){
        edges.push_back(i);
        graph->add_edge(1, i, 1);
    }
    std::vector<int> res = graph->get_neighbors(1);

    std::sort(res.begin(), res.end());

    if(res == edges)
        std::cout << "Same result" << std::endl;
    else
        std::cout << "Different result" << std::endl;


    return 0;
}