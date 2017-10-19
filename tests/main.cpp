#include <iostream>
#include "../include/ALGraph.h"
#include "../include/CSRGraph.h"
#include "../src/GraphAlgo.cpp"
#include "../include/ALGraphV2.h"
#include <chrono>

#define CMP_DFS_ENABLED false // compare dfs latencies
#define CMP_BFS_ENABLED false // compare bfs latencies
#define CMP_DIJIKSTRA_ENABLED false // compare dijikstra latencies

std::vector<int> edges;
std::vector<int> weights;

int main(int argc, char** argv) {
    freopen("out.txt", "r", stdin);
    int v, ssize, to, e;
    std::cin>>v>>e;

    GraphAlgo<ALGraph>* algos1 = new GraphAlgo<ALGraph>(v, e);
    GraphAlgo<CSRGraph>* algos2 = new GraphAlgo<CSRGraph>(v, e);
    GraphAlgo<ALGraphV2>* algos3 = new GraphAlgo<ALGraphV2>(v, e);

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
        algos3->add_edge(i + 1, edges, weights);
    }
    algos1->finished();
    algos2->finished();
    algos3->finished();

#if CMP_DFS_ENABLED == true
    auto begin1 = std::chrono::high_resolution_clock::now();
    int sum = 0;
    for(int i = 1; i <= 200; ++i)
        sum += algos1->dfs(i);
    std::cout<<"sum: "<<sum<<std::endl;
    sum = 0;
    auto end = std::chrono::high_resolution_clock::now();
    auto passed1 = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin1);
    //std::cout << "Adjacency list Time: " << passed.count() << std::endl;
    auto begin2 = std::chrono::high_resolution_clock::now();
    for(int i = 1; i <= 200; ++i)
         sum += algos2->dfs(i);
    std::cout<<"sum: "<<sum<<std::endl;
    sum = 0;
    end = std::chrono::high_resolution_clock::now();
    auto passed2 = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin2);
    //std::cout << "CSR Time: " << passed.count() << std::endl;

    auto begin3 = std::chrono::high_resolution_clock::now();
    for(int i = 1; i <= 200; ++i)
        sum += algos3->dfs(i);
    std::cout<<"sum: "<<sum<<std::endl;
    sum = 0;
    end = std::chrono::high_resolution_clock::now();
    auto passed3 = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin3);
    //std::cout << "Adjacency list Time(V2): " << passed.count() << std::endl<<std::endl;

#endif

#if CMP_BFS_ENABLED == true
    begin1 = std::chrono::high_resolution_clock::now();
    for(int i = 1; i <= 200; ++i)
        sum += algos1->bfs(i);
    std::cout<<"sum: "<<sum<<std::endl;
    sum = 0;
    end = std::chrono::high_resolution_clock::now();
    auto passed4 = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin1);
    //std::cout << "Adjacency list Time: " << passed.count() << std::endl;
    begin2 = std::chrono::high_resolution_clock::now();
    for(int i = 1; i <= 200; ++i)
        sum += algos2->bfs(i);
    std::cout<<"sum: "<<sum<<std::endl;
    sum = 0;
    end = std::chrono::high_resolution_clock::now();
    auto passed5 = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin2);
    //std::cout << "CSR Time: " << passed.count() << std::endl;

    begin3 = std::chrono::high_resolution_clock::now();
    for(int i = 1; i <= 200; ++i)
        sum += algos3->bfs(i);
    std::cout<<"sum: "<<sum<<std::endl;
    sum = 0;
    end = std::chrono::high_resolution_clock::now();
    auto passed6 = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin3);
    //std::cout << "Adjacency list Time(V2): " << passed.count() << std::endl<<std::endl;
#endif

#if CMP_DIJIKSTRA_ENABLED == true
    begin1 = std::chrono::high_resolution_clock::now();
    for(int i = 1; i <= 100; ++i)
        algos1->dijkstra(2, i);
    end = std::chrono::high_resolution_clock::now();
    auto passed7 = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin1);
    //std::cout << "Adjacency list Time: " << passed.count() << std::endl;
    begin2 = std::chrono::high_resolution_clock::now();
    for(int i = 1; i <= 100; ++i)
        algos2->dijkstra(2, i);
    end = std::chrono::high_resolution_clock::now();
    auto passed8 = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin2);
    //std::cout << "CSR Time: " << passed.count() << std::endl;

    begin3 = std::chrono::high_resolution_clock::now();
    for(int i = 1; i <= 100; ++i)
        algos3->dijkstra(2, i);
    end = std::chrono::high_resolution_clock::now();
    auto passed9 = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin3);
    //std::cout << "Adjacency list Time(V2): " << passed.count() << std::endl <<std::endl;
#endif

#if CMP_DFS_ENABLED == true
    std::cout << "DFS Adjacency list Time: " << passed1.count() << std::endl;
    std::cout << "DFS Adjacency list Time(V2): " << passed3.count() << std::endl;
    std::cout << "DFS CSR Time: " << passed2.count() << std::endl << std::endl;
#endif

#if CMP_BFS_ENABLED == true
    std::cout << "BFS Adjacency list Time: " << passed4.count() << std::endl;
    std::cout << "BFS Adjacency list Time(V2): " << passed6.count() << std::endl;
    std::cout << "BFS CSR Time: " << passed5.count() << std::endl << std::endl;
#endif

#if CMP_DIJIKSTRA_ENABLED == true
    std::cout << "Dijkstra Adjacency list Time: " << passed7.count() << std::endl;
    std::cout << "Dijkstra Adjacency list Time(V2): " << passed9.count() << std::endl;
    std::cout << "Dijkstra CSR Time: " << passed8.count() << std::endl << std::endl;
#endif

#if VERIFY_ENABLED == true
    std::vector<int> res1 = algos1->bfs(1);
    std::vector<int> res2 = algos2->bfs(1);

    std::cout<<(res1 == res2)<<std::endl;

    std::vector<int> res3 = algos1->dfs(1);
    std::vector<int> res4 = algos2->dfs(1);

    std::cout<<(res3 == res4)<<std::endl;
    std::cout<<(algos1->dijkstra(1, 25) == algos2->dijkstra(1, 25))<<std::endl;

    algos1->add_edge(30, 5, 4);
    algos1->add_edge(30, 6, 10);
    algos2->add_edge(30, 5, 4);
    algos2->add_edge(30, 6, 10);

    std::cout<<(algos1->dijkstra(30, 25) == algos2->dijkstra(30, 25))<<std::endl;
    std::cout<<((algos1->bfs(30)) == algos2->bfs(30))<<std::endl;


#endif

    delete algos1;
    delete algos2;
    delete algos3;

    return 0;
}