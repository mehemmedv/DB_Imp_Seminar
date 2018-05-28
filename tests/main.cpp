#include <iostream>
#include "../include/ALGraph.h"
#include "../include/CSRGraph.h"
#include "../include/GraphAlgo.h"
#include "../include/CSRGraphV2.h"
#include "../include/ARTGraph.h"
#include "../include/ALGraphV2.h"
#include <chrono>
#include <algorithm>
#include <fstream>

//std::vector<uint32_t > edges[1001000];
std::set<uint32_t> temp;

int main(int argc, char** argv) {
    //freopen("prints.txt", "w", stdout);
    srand(time(NULL));

    int sizeee = 156708;
    ARTGraph *graph = new ARTGraph(15678 + 1, 0);

    for (int i = 1; i <= 400; ++i) {
        for(uint32_t j = 1; j <= sizeee; ++j){
            uint32_t to = j;
            //edges[i].push_back(to);
            graph->add_edge(i, to, 100);
        }
    }

    auto total_update = 0LL;
    auto begin_update = std::chrono::high_resolution_clock::now();
    for(int i = 1; i <= 400;++ i) {
        //std::vector<uint32_t> res;
        for(auto& j : graph->get_neighbors(i));
          //  res.push_back(j.first);

        //std::sort(res.begin(), res.end());
        //std::sort(edges[i].begin(), edges[i].end());

        //if (res != edges[i] && res.size() == sizeee)
        //    std::cout << i << " : Different result " << std::endl;
    }
    auto end_update = std::chrono::high_resolution_clock::now();
    total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
    std::cout << "Get Neighbors time: " << total_update << std::endl;

    return 0;
}