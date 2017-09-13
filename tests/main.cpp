#include <iostream>
#include "../include/ALGraph.h"
#include "../include/CSRGraph.h"
#include "../src/GraphAlgo.cpp"
#include <chrono>

std::vector<int> edges;
std::vector<int> weights;

int main() {
    freopen("out.txt", "r", stdin);
    int v, ssize, to, e;
    std::cin>>v>>e;

    GraphAlgo<ALGraph> algos1(v, e);
    GraphAlgo<CSRGraph> algos2(v, e);
    for(int i = 0; i < v; ++i){
        edges.clear();
        weights.clear();
        std::cin>>ssize;
        for(int j = 0; j < ssize; ++j){
            std::cin>>to;
            edges.push_back(to);
        }
        for(int j = 0; j < ssize; ++j){
            std::cin>>to;
            weights.push_back(to);
        }
        algos1.add_edge(i + 1, edges, weights);
        algos2.add_edge(i + 1, edges, weights);
    }
    algos1.finished();
    algos2.finished();

    std::cout<<"Search started"<<std::endl;

    auto begin1 = std::chrono::high_resolution_clock::now();

    //for(int i = 1; i <= 100; ++i)
    //    algos1.dijiksta(1, i);

    std::cout<<algos1.dijiksta(1, 5)<<" "<<algos2.dijiksta(1, 5)<<std::endl;
    algos1.add_edge(1, 10000, 4);
    algos1.add_edge(10000, 5, 10);
    algos2.add_edge(1, 10000, 4);
    algos2.add_edge(10000, 5, 10);

    std::cout<<algos1.dijiksta(1, 5)<<" "<<algos2.dijiksta(1, 5)<<std::endl;


    auto end = std::chrono::high_resolution_clock::now();
    auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin1);
    std::cout << "Adjacency list Time: " << passed.count() << std::endl;
    auto begin2 = std::chrono::high_resolution_clock::now();
    //for(int i = 1; i <= 100; ++i)
    //    algos2.dijiksta(1, i);
    end = std::chrono::high_resolution_clock::now();
    passed = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin2);
    std::cout << "CSR Time: " << passed.count() << std::endl;

    return 0;
}