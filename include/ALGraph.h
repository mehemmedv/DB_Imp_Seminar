//
// Created by mahammad on 8/21/17.
//

#ifndef DB_IMP_SEMINAR_ALGRAPH_H
#define DB_IMP_SEMINAR_ALGRAPH_H

#include <list>
#include <vector>

// Adjacency list implementation of Graph
class ALGraph{
    uint64_t v, e;
    std::list<uint64_t>* edges;
    std::list<uint64_t>* weights;

public:
    ALGraph(uint64_t v, uint64_t e) : v(v), e(e){
        edges = new std::list<uint64_t>[v + 2];
        weights = new std::list<uint64_t>[v + 2];
        for(int i = 0; i <= v; ++i)
            edges[i].clear(), weights[i].clear();
    }

    ~ALGraph(){
        for(int i = 0; i <= v; ++i)
            edges[i].clear(), weights[i].clear();
        delete[] edges;
        delete[] weights;
        //std::cout<<"ALGraph delete"<<std::endl;
    }

    void add_edge(int from, std::vector<int>& to, std::vector<int>& w);

    void add_edge(int from, int to, int weight = 0);

    void finished();

    void sortByEdgesByNodeId();

    inline std::list<int>::iterator begin(int cur_vertex) {
        return edges[cur_vertex].begin();
    }

    inline std::list<uint64_t>::iterator end(int cur_vertex){
        return edges[cur_vertex].end();
    }

    inline std::list<uint64_t>::iterator begin_weights(int cur_vertex) {
        return weights[cur_vertex].begin();
    }
};


#endif //DB_IMP_SEMINAR_ALGRAPH_H
