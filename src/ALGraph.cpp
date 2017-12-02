//
// Created by mahammad on 8/21/17.
//

#include <iostream>
#include "../include/ALGraph.h"

void ALGraph::add_edge(int from, std::vector<int>& to, std::vector<int>& w) {
    for(int i : to)
        edges[from].push_back((uint64_t)i);
    for(int i : w)
        weights[from].push_back((uint64_t)i);
}

void ALGraph::finished() {
}

void ALGraph::add_edge(int from, int to, int weight) {
    edges[from].push_back((uint64_t)to);
    weights[from].push_back((uint64_t)weight);
}

void ALGraph::sortByEdgesByNodeId() {
    for(int i = 1; i <= v; ++i)
        edges[i].sort();
}