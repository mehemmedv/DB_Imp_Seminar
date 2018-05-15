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

std::vector<uint32_t > edges[1001000];

int main(int argc, char** argv) {

    srand(time(NULL));

    ARTGraph* graph = new ARTGraph(5, 0);
    for(int i = 1; i <= 1000; ++i)
        for(uint32_t j = 1; j <= 40000; ++j){
            uint32_t to = ((rand() % 10007) * (rand() % 10007)) % 10000000;
            edges[i].push_back(to);
            graph->add_edge(i, to, 100);
        }

    for(int i = 1; i <= 1000;++ i) {
        std::vector<uint32_t> res = graph->get_neighbors(i);

        std::sort(res.begin(), res.end());
        std::sort(edges[i].begin(), edges[i].end());

        if (res != edges[i])
            std::cout << i << " : Different result " << std::endl;
    }


    return 0;
}