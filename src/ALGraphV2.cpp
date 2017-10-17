//
// Created by mahammad on 9/26/17.
//


#include <iostream>
#include <algorithm>
#include "../include/ALGraphV2.h"

void ALGraphV2::add_edge(int from, std::vector<int>& to, std::vector<int>& w) {
    for(int i : to)
        edges[from].push_back(i);
    for(int i : w)
        weights[from].push_back(i);
}

void ALGraphV2::finished() {
}

void ALGraphV2::add_edge(int from, int to, int weight) {
    edges[from].push_back(to);
    weights[from].push_back(weight);
}

void ALGraphV2::sortByEdgesByNodeId() {
    for(int i = 1; i <= v; ++i)
        std::sort(edges[i].begin(), edges[i].end());
}