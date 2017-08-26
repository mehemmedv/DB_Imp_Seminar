//
// Created by mahammad on 8/21/17.
//

#include "../include/CSRGraph.h"

void CSRGraph::add_edge(int from, vector<int>& to) {
    offsets[from] = cur_idx;
    for(int i : to)
        edges[cur_idx++] = i;
}

void CSRGraph::finished() {
    offsets[v+1] = e;
    for(int i = 1; i <= v; ++i)
        idx[i] = offsets[i];
}

void CSRGraph::next_neighbor(int v, int &to) {
    if(idx[v] < offsets[v + 1]){
        to = edges[idx[v]++];
        return true;
    }
    return false;
}
