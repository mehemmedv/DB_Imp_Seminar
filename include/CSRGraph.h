//
// Created by mahammad on 8/21/17.
//

#ifndef DB_IMP_SEMINAR_CSRGRAPH_H
#define DB_IMP_SEMINAR_CSRGRAPH_H

#include <vector>
#include <iostream>

// 'Compressed sparse row' implementation of Graph
class CSRGraph {
    int *edges, *offsets;
    int* weights;
    int *delta_e;
    int *delta_w;
    uint64_t cur_idx, v, e;

public:
    CSRGraph(uint64_t v, uint64_t e) : v(v), e(e) {
        edges = new int[e];
        offsets = new int[v + 2];
        cur_idx = 0;
        weights = new int[e];
    }

    ~CSRGraph(){
        delete[] edges;
        delete[] offsets;
        delete[] weights;
        //std::cout<<"CSRGraph delete"<<std::endl;
    }

    void add_edge(int from, std::vector<int> &to, std::vector<int>& w);

    void add_edge(int from, int to, int weight = 0);

    void finished();

    void sortByEdgesByNodeId();

    inline int* begin(int cur_vertex){
        return &(edges[offsets[cur_vertex]]);
    }

    inline int* end(int cur_vertex){
        return &(edges[offsets[cur_vertex + 1]]);
    }

    inline int* begin_weights(int cur_vertex){
        return &(weights[offsets[cur_vertex]]);
    }
};


#endif //DB_IMP_SEMINAR_CSRGRAPH_H
