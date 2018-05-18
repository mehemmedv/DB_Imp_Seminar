#include <iostream>
#include "../include/ALGraph.h"
#include "../include/CSRGraph.h"
#include "../include/GraphAlgo.h"
#include "../include/CSRGraphV2.h"
#include "../include/ARTGraph.h"
#include "../include/ALGraphV2.h"
#include <chrono>
#include <algorithm>
#include <sys/time.h>

#define CMP_DFS_ENABLED false // compare dfs latencies
#define CMP_BFS_ENABLED false // compare bfs latencies
#define CMP_DIJIKSTRA_ENABLED false // compare dijikstra latencies

//std::vector<uint32_t > edges[1001000];

int main(int argc, char** argv) {

    srand(time(NULL));

    std::string type = argv[1];
    if(type == "ART"){
        ARTGraph* graph = new ARTGraph(15678 + 1, 0);

        for(int i = 1; i <= 15678; ++i)
            for(uint32_t j = 1; j <= 15678; ++j){
                //uint32_t to = ((rand() % 10007) * (rand() % 10007)) % 10000000;
                uint32_t to = j;
                //edges[i].push_back(to);
                graph->add_edge(i, to, 100);
            }

        auto total_update = 0LL;
        auto begin_update = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= 15678;++ i) {
            //std::vector<uint32_t> res;
            for(uint32_t j : graph->get_neighbors(i));
                //res.push_back(j);
            /*
            std::sort(res.begin(), res.end());
            std::sort(edges[i].begin(), edges[i].end());

            if (res != edges[i])
                std::cout << i << " : Different result " << std::endl;
            */
        }
        auto end_update = std::chrono::high_resolution_clock::now();
        total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
        std::cout << type << " Get Neighbors time: " << total_update << std::endl;
    } else if(type == "CSRV2"){
        CSRGraphV2* graph = new CSRGraphV2(15678 + 1, 0);

        for(int i = 1; i <= 15678; ++i)
            for(uint32_t j = 1; j <= 15678; ++j){
                //uint32_t to = ((rand() % 10007) * (rand() % 10007)) % 10000000;
                uint32_t to = j;
                //edges[i].push_back(to);
                graph->add_edge(i, to, 100);
            }

        auto total_update = 0LL;
        auto begin_update = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= 15678;++ i) {
            //std::vector<uint32_t> res;
            for(uint32_t j : graph->get_neighbors(i));
            //res.push_back(j);
            /*
            std::sort(res.begin(), res.end());
            std::sort(edges[i].begin(), edges[i].end());

            if (res != edges[i])
                std::cout << i << " : Different result " << std::endl;
            */
        }
        auto end_update = std::chrono::high_resolution_clock::now();
        total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
        std::cout << type << " Get Neighbors time: " << total_update << std::endl;
    } else if(type == "ALV2"){
        ALGraphV2* graph = new ALGraphV2(15678 + 1, 0);

        for(int i = 1; i <= 15678; ++i)
            for(uint32_t j = 1; j <= 15678; ++j){
                //uint32_t to = ((rand() % 10007) * (rand() % 10007)) % 10000000;
                uint32_t to = j;
                //edges[i].push_back(to);
                graph->add_edge(i, to, 100);
            }

        auto total_update = 0LL;
        auto begin_update = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= 15678;++ i) {
            //std::vector<uint32_t> res;
            for(uint32_t j : graph->get_neighbors(i));
            //res.push_back(j);
            /*
            std::sort(res.begin(), res.end());
            std::sort(edges[i].begin(), edges[i].end());

            if (res != edges[i])
                std::cout << i << " : Different result " << std::endl;
            */
        }
        auto end_update = std::chrono::high_resolution_clock::now();
        total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
        std::cout << type << " Get Neighbors time: " << total_update << std::endl;
    } else if(type == "AL"){
        ALGraph* graph = new ALGraph(15678 + 1, 0);

        for(int i = 1; i <= 15678; ++i)
            for(uint32_t j = 1; j <= 15678; ++j){
                //uint32_t to = ((rand() % 10007) * (rand() % 10007)) % 10000000;
                uint32_t to = j;
                //edges[i].push_back(to);
                graph->add_edge(i, to, 100);
            }

        auto total_update = 0LL;
        auto begin_update = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= 15678;++ i) {
            //std::vector<uint32_t> res;
            for(uint32_t j : graph->get_neighbors(i));
            //res.push_back(j);
            /*
            std::sort(res.begin(), res.end());
            std::sort(edges[i].begin(), edges[i].end());

            if (res != edges[i])
                std::cout << i << " : Different result " << std::endl;
            */
        }
        auto end_update = std::chrono::high_resolution_clock::now();
        total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
        std::cout << type << " Get Neighbors time: " << total_update << std::endl;
    }
    return 0;
}