//
// Created by mahammad on 8/21/17.
//

#ifndef DB_IMP_SEMINAR_CSRGRAPH_H
#define DB_IMP_SEMINAR_CSRGRAPH_H

#include <vector>
#include <iostream>

// 'Compressed sparse row' implementation of Graph
class CSRGraph {
    uint64_t *edges, *offsets;
    uint64_t* weights;
    uint64_t *delta_e;
    uint64_t *delta_w;
    int cur_idx, v, e;

public:
    CSRGraph(int v, int e) : v(v), e(e) {
        edges = new uint64_t[e];
        offsets = new uint64_t[v + 2];
        cur_idx = 0;
        weights = new uint64_t[e];
    }

    ~CSRGraph(){
        delete[] edges;
        delete[] offsets;
        delete[] weights;
        std::cout<<"CSRGraph delete"<<std::endl;
    }

    void add_edge(int from, std::vector<int> &to, std::vector<int>& w);

    void add_edge(int from, int to, int weight = 0);

    void finished();

    void sortByEdgesByNodeId();

    inline uint64_t* begin(int cur_vertex){
        return &(edges[offsets[cur_vertex]]);
    }

    inline uint64_t* end(int cur_vertex){
        return &(edges[offsets[cur_vertex + 1]]);
    }

    inline uint64_t* begin_weights(int cur_vertex){
        return &(weights[offsets[cur_vertex]]);
    }
};


#endif //DB_IMP_SEMINAR_CSRGRAPH_H
