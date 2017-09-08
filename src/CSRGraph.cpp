//
// Created by mahammad on 8/21/17.
//

#include "../include/CSRGraph.h"
#include <string.h>
#include <iostream>

void CSRGraph::add_edge(int from, std::vector<int>& to, std::vector<int>& w) {
    offsets[from] = cur_idx;
    int temp_cur_idx = cur_idx;
    //for(int i : to)
    for(int i : to){
        edges[cur_idx++] = i;
    }
    for(int i : w){
        weights[temp_cur_idx++] = w[i];
    }
}

void CSRGraph::finished() {
    offsets[v+1] = e;
    for(int i = 1; i <= v; ++i)
        idx[i] = offsets[i];
}

bool CSRGraph::next_neighbor(int v, int &to) {
    if(idx[v] < offsets[v + 1]){
        to = edges[idx[v]++];
        return true;
    }
    return false;
}

int* CSRGraph::begin(int cur_vertex){
    return &(edges[offsets[cur_vertex]]);
}

int* CSRGraph::end(int cur_vertex){
    return &(edges[offsets[cur_vertex + 1]]);
}

int* CSRGraph::begin_weights(int cur_vertex){
    return &(weights[offsets[cur_vertex]]);
}

void CSRGraph::add_edge(int from, int to, int weight) {
    delta2 = new int[e+1];

    memcpy(&delta2, &delta1, sizeof(int) * offsets[from + 1]);
    delta2[offsets[from + 1]] = to;
    memcpy(&delta2[offsets[from + 1] + 1], &delta1[offsets[from + 1]], sizeof(int) * (e - offsets[from + 1]));

    for(int i = from + 1; i <= v; ++i)
        ++offsets[i];
    ++e;
    edges = delta2;
    delete[] delta1;
    delta1 = delta2;
}