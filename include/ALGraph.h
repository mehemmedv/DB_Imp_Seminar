//
// Created by mahammad on 8/21/17.
//

#ifndef DB_IMP_SEMINAR_ALGRAPH_H
#define DB_IMP_SEMINAR_ALGRAPH_H

#include <Graph.h>
#include <list>
#include <vector>

// Adjacency list implementation of Graph
class ALGraph : public Graph{
    int v;
    std::list<int>* edges;
    std::list<int>::iterator* its;
public:
    ALGraph(int v) : v(v){
        std::list<int> x;

        edges = new list<int>[v + 2];
        its = new std::list<int>::iterator[v + 2];
        for(int i = 0; i <= v; ++i)
            edges[i].clear();
    }

    void add_edge(int v, std::vector<int>& to);

    void finished();

    bool next_neighbor(int v, int& to);
};


#endif //DB_IMP_SEMINAR_ALGRAPH_H
