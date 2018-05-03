//
// Created by mahammad on 8/21/17.
//

#include "../include/CSRGraph.h"
#include <string.h>
#include <iostream>
#include <algorithm>
#include <stdint-gcc.h>

void CSRGraph::add_edge(int from, std::vector<int>& to, std::vector<int>& w) {
    offsets[from] = cur_idx;
    uint64_t temp_cur_idx = cur_idx;
    for(int i : to){
        edges[cur_idx++] = i;
    }
    for(int i : w){
        weights[temp_cur_idx++] = i;
    }
}

void CSRGraph::finished() {
    offsets[v+1] = e;
}

void CSRGraph::add_edge(int from, int to, int weight) {
    // adding a new edge
    delta_e = new int[e+1];
    memcpy(delta_e, edges, sizeof(int) * offsets[from + 1]);
    delta_e[offsets[from + 1]] = to;
    memcpy(delta_e + offsets[from + 1] + 1, edges + offsets[from + 1], sizeof(int) * (e - offsets[from + 1]));
    delete[] edges;
    edges = delta_e;

    // adding weight for the new edge
    delta_w = new int[e+1];
    memcpy(delta_w, weights, sizeof(int) * offsets[from + 1]);
    delta_w[offsets[from + 1]] = weight;
    memcpy(delta_w + offsets[from + 1] + 1, weights + offsets[from + 1], sizeof(int) * (e - offsets[from + 1]));
    delete[] weights;
    weights = delta_w;

    ++e;
    for(int i = from + 1; i <= v + 1; ++i) // offset for the vertices (from + 1 .. v + 1) is one index shifted
        ++offsets[i];

}

void CSRGraph::sortByEdgesByNodeId() {
    for(int i = 1; i <= v; ++i){
        std::sort(edges + offsets[i], edges + offsets[i + 1]);
    }
}