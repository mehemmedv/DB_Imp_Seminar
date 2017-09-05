//
// Created by mahammad on 8/21/17.
//

#ifndef DB_IMP_SEMINAR_ALGRAPH_H
#define DB_IMP_SEMINAR_ALGRAPH_H

#include <list>
#include <vector>
#include "Graph.h"

// Adjacency list implementation of Graph
class ALGraph : public Graph{
    int v, e;
    std::list<int>* edges;
    std::list<int>::iterator* its;
public:
    ALGraph(int v, int e) : v(v), e(e){
        std::list<int> x;
        edges = new std::list<int>[v + 2];
        its = new std::list<int>::iterator[v + 2];
        for(int i = 0; i <= v; ++i)
            edges[i].clear();
    }

    void add_edge(int v, std::vector<int>& to);

    void finished();

    bool next_neighbor(int v, int& to);

    std::list<int>::iterator begin(int cur_vertex){
        return edges[cur_vertex].begin();
    }

    std::list<int>::iterator end(int cur_vertex){
        return edges[cur_vertex].end();
    }
};


#endif //DB_IMP_SEMINAR_ALGRAPH_H
