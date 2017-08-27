#include <iostream>
#include "../include/Graph.h"
#include "../include/ALGraph.h"
#include "../include/GraphAlgo.h"
#include "../include/CSRGraph.h"
#include <sys/time.h>
#pragma comment(linker, "/STACK:200000000")
#pragma comment(linker, "/HEAP:200000000")

int main() {
    freopen("out.txt", "r", stdin);
    int v, ssize, to, e;
    std::cin>>v>>e;
    std::vector<int> edges;
    ALGraph* algraph = new ALGraph(v);
    CSRGraph* csrgraph = new CSRGraph(v, e);

    for(int i = 0; i < v; ++i){
        edges.clear();
        std::cin>>ssize;
        for(int j = 0; j < ssize; ++j){
            std::cin>>to;
            edges.push_back(to);
        }
        algraph->add_edge(i + 1, edges);
        csrgraph->add_edge(i + 1, edges);
    }

    algraph->finished();
    csrgraph->finished();
    GraphAlgo algos1(v, algraph);
    GraphAlgo algos2(v, csrgraph);

    struct timeval tp1;
    gettimeofday(&tp1, NULL);
    long int ms1 = tp1.tv_sec * 1000 + tp1.tv_usec / 1000;
    std::cout<<"Search started"<<std::endl;
    for(int i = 1; i <= v; ++i)
        algos1.bfs(i);

    struct timeval tp2;
    gettimeofday(&tp2, NULL);
    long int ms2 = tp2.tv_sec * 1000 + tp2.tv_usec / 1000;

    for(int i = 1; i <= v; ++i)
        algos2.bfs(i);

    struct timeval tp3;
    gettimeofday(&tp3, NULL);
    long int ms3 = tp3.tv_sec * 1000 + tp3.tv_usec / 1000;


    std::cout<<"CSR TIME: "<<ms3 - ms2<<std::endl<<"Adjacency List:"<<ms2 - ms1<<std::endl;

    return 0;
}