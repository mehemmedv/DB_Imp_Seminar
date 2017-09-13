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
        weights[temp_cur_idx++] = i;
    }
}

void CSRGraph::finished() {
    offsets[v+1] = e;
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
    delta_edge_2 = new int[e+1];
    edges = delta_edge_2;
    memcpy(delta_edge_2, delta_edge_1, sizeof(int) * offsets[from + 1]);
    delta_edge_2[offsets[from + 1]] = to;
    memcpy(delta_edge_2 + offsets[from + 1] + 1, delta_edge_1 + offsets[from + 1], sizeof(int) * (e - offsets[from + 1]));

    delete[] delta_edge_1;
    edges = delta_edge_2;
    delta_edge_1 = delta_edge_2;

    delta_w_2 = new int[e+1];
    weights = delta_w_2;
    memcpy(delta_w_2, delta_w_1, sizeof(int) * offsets[from + 1]);
    delta_w_2[offsets[from + 1]] = weight;
    memcpy(delta_w_2 + offsets[from + 1] + 1, delta_w_1 + offsets[from + 1], sizeof(int) * (e - offsets[from + 1]));

    delete[] delta_w_1;
    weights = delta_w_2;
    delta_w_1 = delta_w_2;
    ++e;
    for(int i = from + 1; i <= v + 1; ++i)
        ++offsets[i];
}