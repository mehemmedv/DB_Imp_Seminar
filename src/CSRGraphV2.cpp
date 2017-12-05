//
// Created by mahammad on 12/5/17.
//


#include "../include/CSRGraphV2.h"
#include <string.h>
#include <iostream>
#include <algorithm>
#include <stdint-gcc.h>

void CSRGraphV2::add_edge(int from, std::vector<int>& to, std::vector<int>& w) {
    offsets[from] = cur_idx;
    uint64_t temp_cur_idx = cur_idx;
    for(int i : to){
        edges[cur_idx++] = i;
    }
    for(int i : w){
        weights[temp_cur_idx++] = i;
    }
}

void CSRGraphV2::finished() {
    offsets[v+1] = e;
}

void CSRGraphV2::add_edge(int from, int to, int weight) {
    // adding a new edge
    bool isFull = false;
    int *dest_edges = edges, *dest_weights = weights;

    if(e == current_size){
        isFull = true;
        current_size += additional_space;
    }
    if(!isFull) {
        memmove(dest_edges + offsets[from + 1] + 1, edges + offsets[from + 1], sizeof(int) * (e - offsets[from + 1]));
        dest_edges[offsets[from + 1]] = to;
        memmove(dest_weights + offsets[from + 1] + 1, weights + offsets[from + 1], sizeof(int) * (e - offsets[from + 1]));
        dest_weights[offsets[from + 1]] = weight;
    } else {
        dest_edges = new int[current_size];
        memcpy(dest_edges, edges, sizeof(int) * offsets[from + 1]);
        dest_edges[offsets[from + 1]] = to;
        memcpy(dest_edges + offsets[from + 1] + 1, edges + offsets[from + 1], sizeof(int) * (e - offsets[from + 1]));
        delete[] edges;
        edges = dest_edges;
        dest_weights = new int[current_size];
        memcpy(dest_weights, weights, sizeof(int) * offsets[from + 1]);
        dest_weights[offsets[from + 1]] = weight;
        memcpy(dest_weights + offsets[from + 1] + 1, weights + offsets[from + 1], sizeof(int) * (e - offsets[from + 1]));
        delete[] weights;
        weights = dest_weights;
    }

    ++e;
    for(int i = from + 1; i <= v + 1; ++i) // offset for the vertices (from + 1 .. v + 1) is one index shifted
        ++offsets[i];
}

void CSRGraphV2::sortByEdgesByNodeId() {
    for(int i = 1; i <= v; ++i){
        std::sort(edges + offsets[i], edges + offsets[i + 1]);
    }
}