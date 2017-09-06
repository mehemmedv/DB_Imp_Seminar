#include <iostream>
#include "../include/ALGraph.h"
#include "../include/CSRGraph.h"
#include "../src/GraphAlgo.cpp"
#include <chrono>

int main() {
    freopen("out.txt", "r", stdin);
    int v, ssize, to, e;
    std::cin>>v>>e;
    std::vector<int> edges;

    GraphAlgo<ALGraph> algos1(v, e);
    GraphAlgo<CSRGraph> algos2(v, e);
    for(int i = 0; i < v; ++i){
        edges.clear();
        std::cin>>ssize;
        for(int j = 0; j < ssize; ++j){
            std::cin>>to;
            edges.push_back(to);
        }
        algos1.add_edge(i + 1, edges);
        algos2.add_edge(i + 1, edges);
    }

    algos1.finished();
    algos2.finished();

    std::cout<<"Search started"<<std::endl;

    auto begin1 = std::chrono::high_resolution_clock::now();

    for(int i = 1; i <= 40; ++i)
        algos1.bfs(i);

    auto end = std::chrono::high_resolution_clock::now();
    auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin1);
    std::cout << "Adjacency list Time: " << passed.count() << std::endl;
    auto begin2 = std::chrono::high_resolution_clock::now();
    for(int i = 1; i <= 40; ++i)
        algos2.bfs(i);
    end = std::chrono::high_resolution_clock::now();
    passed = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin2);
    std::cout << "CSR Time: " << passed.count() << std::endl;

    return 0;
}