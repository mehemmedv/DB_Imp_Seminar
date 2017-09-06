//
// Created by mahammad on 8/21/17.
//

#ifndef DB_IMP_SEMINAR_CSRGRAPH_H
#define DB_IMP_SEMINAR_CSRGRAPH_H

#include <vector>
#include "Graph.h"

// 'Compressed sparse row' implementation of Graph
class CSRGraph : public Graph {
    int *edges, *offsets;
    int *delta1, *delta2;
    int cur_idx, v, e;
    int *idx;

public:
    CSRGraph(int v, int e) : v(v), e(e) {
        delta1 = new int[e];
        edges = delta1;
        offsets = new int[v + 2];
        cur_idx = 0;
        idx = new int[v + 2];
    }

    void add_edge(int from, std::vector<int> &to);

    void add_edge(int from, int to, int weight = 0);

    void finished();

    bool next_neighbor(int v, int &to);

    int* begin(int cur_vertex);

    int* end(int cur_vertex);
};


#endif //DB_IMP_SEMINAR_CSRGRAPH_H
