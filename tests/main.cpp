#include <iostream>
#include "../include/ALGraph.h"
#include "../include/CSRGraph.h"
#include "../src/GraphAlgo.cpp"
#include <chrono>

#define CMP_DFS_ENABLED true // compare dfs latencies
#define CMP_BFS_ENABLED true // compare bfs latencies
#define CMP_DIJIKSTRA_ENABLED true // compare dijikstra latencies

std::vector<int> edges;
std::vector<int> weights;

int main() {
    freopen("out.txt", "r", stdin);
    int v, ssize, to, e;
    std::cin>>v>>e;

    GraphAlgo<ALGraph>* algos1 = new GraphAlgo<ALGraph>(v, e);
    GraphAlgo<CSRGraph>* algos2 = new GraphAlgo<CSRGraph>(v, e);
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
        algos1->add_edge(i + 1, edges, weights);
        algos2->add_edge(i + 1, edges, weights);
    }
    algos1->finished();
    algos2->finished();

#if CMP_DFS_ENABLED == true
    auto begin1 = std::chrono::high_resolution_clock::now();
    for(int i = 1; i <= 200; ++i)
        algos1->dfs(i);
    auto end = std::chrono::high_resolution_clock::now();
    auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin1);
    std::cout << "Adjacency list Time: " << passed.count() << std::endl;
    auto begin2 = std::chrono::high_resolution_clock::now();
    for(int i = 1; i <= 200; ++i)
        algos2->dfs(i);
    end = std::chrono::high_resolution_clock::now();
    passed = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin2);
    std::cout << "CSR Time: " << passed.count() << std::endl;
#endif

#if CMP_BFS_ENABLED == true
    begin1 = std::chrono::high_resolution_clock::now();
    for(int i = 1; i <= 200; ++i)
        algos1->bfs(i);
    end = std::chrono::high_resolution_clock::now();
    passed = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin1);
    std::cout << "Adjacency list Time: " << passed.count() << std::endl;
    begin2 = std::chrono::high_resolution_clock::now();
    for(int i = 1; i <= 200; ++i)
        algos2->bfs(i);
    end = std::chrono::high_resolution_clock::now();
    passed = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin2);
    std::cout << "CSR Time: " << passed.count() << std::endl;
#endif

#if CMP_DIJIKSTRA_ENABLED == true
    begin1 = std::chrono::high_resolution_clock::now();
    for(int i = 1; i <= 100; ++i)
        algos1->dijkstra(2, i);
    end = std::chrono::high_resolution_clock::now();
    passed = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin1);
    std::cout << "Adjacency list Time: " << passed.count() << std::endl;
    begin2 = std::chrono::high_resolution_clock::now();
    for(int i = 1; i <= 100; ++i)
        algos2->dijkstra(2, i);
    end = std::chrono::high_resolution_clock::now();
    passed = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin2);
    std::cout << "CSR Time: " << passed.count() << std::endl;
#endif


#if VERIFY_ENABLED == true
    std::vector<int> res1 = algos1.bfs(2);
    std::vector<int> res2 = algos2.bfs(2);

    std::cout<<(res1 == res2)<<std::endl;

    std::vector<int> res3 = algos1.dfs(2);
    std::vector<int> res4 = algos2.dfs(2);

    std::cout<<(res3 == res4)<<std::endl;
    std::cout<<(algos1.dijiksta(1, 1000) == algos2.dijiksta(1, 1000))<<std::endl;

    algos1.add_edge(1, 10000, 4);
    algos1.add_edge(10000, 1000, 10);
    algos2.add_edge(1, 10000, 4);
    algos2.add_edge(10000, 1000, 10);

    std::cout<<(algos1.dijiksta(1, 1000) == algos2.dijiksta(1, 1000))<<std::endl;
#endif

    delete algos1;
    delete algos2;

    return 0;
}