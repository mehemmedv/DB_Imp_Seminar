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
#include <functional>

std::vector<uint32_t> edges[1001000];
std::set<uint32_t> temp;


int main(int argc, char **argv) {
    //freopen("prints.txt", "w", stdout);

    srand(time(NULL));

    int sizeee = 156708;
    std::string type = argv[1];
    uint64_t sum = 0;
    auto lambdaFunction = [&sum](uint32_t to, uint32_t weight){
        sum += weight;
    };

    if(type == "CSR") {
        CSRGraphV2 *graph = new CSRGraphV2(200, 31341600);
        for (uint32_t i = 1; i <= sizeee; ++i)
            edges[1].push_back(i);


        for (int i = 1; i <= 200; ++i) {

            // for(uint32_t j = 1; j <= sizeee; ++j){
            //    uint32_t to = j;
            //    edges[i].push_back(to);
            //    graph->add_edge(i, to, j);
            //}
            //
            graph->add_edge(i, edges[1], edges[1]);
        }
        graph->finished();

        auto total_update = 0LL;
        auto begin_update = std::chrono::high_resolution_clock::now();
        uint32_t x, y, cnt = 0;
        for (int i = 1; i <= 2000; ++i) {
            //for (auto &j : graph->get_neighbors((i % 200) + 1))
            //    x = j.first, y = j.second, ++cnt;
            graph->applyAllEdges((i % 200) + 1, lambdaFunction);
        }
        std::cout<<cnt<<std::endl;
        auto end_update = std::chrono::high_resolution_clock::now();
        total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
        std::cout << "Get Neighbors time: " << total_update << std::endl;
    } else if(type == "ART"){
        ARTGraph *graph = new ARTGraph(15678 + 1, 0);

        for (int i = 1; i <= 200; ++i) {
            for(uint32_t j = 1; j <= sizeee; ++j){
                uint32_t to = j;
                //edges[i].push_back(to);
                graph->add_edge(i, to, 100);
            }
        }

        auto total_update = 0LL;
        auto begin_update = std::chrono::high_resolution_clock::now();
        uint32_t x, y, cnt = 0;
        for(int i = 1; i <= 2000;++ i) {
            graph->applyAllEdges((i % 200) + 1, lambdaFunction);
            //std::vector<uint32_t> res;
            //for(auto& j : graph->get_neighbors((i % 200) + 1))
            //    x = j.first, y = j.second, ++cnt;
            //  res.push_back(j.first);

            //std::sort(res.begin(), res.end());
            //std::sort(edges[i].begin(), edges[i].end());

            //if (res != edges[i] && res.size() == sizeee)
            //    std::cout << i << " : Different result " << std::endl;
        }
        std::cout<<cnt<<std::endl;
        auto end_update = std::chrono::high_resolution_clock::now();
        total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
        std::cout << "Get Neighbors time: " << total_update << std::endl;

    }

    else if(type == "ALV2"){
        ALGraphV2 *graph = new ALGraphV2(sizeee, 0);

        for (int i = 1; i <= 200; ++i) {
            for(uint32_t j = 1; j <= sizeee; ++j){
                uint32_t to = j;
                //edges[i].push_back(to);
                graph->add_edge(i, to, 100);
            }
        }

        auto total_update = 0LL;
        auto begin_update = std::chrono::high_resolution_clock::now();
        uint32_t x, y, cnt = 0;
        for(int i = 1; i <= 2000;++ i) {
            graph->applyAllEdges((i % 200) + 1, lambdaFunction);
            //std::vector<uint32_t> res;
            //for(auto& j : graph->get_neighbors((i % 200) + 1))
            //    x = j.first, y = j.second, ++cnt;
            //  res.push_back(j.first);

            //std::sort(res.begin(), res.end());
            //std::sort(edges[i].begin(), edges[i].end());

            //if (res != edges[i] && res.size() == sizeee)
            //    std::cout << i << " : Different result " << std::endl;
        }
        std::cout<<cnt<<std::endl;
        auto end_update = std::chrono::high_resolution_clock::now();
        total_update += (std::chrono::duration_cast<std::chrono::milliseconds>(end_update - begin_update)).count();
        std::cout << "Get Neighbors time: " << total_update << std::endl;

    }
    return 0;
}