//
// Created by mahammad on 13.10.2017.
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

int main(int argc, char **argv) {

    std::string type = argv[1];
    std::string algo_type = argv[2];
    std::string sorted = argv[3];

    freopen("out.txt", "r", stdin);
    int v, ssize, to, e;
    std::cin >> v >> e;

    if (type == "-CSR") { // CSR
        auto algo = new GraphAlgo<CSRGraph>(v, e);

        for (int i = 0; i < v; ++i) {
            edges.clear();
            weights.clear();
            std::cin >> ssize;
            for (int j = 0; j < ssize; ++j) {
                std::cin >> to;
                edges.push_back(to);
            }
            for (int j = 0; j < ssize; ++j) {
                std::cin >> to;
                weights.push_back(to);
            }
            algo->add_edge(i + 1, edges, weights);
        }
        algo->finished();

        if (algo_type == "DFS") {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            for(int i = 1; i <= 200; ++i)
                sum += algo->dfs(i);
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
            std::cout<<"sum: "<<sum<<std::endl;
            std::cout<<"CSR Graph DFS time: "<<passed.count()<<std::endl;
        } else if (algo_type == "BFS") {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            for(int i = 1; i <= 200; ++i)
                sum += algo->bfs(i);
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
            std::cout<<"sum: "<<sum<<std::endl;
            std::cout<<"CSR Graph BFS time: "<<passed.count()<<std::endl;
        } else {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            for(int i = 1; i <= 200; ++i)
                sum += algo->dijkstra(1, i);
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
            std::cout<<"sum: "<<sum<<std::endl;
            std::cout<<"CSR Graph Dijkstra time: "<<passed.count()<<std::endl;
        }
        delete algo;
    } else if (type == "-AL") { // ALGraph
        auto algo = new GraphAlgo<ALGraph>(v, e);

        for (int i = 0; i < v; ++i) {
            edges.clear();
            weights.clear();
            std::cin >> ssize;
            for (int j = 0; j < ssize; ++j) {
                std::cin >> to;
                edges.push_back(to);
            }
            for (int j = 0; j < ssize; ++j) {
                std::cin >> to;
                weights.push_back(to);
            }
            algo->add_edge(i + 1, edges, weights);
        }
        algo->finished();

        if (algo_type == "DFS") {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            for(int i = 1; i <= 200; ++i)
                sum += algo->dfs(i);
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
            std::cout<<"sum: "<<sum<<std::endl;
            std::cout<<"AL Graph DFS time: "<<passed.count()<<std::endl;
        } else if (algo_type == "BFS") {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            for(int i = 1; i <= 200; ++i)
                sum += algo->bfs(i);
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
            std::cout<<"sum: "<<sum<<std::endl;
            std::cout<<"AL Graph BFS time: "<<passed.count()<<std::endl;
        } else {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            for(int i = 1; i <= 200; ++i)
                sum += algo->dijkstra(1, i);
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
            std::cout<<"sum: "<<sum<<std::endl;
            std::cout<<"AL Graph Dijkstra time: "<<passed.count()<<std::endl;
        }

        delete algo;
    } else { // ALGraphV2
        auto algo = new GraphAlgo<ALGraphV2>(v, e);

        for (int i = 0; i < v; ++i) {
            edges.clear();
            weights.clear();
            std::cin >> ssize;
            for (int j = 0; j < ssize; ++j) {
                std::cin >> to;
                edges.push_back(to);
            }
            for (int j = 0; j < ssize; ++j) {
                std::cin >> to;
                weights.push_back(to);
            }
            algo->add_edge(i + 1, edges, weights);
        }
        algo->finished();

        if (algo_type == "DFS") {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            for(int i = 1; i <= 200; ++i)
                sum += algo->dfs(i);
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
            std::cout<<"sum: "<<sum<<std::endl;
            std::cout<<"ALV2 Graph DFS time: "<<passed.count()<<std::endl;
        } else if (algo_type == "BFS") {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            for(int i = 1; i <= 200; ++i)
                sum += algo->bfs(i);
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
            std::cout<<"sum: "<<sum<<std::endl;
            std::cout<<"ALV2 Graph BFS time: "<<passed.count()<<std::endl;
        } else {
            int sum = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            for(int i = 1; i <= 200; ++i)
                sum += algo->dijkstra(1, i);
            auto end = std::chrono::high_resolution_clock::now();
            auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
            std::cout<<"sum: "<<sum<<std::endl;
            std::cout<<"ALV2 Graph Dijkstra time: "<<passed.count()<<std::endl;
        }

        delete algo;
    }

    return 0;
}