#include <iostream>
#include "../include/ALGraph.h"
#include "../include/CSRGraph.h"
#include <sys/time.h>
#include "../src/GraphAlgo.cpp"

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

    struct timeval tp1;
    gettimeofday(&tp1, NULL);
    long int ms1 = tp1.tv_sec * 1000 + tp1.tv_usec / 1000;
    std::cout<<"Search started"<<std::endl;
    for(int i = 1; i <= 30; ++i)
        algos1.bfs(i);

    std::cout<<"algo 1 ended"<<std::endl;
    struct timeval tp2;
    gettimeofday(&tp2, NULL);
    long int ms2 = tp2.tv_sec * 1000 + tp2.tv_usec / 1000;

    for(int i = 1; i <= 30; ++i)
        algos2.bfs(i);

    struct timeval tp3;
    gettimeofday(&tp3, NULL);
    long int ms3 = tp3.tv_sec * 1000 + tp3.tv_usec / 1000;


    std::cout<<"CSR TIME: "<<ms3 - ms2<<std::endl<<"Adjacency List:"<<ms2 - ms1<<std::endl;

    return 0;
}