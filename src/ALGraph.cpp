//
// Created by mahammad on 8/21/17.
//

#include <iostream>
#include "../include/ALGraph.h"

void ALGraph::add_edge(int from, std::vector<uint32_t>& to, std::vector<uint32_t>& w) {
    for(uint32_t i : to)
        edges[from].push_back(i);
    for(uint32_t i : w)
        weights[from].push_back(i);
}

void ALGraph::finished() {
}

void ALGraph::add_edge(int from, uint32_t to, uint32_t weight) {
    edges[from].push_back(to);
    weights[from].push_back(weight);
}

void ALGraph::sortByEdgesByNodeId() {
    for(int i = 1; i <= v; ++i)
        edges[i].sort();
}