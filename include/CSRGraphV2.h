//
// Created by mahammad on 12/5/17.
//

#ifndef DB_IMP_SEMINAR_CSRGRAPHV2_H
#define DB_IMP_SEMINAR_CSRGRAPHV2_H


#include <vector>
#include <iostream>

// 'Compressed sparse row' implementation of Graph
class CSRGraphV2 {
    int *edges, *offsets;
    int* weights;
    uint64_t cur_idx, v, e;
    uint64_t additional_space = 100;
    uint64_t current_size = 0;

public:
    CSRGraphV2(uint64_t v, uint64_t e) : v(v), e(e) {
        current_size = e + additional_space;
        edges = new int[current_size];
        offsets = new int[v + 2];
        cur_idx = 0;
        weights = new int[current_size];
    }

    ~CSRGraphV2(){
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

#endif //DB_IMP_SEMINAR_CSRGRAPHV2_H
