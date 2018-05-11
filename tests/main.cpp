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

std::vector<uint32_t > edges;

int main(int argc, char** argv) {

    srand(time(NULL));

    ARTGraph* graph = new ARTGraph(5, 0);

    for(uint32_t j = 1; j <= 10; ++j){
        edges.push_back(j);
        graph->add_edge(1, j, 100);
    }

    std::vector<uint32_t > res = graph->get_neighbors(1);

    std::sort(res.begin(), res.end());
    std::sort(edges.begin(), edges.end());
    //std::cout<<i<<" : ";
    for(int j : res)
        std::cout<<j<<" ";
    std::cout<<std::endl;
    if(res != edges)
        std::cout << 1 << " : Different result "<< std::endl;



    return 0;
}