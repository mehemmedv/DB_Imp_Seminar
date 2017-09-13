//
// Created by mahammad on 8/21/17.
//

#ifndef DB_IMP_SEMINAR_CSRGRAPH_H
#define DB_IMP_SEMINAR_CSRGRAPH_H

#include <vector>

// 'Compressed sparse row' implementation of Graph
class CSRGraph {
    int *edges, *offsets;
    int* weights;
    int *delta_edge_1, *delta_edge_2;
    int *delta_w_1, *delta_w_2;
    int cur_idx, v, e;
    bool even; // true if number of new edge is even

public:
    CSRGraph(int v, int e) : v(v), e(e) {
        delta_edge_1 = new int[e];
        edges = delta_edge_1;
        offsets = new int[v + 2];
        cur_idx = 0;
        delta_w_1 = new int[e];
        weights = delta_w_1;
        even = true; // there is 0 new edge so far
    }

    void add_edge(int from, std::vector<int> &to, std::vector<int>& w);

    void add_edge(int from, int to, int weight = 0);

    void finished();

    int* begin(int cur_vertex);

    int* end(int cur_vertex);

    int* begin_weights(int cur_vertex);
};


#endif //DB_IMP_SEMINAR_CSRGRAPH_H
