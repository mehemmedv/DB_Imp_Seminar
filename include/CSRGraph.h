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
    int cur_idx, v, e;
    int* idx;

public:
    CSRGraph(int v, int e) : v(v), e(e) {
        edges = new int[e];
        offsets = new int[v + 2];
        cur_idx = 0;
        idx = new int[v + 2];
    }

    void add_edge(int v, std::vector<int>& to);

    void finished();

    bool next_neighbor(int v, int& to);
};


#endif //DB_IMP_SEMINAR_CSRGRAPH_H
